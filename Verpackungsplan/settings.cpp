//
//  settings.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 17-09-2025.
//
#include "settings.h"


Settings::Settings(){
    
//    std::make_pair("Settings_file", "/Settings.json"),
//    std::make_pair("Verpackungs_Plan_file", "/Plan.txt"),
//    std::make_pair("Data_file", "/Data.txt"),
//    std::make_pair("RTF_template_file", "/template.rtf"),
//    std::make_pair("RTF_OUT_file", "/OUT.rtf"),
//    std::make_pair("RTF_END_file", "/End_of.txt")
    
    
    const string current_path  { fs::current_path().string()};

    
    string  Verpackungs_Plan_file{current_path.data()};
    Verpackungs_Plan_file.append(files[5]);
    Verpackungs_Plan_file.append(files[0]);
    //const char * verpackungsplan_file_ch {  Verpackungs_Plan_file.c_str() } ;
    settings.emplace(std::make_pair("Verpackungs_Plan_file", Verpackungs_Plan_file.c_str()));

    string  Data_file{current_path.data()};
    Data_file.append(files[5]);
    Data_file.append(files[1]);
    //const char * data_file_ch {  Data_file.c_str() } ;
    settings.emplace(std::make_pair("Data_file", Data_file.c_str()));
   
    string  RTF_template_file{current_path.data()};
    RTF_template_file.append(files[5]);
    RTF_template_file.append(files[2]);
    //const char * RTF_template_file_ch {  RTF_template_file.c_str() } ;
    settings.emplace(std::make_pair("RTF_template_file", RTF_template_file.c_str()));
    
    string  RTF_OUT_file{current_path.data()};
    RTF_OUT_file.append(files[5]);
    RTF_OUT_file.append(files[3]);
    //const char * RTF_out_file_ch {  RTF_OUT_file.c_str() } ;
    settings.emplace(std::make_pair("RTF_OUT_file", RTF_OUT_file.c_str()));
    
    
    string  RTF_END_file{current_path.data()};
    RTF_END_file.append(files[5]);
    RTF_END_file.append(files[4]);
    //const char * RTF_END_in_file_ch {  RTF_END_file.c_str() } ;
    settings.emplace(std::make_pair("RTF_END_file", RTF_END_file.c_str()));
    
    
    string system_call {"open ~/../../Applications/Pages.app '"};
    system_call.append(RTF_OUT_file.c_str());
    system_call.append("'");
    settings.emplace(std::make_pair("system_call", system_call));
    
    
    
    
    std::ofstream out_stream("Settings.json");
    cereal::JSONOutputArchive jarchive (out_stream);
    // jarchive(CEREAL_RAPIDJSON_NOTHING(vec), CEREAL_RAPIDJSON_NOTHING(settings), arr );
    jarchive(CEREAL_RAPIDJSON_NOTHING(settings) );
}

Settings::~Settings(){};

Settings* Settings::getInstance(){
    static Settings instance;
    return &instance;
}

std::string Settings::getParameter(std::string search){
    std::map<string, string>::iterator it;
    it = settings.find(search);
    return it->second;
}
