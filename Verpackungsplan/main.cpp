//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "elements_selection.h"
namespace fs = std::filesystem;

//const char * verpackungsplan_file   {"/Users/and/Downloads/Verpackungsplan/verpack.txt"};
//const char * data_file      =           {"/Users/and/Downloads/Verpackungsplan/data.txt"};
//const char* RTF_template_file        {"/Users/and/Downloads/Verpackungsplan/template.rtf"};
//const char* RTF_out_file                {"/Users/and/Downloads/Verpackungsplan/OUT.rtf"};

const char * files [] {
    "/verpack.txt",
    "/data.txt",
    "/template.rtf",
    "/OUT.rtf"
};



int main(int argc, const char * argv[]) {
    
    const string current_path  { fs::current_path().string()};
    
    string  verpackungsplan_file_s{current_path.data()};
    verpackungsplan_file_s.append(files[0]);
    const char * verpackungsplan_file {  verpackungsplan_file_s.c_str() } ;

    string  data_file_s{current_path.data()};
    data_file_s.append(files[1]);
    const char * data_file {  data_file_s.c_str() } ;
   
    string  RTF_template_file_s{current_path.data()};
    RTF_template_file_s.append(files[2]);
    const char * RTF_template_file {  RTF_template_file_s.c_str() } ;
    
    string  RTF_out_file_s{current_path.data()};
    RTF_out_file_s.append(files[3]);
    const char * RTF_out_file {  RTF_out_file_s.c_str() } ;
    
  

    
    
   
    
    try {

        
            const std::filesystem::path dir{verpackungsplan_file};
            if (!exists(dir)) {
                std::printf("Can'n open the verpack.txt file.\n\n");
                return 1;
            }

           
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
                               "([0-9]*[.])?[0-9]+" ) };
        
        
        elements_selection dumpf{verpak, data};
        dumpf.read_write_RTF(RTF_template_file, RTF_out_file);
    } catch (exception ex) {
        std::printf("\n something didn't go as planned!\n") ;
        return 1;
    }

        
    std::printf("\n OK!\n") ;
    return 0;
}

