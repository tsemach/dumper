/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "dump_ast_node.h"

CDumpASTNode::CDumpASTNode()
{
}

CDumpASTNode::~CDumpASTNode()
{
}

CDumpASTNode &
CDumpASTNode::operator=(const CDumpASTNode &_rhs)
{
    if (this == &_rhs) {
        return *this;
    }
    m_type_name = _rhs.m_type_name;
    m_varx_name = _rhs.m_varx_name;
    
    return *this;
}

void
CDumpASTNode::setTypeName(const std::string &_type_name)
{
    m_type_name = _type_name;
}

void 
CDumpASTNode::setVarxName(const std::string &_varx_name)   
{
    m_varx_name = _varx_name;
}
 
const std::string &
CDumpASTNode::getTypeName() const
{
    return m_type_name;
}

const std::string &
CDumpASTNode::getVarxName() const
{
    return m_varx_name;
}
    


