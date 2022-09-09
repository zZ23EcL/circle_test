#include "Control.h"
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "ftdi.hpp"
void Delay(int time)
{
    clock_t  now = clock();
    while(clock() - now < time);
}



int main()
{
//    RS232 FH;
//    unsigned char word[13];
//    FH.getData(word,1000,1);
//    string Buffer(word,word+13);
//    cout<<Buffer<<endl;
//    cout<<"-----------"<<endl;
//    auto j =Buffer.begin();
//    while(j!=Buffer.end()){
//        printf("%x\n",uint8_t (*j));
//        j++;
//    }
//    FH.BufferPush(Buffer);
//    cout<<"----------"<<endl;
//    FH.DealQueue();

    Control C;
    unsigned char d[13];
    C.OpenSerial();
    C.parameterInit();
    C.MotorInit();
    C.setPos(0);
//    printf("start.....\n");
//    C.MotorEnable();
//    sleep(1);
//    C.FH.getData(d,1000,1);
//    printf("write Speed........\n");
//    cout<<C.FTDI.write(d,13)<<endl;
//    sleep(3);
//    C.FH.getData(d,0,1);
//    C.FTDI.write(d,13);
//    C.MotorDisable();
    C.OpenL();
    C.StartC();
//    for (int i=0;i<20;i++){
//        C.setPos(i*10000);
//        sleep(1);
//    }
    getchar();

//    C.MotorDisable();
//    unsigned char controlw[8];





    return 0;
}
