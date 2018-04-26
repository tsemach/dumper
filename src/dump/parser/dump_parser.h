
#ifndef DUMP_PARSER_H
#define DUMP_PARSER_H

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "dump_ast.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class CDumpParser {
public:
	CDumpParser();
   ~CDumpParser();

	bool init(int _argc, const char *_argv[]);
	bool parse(const std::string &_file, const std::string &_class, CDumpAST &_ast);
	//bool match(const std::string &_class, const std::string &_file, MatchFinder::MatchCallback &_cb);
    bool match(const std::string &_class, const std::string &_file, CDumpAST &_ast);

    class CRecordDumper : public MatchFinder::MatchCallback {
    public:        
        CRecordDumper(CDumpAST &_ast);
        
        virtual void run(const MatchFinder::MatchResult &_result);
		
        CDumpAST &getAST();
        bool isok();
        
    private:    
       CDumpAST &m_ast;
    };
    
private:
	int    m_argc;
	char  *m_argv[];
};

#endif
