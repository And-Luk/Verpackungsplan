//
//  main.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 2025-03-25.

#include "functions.h"
#include "elements_selection.h"
namespace fs = std::filesystem;

//#include <chrono>
//#include <ctime>

//namespace chrono = std::chrono;
//using namespace std::chrono_literals;


//const char * verpackungsplan_file   {"pwd ./verpack.txt"};    "C:\\Users\\lager\\Documents\\And\\Verpackungsplan\\verpack.txt"
//const char * data_file                      {"pwd ./data.txt"};           "C:\\Users\\lager\\Documents\\And\\Verpackungsplan\\data.txt"
//const char* RTF_template_file        {"pwd ./template.rtf"};     "C:\\Users\\lager\\Documents\\And\\Verpackungsplan\\RTF_in.rtf"
//const char* RTF_out_file                {"pwd ./OUT.rtf"};            "C:\\Users\\lager\\Documents\\And\\Verpackungsplan\\RTF_out.rtf"
//const char* RTF_END_in_file         {"pwd ./END_of.rtf"};

//const char * parameter_names [] {
//    "verpackungsplan_file",
//    "data_file",
//    "RTF_template_file",
//    "RTF_out_file",
//    "RTF_END_in_file"
//};


const char * files [] {
    "verpack.txt",
    "data.txt",
    "template.rtf",
    "OUT.rtf",
    "End_of.txt",
    "/"
};

//template <typename Clock, typename Duration>
//std::ostream& operator << ( std::ostream& outs, const std::chrono::time_point <Clock, Duration> & dt )
//{
//  char s[200];
//  auto t = Clock::to_time_t( dt );
//  std::strftime( s, sizeof(s), "%c", std::localtime( &t ) );
//  return outs << s;
//}


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
    








//  std::chrono::time_point today = std::chrono::system_clock::now();
//  std::cout << "Today is " << today.time_since_epoch() << "\n";
    
    
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%d-%m-%Y    %T",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
    
    std::printf("%s",buffer);
    //std::puts(buffer);
    
    
//  auto tomorrow = today + 24h;
//  std::cout << "Tomorrow is " << tomorrow << "\n";
//  
//  auto day_after = today + 24h * 2;
//  std::cout << "The day after that is " << day_after << "\n";

    
    
//    "\033[31m"
//    "\033[32m"
//    "\033[33m"
//    "\033[34m"
//    "\033[35m"
//    "\033[36m"
//    const std: string reset {"\033[0m"};
    
    
   
    
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
        dumpf.read_write_RTF(RTF_template_file, RTF_out_file, RTF_END_in_file);
    } catch (exception ex) {
        std::printf("\n something didn't go as planned!\n") ;
        return 1;
    }

    cout<<"\033[32m"<<endl;
    std::printf("\n OK!\n") ;
    return 0;
}

