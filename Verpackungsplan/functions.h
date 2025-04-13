//
//  functions.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#pragma once
#include "header.h"


vector<tuple<string, string, string>> matches (const path &, const char*);

pair<string, string> substring (const string & , const char*);

bool read_write_RTF (const path &, const path &);

deque<size_t> read_verpack_txt(const path &, const char*);

void write_RTF(const path &, const ostringstream &);

typedef pair<const size_t, string> subI_subS;
typedef multimap<size_t, subI_subS, std::less<size_t>, std::allocator<std::pair<const size_t, subI_subS>>> multimap_data;
//typedef multimap<size_t, subI_subS> multimap_data;
auto read_data_txt(const path & , const char*)-> multimap_data;

