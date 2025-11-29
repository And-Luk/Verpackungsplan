//
//  serialization.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 15-11-2025.
//

#include "serialization.h"
Serializer::Serializer(const path & path_to_file) {
    std::strcpy(pathToFile, path_to_file.c_str());
    fileData.open(path_to_file.c_str(),  ios::in | std::ios::binary );
    if (!fileData) throw exception() ;
    fileData.close();
}

Serializer::~Serializer(){
    fileData.close();
}

Serializer* Serializer::getInstance(const path & path_to_file ){
    static Serializer serializer(path_to_file);
    return  &serializer;
}

int Serializer::writeDataFile(const multimap_data& multi){
    data_entry entry;
    fileData.open(pathToFile,  ios::out | std::ios::binary ); //os::trunc |
    //std::printf("\nwrite DATA to \"%s\"\n", pathToFile ) ;
    for (const auto& item : multi) {
        entry.operation = item.first;
        entry.article = get<0>(item.second);
        entry.amount = get<1>(item.second);
        std::strcpy (entry.title, get<2>(item.second).c_str());
        fileData.write((const char*) &entry , sizeof(data_entry));
        //std::printf("\t %lu  %lu  %f  %s \n", entry.operation, entry.article, entry.amount, entry.title) ;
        }
    fileData.close();
    return 1;
}

auto Serializer::readDataFile()-> multimap_data*{
    data_entry entry;
    tup_element multimap_data_value;
    multimap_data* data = new multimap_data;

    fileData.open(pathToFile,  ios::in | std::ios::binary );
    fileData.seekg(ios::beg);
    while (true) {
        fileData.read((char*) &entry , sizeof(data_entry));
        
        if(fileData.eof()) {// exit the loop on EOF
            fileData.close();
            break;
        }
        
        if(!fileData) { // ошибка чтения типа
            std::cout << "Unable to read type of Data.txt file\n";
            return std::move(data); // ??
        }
        //std::printf(" %lu     %lu    %-60s%10f \n", entry.operation, entry.article, entry.title, entry.amount) ;
        get<0>(multimap_data_value) = entry.article;
        get<1>(multimap_data_value) = entry.amount;
        get<2>(multimap_data_value) = entry.title;
        data->insert( {entry.operation, multimap_data_value} );
    }
   return std::move(data);
}
