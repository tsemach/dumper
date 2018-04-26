
#include <fstream>
#include <string>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
 
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;

//using namespace clang;

static llvm::cl::OptionCategory ParserCategory("Tooling parser");
static llvm::cl::OptionCategory ToolingSampleCategory("Tsemach Sample");

struct RecordDumper : public MatchFinder::MatchCallback {
  virtual void run(const MatchFinder::MatchResult &Result) {
    auto *d = Result.Nodes.getNodeAs<TypeLoc>("stuff");
    SourceLocation locstart = d->getLocStart();
    llvm::errs() << "*\n";
    llvm::errs() << " start: " << locstart.printToString(*Result.SourceManager) << "\n";
    SourceLocation locend = d->getLocEnd();
    llvm::errs() << " end: " << locend.printToString(*Result.SourceManager) << "\n";
  }
};

class FindNamedClassVisitor
  : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context) {}

  bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
    //llvm::outs() << "FindNamedClassVisitor::VisitCXXRecordDecl() enter to .." << "\n";  
    if (Declaration->getQualifiedNameAsString() == "CTest") {
      (*Declaration).dump();
      FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getLocStart());
      if (FullLocation.isValid())
        llvm::outs() << "Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << "\n";
    }            
    return true;
  }
  
  bool VisitPragmaCommentDecl (PragmaCommentDecl *_decl) {
    llvm::outs() << "FindNamedClassVisitor::VisitPragmaCommentDecl() enter to .." << "\n";  
    _decl->getCanonicalDecl()->dump();
      (*_decl).dump();
      FullSourceLoc FullLocation = Context->getFullLoc(_decl->getLocStart());
      if (FullLocation.isValid())
        llvm::outs() << "Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << "\n";
                
    return true;      
  }
  
  bool VisitFieldDecl (FieldDecl *_decl) {
      llvm::outs() << "FindNamedClassVisitor::VisitFieldDecl() enter to .." << "\n";  
      //_decl->getCanonicalDecl()->dump();
      (*_decl).dump();
      llvm::outs() << "FindNamedClassVisitor::VisitFieldDecl() goinf to dump type of field:" << "\n";  
      _decl->getType().dump();
      llvm::outs() << "FindNamedClassVisitor::VisitFieldDecl() _decl->getType().getQualifiers().getAsString() = " << _decl->getType().getAsString() << "\n";
      FullSourceLoc FullLocation = Context->getFullLoc(_decl->getLocStart());
      if (FullLocation.isValid())
        llvm::outs() << "Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << "\n";
                
    return true;      

  }

private:
  ASTContext *Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumer(ASTContext *Context)
        : Visitor(Context) {}

    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
        llvm::outs() << "FindNamedClassConsumer::HandleTranslationUnit() enter to .. translation unit = " <<  "\n";      
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }  
  
#if 0  
  // comde from tooling_sample: no need can delete
  // declaration.
  bool HandleTopLevelDecl(DeclGroupRef DR) override {
    for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
      // Traverse the declaration using our AST visitor.
      Visitor.TraverseDecl(*b);
      //(*b)->dump();
    }
    return true;
  }
#endif
  
private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
        llvm::errs() << "** Creating AST consumer for: " << InFile << "\n";        
        
        return std::unique_ptr<clang::ASTConsumer>(new FindNamedClassConsumer(&Compiler.getASTContext()));
    }        
};

int main(int argc, const char **argv) {
    if (argc > 1) {
        /*
        std::ifstream ifs("test.cpp");
      std::string content((std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()));
        llvm::errs() << "content = " << content << "\n";
        
        clang::tooling::runToolOnCode(new FindNamedClassAction, content);
        //clang::tooling::runToolOnCode(new FindNamedClassAction);
        */
        
        
    }
      
  CommonOptionsParser op(argc, argv, ToolingSampleCategory);
  
  for (std::string s : op.getSourcePathList()) {
      llvm::errs() << "main() s = " << s << "\n";      
  }
  
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());    

  // ClangTool::run accepts a FrontendActionFactory, which is then used to
  // create new objects implementing the FrontendAction interface. Here we use
  // the helper newFrontendActionFactory to create a default factory that will
  // return a new MyFrontendAction object every time.
  // To further customize this, we could create our own factory class.
  
  if ( ! Tool.run(newFrontendActionFactory<FindNamedClassAction>().get()) ) {
      llvm::errs() << "main() ERROR failed running Fronted Action" << "\n";
  }
  
  MatchFinder Finder;

  RecordDumper recoredHandler;

  Finder.addMatcher(loc(templateSpecializationType(hasDeclaration(namedDecl(hasName("Frob::Homer"))))).bind("stuff"), &recoredHandler);

  
}

