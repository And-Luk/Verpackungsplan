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



using namespace std;
using namespace filesystem;

static vector<tuple<string, string, string>> matches (const path &, const char*);
pair<string, string> substring (const string & source, const string & pattern);
bool read_write_RTF (const path &, const path &);

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
        std::printf(" ERROR of writing the out file ");
    }
  
    std::printf("\n OK!\n") ;
    return 0;
}

static vector<tuple<string,string,string>> matches (const path & path_of, const char*  reg_of_fir = ""){
    vector<tuple<string,string, string>> data_vec;
    ifstream ifstrm{path_of.c_str()};
    string str_all,str_temp, str_old{};
    size_t ident=0;
    smatch result;
    pair<string, string> pair_temp;
    
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_of_fir,std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_all,result,reg)) {   //regex_search(begin(s), end(s),reg)
            str_temp = result.str();
            str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            
            if (str_temp[0]=='9' ) { //&& ident ==0
                ident = 1;
                pair_temp = substring(result.suffix(), string{"(9|5)\\d{5}[^(\\d|[:alpha:]\\|)](\"\\|\\\\:|[[:space:]])*(\\:)*([[:space:]])*"});
                data_vec.emplace_back(str_temp,pair_temp.first, pair_temp.second);
                str_old=str_temp;
                continue;
            }
            if (ident==1) {
                
                data_vec.emplace_back(str_old, str_temp, result.suffix());
                //ident = 0;
                continue;
            }
            
            data_vec.emplace_back(str_old, str_temp, result.suffix());
            //str_old=str_temp;
            ident = 0;
        }
    }
    
    
    
    return data_vec;
}
	
pair<string, string> substring (const string & source, const string & pattern){
    smatch result;
    string str_temp;
    
    regex reg{pattern,std::regex_constants::ECMAScript | std::regex_constants::icase};
    if (regex_search(source,result,reg)) {   //regex_search(begin(s), end(s),reg)
        str_temp = result.str();
        str_temp.erase(6, str_temp.length());  // shrink to 6 digits
        
        
    }
    return pair<string, string>(str_temp,result.suffix());
}

//tuple<string,string,string>
bool read_write_RTF (const path & path_of, const path & path_to){
    ifstream in_RTF{path_of.c_str()};
    ofstream out_RTF{path_to.c_str()};
    smatch result;
    string str_in;
    ostringstream ostring_out;
    
    //std::match_results<BidirIt>;
    for (;getline(in_RTF, str_in);) {
        regex reg{"n/u#33",std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_in,result,reg)) {
            
            out_RTF<<regex_replace(str_in, reg, "NEW")<<std::endl;
            //std::cout<<"changed: "<< "\\"<< str_in <<"\\"<<"\n";
            //ostring_out<<str_in<<std::endl;
            //out_RTF<<ostring_out.str()<<std::endl;
            //out_RTF<<str_in;
            continue;
        }
        //ostring_out<<str_in;
        //out_RTF<<ostring_out.str();
        //out_RTF<<ostring_out.str()<<std::endl;
        out_RTF<<str_in<<std::endl;
    }
    
    //out_RTF.write(string_out, string_out.str().size()) ;
    //ofstream out;
    //out_RTF<<ostring_out.str();
    //out_RTF.copyfmt(string_out);
    out_RTF.close();
    //std::cout<<string_out.str();
    return true;
}
