//
// Created by graphite on 22-9-8.
//

#ifndef CPPSENT_DATA_H
#define CPPSENT_DATA_H



#include <iostream>
#include "shrmm.hpp"

using namespace std;

int initial_memory();

typedef struct Features {
    int data1;//actual pos
    int data2;//speed
    int data3;//target pos
    int data4;//motor flag
}Features;

Memory m_sh_cmd_features;
Features *pStatus_feature;


// share_memory m_sh_cmd_feature;




#endif //CPPSENT_DATA_H
