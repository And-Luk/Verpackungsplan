//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "elements_selection.h"

#include <sys/stat.h>

#include "write_Excel_file.h"
#include "settings.h"





int main(int argc, const char * argv[]) {
    
    Settings* const SET = Settings::getInstance();
    
    
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer,80,"%d-%m-%Y    %H:%M:%S",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
    cout<<"\033[31m"<<endl;
    std::printf("%s",buffer);
    //std::puts(buffer);
    
    
//  auto tomorrow = today + 24h;
//  std::cout << "Tomorrow is " << tomorrow << "\n";
//  
//  auto day_after = today + 24h * 2;
//  std::cout << "The day after that is " << day_after << "\n";

    
    
//    "\033[31m"   rot
//    "\033[32m"  green
//    "\033[33m" light green
//    "\033[34m"  pourpur
//    "\033[35m"  lila
//    "\033[36m"
//    const std: string reset {"\033[0m"};
    
    
   
    
    try {
            const std::filesystem::path dir{SET->getParameter("Verpackungs_Plan_file").c_str()};
            if (!exists(dir)) {
                std::printf("Can'n open the verpack.txt file.\n\n");
                return 1;
            }
        
        
        struct stat fileInfo;
        stat(SET->getParameter("Verpackungs_Plan_file").c_str(), &fileInfo);
        unsigned long fileSize =  fileInfo.st_size;
        string file_Info_string{to_string (fileSize)};
       
        fileSize = fileInfo.st_ino;
        file_Info_string.append(to_string (fileSize));
        
        fileSize = fileInfo.st_mtimespec.tv_nsec;
        file_Info_string.append(to_string (fileSize));
        
        std::printf("Size of a last modefied = %s", file_Info_string.c_str() )   ;
        std::cout<<endl;
           
        } catch (std::exception ex){
            std::printf(" an error.\n\n");
        }
    
    try {
        vector_of_pair_size_t verpak{
            read_verpack_txt(SET->getParameter("Verpackungs_Plan_file").c_str(),
                             "9\\d{5}[^(\\d|:alpha:)]",
                             "([0-9]{2}[.][0-9]{2}[.]|Tage[^:alpha:])",
                             "[[:digit:]]+")};
        
        multimap_data data{
            read_data_txt( SET->getParameter("Data_file").c_str(),
                               "(5|9)\\d{5}[^(\\d|[:alpha:]|)](\"|[[:space:]])*" ,
                               "5\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*",
                               "([0-9]+(\\.|\\,)+)?[0-9]+" ) };
        
        
        elements_selection dumpf{verpak, data};
        
        dumpf.read_write_RTF(SET->getParameter("RTF_template_file").c_str(),
                                              SET->getParameter("RTF_OUT_file").c_str(),
                                              SET->getParameter("RTF_END_file").c_str());
    } catch (exception ex) {
        std::printf("\n something didn't go as planned!\n") ;
        return 1;
    }



    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    cout<<"\033[34m"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    //std::printf("\n OK!\n") ;
    for (auto &item : buffer) {
        item=' ';
    }
      
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer, 80,"%H:%M:%S",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
    std::printf("%s",buffer);
    
    
    
    cout<<"\033[35m"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    for (auto &item : buffer) {
        item=' ';
    }
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer, 80,"%H:%M:%S",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
    std::printf("%s",buffer);
    
    
    //system(SET->getParameter("system_call").c_str());
    //"'make an Excel file"
    //write_Excel();
    



    
    
    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    cout<<"\033[0m"<<endl;
    return 0;
}

