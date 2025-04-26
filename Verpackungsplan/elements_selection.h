//
//  elements_selection.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 19-04-2025.
//

#pragma once
#include "header.h"
#include "functions.h"


class elements_selection {
    //new_multimap_data internal_data; ///vector<pair<size_t, float>>
    
   // typedef multimap<size_t, tup_element, std::less<size_t>, std::allocator<std::pair<const size_t, tup_element>>> ;
    
    multimap<size_t, std::tuple<size_t, int, string >, std::less<size_t>, std::allocator<std::pair<const size_t, std::tuple<size_t, int, string >>>> internal_data;
    
   // tup_element temp_element;
    std::tuple<size_t, float, string > temp_element;
    
    ostringstream ostring_out;
    
public:
    elements_selection();
    elements_selection(vector_of_pair_size_t, new_multimap_data);
    ~elements_selection();
    void read_write_RTF(const path & in, const path & out);
};
