/* 
 * File:   CDumpAST.h
 * Author: tsemach
 *
 * Created on October 9, 2016, 11:00 PM
 */

#ifndef CDUMP_AST_H
#define CDUMP_AST_H

#include "dump_ast_node.h"

class CDumpAST {
public:    
    CDumpAST();
    virtual ~CDumpAST();
        
private:
    CDumpASTNode  m_root;
};

#endif 

