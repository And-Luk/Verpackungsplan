//
//  serialization.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 15-11-2025.
//

#include "serialization.h"
Serializer::Serializer(const path & path_to_file) {     //: pathToFile(path_to_file.c_str())
    std::strcpy(pathToFile, path_to_file.c_str());
    fileData.open(path_to_file.c_str(),  ios::in | std::ios::binary );
    if (!fileData) throw exception() ;
    fileData.close();
}

Serializer::~Serializer(){
    fileData.close();
}


//int Serializer::openDataFile(const path & path_to_file){
//    fileData.open(path_to_file.c_str(),  ios::out|std::ios::binary ); //os::trunc |
//    //fileData.write((const char*) &entry , sizeof(data_entry));
//    return 1;
//}


int Serializer::writeDataFile(const multimap_data& multi){
    data_entry entry;
    fileData.open(pathToFile,  ios::out | std::ios::binary ); //os::trunc |
    //std::printf("\n in writeDataFile %s \n", pathToFile ) ;
    for (const auto& item : multi) {
        entry.operation = item.first;
        entry.article = get<0>(item.second);
        entry.amount = get<1>(item.second);
        std::strcpy (entry.title, get<2>(item.second).c_str());
        
        //std::printf("\t %lu  %lu  %f  %s \n", entry.operation, entry.article, entry.amount, entry.title.c_str()) ;
        fileData.write((const char*) &entry , sizeof(data_entry));
        }
    fileData.close();
    
    return 1;
}

int Serializer::readDataFile(){
    data_entry entry;
    

    fileData.open(pathToFile,  ios::in | std::ios::binary );
    fileData.seekg(ios::beg); //)
    while (true) {
        fileData.read((char*) &entry , sizeof(data_entry));
        
        if(fileData.eof()) {// выход из цикла по EOF
            fileData.close();
            break;
        }
        
        if(!fileData) { // ошибка чтения типа
            cout << "\n Невозможно чтение типа\n";
            return 0;
        }
        std::printf("\t %lu     %lu    %-60s%f \n", entry.operation, entry.article, entry.title, entry.amount) ;
    }
    
   return 1;
}
