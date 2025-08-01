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

    std::vector<pair<size_t, std::tuple<size_t, int, string >>> internal_data;
    std::tuple<size_t, float, string > temp_element;
    std::ostringstream ostring_out;
    std::map<size_t, tuple<size_t, size_t, size_t>> set_of_items;
    
    typedef std::map<size_t, pair<size_t, size_t>>::key_type     set_of_items_key_type;
    
    std::map<size_t, tuple<size_t, size_t, size_t>>::iterator iter_set = set_of_items.begin();
    std::vector<pair<size_t, std::tuple<size_t, string, string>>> internal_data_2;
    
    
public:
    elements_selection();
    elements_selection(vector_of_pair_size_t verpak_txt, multimap_data data_txt);
    ~elements_selection();
    void read_write_RTF(const path & path_in, const path & path_out, const path & path_End_of_RTF);
    void how_much_items ();
};
