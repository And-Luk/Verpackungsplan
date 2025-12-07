//
//  settings.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 17-09-2025.
//
#include "settings.h"


Settings::Settings(): path_to_settings {"./Settings.json"}{
    std::ifstream in_stream(path_to_settings);
    
    cereal::JSONInputArchive JSON_in (in_stream);
    JSON_in(settings); //read JSON to map

    in_stream.close();
}

Settings::Settings(const char* const path_to_settings_file ): path_to_settings {path_to_settings_file}{
    std::ifstream in_stream(path_to_settings);
    
    cereal::JSONInputArchive JSON_in (in_stream);
    JSON_in(settings); //read JSON to map

    in_stream.close();
}

Settings::~Settings(){};

Settings* Settings::getInstance(const char* const path_to_settings_file){
    static Settings instance(path_to_settings_file);
    return &instance;
}

const char* Settings::getParameter(const char* const key){
    std::map<string, string>::iterator ellement{settings.find(key)};
    char* value = new char[200];
    std::strcpy(value, ellement->second.c_str());
    return std::move (value);
}

void Settings::setParameter(const char* const key, const char* const value){
    settings.insert_or_assign(key, value);
    
    std::ofstream out_stream(path_to_settings);
    cereal::JSONOutputArchive JSON_out (out_stream);
    // jarchive(CEREAL_RAPIDJSON_NOTHING(vec), CEREAL_RAPIDJSON_NOTHING(settings), arr );
    JSON_out(CEREAL_RAPIDJSON_NOTHING(settings) );
}


//constexpr const char* const  Settings::path_to_settings = {"/Users/and/Downloads/Verpackungsplan/Database/Settings.json"};

//first settigs{

  //current_path  = { fs::current_path().string()};
  //string current_path  { fs::current_path().string()};
//
//
//    string  Verpackungs_Plan_file{current_path.data()};
//    Verpackungs_Plan_file.append(files[5]);
//    Verpackungs_Plan_file.append(files[0]);
//    settings.emplace(std::make_pair("Verpackungs_Plan_file", Verpackungs_Plan_file.c_str()));
//
//    string  Data_file{current_path.data()};
//    Data_file.append(files[5]);
//    Data_file.append(files[1]);
//    settings.emplace(std::make_pair("Data_file", Data_file.c_str()));
//
//    string  RTF_template_file{current_path.data()};
//    RTF_template_file.append(files[5]);
//    RTF_template_file.append(files[2]);
//    settings.emplace(std::make_pair("RTF_template_file", RTF_template_file.c_str()));
//
//    string  RTF_OUT_file{current_path.data()};
//    RTF_OUT_file.append(files[5]);
//    RTF_OUT_file.append(files[3]);
//    settings.emplace(std::make_pair("RTF_OUT_file", RTF_OUT_file.c_str()));
//
//    string  RTF_END_file{current_path.data()};
//    RTF_END_file.append(files[5]);
//    RTF_END_file.append(files[4]);
//    settings.emplace(std::make_pair("RTF_END_file", RTF_END_file.c_str()));
//
//    string system_call {"open ~/../../Applications/Pages.app '"};
//    system_call.append(RTF_OUT_file.c_str());
//    system_call.append("'");
//    settings.emplace(std::make_pair("system_call", system_call));
//
//    settings.emplace(std::make_pair("read_verpack_txt_reg_expr_1", "9\\d{5}[^(\\d|:alpha:)]"));
//    settings.emplace(std::make_pair("read_verpack_txt_reg_expr_2", "([0-9]{2}[.][0-9]{2}[.]|Tage[^:alpha:])"));
//    settings.emplace(std::make_pair("read_verpack_txt_reg_expr_3", "[[:digit:]]+"));
//
//    settings.emplace(std::make_pair("read_data_txt_reg_expr_1", "(5|9)\\d{5}[^(\\d|[:alpha:]|)](\"|[[:space:]])*"));
//    settings.emplace(std::make_pair("read_data_txt_reg_expr_2", "5\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*"));
//    settings.emplace(std::make_pair("read_data_txt_reg_expr_3", "([0-9]+(\\.|\\,)+)?[0-9]+"));
  

  
  //    const char * verpackungsplan_file_ch {  SET->getParameter("Verpackungs_Plan_file").c_str() } ;
  //    const char * data_file_ch {   SET->getParameter("Data_file").c_str(), } ;
  //    const char * RTF_template_file_ch {  SET->getParameter("RTF_template_file").c_str() } ;
  //    const char * RTF_out_file_ch { SET->getParameter("RTF_OUT_file").c_str(), } ;
  //    const char * RTF_END_file_ch {  SET->getParameter("RTF_END_file").c_str() } ;
  //    const char * system_call_ch {  SET->getParameter("system_call").c_str() } ;
  
  
//    std::ofstream out_stream("Settings.json");
//    cereal::JSONOutputArchive JSON_out (out_stream);
//    // jarchive(CEREAL_RAPIDJSON_NOTHING(vec), CEREAL_RAPIDJSON_NOTHING(settings), arr );
//    JSON_out(CEREAL_RAPIDJSON_NOTHING(settings) );

//}
