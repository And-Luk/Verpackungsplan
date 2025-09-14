//
//  write_Excel_file.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 07-09-2025.
//
#include "write_Excel_file.h"
int write_Exel()
{
    Book* book = xlCreateBook();
    if(book)
    {
        Sheet* sheet = book->addSheet("Sheet1");
        if(sheet)
        {
            sheet->writeStr(5, 2, "5, 2 test            how long");
            sheet->writeStr(1, 1, "Halo");
            sheet->writeStr(2, 1, "Hello, World !");
            sheet->writeNum(3, 1, 1000);
            
            Format* dateFormat = book->addFormat();
            dateFormat->setNumFormat(NUMFORMAT_DATE);
            sheet->writeNum(4, 1, book->datePack(2025, 9, 7), dateFormat);
            
            sheet->setCol(1, 1, 12);
        }

        if(book->save("example.xls")) {
            std::cout << "File example.xls has been created." << std::endl;
        }
        book->release();
    }

    return 0;
}
