/* 
 * File:   CDumpASTNode.h
 * Author: tsemach
 *
 * Created on October 9, 2016, 10:52 PM
 */

#ifndef CDUMPASTNODE_H
#define CDUMPASTNODE_H

#include <string>
#include <list>
#include <map>

class CDumpASTNode {
public:
    CDumpASTNode();
    virtual ~CDumpASTNode();
    
    typedef std::list<CDumpASTNode *> node_list_t;

    CDumpASTNode &operator=(const CDumpASTNode &_rhs);
    
    void setTypeName(const std::string &);
    void setVarxName(const std::string &);
    
    const std::string &getTypeName() const;
    const std::string &getVarxName() const;
    
private:
    std::string     m_type_name;
    std::string     m_varx_name;
    
    CDumpASTNode *m_parent;
    node_list_t     m_members;
};

#endif 


