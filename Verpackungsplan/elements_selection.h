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

    vector<pair<size_t, std::tuple<size_t, int, string >>> internal_data;
    std::tuple<size_t, float, string > temp_element;
    ostringstream ostring_out;
    
public:
    elements_selection();
    elements_selection(vector_of_pair_size_t verpak_txt, multimap_data data_txt);
    ~elements_selection();
    void read_write_RTF(const path & path_in, const path & path_out);
};
