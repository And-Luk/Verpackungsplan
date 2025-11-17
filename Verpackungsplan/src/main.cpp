//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "statistics.h"
#include "settings.h"
#include "elements_selection.h"
#include "write_Excel_file.h"
#include "read_Excel_file.h"
#include "photo.h"
#include "serialization.h"



#include <sys/stat.h>
#include <thread>





int main(int argc, const char * argv[]) {
    
    
    //system("pbpaste > Plan.txt");
    Settings* const settings = Settings::getInstance();
    
   // const char * verpackungsplan_file_ch = settings->getParameter("Verpackungs_Plan_file").c_str()  ;
//    const char * data_file_ch {   settings->getParameter("Data_file").c_str(), } ;
//    const char * RTF_template_file_ch {  settings->getParameter("RTF_template_file").c_str() } ;
//    const char * RTF_out_file_ch { settings->getParameter("RTF_OUT_file").c_str(), } ;
//    const char * RTF_END_file_ch {  settings->getParameter("RTF_END_file").c_str() } ;
    
//    const char * system_call_ch {  settings->getParameter("system_call").c_str() } ;
    
    char Plan_file[200];
    char Data_file[200];
    char RTF_template_file[200];
    char RTF_OUT_file[200];
    char RTF_END_file[200];
    
    strcpy(Plan_file, settings->getParameter("Plan_file").c_str() );
    //strcpy(Plan_file_ch,  std::move( settings->getParameter("Plan_file").c_str()) );
    strcpy(Data_file,  settings->getParameter("Data_file").c_str() );
    //strcpy(Data_file_ch,  std::move( settings->getParameter("Data_file").c_str()) );
    strcpy(RTF_template_file, settings->getParameter("RTF_template_file").c_str() );
    //strcpy(RTF_template_file_ch,  std::move( settings->getParameter("RTF_template_file").c_str()) );
    strcpy(RTF_OUT_file,  settings->getParameter("RTF_OUT_file").c_str() );
    //strcpy(RTF_OUT_file_ch,  std::move( settings->getParameter("RTF_OUT_file").c_str()) );
    strcpy(RTF_END_file,  settings->getParameter("RTF_END_file").c_str() );
    //strcpy(RTF_END_file_ch,  std::move( settings->getParameter("RTF_END_file").c_str()) );

    
    char read_verpack_txt_reg_expr_1[100];
    char read_verpack_txt_reg_expr_2[100];
    char read_verpack_txt_reg_expr_3[100];
    strcpy(read_verpack_txt_reg_expr_1,  std::move( settings->getParameter("read_verpack_txt_reg_expr_1").c_str()) );
    strcpy(read_verpack_txt_reg_expr_2,  std::move( settings->getParameter("read_verpack_txt_reg_expr_2").c_str()) );
    strcpy(read_verpack_txt_reg_expr_3,  std::move( settings->getParameter("read_verpack_txt_reg_expr_3").c_str()) );

    
    
    char read_data_txt_reg_expr_1[100];
    char read_data_txt_reg_expr_2[100];
    char read_data_txt_reg_expr_3[100];
    strcpy(read_data_txt_reg_expr_1,  std::move( settings->getParameter("read_data_txt_reg_expr_1").c_str()) );
    strcpy(read_data_txt_reg_expr_2,  std::move( settings->getParameter("read_data_txt_reg_expr_2").c_str()) );
    strcpy(read_data_txt_reg_expr_3,  std::move( settings->getParameter("read_data_txt_reg_expr_3").c_str()) );

    
    char read_data_dat[100];
    strcpy(read_data_dat,  std::move( settings->getParameter("read_data_dat").c_str()) );
   // const std::string read_data_dat        { settings->getParameter("read_data_dat").c_str() } ;

    char system_call_ch[100];
    strcpy(system_call_ch,  std::move( settings->getParameter("system_call").c_str()) );
    //const std::string system_call_ch                          { settings->getParameter("system_call").c_str() } ;
    
    char hash_value[100];
    strcpy(hash_value,  std::move( settings->getParameter("hash_value").c_str()) );
    
    
    
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
            const std::filesystem::path dir{ Plan_file };
            if (!exists(dir)) {
                std::cout<<std::endl<<" getParameter(\"Plan_file\")  "<<Plan_file<<std::endl<<std::endl;
                std::printf("Can'n open the %s file.\n\n", Plan_file );
                return 1;
            }
        
        
        struct stat fileInfo;
        stat( Plan_file , &fileInfo);
        unsigned long fileSize =  fileInfo.st_size;
        string file_Info_string{to_string (fileSize)};
       
        fileSize = fileInfo.st_ino;
        file_Info_string.append(to_string (fileSize));
        
        fileSize = fileInfo.st_mtimespec.tv_nsec;
        file_Info_string.append(to_string (fileSize));
        
        std::printf("\nSize of a last modefied %s", file_Info_string.c_str() )   ;
        std::cout<<endl;
           
        } catch (std::exception ex){
            std::printf(" an error.\n\n");
        }
    
    try {
        vector_of_pair_size_t verpak{
            read_verpack_txt( Plan_file ,
                             read_verpack_txt_reg_expr_1,
                             read_verpack_txt_reg_expr_2,
                             read_verpack_txt_reg_expr_3)};
        
        multimap_data data{
            read_data_txt( Data_file,
                          read_data_txt_reg_expr_1,
                          read_data_txt_reg_expr_2,
                          read_data_txt_reg_expr_3)
        };
        
 // out to a file
        if (verpak.empty()) {
            
            
            system(" osascript -e \'display dialog \" Nothing was copied to the clipboard \" \' ");
            throw exception();
        }
        
        try {
            Serializer serializer {read_data_dat};
            //serializer.writeDataFile(data);
            auto thread_serializer = std::thread  (std::mem_fn(&Serializer::readDataFile),  &serializer 	);
            //serializer.readDataFile();
            thread_serializer.join();

        } catch (exception ex) {
            std::printf("\n data.dat file write !\n") ;
        }
        
        
        elements_selection dumpf{verpak, data};
        
//        dumpf.read_write_RTF( RTF_template_file_ch.c_str(),
//                                                RTF_OUT_file_ch.c_str(),
//                                                RTF_END_file_ch.c_str() );
    } catch (exception ex) {
        std::printf("\n something didn't go as planned!\n") ;
        //system( "rm  ./Plan.txt");
        return 1;
    }



    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    cout<<"\033[34m"<<endl;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    
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
    
    //system( "rm  ./Plan.txt");
    
    //system(system_call_ch.c_str());

    
//    std::string test;
//    std::cout<<std::endl;
//    while (std::cin>>test ) {
//        cout<<test<<endl;
//    }
    
    //take_a_photo();
    //std::thread thread_take_a_photo (take_a_photo);
    //thread_take_a_photo.join();

    
// 'make an Excel file"
//    std::thread thread_write_Excel (write_Excel);
   // std::thread thread_read_Excel (read_Excel, "input.xls");
    
//    thread_write_Excel.join();
   // thread_read_Excel.join();
    
    
//write_Excel();
//read_Excel("input.xlsx");
 // I have made yet  take_a_photo();
    
    
    
    Statistics* Stat = Statistics::getInstance();
    cout<<"\033[35m"<<endl;
    std::printf("\n amount of allocated memory %u  \n",  (uint)Stat->getStatistics()  );
    cout<<endl;
    //------------------------------------------------------------
    


    
    
    
    
    
    //------------------------------------------------------------
    
    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    cout<<"\033[0m"<<endl;
    return 0;
}

