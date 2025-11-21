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



#include <thread>





int main(int argc, const char * argv[]) {
    
    
    //system("pbpaste > Plan.txt");
    Settings* const settings = Settings::getInstance();
    
    
    char Plan_file[200];
    char Data_txt_file[200];
    char RTF_template_file[200];
    char RTF_OUT_file[200];
    char RTF_END_file[200];
    strcpy(Plan_file, settings->getParameter("Plan_file").c_str() );
    strcpy(Data_txt_file,  settings->getParameter("Data_file").c_str() );
    strcpy(RTF_template_file, settings->getParameter("RTF_template_file").c_str() );
    strcpy(RTF_OUT_file,  settings->getParameter("RTF_OUT_file").c_str() );
    strcpy(RTF_END_file,  settings->getParameter("RTF_END_file").c_str() );
    
    char read_verpack_txt_reg_expr_1[100];
    char read_verpack_txt_reg_expr_2[100];
    char read_verpack_txt_reg_expr_3[100];
    strcpy(read_verpack_txt_reg_expr_1,  settings->getParameter("read_verpack_txt_reg_expr_1").c_str() );
    strcpy(read_verpack_txt_reg_expr_2,   settings->getParameter("read_verpack_txt_reg_expr_2").c_str() );
    strcpy(read_verpack_txt_reg_expr_3,   settings->getParameter("read_verpack_txt_reg_expr_3").c_str() );

    char read_data_txt_reg_expr_1[100];
    char read_data_txt_reg_expr_2[100];
    char read_data_txt_reg_expr_3[100];
    strcpy(read_data_txt_reg_expr_1,  settings->getParameter("read_data_txt_reg_expr_1").c_str() );
    strcpy(read_data_txt_reg_expr_2,  settings->getParameter("read_data_txt_reg_expr_2").c_str() );
    strcpy(read_data_txt_reg_expr_3,   settings->getParameter("read_data_txt_reg_expr_3").c_str() );

    char Data_dat_file[200];
    strcpy(Data_dat_file,  std::move( settings->getParameter("read_data_dat").c_str()) );
   // const std::string read_data_dat        { settings->getParameter("read_data_dat").c_str() } ;

    char system_call_ch[100];
    strcpy(system_call_ch,  std::move( settings->getParameter("system_call").c_str()) );
    //const std::string system_call_ch                          { settings->getParameter("system_call").c_str() } ;
    
    char HASH_of_Settings_json[100];
    strcpy(HASH_of_Settings_json,  std::move( settings->getParameter("hash_value").c_str()) );
    
    std::cout<<"\033[32m"<<endl;
    printTIME();
    std::cout<<"\033[0m"<<endl;


    try {
            const std::filesystem::path dir{ Plan_file };
            if (!exists(dir)) {
                std::cout<<std::endl<<" getParameter(\"Plan_file\")  "<<Plan_file<<std::endl<<std::endl;
                std::printf("Can'n open the %s file.\n\n", Plan_file );
                return 1;
            }

        } catch (std::exception ex){
            std::printf(" an error.\n\n");
        }
    
    multimap_data* data;
    
    char* HASH_Data_txt = new char ;
    HASH_Data_txt = getFileHASH(Data_txt_file);
    //std::printf("HASH_Data_txt is \" %s \"\n", HASH_Data_txt  );
    //std::printf("HASH value of Data.txt file is %s\n", HASH_Data_txt );
    Serializer * const serializer{Serializer::getInstance(Data_dat_file)};
    
    if (std::strcmp(HASH_of_Settings_json, HASH_Data_txt)==0) { // read DATA of Data.dat
        //std::printf("HASH value of Data.txt file is %s\n", HASH_Data_txt );
        std::printf("HASH value is equal and it is \"%s\"\n", HASH_of_Settings_json );
        try {
            //serializer.writeDataFile(data);
            //auto thread_serializer = std::thread  (std::mem_fn(&Serializer::readDataFile),  &serializer     );
            std::printf("DATA of \"%s\" \n", Data_dat_file);
            data= serializer->readDataFile();
            //thread_serializer.join();
            if (data->empty()) {

                system(" osascript -e \'display dialog \" \tAn error:\r\n\tData.dat file is empty\" \' ");
                throw exception();
            }

        } catch (exception ex) {std::printf("\n Data.dat file read ERROR !\n") ; }
    }
    else{
        try {
            std::printf("DATA of \"%s\"\n", Data_txt_file );
            std::printf("HASH_Data_txt is --1\"%s\"\n", HASH_Data_txt  );
            data=read_data_txt( Data_txt_file,  read_data_txt_reg_expr_1,  read_data_txt_reg_expr_2,   read_data_txt_reg_expr_3);
            std::printf("HASH_ is \n" );
            std::printf("HASH_Data_txt is --2\"%s\"\n", HASH_Data_txt  );
            
            //Serializer * const serializer{Serializer::getInstance(Data_dat_file)};
            serializer->writeDataFile(*data);
            
            //std::printf("HASH_Data_txt is --3\"%s\"\n", HASH_Data_txt  );
            Settings* const settings = Settings::getInstance();
            //std::printf("HASH_Data_txt is --4\"%s\"\n", HASH_Data_txt  );
            settings->setParameter("hash_value", HASH_Data_txt );
            
            
        } catch (exception ex) { std::printf("\n Data.txt file read ERROR !\n") ;   }
    }
    
//    { /// Get HASH of Data.txt
//        struct stat fileInfo;
//        stat( Data_file , &fileInfo);
//        unsigned long fileSize =  fileInfo.st_size;
//        string file_Info_string{to_string (fileSize)};
//        
//        fileSize = fileInfo.st_ino;
//        file_Info_string.append(to_string (fileSize));
//        fileSize = fileInfo.st_mtimespec.tv_nsec;
//        file_Info_string.append(to_string (fileSize));
//
//        std::printf("\nHASH value Data.txt file\t%s\nHASH value of Settings.json     %s\n", file_Info_string.c_str(), hash_value  )   ;
//
//        if (std::strcmp(hash_value, file_Info_string.c_str())==0) {
//           std::printf("HASH value is equal %s\n", hash_value )  ;
//        }
//    }
    
    try {
        vector_of_pair_size_t verpak{
            read_verpack_txt( Plan_file ,
                             read_verpack_txt_reg_expr_1,
                             read_verpack_txt_reg_expr_2,
                             read_verpack_txt_reg_expr_3)};
        
//        multimap_data data{
//            read_data_txt( Data_file,
//                          read_data_txt_reg_expr_1,
//                          read_data_txt_reg_expr_2,
//                          read_data_txt_reg_expr_3)
//        };
        
 // out to a file
        if (verpak.empty()) {

            system(" osascript -e \'display dialog \" Nothing was copied to the clipboard \" \' ");
            throw exception();
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
    //std::cout<<"\033[32m"<<endl;
    
    
    std::cout<<"\033[32m"<<endl;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    printTIME();
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    std::cout<<"\033[32m"<<endl;
    printTIME();
    
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
    cout<<"\033[31m"<<endl;
    std::printf("Amount of allocated memory %u  \n",  (uint)Stat->getStatistics()  );
    cout<<endl;
    //------------------------------------------------------------
    


    
    
    
    
    
    //------------------------------------------------------------
    
    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    cout<<"\033[0m"<<endl;
    return 0;
}

