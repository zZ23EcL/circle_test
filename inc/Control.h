#ifndef FH_MOTOR_LIBRARY_H
#define FH_MOTOR_LIBRARY_H

#include "RS232.h"
#include <thread>
#include "MiniPID.h"
#include "ftdi.hpp"


using namespace std;



class Control {
public:
    Control(){}

    ~Control(){}

public:
    void MotorEnable(void);
    void MotorDisable(void);
    void OpenSerial(void);
    void MotorInit(void);
    void PDcontrol();
    void StartC(void);
    void OpenListen(void);
    void OpenL(void);
    bool setP(float);
    bool setD(float);
    float getP(void);
    float getD(void);
    bool setPos(int);
    bool setFlag(bool,bool);
    int getPos(void);
    int getSpeed(void);
    void parameterInit(void);
    int getASpeed(void);
    void getQueueData(void);
    RS232 FH;
    Ftdi::Context FTDI;

private:


    MiniPID PD;
    unsigned char controlw[8];
    unsigned char setMode[10];
    unsigned char data[13];
    unsigned char PosRequest[13];
    unsigned char readbuffer[5];
    bool PDflag;
    bool ListenFlag;
    int ActualPos;
    int TargetPos;
    int Speed;
    int actualspeed;
};


#endif //FH_MOTOR_LIBRARY_H
