//
// Created by zz23ecl on 22-7-23.
//

#include "Control.h"
#include "data.h"

int initial_memory() {
    int i = shmget(4600, 1024, 0666|IPC_CREAT);;
    if(i == 0) {
        cout<< "error"<< endl;
        return 0;
    }
    void* addr = NULL;
    addr = shmat(i, (void *)0, 0);
    pStatus_feature = (Features*)addr;
    memset(pStatus_feature, 0, sizeof(Features));

    return 1;
}


void Control::MotorEnable() {
    FH.writeControlWord(controlw,0x06);
    FTDI.write(controlw,8);
    FH.writeControlWord(controlw,0x07);
    FTDI.write(controlw,8);
    FH.writeControlWord(controlw,0x0F);
    FTDI.write(controlw,8);
}

void Control::MotorDisable() {
    FH.writeControlWord(controlw,0x0D);
    FTDI.write(controlw,8);
}

void Control::OpenSerial() {
    FTDI.open(0x403,0x6001);
    FTDI.set_line_property(BITS_8,STOP_BIT_1,NONE);
    FTDI.set_baud_rate(115200);
    initial_memory();
}

void Control::MotorInit() {
    //Set PV Mode
    FH.writeOperationMode(setMode,0x02);
    FTDI.write(setMode,10);
}

void Control::PDcontrol() {
    int TargetPos;
    while(PDflag){
//        Speed=PD.getOutput(FH.getPosData(),TargetPos);
        pStatus_feature->data2 = 0;
//        cout<<"in PD Control speed:"<<Speed<<endl;
//        printf("now PDout is %d\n",Speed);
//        printf(" AND the demand pos is %d\n",TargetPos);
//        printf(" AND the actual pos is %d\n",ActualPos);
        TargetPos=pStatus_feature->data3;
//        FH.getData(data,Speed,1);
        cout<<"now target pos is:"<<TargetPos<<endl;
        FH.getData(data,TargetPos,2);
        FTDI.write(data,13);
        this_thread::sleep_for(chrono::milliseconds(5));

    }
}

void Control::StartC() {
    PDflag=true;
    thread PDC(&Control::PDcontrol,this);
    PDC.detach();
}

void Control::OpenListen() {
    while(ListenFlag){
        //auto starttime = chrono::system_clock::now();
        FH.setPosRequest(PosRequest);
        FTDI.write(PosRequest,13);
        //this_thread::sleep_for(chrono::milliseconds (1));
//        for(int i=0;i<20;i++){
//            printf("%x,",readbuffer[i]);
//        }
//        cout<<endl;
//        cout<<"----------------"<<endl;
        FTDI.read(readbuffer,5);
        FH.BufferPush(readbuffer);
//        FH.BufferPush(readData);
//        for(int i=0;i<20;i++){
//            printf("%x,",readbuffer[i]);
//        }
//        cout<<endl;
        //     printf("in L APOS is %d\n",ActualPos);
        this_thread::sleep_for(chrono::milliseconds(2));
       // chrono::duration<double> diff = chrono::system_clock::now()-starttime;
        //cout<<"time is :"<<diff.count()<<"s"<<endl;
    }
}

void Control::getQueueData(){
    bool MotorFlag1= false;
    int MotorFlag2=0;
    while(ListenFlag){

        FH.DealQueue();
        MotorFlag2=pStatus_feature->data4;
        //printf("dealing with the Queue...\n");
//        printf("Actual Pos is %d...\n",FH.getPosData());
        pStatus_feature->data1 = FH.getPosData();
        if(!MotorFlag1&&(MotorFlag2==1)){
            MotorEnable();
            MotorFlag1= true;
        }
        if(MotorFlag1&&(MotorFlag2==0)){
            MotorDisable();
            MotorFlag1= false;
        }
        this_thread::sleep_for(chrono::milliseconds(2));
    }
}

void Control::OpenL(){
    ListenFlag=true;
    thread SL(&Control::OpenListen,this);
    thread DL(&Control::getQueueData,this);
    SL.detach();
    DL.detach();
}


bool Control::setP(float PP) {
    PD.setP(PP);
    return 1;
}

bool Control::setD(float DD) {
    PD.setD(DD);
    return 1;
}

float Control::getP(void) {
    return PD.getP();
}

float Control::getD(void) {
    return PD.getD();
}

bool Control::setPos(int Pos) {
    TargetPos=Pos;
    return 1;
}

bool Control::setFlag(bool Pflag, bool Lflag) {
    PDflag=Pflag;
    ListenFlag=Lflag;
    return 1;
}

int Control::getPos(void) {
    return FH.getPosData();
}

int Control::getSpeed(void) {
    return Speed;
}

int Control::getASpeed(void) {
    return actualspeed;
}

void Control::parameterInit(void){
    PD.setPID(0.011,0);
    PD.setOutputLimits(32700);
}



