//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "elements_selection.h"
#include "write_Excel_file.h"
#include "settings.h"

#include <sys/stat.h>

#include "statistics.h"





int main(int argc, const char * argv[]) {
    
    Settings* const SET = Settings::getInstance();
    
//    const char * verpackungsplan_file_ch {  SET->getParameter("Verpackungs_Plan_file").c_str() } ;
//    const char * data_file_ch {   SET->getParameter("Data_file").c_str(), } ;
//    const char * RTF_template_file_ch {  SET->getParameter("RTF_template_file").c_str() } ;
//    const char * RTF_out_file_ch { SET->getParameter("RTF_OUT_file").c_str(), } ;
//    const char * RTF_END_file_ch {  SET->getParameter("RTF_END_file").c_str() } ;
    
//    const char * system_call_ch {  SET->getParameter("system_call").c_str() } ;
    
    const std::string Plan_file_ch                             { SET->getParameter("Plan_file").c_str() } ;
    const std::string Data_file_ch                             { SET->getParameter("Data_file").c_str() } ;
    const std::string RTF_template_file_ch               { SET->getParameter("RTF_template_file").c_str() } ;
    const std::string RTF_OUT_file_ch                      { SET->getParameter("RTF_OUT_file").c_str() } ;
    const std::string RTF_END_file_ch                      { SET->getParameter("RTF_END_file").c_str() } ;
        
    const std::string read_verpack_txt_reg_expr_1  { SET->getParameter("read_verpack_txt_reg_expr_1").c_str() } ;
    const std::string read_verpack_txt_reg_expr_2  { SET->getParameter("read_verpack_txt_reg_expr_2").c_str() } ;
    const std::string read_verpack_txt_reg_expr_3  { SET->getParameter("read_verpack_txt_reg_expr_3").c_str() } ;
    
    const std::string read_data_txt_reg_expr_1        { SET->getParameter("read_data_txt_reg_expr_1").c_str() } ;
    const std::string read_data_txt_reg_expr_2        { SET->getParameter("read_data_txt_reg_expr_2").c_str() } ;
    const std::string read_data_txt_reg_expr_3        { SET->getParameter("read_data_txt_reg_expr_3").c_str() } ;

    const std::string system_call_ch                          { SET->getParameter("system_call").c_str() } ;
    
    
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
            const std::filesystem::path dir{ Plan_file_ch.c_str() };
            if (!exists(dir)) {
                std::cout<<std::endl<<" getParameter(\"Plan_file\")  "<<Plan_file_ch.c_str()<<std::endl<<std::endl;
                std::printf("Can'n open the %s file.\n\n", Plan_file_ch.c_str() );
                return 1;
            }
        
        
        struct stat fileInfo;
        stat( Plan_file_ch.c_str() , &fileInfo);
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
            read_verpack_txt( Plan_file_ch.c_str() ,
                             read_verpack_txt_reg_expr_1.c_str(),
                             read_verpack_txt_reg_expr_2.c_str(),
                             read_verpack_txt_reg_expr_3.c_str())};
        
        multimap_data data{
            read_data_txt( Data_file_ch.c_str(),
                          read_data_txt_reg_expr_1.c_str() ,
                          read_data_txt_reg_expr_2.c_str(),
                          read_data_txt_reg_expr_3.c_str() )
        };
        
        
        elements_selection dumpf{verpak, data};
        
        dumpf.read_write_RTF( RTF_template_file_ch.c_str(),
                                                RTF_OUT_file_ch.c_str(),
                                                RTF_END_file_ch.c_str() );
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
    
    
    //system(system_call_ch.c_str());
    
    //write_Excel();  //"'make an Excel file"
    
    Statistics* Stat = Statistics::getInstance();
    cout<<"\033[35m"<<endl;
    std::printf("\n amount of allocated memory %u  \n",  (uint)Stat->getStatistics()  );
    cout<<endl;
    
    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    cout<<"\033[0m"<<endl;
    return 0;
}

