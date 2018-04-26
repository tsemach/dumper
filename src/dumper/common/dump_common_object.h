
/* 
 * File:   dump_object.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 9:53 PM
 */

#ifndef DUMP_COMMON_OBJECT_H
#define DUMP_COMMON_OBJECT_H

#include <string>

template<class T>
class CDumpCommonObject {
public:
    CDumpCommonObject() {}
    CDumpCommonObject(const std::string &_object_name) {
        m_object_name = _object_name;
    }
    virtual ~CDumpCommonObject() {}            
      
    virtual T *clone() = 0; 
    virtual void setObjectName(const std::string &_object_name) {
        m_object_name = _object_name;
    }
   
    virtual const std::string &getObjectName() const {
        return m_object_name;
    }
   
protected:
    std::string m_object_name;
};

#endif /* DUMP_COMMON_OBJECT_H */

