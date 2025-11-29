//
//  statistics.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 24-09-2025.
//

#include "statistics.h"

Statistics::Statistics():memory(0){} //:memory{0}
Statistics::~Statistics(){}

Statistics* Statistics::getInstance(){
    static Statistics Stat;
    return  &Stat;
}

size_t Statistics::getStatistics(){return memory;}

void Statistics::setStatistics(size_t value){memory+=value;}
void Statistics::cutStatistics(size_t value){memory-=value;}

