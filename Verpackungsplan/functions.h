//
//  functions.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#pragma once
#include "header.h"

typedef pair<const size_t, string> subI_subS;
typedef deque<pair<size_t, size_t>> deque_of_pair_size_t;
typedef vector<pair<size_t, size_t>> vector_of_pair_size_t;
typedef std::tuple<size_t, float, string > tup_element ;

typedef multimap<size_t, subI_subS, std::less<size_t>, std::allocator<std::pair<const size_t, subI_subS>>> multimap_data;
typedef multimap<size_t, tup_element, std::less<size_t>, std::allocator<std::pair<const size_t, tup_element>>> new_multimap_data;





bool read_write_RTF (const path &, const path &);
void write_RTF(const path &, const ostringstream &);
auto find_and_replace (const string &, const char*, const char*)-> string;
auto find_the_desired_string (const string & , const char*)-> bool;

auto new_read_verpack_txt(const path &, const char*, const char* )-> vector_of_pair_size_t;
auto substring_verpack_txt(const string & , const char*)-> deque<size_t>;


auto new2_read_data_txt(const path & , const char* reg_expr_1  , const char* reg_expr_2, const char* reg_expr_3)-> new_multimap_data;
auto new2_substring (const string & source, const char* reg_expr_1  , const char* reg_expr_2  )-> tup_element;



//auto matches (const path &, const char*)-> vector<tuple<string, string, string>>;
//auto substring (const string & , const char*)-> pair<string, string>;
//auto read_verpack_txt(const path &, const char*)-> deque_of_pair_size_t;
//auto read_data_txt(const path & , const char*)-> multimap_data;
//auto new_read_data_txt(const path & , const char*)-> new_multimap_data;
//auto new_substring (const string & , const char*)-> tup_element;
