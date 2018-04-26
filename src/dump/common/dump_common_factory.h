/* 
 * File:   dump_common_factory.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 9:35 PM
 */

#ifndef DUMP_COMMON_FACTORY_H
#define DUMP_COMMON_FACTORY_H

#include <map>
#include <string>

template<typename K, typename T>
class CDumpCommonFacory {
public:    
    //CDumpCommonFacory() {}
    //virtual ~CDumpCommonFacory() {}
    
    typedef std::map<K, T *> factory_map_t;
        
    virtual T *get(const K &_id) {
        typename factory_map_t::iterator it = m_objects.find(_id);
        if (it == m_objects.end()) {
            return NULL;
        }
        
        return (it->second)->clone();
    }
    
    virtual void signeme(const K &_id, T *_p_object) {
        if ( ! _p_object ) {
            return;
        }
        m_objects.insert(typename factory_map_t::value_type(_id, _p_object));
    }
    
protected:
    factory_map_t   m_objects;
};

#endif /* DUMP_COMMON_FACTORY_H */

