//
//  settings.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 17-09-2025.
//
#pragma once
#include "header.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>




namespace fs = std::filesystem;


class Settings {
private:
    Settings()	;
    ~Settings();
//    bool arr[2] ={true, false};
//    std::vector<int> vec  {1, 2, 3, 4, 5};
    
//    const char * files [6] {
//        "Plan.txt",
//        "Data.txt",
//        "template.rtf",
//        "OUT.rtf",
//        "End_of.txt",
//        "/"
//    };
    
    string current_path; //= { fs::current_path().string()};
    std::map<std::string, std::string> settings;
    //std::map<std::string, std::string> settings_in;
//    std::map<std::string, std::string> settings{
//        std::make_pair("Settings_file", "/Settings.json"),
//        std::make_pair("Verpackungs_Plan_file", "/Plan.txt"),
//        std::make_pair("Data_file", "/Data.txt"),
//        std::make_pair("RTF_template_file", "/template.rtf"),
//        std::make_pair("RTF_OUT_file", "/OUT.rtf"),
//        std::make_pair("RTF_END_file", "/End_of.txt")
//    };

public:
    static Settings* getInstance();
    const char* getParameter(std::string search);
    void setParameter(const char* key, const char* value);
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};
    
