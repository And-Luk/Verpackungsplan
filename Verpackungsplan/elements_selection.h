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
    new_multimap_data internal_data; ///vector<pair<size_t, float>>
    tup_element temp_element;
    ostringstream ostring_out;
    
public:
    elements_selection();
    elements_selection(vector_of_pair_size_t, new_multimap_data);
    ~elements_selection();
    void read_write_RTF(const path & in, const path & out);
};
