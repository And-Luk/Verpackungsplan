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

    std::printf("Date and Time: \033[32m%s\033[0m\n", printTIME() );
    system("cat ./Plan.txt | pbcopy"); //system("pbpaste > Plan.txt");  cat ./Plan.txt | pbcopy
    
    Settings* const settings = Settings::getInstance();

    const char* const Plan_file {settings->getParameter("Plan_file") };
    //const char* const Data_txt_file {settings->getParameter("Data_txt_file") };
    const char* const Data_New_txt_file {settings->getParameter("Data_New_txt_file") };
    const char* const Data_dat_file {settings->getParameter("Data_dat_file") };
    
    const char* const RTF_template_file {settings->getParameter("RTF_template_file") };
    const char* const RTF_OUT_file {settings->getParameter("RTF_OUT_file") };
    const char* const RTF_END_file {settings->getParameter("RTF_END_file") };

    const char* const read_verpack_txt_reg_expr_1 {settings->getParameter("read_verpack_txt_reg_expr_1") };
    const char* const read_verpack_txt_reg_expr_2 {settings->getParameter("read_verpack_txt_reg_expr_2") };
    const char* const read_verpack_txt_reg_expr_3 {settings->getParameter("read_verpack_txt_reg_expr_3") };

    const char* const read_data_txt_reg_expr_1 {settings->getParameter("read_data_txt_reg_expr_1") };
    const char* const read_data_txt_reg_expr_2 {settings->getParameter("read_data_txt_reg_expr_2") };
    //const char* const read_data_txt_reg_expr_3 {settings->getParameter("read_data_txt_reg_expr_3") };

    //const char* const system_call_ch {settings->getParameter("system_call") };
 
    const char* const HASH_of_Settings_json {settings->getParameter("hash_value") };

    char* FILE_HASH = new char[100] ;
    FILE_HASH = getFileHASH(Data_New_txt_file);
    
    
    try {
        const std::filesystem::path dir_Plan_file{ Plan_file };
        const std::filesystem::path dir_Data_dat_file{ Data_dat_file };
        if (!exists(dir_Plan_file)) {
            std::printf("Can'n open the \"\033[31m%s\033[0m\" file.\n\n", Plan_file );
            return 1;
        }
        if (!exists(dir_Data_dat_file)) {
            std::printf("Can'n open the \"\033[31m%s\033[0m\" file.\n\n", Data_dat_file );
            return 1;
        }

        } catch (std::exception ex){
            std::printf("Exception Can'n open the \"\033[31m%s\033[0m\"  file.\n\n", Plan_file );
        }
    
    multimap_data* data{nullptr};

    

    Serializer * const serializer{Serializer::getInstance(Data_dat_file)};
    
    
    if (std::strcmp(HASH_of_Settings_json, FILE_HASH)==0) { // read DATA of Data.dat   >>>HASH_of_Settings_json, HASH_Data_txt

        std::printf("HASH value is equal and it is \"\033[31m%s\033[0m\" \n", HASH_of_Settings_json );
        try {
            //serializer.writeDataFile(data);
            //auto thread_serializer = std::thread  (std::mem_fn(&Serializer::readDataFile),  &serializer     );
            std::printf("DATA from \"\033[31m%s\033[0m\" \n", Data_dat_file);
            data= serializer->readDataFile();
            //thread_serializer.join();
            if (data->empty()) {

                system(" osascript -e \'display dialog \" \tAn error:\r\n\tData.dat file is empty\" \' ");
                throw exception();
            }

        } catch (exception ex) {std::printf("\n Data.dat file read ERROR !\n") ; }
    }
    else{
        // read DATA of Data.txt
        try {
            // data=read_Data_txt( Data_txt_file,  read_data_txt_reg_expr_1,  read_data_txt_reg_expr_2,   read_data_txt_reg_expr_3);
            //data = read_Data_New_txt(Data_New_txt_file,read_data_txt_reg_expr_1,read_data_txt_reg_expr_2,"NOT USED", "NOT USED");
            data = read_Data_txt(Data_New_txt_file,read_data_txt_reg_expr_1,read_data_txt_reg_expr_2);
            //std::printf("\t data SIZE = \"\033[31m%lu\033[0m\" \n", data->size()) ;
            
            std::printf("\nDATA was written to \"\033[31m%s\033[0m\" file\n", Data_dat_file ) ;
            serializer->writeDataFile(*data);
            Settings* const settings = Settings::getInstance();
            settings->setParameter("hash_value", FILE_HASH );

            std::printf("DATA from \"\033[31m%s\033[0m\"\n", Data_New_txt_file);
            
        } catch (exception ex) { std::printf("\n Data_New.txt file read ERROR !\n") ;   }
    }
    
    try {
        vector_of_pair_size_t verpak{
            read_verpack_txt( Plan_file ,
                             read_verpack_txt_reg_expr_1,
                             read_verpack_txt_reg_expr_2,
                             read_verpack_txt_reg_expr_3)};
        
        if (verpak.empty()) {

            system(" osascript -e \'display dialog \" Nothing was copied to the clipboard \" \' ");
            throw exception();
        }
        
        std::printf("DATA SIZE = \"\033[31m%lu\033[0m\" \n", data->size()) ;

        elements_selection dumpf{verpak, data};
//        dumpf.read_write_RTF( RTF_template_file,
//                                                RTF_OUT_file,
//                                                RTF_END_file);
    } catch (exception ex) {
        std::printf("\t something didn't go as planned!\n") ;
        //system( "rm  ./Plan.txt");
        return 1;
    }

    
    std::cout<<"\033[32m";
    printTIME();
    
    //system( "rm  ./Plan.txt");
    
    //system(system_call_ch.c_str());

    

    
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
    
    
    
//    Statistics* Stat = Statistics::getInstance();
//    cout<<"\033[31m";
//    std::printf("\033[32m Amount of allocated memory \033[31m %u \033[0m \n",  (uint)Stat->getStatistics()  );
    
    //------------------------------------------------------------
    
    data->clear();
    delete data;
        
//        for (const auto& item : *data) {
//            first_el = item.first;
//            second_el = get<0>(item.second);
//            amount_el = get<1>(item.second);
//            string_el = get<2>(item.second).c_str();
//            std::printf("\t %lu  %lu  \"\033[31m%s\033[0m\" \t\t\t%f\n", first_el, second_el, string_el.c_str(), amount_el) ;
//        }
        
        
  //  }


    
    
    
    
    
    //------------------------------------------------------------

    
    
    cout<<"\033[31m";
    //std::printf("Amount of allocated memory %u  \n",  (uint)Stat->getStatistics()  );
    
    cout<<"\033[32m";
    std::printf("\n OK!\n") ;
    cout<<"\033[0m";
    return 0;
}

