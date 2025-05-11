//
//  elements_selection.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 19-04-2025.
//

#include "elements_selection.h"



elements_selection::elements_selection(vector_of_pair_size_t verpak, multimap_data data){
    for (auto & ID_OP : verpak) {
        if (data.count(ID_OP.first)==0) {
            temp_element = make_tuple(size_t{0}, float{0.0}, string{"   ------- ? ? ? -------  "});
            //In der data.txt ist kein solches Element vorhanden.
            internal_data.insert(internal_data.end(), { ID_OP.first , temp_element  } );
            continue;
        }
        
        for (auto it =  data.lower_bound(ID_OP.first) ; it != data.upper_bound(ID_OP.first); ++it) {
            temp_element = (it)->second;
            get<1>(temp_element) =(int) ( ID_OP.second * get<1>((it)->second));
            internal_data.insert(internal_data.end(),{ID_OP.first , temp_element});
        }
    }
}

elements_selection::~elements_selection(){}

elements_selection::elements_selection():internal_data{}{}

void elements_selection::read_write_RTF( const path & path_in, const path & path_out){
    
    ifstream in_RTF{path_in.c_str()};
    smatch result;
    string str_in,  title , amount_str, article_next;
    size_t article = 0, article_old = 0,   material = 0,  count =0, repeat_article = 0;
    float amount = 0 ;
    
    
    for (auto & ID_OP : internal_data) {
        
        temp_element = ID_OP.second;
        article =          ID_OP.first;
        article_next =  to_string(article);
        material = get<0>(temp_element);
        amount =  get<1>(temp_element);
        if (amount ==0 && material != 0) {
            amount_str="    1 Rolle";
        }else amount_str = to_string((int)amount).c_str();
        
        title =  get<2>(temp_element);
        
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

        {
            std::pair<const char*, const char*>array_replacement [4] {
                make_pair("n\\/a#", article_next.c_str()),
                make_pair("n\\/b#", to_string(material).c_str()),
                make_pair("n\\/c#", title.c_str()),
                make_pair("n\\/d#", amount_str.c_str())
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
    // ending of the RTF file  End_of
    const string current_path  { std::filesystem::current_path().string()};
   string  in_END_s{current_path.data()};
    in_END_s.append("/End_of.txt");
    
    ifstream in_END{in_END_s.c_str()};
    
    for (;getline(in_END, str_in);) {

       
             ostring_out<<str_in;

        ostring_out<<str_in<<std::endl;
    }
    write_RTF(path_out, ostring_out);
}


