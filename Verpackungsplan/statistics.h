//
//  statistics.h
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 24-09-2025.
//

#pragma once

#include "header.h"
//#include <sys/stat.h>


class Statistics {
private:
    Statistics();
    ~Statistics();
    size_t memory;
    
public:
    static Statistics* getInstance();
    size_t getStatistics();
    void setStatistics(size_t value);
    Statistics(const Statistics&) = delete;
    Statistics& operator=(const Statistics&) = delete;
};
//size_t Statistics::memory {0};
