//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.
//  g++ main.cpp -std=c++23 -Wall -o main
//  ./main /Users/and/Downloads/Makefile.txt DEBUG
//  rm ./main; clear; g++ main.cpp -std=c++23 -Wall -o main; ls -alSF
//  clear ; ~/workspace/Verpackungsplan/Verpackungsplan/main /Users/and/Downloads/return/test.txt "(\\w{7,})"
//  clear ; ~/workspace/Verpackungsplan/Verpackungsplan/main /Users/and/Downloads/return/test.txt "\d{6}[9]"

#include <iostream>
 
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>


using namespace std;
using namespace filesystem;

static vector<pair<size_t, string>> matches (const path &, const char*, const char* ); //const regex &, const regex &

int main(int argc, const char * argv[]) {
    
    
    if (argc<=2) {
        std::cout<< "Usage:"<<argv[0]<<"<path>\n";
        std::printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    const std::filesystem::path dir{argv[1]};
    if (!exists(dir)) {
        std::printf("Path dose not exist.\n\n");
        return 1;
    }
    std::printf("\n %s The Path exist\n\n",canonical(dir).c_str());
    std::printf(" [0] %s\n [1] %s\n [2] %s\n\n",argv[0],argv[1],argv[2]);
//    regex pattern;
//    try {
//        pattern =regex{argv[1]};
//    } catch (const regex_error &err) {
//        std::printf("Invalid regular expression provided.n");
//        return 1;
//    }
    
    vector<pair<size_t, string>> data ( matches(argv[1], argv[2], argv[2]));
    for (const auto &[number, content]: data) {
        printf(" [%5i]  -->  %s\n", (int)number, content.c_str());
    }
    
    
    std::printf("\n OK!\n") ;
    return 0;
}

static vector<pair<size_t, string>> matches (const path & path_to, const char*  reg_of_fir = "", const char* reg_of_sec = ""){
    vector<pair<size_t, string>> data_vec;
    ifstream ifstrm{path_to.c_str()};  // "/Users/and/Downloads/Makefile.txt"
    string s;
    for (size_t line{1}; getline(ifstrm, s); ++line) {
        //printf("%s", s.c_str());

        if (regex_search(begin(s), end(s),regex{reg_of_fir,std::regex_constants::ECMAScript | std::regex_constants::icase})) {
            data_vec.emplace_back(line,std::move(s));
        }
    }
    return data_vec;
}
	
