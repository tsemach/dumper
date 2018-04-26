
#ifndef DUMP_MATCHER_H
#define DUMP_MATCHER_H

#include "clang/Tooling/CommonOptionsParser.h"

#include "dump_ast.h"

class CDumpMatcher {
public:
	CDumpMatcher();
   ~CDumpMatcher();

	bool init(int _argc, const char *_argv[]);
	bool parse(const std::string &_file, const std::string &_class, CDumpAST &_ast);
	bool match(const std::string &_class, const std::string &_file, MatchFinder::MatchCallback &_cb);

private:
	int    m_argc;
	char  *m_argv[];
};

#endif
