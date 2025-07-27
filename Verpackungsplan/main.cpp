//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "elements_selection.h"
namespace fs = std::filesystem;
#include <sys/stat.h>




const char * files [] {
    "Plan.txt",
    "Data.txt",
    "template.rtf",
    "OUT.rtf",
    "End_of.txt",
    "/"
};


int main(int argc, const char * argv[]) {
    
    const string current_path  { fs::current_path().string()};

    
    string  verpackungsplan_file_s{current_path.data()};
    verpackungsplan_file_s.append(files[5]);
    verpackungsplan_file_s.append(files[0]);
    const char * verpackungsplan_file {  verpackungsplan_file_s.c_str() } ;

    string  data_file_s{current_path.data()};
    data_file_s.append(files[5]);
    data_file_s.append(files[1]);
    const char * data_file {  data_file_s.c_str() } ;
   
    string  RTF_template_file_s{current_path.data()};
    RTF_template_file_s.append(files[5]);
    RTF_template_file_s.append(files[2]);
    const char * RTF_template_file {  RTF_template_file_s.c_str() } ;
    
    string  RTF_out_file_s{current_path.data()};
    RTF_out_file_s.append(files[5]);
    RTF_out_file_s.append(files[3]);
    const char * RTF_out_file {  RTF_out_file_s.c_str() } ;
    
    
    string  RTF_END_in_s{current_path.data()};
    RTF_END_in_s.append(files[5]);
    RTF_END_in_s.append(files[4]);
    const char * RTF_END_in_file {  RTF_END_in_s.c_str() } ;
    
    
    string system_call {"open ~/../../Applications/Pages.app '"};
    system_call.append(RTF_out_file);
    system_call.append("'");


    
    
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
            const std::filesystem::path dir{verpackungsplan_file};
            if (!exists(dir)) {
                std::printf("Can'n open the verpack.txt file.\n\n");
                return 1;
            }
        
//        auto tmp1 = fs::path{dir};
//        std::cout<<endl;
//        std::printf("%s", tmp1.c_str()   )   ;
//        std::cout<<endl;
        
        struct stat fileInfo;
        stat(verpackungsplan_file_s.c_str(), &fileInfo);
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
            read_verpack_txt(verpackungsplan_file,
                             "9\\d{5}[^(\\d|:alpha:)]",
                             "([0-9]{2}[.][0-9]{2}[.]|Tage[^:alpha:])",
                             "[[:digit:]]+")};
        
        multimap_data data{
            read_data_txt( data_file,
                               "(5|9)\\d{5}[^(\\d|[:alpha:]|)](\"|[[:space:]])*" ,
                               "5\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*",
                               "([0-9]+(\\.|\\,)+)?[0-9]+" ) };
        
        
        elements_selection dumpf{verpak, data};
        dumpf.read_write_RTF(RTF_template_file, RTF_out_file, RTF_END_in_file);
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
    
    
    //temp
    //system(system_call.c_str());
    

    
    
    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    cout<<"\033[0m"<<endl;
    return 0;
}

