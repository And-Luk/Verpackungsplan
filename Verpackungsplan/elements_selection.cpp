//
//  elements_selection.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 19-04-2025.
//

#include "elements_selection.h"


elements_selection::elements_selection(vector_of_pair_size_t verpak, new_multimap_data data){
    for (auto & ID_OP : verpak) {
        for (auto it =  data.lower_bound(ID_OP.first) ; it != data.upper_bound(ID_OP.first); ++it) {
            temp_element = (it)->second;
            get<1>(temp_element) =(int) ( ID_OP.second * get<1>((it)->second));
            internal_data.insert({ID_OP.first , temp_element});
        }
    }
}

elements_selection::~elements_selection(){}

elements_selection::elements_selection():internal_data{}{}



void elements_selection::read_write_RTF(const path & path_in, const path & path_out){
    
    ifstream in_RTF{path_in.c_str()};
    smatch result;
    string str_in,  title ,  article_next;
    size_t article = 0, article_old = 0,   material = 0,  count =0, repeat_article = 0;  //repeat_article = 0,
    float amount = 0 ;
    for (auto & ID_OP : internal_data) {
                
        temp_element = ID_OP.second;
        
        article =          ID_OP.first;
        article_next =  to_string(article);
        material =       get<0>(temp_element);
        amount =        get<1>(temp_element);
        title =              get<2>(temp_element);
        
        if ( repeat_article == 0  &&  count ==0 ) {
            article_old = article;
        }
                
        if (count ==1 &&  article == article_old) {
            repeat_article = 1;
            article_next ="";
        }
                
        for (;getline(in_RTF, str_in);) {
            
            if ( article != article_old && count == 1 ) {
                
                if (find_the_desired_string(str_in,"n/a#")) {
                    ostring_out<< find_and_replace(str_in, "n/a#", "" ) <<std::endl;
                    continue;
                }
                if (find_the_desired_string(str_in,"n/b#")) {
                    ostring_out<< find_and_replace(str_in, "n/b#", "" ) <<std::endl;
                    continue;
                }
                if (find_the_desired_string(str_in,"n/c#")) {
                    ostring_out<< find_and_replace(str_in, "n/c#", "" ) <<std::endl;
                    continue;
                }
                if (find_the_desired_string(str_in,"n/d#")) {
                    ostring_out<< find_and_replace(str_in, "n/d#", "" ) <<std::endl;
                    //count = 0;
                    repeat_article = 0;
                    count = 0;
                    article_old = article;
                    continue;
                }
            }
            
            if (find_the_desired_string(str_in,"n/a#")) {
                ostring_out<< find_and_replace(str_in, "n/a#",  article_next.c_str() )<<std::endl;
                continue;
            }
            if (find_the_desired_string(str_in,"n/b#")) {
                ostring_out<< find_and_replace(str_in, "n/b#", to_string(material).c_str())<<std::endl;
                continue;
            }
            if (find_the_desired_string(str_in,"n/c#")) {
                ostring_out<< find_and_replace(str_in, "n/c#", title.c_str())<<std::endl;
                continue;
            }
            if (find_the_desired_string(str_in,"n/d#")) {
                ostring_out<< find_and_replace(str_in, "n/d#", to_string((int)amount).c_str())<<std::endl;
                repeat_article = 1;
                count = 1;
                break;
            }

            ostring_out<<str_in<<std::endl;
        }
        
    }
   
    //END OF THE FILE
    for (;getline(in_RTF, str_in);) {
        
        if (find_the_desired_string(str_in,"\\\\cf0 \\\\cell \\\\row") ) {
            ostring_out<<find_and_replace(str_in, "\\\\cf0 \\\\cell \\\\row", "}%")<<std::endl;
            break;
        }
        ostring_out<<str_in<<std::endl;
    }
    
    write_RTF(path_out, ostring_out);
}
