//
//  functions.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#pragma once
#include "header.h"
#include "statistics.h"

#include <sys/stat.h> // file info HASH
#include <cstdlib> // "system" & file info HASH


typedef pair<const size_t, string> subI_subS;
typedef deque<pair<size_t, size_t>> deque_of_pair_size_t;
typedef vector<pair<size_t, size_t>> vector_of_pair_size_t;
typedef std::tuple<size_t, float, string > tup_element ;
typedef multimap<size_t, tup_element, std::less<size_t>, std::allocator<std::pair<const size_t, tup_element>>> multimap_data;

//void* operator new (const size_t size);
//void operator delete(void *ptr, const size_t size) noexcept;

void write_RTF(const path &, const ostringstream &);

auto find_and_replace (const string &, const char*, const  string)-> string;
bool find_and_change(string &str_in , const char* pattern, const char* replacement);
auto find_the_desired_string (const string & , const char*)-> bool;

auto read_verpack_txt(const path &, const char*  reg_expr_1, const char*   reg_expr_2, const char* reg_expr_3)-> vector_of_pair_size_t;
auto substring_verpack_txt(const string & , const char*)-> deque<size_t>;

auto read_data_txt(const path & path_to_file, const char* reg_expr_1  , const char* reg_expr_2, const char* reg_expr_3)-> multimap_data*;


auto read_data_New_txt(const path & path_to_file, const char* reg_expr_1  , const char* reg_expr_2, const char* reg_expr_3 = "NOT USED", const char* reg_expr_4= "NOT USED")-> multimap_data*;


auto substring (const string & source, const char* reg_expr_1  , const char* reg_expr_2  )-> tup_element;

void umlauts (vector<pair<size_t, std::tuple<size_t, int, string >>> & internal_data );

char* getFileHASH(const path &);

char* printTIME();
