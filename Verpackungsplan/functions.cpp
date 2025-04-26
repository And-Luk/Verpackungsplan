//
//  functions.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#include "functions.h"





void write_RTF(const path & path_to, const ostringstream & ostring_out ){
    ofstream out_RTF{path_to.c_str()};
    if (!exists(path_to)) {
        std::printf("An Error with path to Verpackungsplan.rtf .\n\n");
        throw std::exception().what();
    }
    out_RTF<<ostring_out.str();
    out_RTF.close();
}

auto find_the_desired_string (const string & str_in, const char* reg_expr = "")-> bool{
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    if (regex_search(str_in,reg)) {
        return true;
    }
    return false;
}

auto find_and_replace (const string & str_in, const char* reg_expr= "", const char* replacement= "")-> string{
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    return regex_replace(str_in, reg, replacement);
}



auto read_verpack_txt(const path & path_to, const char* reg_expr_1 = "" , const char* reg_expr_2 = "")-> vector_of_pair_size_t{
    ifstream ifstrm{path_to.c_str()};
    vector_of_pair_size_t data;
    
    string str_in, str_temp, str_suffix;
    smatch result;
    regex reg_1{reg_expr_1,std::regex_constants::ECMAScript | std::regex_constants::icase};
    regex reg_2{reg_expr_2,std::regex_constants::ECMAScript | std::regex_constants::icase};
    pair<size_t, size_t> temp_pair;
    
    for (;getline(ifstrm, str_in);) {

        if (regex_search(str_in, result, reg_1)) {
            str_temp = result.str();
            str_temp = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            temp_pair.first = std::stoi( str_temp);
            temp_pair.second = 1;
            str_suffix =result.suffix();
            if (regex_search(str_suffix, result, reg_2)) {
                
                str_temp =result.suffix();
                
                
                regex reg_3{"[[:digit:]]+",std::regex_constants::ECMAScript | std::regex_constants::icase};
                
                if (regex_search(str_temp, result, reg_3)) {
                    //str_temp.clear();
                    str_temp = result.str();
                    temp_pair.second = (size_t)std::stoi( str_temp);
                    data.emplace_back(temp_pair);
                    continue;
                    }
            }

                temp_pair.second = 1;
                data.emplace_back(temp_pair);
                continue;
        }
            
            
    }

    return data;
}

auto substring_verpack_txt(const string & source, const char* reg_expr= "")-> deque<size_t>{
    
    string str_in,str_temp;
    smatch result;

    deque<size_t> data_vec;
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};

        if (regex_search(str_in,result,reg)) {
            str_temp = result.str();
            str_in = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            str_temp =result.suffix();
            data_vec.emplace_back(std::stoi(str_temp) );
        }

    return data_vec;
    
}





auto read_data_txt(const path & path_to, const char* reg_expr_1 = "", const char* reg_expr_2 = "" , const char* reg_expr_3 = "")-> new_multimap_data{
    ifstream ifstrm{path_to.c_str()};
    string str_all,str_temp, str_old;  //str_old{"0"}
    smatch result;
    //pair<string, string> pair_temp;
    tup_element tuple_temp;

    new_multimap_data data;
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_expr_1, std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_all,result,reg)) {
            str_temp = result.str();
            str_temp = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            get<1>(tuple_temp)= 0.07;
            
            if (str_temp[0]=='9' ) {
                str_old = str_temp;
                
                
                tuple_temp = substring(result.suffix(), reg_expr_2 , reg_expr_3);
               
                data.insert( {(size_t)stoi(str_old), tuple_temp} );
                continue;
            }
            
            if (str_temp[0]=='5' ) {
                
                tuple_temp = substring(str_all, reg_expr_2 , reg_expr_3);
                
                
                get<0>(tuple_temp)= stoi(str_temp);
                //get<1>(tuple_temp)= 0.08;
                //get<2>(tuple_temp)= result.suffix(); //pair_temp.second;
                data.insert({(size_t)stoi(str_old), tuple_temp});
            }
            
            
            
        }
    }
    return data;
}

auto substring (const string & source, const char* reg_expr_1 = "" , const char* reg_expr_2 = "")-> tup_element{
    
    tup_element tuple_temp;
    smatch result;
    string str_temp, str_suffix , str_suffix_2;
    size_t shrink=0;
    float float_temp=0.070;
   
    regex reg_1{reg_expr_1,std::regex_constants::ECMAScript | std::regex_constants::icase};
    regex reg_2{reg_expr_2,std::regex_constants::ECMAScript | std::regex_constants::icase};
    //regex reg_2{"[[:digit:]]+",std::regex_constants::ECMAScript | std::regex_constants::icase};
    

    if (regex_search(source, result, reg_1)) {
        str_temp = result.str();
        
        str_temp.erase(6, str_temp.length());  // shrink to 6 digits
        get<0>(tuple_temp)= stoi(str_temp);
        str_suffix =result.suffix();
        str_suffix_2 = str_suffix;
        
        shrink= str_suffix.find('=');
       str_suffix.erase(shrink, str_suffix.length());
        
        str_suffix_2 = str_suffix_2.substr(shrink); ///exeption
        //str_suffix = source.    str_suffix_2;
        
        get<2>(tuple_temp)= str_suffix;

        
        if (regex_search( str_suffix_2, result, reg_2)) {
            
            str_temp = result.str();
            float_temp = (float)std::stof( str_temp);
            get<1>(tuple_temp)= float_temp;

        }else  get<1>(tuple_temp)=1;
        
        
        return tuple_temp;
    }
    
    //return pair<string, string>(str_temp,result.suffix());
    return tup_element{0, float_temp, "substring does not exist"};  //stoi(result.suffix())
    
}


