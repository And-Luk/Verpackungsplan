//
//  functions.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#include "functions.h"

vector<tuple<string,string,string>> matches (const path & path_to, const char* reg_expr = ""){
    vector<tuple<string,string, string>> data_vec;
    ifstream ifstrm{path_to.c_str()};
    string str_all,str_temp, str_old;
    size_t ident{0};
    smatch result;
    pair<string, string> pair_temp;
    
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_all,result,reg)) {   //regex_search(begin(s), end(s),reg)
            str_temp = result.str();
            str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            
            if (str_temp[0]=='9' ) { //&& ident ==0
                ident = 1;
                str_old=str_temp;
                pair_temp = substring(result.suffix(), "(5|9)\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*");
                data_vec.emplace_back(str_temp,pair_temp.first, pair_temp.second);
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
    
pair<string, string> substring (const string & source, const char* reg_expr= "" ){
    smatch result;
    string str_temp;
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    if (regex_search(source,result,reg)) {
        str_temp = result.str();
        str_temp.erase(6, str_temp.length());  // shrink to 6 digits
    }
    return pair<string, string>(str_temp,result.suffix());
}

bool read_write_RTF (const path & path_of, const path & path_to){
    ifstream in_RTF{path_of.c_str()};
    ostringstream ostring_out;
    smatch result;
    string str_in;
    size_t count= 0;
    for (;getline(in_RTF, str_in);) {
        regex reg_end{"\\\\cf0 \\\\cell \\\\row",std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_in,result,reg_end) && count==32) {  //count to 32 string in in the blat
            ostring_out<<str_in<<std::endl<<"}%"<<endl;
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
    
    write_RTF(path_to, ostring_out);
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
        }
    }
    return data_vec;
}

void write_RTF(const path & path_to, const ostringstream & ostring_out ){
    ofstream out_RTF{path_to.c_str()};
    if (!exists(path_to)) {
        std::printf("An Error with path to Verpackungsplan.rtf .\n\n");
        throw std::exception().what();
    }
    out_RTF<<ostring_out.str();
    out_RTF.close();
}

auto read_data_txt(const path & path_to, const char*reg_expr = "")-> multimap_data{
    ifstream ifstrm{path_to.c_str()};
    string str_all,str_temp, str_old;
    size_t repeat{0};
    smatch result;
    pair<string, string> pair_temp;
    multimap_data data;
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
        
        if (regex_search(str_all,result,reg)) {
            
            str_temp = result.str();
            str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            
            if (str_temp[0]=='9' ) {
                str_old = str_temp;
                repeat = 1;
                pair_temp = substring(result.suffix(), "5\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*");
                
                //data.insert({(size_t)stoi(str_temp), {(size_t)stoi(pair_temp.first), pair_temp.second}});
                //data.emplace((size_t)stoi(str_temp), make_pair((size_t)stoi(pair_temp.first), pair_temp.second) );
                data.insert({(size_t)stoi(str_old), {(size_t)stoi(pair_temp.first), pair_temp.second}});
              
                continue;
            }
            
            if (repeat==1) {
                data.insert({(size_t)stoi(str_old), {(size_t)stoi(str_temp), result.suffix()}});
                //data.emplace((size_t)stoi(str_old), make_pair((size_t)stoi(str_temp), result.suffix()) );
                continue;
            }
            
//            data.insert({(size_t)stoi(str_old), {(size_t)stoi(str_temp), result.suffix()}});
//            //data.emplace((size_t)stoi(str_old), make_pair((size_t)stoi(str_temp), result.suffix()) );
//            repeat = 0;
        }
    }
    return data;
    
}
