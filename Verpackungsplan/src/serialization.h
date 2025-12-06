//
//  serialization.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 15-11-2025.
//
#pragma once
#include "header.h"

#include "settings.h"

typedef std::tuple<size_t, float, string > tup_element ;
typedef std::tuple<string, float, size_t, size_t> element;
typedef multimap<size_t, tup_element, std::less<size_t>, std::allocator<std::pair<const size_t, tup_element>>> multimap_data;
typedef struct {
    char  title [60];
    float amount;
    size_t article;
    size_t operation;
} data_entry;


class Serializer {
    std::fstream  fileData;
    char pathToFile[200];
    Serializer(const path & path_to_file = "./");
    Serializer()= delete;
    
    //friend istream& operator>>(istream& s, const element& d);
    //friend ostream& operator<<(ostream& s, const element& d);
    //fstream& operator <<( const element);
public:
    Serializer(const Serializer& )= delete;
    Serializer& operator =(const Serializer&) = delete;
    ~Serializer();
    
    int writeDataFile(const multimap_data& multimap);
    auto readDataFile ()-> multimap_data*;
    static Serializer* getInstance(const path & path_to_file = "./");
    
};
