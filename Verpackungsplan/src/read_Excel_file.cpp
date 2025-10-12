//
//  read_Excel_file.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 28-09-2025.
//
#include "read_Excel_file.h"

int read_Excel(const char* input){
    
    
    
    Book* book = xlCreateBook();
    
    std::wcout <<"\n"<< "in read Excel 2 Book* book = xlCreateBook() "<<std::endl; //delll

    if(book->load("input.xls"))  //load(L"input.xls"))
    {
        std::wcout <<"\n"<< "in read Excel 3 book->load(input) "<<std::endl; //delll
       Sheet* sheet = book->getSheet(0);
       if(sheet)
       {
           std::wcout <<"\n"<< "in read Excel 4 if(sheet)"<<std::endl; //delll
          for(int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
          {
             for(int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
             {
                CellType cellType = sheet->cellType(row, col);
                std::wcout << "(" << row << ", " << col << ") = ";
                if(sheet->isFormula(row, col))
                {
                    const char* s =sheet->readFormula(row, col);   //const wchar_t* s = sheet->readFormula
                   std::wcout << (s ? s : "null") << " [formula]";
                }
                else
                {
                   switch((int)cellType)
                   {
                      case CELLTYPE_EMPTY: std::wcout << "[empty]"; break;
                      case CELLTYPE_NUMBER:
                      {
                         double d = sheet->readNum(row, col);
                         std::wcout << d << " [number]";
                         break;
                      }
                      case CELLTYPE_STRING:
                      {
                         const char* s = sheet->readStr(row, col); //const wchar_t* s = sheet->readStr(row, col);
                         std::wcout << (s ? s : "null") << " [string]"; //std::wwcout << (s ? s : L"null") << " [string]";
                         break;
                      }
                      case CELLTYPE_BOOLEAN:
                      {
                         bool b = sheet->readBool(row, col);
                         std::wcout << (b ? "true" : "false") << " [boolean]";
                         break;
                      }
                      case CELLTYPE_BLANK: std::wcout << "[blank]"; break;
                      case CELLTYPE_ERROR: std::wcout << "[error]"; break;
                   }
                }
                std::wcout << std::endl;
             }
          }
       }
    }

    book->release();
    return 0;
    
}
