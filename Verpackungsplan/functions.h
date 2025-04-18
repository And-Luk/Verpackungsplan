//
//  functions.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#pragma once
#include "header.h"


auto matches (const path &, const char*)-> vector<tuple<string, string, string>>;

auto substring (const string & , const char*)-> pair<string, string>;

bool read_write_RTF (const path &, const path &);
auto find_and_replace (const string &, const char*, const char*)-> string;
auto find_the_desired_string (const string & , const char*)-> bool;



auto read_verpack_txt(const path &, const char*)-> deque<pair<size_t, size_t>>;
auto substring_verpack_txt(const string & , const char*)-> deque<size_t>;

void write_RTF(const path &, const ostringstream &);

typedef pair<const size_t, string> subI_subS;
typedef multimap<size_t, subI_subS, std::less<size_t>, std::allocator<std::pair<const size_t, subI_subS>>> multimap_data;
auto read_data_txt(const path & , const char*)-> multimap_data;

typedef std::tuple<size_t, size_t, string > tup_element ; //(size_t ID, size_t article ,size_t amount, string name);
typedef multimap<size_t, tup_element, std::less<size_t>, std::allocator<std::pair<const size_t, tup_element>>> new_multimap_data;
auto new_read_data_txt(const path & , const char*)-> new_multimap_data;
auto new_substring (const string & , const char*)-> tup_element;
