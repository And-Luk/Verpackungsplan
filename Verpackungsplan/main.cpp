//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.
//  g++ main.cpp -std=c++23 -Wall -o main

#include <iostream>
 
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
using namespace filesystem;


int main(int argc, const char * argv[]) {
    
    
    if (argc!=2) {
        std::cout<< "Usage:"<<argv[0]<<"<path>\n";
        std::printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    const std::filesystem::path dir{argv[1]};
    if (!exists(dir)) {
        std::printf("Path dose not exist.\n");
        return 1;
    }
    std::printf("%s\n",canonical(dir).c_str());
    
    regex pattern;
    try {
        pattern =regex{argv[1]};
    } catch (const regex_error &err) {
        std::printf("Invalid regular expression provided.n");
        return 1;
    }
    vector<pair<size_t, string>> data_vec {matches(argv[0], argv[1]).c_str()};
    for (const auto &[number, content]: data_vec) {
        printf("%s :  - content %s \n",number,content);
    }
    
    
    //std::printf("End of Program\n") ;
    return 0;
}

static vector<pair<size_t, string>> matches (const path & path_to, regex & regex_of_fir, regex regex_of_sec=" "){
    vector<pair<size_t, string>> data_vec;
    ifstream ifstrm{path_to.c_str()};
    string s;
    for (size_t line{1}; getline(ifstrm, s); ++line) {
        if (regex_search(begin(s), end(s),regex_of_fir)) {
            data_vec.emplace_back(line,std::move(s));
        }
    }
    return data_vec;
}
	
