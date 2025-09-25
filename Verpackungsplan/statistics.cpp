//
//  statistics.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 24-09-2025.
//

#include "statistics.h"

Statistics::Statistics():memory{0}{}
Statistics::~Statistics(){}
Statistics* Statistics::getInstance(){
    static Statistics Stat;
    return  &Stat;
}

size_t Statistics::getStatistics(){
    
//    struct stat fileInfo;
//    stat( Plan_file_ch.c_str() , &fileInfo);
//    unsigned long fileSize =  fileInfo.st_size;
//    string file_Info_string{to_string (fileSize)};
//   
//    fileSize = fileInfo.st_ino;
//    file_Info_string.append(to_string (fileSize));
//    
//    fileSize = fileInfo.st_mtimespec.tv_nsec;
//    file_Info_string.append(to_string (fileSize));
//    
//    std::printf("Size of a last modefied = %s", file_Info_string.c_str() )   ;
//    std::cout<<endl;
//       
//    } catch (std::exception ex){
//        std::printf(" an error.\n\n");
//    }
    
    
    return memory;}

void Statistics::setStatistics(size_t value){memory+=value;}
