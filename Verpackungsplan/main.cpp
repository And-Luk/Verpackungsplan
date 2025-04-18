//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.


#include "functions.h"


int main(int argc, const char * argv[]) {
    
    if (argc<=2) {
        std::cout<< "Usage:"<<argv[0]<<"<path>\n";
        std::printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    const std::filesystem::path dir{argv[1]};
    if (!exists(dir)) {
        std::printf("Path dose not exist.\n\n");
        return 1;
    }
    std::printf("\n %s The Path exist\n\n",canonical(dir).c_str());
    std::printf(" [0] %s\n [1] %s\n [2] %s\n\n",argv[0],argv[1],argv[2]);

//    try {
//        auto data (matches(argv[1], argv[2]));
//        for (const auto &[ID_Operation,result,content]: data) {
//            printf(" [%s]  [%s] -->  %s\n",ID_Operation.c_str(), result.c_str(), content.c_str());
//        }
//    } catch (const regex_error &err) {
//        std::printf("Invalid regular expression provided.\n");
//        return 1;
//    }
    
    try {
        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/RTF_in.rtf"};
        if (!exists(dir)) {
            std::printf("Can'n open the RTF file.\n\n");
            return 1;
        }
        
        read_write_RTF ("/Users/and/Downloads/Verpackungsplan/RTF_in.rtf", "/Users/and/Downloads/Verpackungsplan/RTF_out.rtf");
    } catch (std::exception ex){
        std::printf(" ERROR of writing the out file \n");
    }
    
//    try {
//        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/verpack.txt"};
//        if (!exists(dir)) {
//            std::printf("Can'n open the verpak.txt file.\n\n");
//            return 1;
//        }
//        
//        auto list_of_ID = read_verpack_txt("/Users/and/Downloads/Verpackungsplan/verpack.txt","\\d{6}[^(\\d|:alpha:)]");
//    
//        for (auto & artikel: list_of_ID) {
//            std::printf("   %i\n", (int)artikel);
//        }
//        
//    } catch (std::exception ex) {
//        std::printf(" ERROR of reading the verpack.txt file \n");
//    }
    
    try {
        const std::filesystem::path dir{"/Users/and/Downloads/Verpackungsplan/data_test_1.txt"};
        if (!exists(dir)) {
            std::printf("Can'n open the data_test_1.txt file.\n\n");
            return 1;
        }

        auto list_of_ID = new_read_data_txt("/Users/and/Downloads/Verpackungsplan/data_test_1.txt","(5|9)\\d{5}[^(\\d|[:alpha:]|)](\"|[[:space:]])*");
        
        
        size_t search_element = 955342;
        for (auto it =  list_of_ID.lower_bound(search_element) ; it != list_of_ID.upper_bound(search_element); ++it) {
             std::printf("   [%i]    %i  ->  %s\n", (int)it->first, (int)get<0>((*it).second), (get<2>((*it).second)).c_str() );
//            std::printf("   %i  %i  ->  %s  %i St.\n",
//                        (int)it->first, (int)get<0>((*it).second), (get<2>((*it).second)).c_str(), (int)get<1>((*it).second) );
            }
        
        
        for (auto & it :list_of_ID) {
            std::cout<<(int)get<1>(it.second)<<"\t"<<(int)it.first<<"\t\t"<<(int)get<0>(it.second)<<"\t\t"<<(get<2>(it.second)).c_str()<<"\t\n";
            }
        
    } catch (std::exception ex) {
        std::printf(" ERROR of reading the verpack.txt file to DATA MULTIMAP \n\n");
        std::printf("\n An exception!\n");
    }
    
    
    
    std::printf("\n OK!\n") ;
    return 0;
}

//________________________________________________________________________________________________________

