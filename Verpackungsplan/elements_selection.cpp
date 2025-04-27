//
//  elements_selection.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 19-04-2025.
//

#include "elements_selection.h"




elements_selection::elements_selection(vector_of_pair_size_t verpak, multimap_data data){
    for (auto & ID_OP : verpak) {
        for (auto it =  data.lower_bound(ID_OP.first) ; it != data.upper_bound(ID_OP.first); ++it) {
            temp_element = (it)->second;
            get<1>(temp_element) =(int) ( ID_OP.second * get<1>((it)->second));
            internal_data.insert(internal_data.end(),{ID_OP.first , temp_element});
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
           //string str_test ;
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
                 std::cout<< find_and_replace(str_in, "n/c#", title.c_str())<<std::endl;
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


void elements_selection::new_read_write_RTF( const path & path_in, const path & path_out){
    
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

        if ( article != article_old && count == 1 ) {
                std::pair<const char*, const char*>array_cleaning [4] {
                    make_pair("n\\/a#", ""),
                    make_pair("n\\/b#", ""),
                    make_pair("n\\/c#", ""),
                    make_pair("n\\/d#", "")
                };
            
            getline(in_RTF, str_in);
            for (size_t it=0; it<4; it++) {
                while (  ! find_and_change(str_in, array_cleaning[it].first, array_cleaning[it].second) ){
                    ostring_out<<str_in<<std::endl;
                    getline(in_RTF, str_in);
                }
            }
            
            ostring_out<<str_in<<std::endl;
            repeat_article = 0;
            count = 0;
            article_old = article;
            }

        if (true) {
            std::pair<const char*, const char*>array_replacement [4] {
                make_pair("n\\/a#",article_next.c_str()),
                make_pair("n\\/b#",to_string(material).c_str()),
                make_pair("n\\/c#",title.c_str()),
                make_pair("n\\/d#",to_string((int)amount).c_str())
            };

            getline(in_RTF, str_in);
            for (size_t it=0; it<4; it++) {
                while (  ! find_and_change(str_in, array_replacement[it].first, array_replacement[it].second) ){
                    ostring_out<<str_in<<std::endl;
                    getline(in_RTF, str_in);
                }
            }
            repeat_article = 1;
            count = 1;
            ostring_out<<str_in<<std::endl;
        }
        
        
    }
    //END OF THE FILE
    for (;getline(in_RTF, str_in);) {
        
        //\\\\pard\\intbl\\\\itap1\\\\pardeftab720\\\\
        //
        
        if (find_the_desired_string(str_in,"intbl") ) {
             ostring_out<<std::endl<<"}}"<<std::endl;
            break;
        }
        ostring_out<<str_in<<std::endl;
    }
    
    write_RTF(path_out, ostring_out);
}


