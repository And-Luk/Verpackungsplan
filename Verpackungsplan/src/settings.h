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
    explicit Settings(const char* const path_to_settings_file );
    ~Settings();
    
    const char* path_to_settings ;
    std::map<std::string, std::string> settings;

    
public:
    static Settings* getInstance(const char* const path_to_settings_file = "./");
    const char* getParameter(const char* const key);
    void setParameter(const char* const key, const char* const value);
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};
