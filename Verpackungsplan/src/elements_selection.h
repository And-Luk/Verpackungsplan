//
//  elements_selection.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 19-04-2025.
//

#pragma once
//#include "header.h"
#include "functions.h"


class elements_selection {

    std::vector<pair<size_t, std::tuple<size_t, int, string >>> internal_data;
    std::vector<pair<size_t, std::tuple<size_t, string, string>>> internal_data_2;
    std::map<size_t, tuple<size_t, size_t, size_t>> set_of_items;
    
    std::tuple<size_t, float, string > temp_element;
    std::tuple<size_t, string, string > temp_element_2;
    
    std::ostringstream ostring_out;
    
    
    typedef std::map<size_t, pair<size_t, size_t>>::key_type     set_of_items_key_type;
    
    std::map<size_t, tuple<size_t, size_t, size_t>>::iterator iter_set = set_of_items.begin();
    
    
    
public:
    elements_selection();
    elements_selection(vector_of_pair_size_t verpak_txt, multimap_data* data_txt);
    
    ~elements_selection();
    
    void how_much_items ();     //      ==>     internal_data_2.push_back(element);
    void read_write_RTF(const path & path_in, const path & path_out, const path & path_End_of_RTF);
    
};
