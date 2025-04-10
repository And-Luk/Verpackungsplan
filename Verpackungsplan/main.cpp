//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.
//  g++ main.cpp -std=c++23 -Wall -o main
//  ./main /Users/and/Downloads/Makefile.txt DEBUG
//  rm ./main; clear; g++ main.cpp -std=c++23 -Wall -o main; ls -alSF
//  clear; ~/workspace/Verpackungsplan/Verpackungsplan/main ~/Downloads/return/test.txt "\\d{6}[^(\\d|:alpha:)]"
//  clear; ~/workspace/Verpackungsplan/Verpackungsplan/main ~/Downloads/Verpackungsplan/data_test_1.txt "[\\d(9|5)]\\d{5}"
//  clear; ~/workspace/Verpackungsplan/Verpackungsplan/main ~/Downloads/Verpackungsplan/data_test_1.txt "[\\d(9|5)]\\d{5}"
//  rm ./main; clear; g++ ./main.cpp -std=c++23 -Wall -o ./main;
//rm ~/workspace/Verpackungsplan/Verpackungsplan/main; clear; g++ ~/workspace/Verpackungsplan/Verpackungsplan/main.cpp -std=c++23 -Wall -o ~/workspace/Verpackungsplan/Verpackungsplan/main


#include <iostream>
 
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
//#include <algorithm>
#include <sstream>
#include <deque>



using namespace std;
using namespace filesystem;

static vector<tuple<string, string, string>> matches (const path &, const char*);
pair<string, string> substring (const string & source, const string & pattern);
bool read_write_RTF (const path &, const path &);
deque<size_t> read_verpack_txt(const path &, const char*);


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

    try {
        auto data (matches(argv[1], argv[2]));
        for (const auto &[ID_Operation,result,content]: data) {
            printf(" [%s]  [%s] -->  %s\n",ID_Operation.c_str(), result.c_str(), content.c_str());
        }
    } catch (const regex_error &err) {
        std::printf("Invalid regular expression provided.\n");
        return 1;
    }
    try {
        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/RTF_in.rtf"};
        if (!exists(dir)) {
            std::printf("Can'n open the RTF file.\n\n");
            return 1;
        }
        
        read_write_RTF ("/Users/and/Downloads/Verpackungsplan/RTF_in.rtf", "/Users/and/Downloads/Verpackungsplan/RTF_out.rtf");
    } catch (std::exception ex){
        std::printf(" ERROR of writing the out file \n");
    }
    
    try {
        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/verpack.txt"};
        if (!exists(dir)) {
            std::printf("Can'n open the verpak.txt file.\n\n");
            return 1;
        }
        auto list_of_ID = read_verpack_txt("/Users/and/Downloads/Verpackungsplan/verpack.txt","\\d{6}[^(\\d|:alpha:)]");
        
        for (auto & artikel: list_of_ID) {
            std::printf("   %i\n", (int)artikel);
        }
        
    } catch (std::exception ex) {
        std::printf(" ERROR of reading the Verpackungsplan.txt file \n");
    }
    
    std::printf("\n OK!\n") ;
    return 0;
}

//________________________________________________________________________________________________________

static vector<tuple<string,string,string>> matches (const path & path_to, const char* reg_expr = ""){
    vector<tuple<string,string, string>> data_vec;
    ifstream ifstrm{path_to.c_str()};
    string str_all,str_temp, str_old{};
    size_t ident=0;
    smatch result;
    pair<string, string> pair_temp;
    
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_all,result,reg)) {   //regex_search(begin(s), end(s),reg)
            str_temp = result.str();
            str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            
            if (str_temp[0]=='9' ) { //&& ident ==0
                ident = 1;
                pair_temp = substring(result.suffix(), string{"(5|9)\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*"});
                data_vec.emplace_back(str_temp,pair_temp.first, pair_temp.second);
                str_old=str_temp;
                continue;
            }
            if (ident==1) {
                data_vec.emplace_back(str_old, str_temp, result.suffix());
                continue;
            }
            data_vec.emplace_back(str_old, str_temp, result.suffix());
            ident = 0;
        }
    }
    return data_vec;
}
	
pair<string, string> substring (const string & source, const string & pattern){
    smatch result;
    string str_temp;
    regex reg{pattern,std::regex_constants::ECMAScript | std::regex_constants::icase};
    if (regex_search(source,result,reg)) {
        str_temp = result.str();
        str_temp.erase(6, str_temp.length());  // shrink to 6 digits
    }
    return pair<string, string>(str_temp,result.suffix());
}


bool read_write_RTF (const path & path_of, const path & path_to){
    ifstream in_RTF{path_of.c_str()};
    ofstream out_RTF{path_to.c_str()};
    ostringstream ostring_out;
    smatch result;
    string str_in;
    size_t count= 0;
    for (;getline(in_RTF, str_in);) {
        regex reg_end{"\\\\cf0 \\\\cell \\\\row",std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_in,result,reg_end) && count==32) {  //count to 32 string in in the blat
            ostring_out<<str_in<<std::endl<<"}%"<<endl;
            out_RTF<<ostring_out.str();
            out_RTF.close();
            return true;
        }
        regex reg{"n/u#",std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_in,result,reg)) {
            ostring_out<<regex_replace(str_in, reg, "a new replaced string")<<std::endl;
            count++;
            continue;
        }
        ostring_out<<str_in<<std::endl;
    }
    out_RTF<<ostring_out.str();
    out_RTF.close();
    return true;
}


deque<size_t> read_verpack_txt(const path & path_to, const char* reg_expr = ""){
    ifstream ifstrm{path_to.c_str()};
    
    string str_in,str_temp;
    smatch result;
    if (!exists(path_to)) {
        std::printf("Path to Verpackungsplan.txt dose not exist.\n\n");
        throw std::exception().what();
    }

    deque<size_t> data_vec;
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    for (;getline(ifstrm, str_in);) {

        if (regex_search(str_in,result,reg)) {

            str_temp = result.str();
            str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            data_vec.emplace_back( std::stoi(str_temp));
            //data_vec.emplace_back(stoi(str_temp));
        }
    }
    return data_vec;
}
