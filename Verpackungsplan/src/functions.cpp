//
//  functions.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 10-04-2025.
//
#include "functions.h"



void* operator new (size_t allocate){
//    static size_t memory {0};
//    memory +=allocate;
//    std::cout<<" allocate "<< memory << "   bytes memory \n";
    Statistics* Stat = Statistics::getInstance();
    Stat->setStatistics(allocate);
    return malloc(allocate);
}

void write_RTF(const path & path_to, const ostringstream & ostring_out ){
    ofstream out_RTF{path_to.c_str()};
    if (!exists(path_to)) {
        std::printf("An Error with path to Verpackungsplan.rtf .\n\n");
        throw std::exception().what();
    }
    out_RTF<<ostring_out.str();
    out_RTF.close();
}

auto find_the_desired_string (const string & str_in, const char* reg_expr = "")-> bool{
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    if (regex_search(str_in,reg)) {
        return true;
    }
    return false;
}

auto find_and_replace (const string & str_in, const char* reg_expr= "", const string replacement= "")-> string{
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
    return regex_replace(str_in, reg,  replacement );  //replacement
    
}

bool find_and_change( string &str_in , const char* pattern, const char* replacement) {
    if (find_the_desired_string(str_in,pattern)) {
        str_in = find_and_replace(str_in, pattern, replacement );
        return true;
    }
    return false;
}


auto read_verpack_txt(const path & path_to, const char* reg_expr_1 = "" , const char* reg_expr_2 = "", const char* reg_expr_3= "")-> vector_of_pair_size_t{
    ifstream ifstrm{path_to.c_str()};
    vector_of_pair_size_t data;
    string str_in, str_temp, str_suffix;
    smatch result;
    pair<size_t, size_t> temp_pair;
    regex reg_1{reg_expr_1,std::regex_constants::ECMAScript | std::regex_constants::icase};
    regex reg_2{reg_expr_2,std::regex_constants::ECMAScript | std::regex_constants::icase};
    regex reg_3{reg_expr_3,std::regex_constants::ECMAScript | std::regex_constants::icase};

    for (;getline(ifstrm, str_in);) {
        if (regex_search(str_in, result, reg_1)) {
            str_temp = result.str();
            str_temp = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            temp_pair.first = std::stoi( str_temp);
            temp_pair.second = 1;           //1
            str_suffix =result.suffix();
            if (regex_search(str_suffix, result, reg_2)) {
                str_temp =result.suffix();

                if (regex_search(str_temp, result, reg_3)) {
                    //str_temp.clear();
                    str_temp = result.str();
                    temp_pair.second = (size_t)std::stoi( str_temp);
                    //data.emplace_back(temp_pair);
                    data.insert(data.end(), temp_pair);
                    continue;
                    }
            }
                temp_pair.second = 1;       //1
                data.emplace_back(temp_pair);
                continue;
        }
    }

    return data;
}

auto substring_verpack_txt(const string & source, const char* reg_expr= "")-> deque<size_t>{
    
    string str_in,str_temp;
    smatch result;
    deque<size_t> data;
    
    regex reg{reg_expr,std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_in,result,reg)) {
            str_temp = result.str();
            str_in = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            str_temp =result.suffix();
            data.emplace_back(std::stoi(str_temp) );
        }
    return data;
}

auto read_data_txt(const path & path_to, const char* reg_expr_1 = "", const char* reg_expr_2 = "" , const char* reg_expr_3 = "")-> multimap_data*{
    ifstream ifstrm{path_to.c_str()};
    string str_all,str_temp, str_old;
    smatch result;
    tup_element tuple_temp;
    multimap_data* data =new multimap_data;
    
    for (;getline(ifstrm, str_all);) {
        regex reg{reg_expr_1, std::regex_constants::ECMAScript | std::regex_constants::icase};
        if (regex_search(str_all,result,reg)) {
            str_temp = result.str();
            str_temp = str_temp.erase(6, str_temp.length());  // shrink to 6 digits
            get<1>(tuple_temp)= 0;  // ???
            
            if (str_temp[0]=='9' ) {
                str_old = str_temp;
                tuple_temp = substring(result.suffix(), reg_expr_2 , reg_expr_3);
                data->insert( {(size_t)stoi(str_old), tuple_temp} );
                continue;
            }
            
            if (str_temp[0]=='5' ) {
                tuple_temp = substring(str_all, reg_expr_2 , reg_expr_3);
                get<0>(tuple_temp)= stoi(str_temp);
                data->insert({(size_t)stoi(str_old), tuple_temp});
            }
        }
    }
    //return std::move (data);
    return std::move(data);
}

auto substring (const string & source, const char* reg_expr_1 = "" , const char* reg_expr_2 = "")-> tup_element{
    
    tup_element tuple_temp;
    smatch result;
    string str_temp, str_suffix , str_suffix_2;
    size_t shrink=0;
    float float_temp{0.0};
   
    regex reg_1{reg_expr_1,std::regex_constants::ECMAScript | std::regex_constants::icase};
    regex reg_2{reg_expr_2,std::regex_constants::ECMAScript | std::regex_constants::icase}; // "[[:digit:]]+"
      

    if (regex_search(source, result, reg_1)) {
        str_temp = result.str();
        
        str_temp.erase(6, str_temp.length());  // shrink to 6 digits
        get<0>(tuple_temp)= stoi(str_temp);
        str_suffix =result.suffix();
        str_suffix_2 = str_suffix;
        
        shrink= str_suffix.find('=');
       str_suffix.erase(shrink, str_suffix.length());
       str_suffix_2 = str_suffix_2.substr(shrink); // exeption
       get<2>(tuple_temp)= str_suffix;

        if (regex_search( str_suffix_2, result, reg_2)) {
            str_temp = result.str();
            std::replace(str_temp.begin(), str_temp.end(), ',', '.');
            float_temp = (float)std::stof( str_temp);
            get<1>(tuple_temp)= float_temp;
        }else  get<1>(tuple_temp)=1;

        return tuple_temp;
    }

    return tup_element{0, float_temp, "substring does not exist"};  
}


void umlauts (vector<pair<size_t, std::tuple<size_t, int, string >>> & internal_data ){
    string str;
    stringstream strout;
    for (auto & element : internal_data) {
        str = {};
        str = get<2>(element.second);
        for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
            
            if ((*it)=='\xc3') {  continue;  }
            
            switch ((*it)) {
                case '\x84':  strout<<"\\uc1\\u196\\0";  continue;      //  Ä
                case '\x96':  strout<<"\\uc1\\u214\\0";   continue;     //  Ö
                case '\x9c':  strout<<"\\uc1\\u220\\0";   continue;     //  Ü
                case '\xa4':  strout<<"\\uc1\\u228\\0";   continue;      // ä
                case '\xb6':  strout<<"\\uc1\\u246\\0";   continue;     //  ö
                case '\xbc':  strout<<"\\uc1\\u252\\0";  continue;      //  ü
                case '\x9f':  strout<<"\\uc1\\u223\\0";   continue;     //  ß
                default:    strout<<*it;    continue;
            }
        }
        get<2>(element.second)=strout.str();
        strout.str("");
    }
}

char* getFileHASH(const path & path_to_file){
    struct stat fileInfo;
    stat( path_to_file.c_str() , &fileInfo);
    unsigned long fileSize =  fileInfo.st_size;
    
    char* HASH = new char;
    std::strcat(HASH, to_string( fileSize).c_str());
       
    fileSize = fileInfo.st_ino;
    std::strcat(HASH, to_string( fileSize).c_str());

    fileSize = fileInfo.st_mtimespec.tv_nsec;
    std::strcat(HASH, to_string( fileSize).c_str());
    
    return std::move ( HASH );
}

char* printTIME(){
    
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer,80,"%d-%m-%Y    %H:%M:%S",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
    std::printf("TIME is : %s\n", buffer );
    //std::puts(buffer);


    ////  auto tomorrow = today + 24h;
    ////  std::cout << "Tomorrow is " << tomorrow << "\n";
    ////
    ////  auto day_after = today + 24h * 2;
    ////  std::cout << "The day after that is " << day_after << "\n";

    ////    "\033[30m"   black
    ////    "\033[31m"   rot
    ////    "\033[32m"  green
    ////    "\033[33m"  light green
    ////    "\033[34m"  pourpur
    ////    "\033[35m"  lila
    ////    "\033[36m"
    ////    const std: string reset {"\033[0m"};
    
    
    
    char* time = new char[80];
    std::strcpy(time, buffer);
    
    return std::move( time );
}
