//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.


#include "functions.h"
#include "elements_selection.h"

int main(int argc, const char * argv[]) {
    
    vector_of_pair_size_t verpak{
        read_verpack_txt("/Users/and/Downloads/Verpackungsplan/verpack.txt",
                         "9\\d{5}[^(\\d|:alpha:)]",
                         "Tage[^:alpha:]",
                         "[[:digit:]]+")};
    
    multimap_data data{
        read_data_txt( "/Users/and/Downloads/Verpackungsplan/data.txt",
                           "(5|9)\\d{5}[^(\\d|[:alpha:]|)](\"|[[:space:]])*" ,
                           "5\\d{5}[^(\\d|[:alpha:]|)](\")*([[:space:]])*(\\:)*([[:space:]])*",
                           "([0-9]*[.])?[0-9]+" ) };  
    
    
    elements_selection dumpf{verpak, data};
    
        dumpf.new_read_write_RTF("/Users/and/Downloads/Verpackungsplan/RTF_in.rtf",
                             "/Users/and/Downloads/Verpackungsplan/RTF_out.rtf");
    
    
    std::printf("\n OK!\n") ;
    return 0;
}

//________________________________________________________________________________________________________

//    if (argc<=2) {
//        std::cout<< "Usage:"<<argv[0]<<"<path>\n";
//        std::printf("Usage: %s <path>\n", argv[0]);
//        return 1;
//    }
//    const std::filesystem::path dir{argv[1]};
//    if (!exists(dir)) {
//        std::printf("Path dose not exist.\n\n");
//        return 1;
//    }




// std::printf("\n %s The Path exist\n\n",canonical(dir).c_str());
// std::printf(" [0] %s\n [1] %s\n [2] %s\n\n",argv[0],argv[1],argv[2]);

//    try {
//        auto data (matches(argv[1], argv[2]));
//        for (const auto &[ID_Operation,result,content]: data) {
//            printf(" [%s]  [%s] -->  %s\n",ID_Operation.c_str(), result.c_str(), content.c_str());
//        }
//    } catch (const regex_error &err) {
//        std::printf("Invalid regular expression provided.\n");
//        return 1;
//    }
    
//    try {
//        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/RTF_in.rtf"};
//        if (!exists(dir)) {
//            std::printf("Can'n open the RTF file.\n\n");
//            return 1;
//        }
//
//        read_write_RTF ("/Users/and/Downloads/Verpackungsplan/RTF_in.rtf", "/Users/and/Downloads/Verpackungsplan/RTF_out.rtf");
//    } catch (std::exception ex){
//        std::printf(" ERROR of writing the out file \n");
//    }
