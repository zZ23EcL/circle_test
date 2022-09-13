//
// Created by graphite on 22-9-5.
//
//
// Created by zz23ecl on 22-7-23.
//
#include "RS232.h"

//CRC cal
uint8_t RS232::CalcCRCByte(uint8_t u8Byte, uint8_t u8CRC) {
    uint8_t i;
    u8CRC = u8CRC ^ u8Byte;
    for (i = 0; i <8 ; i++) {
        if (u8CRC & 0x01) {
            u8CRC = (u8CRC >> 1) ^ 0xD5;
        }
        else {
            u8CRC >>= 1;
        }
    }
    return u8CRC;
}

//写控制字
void RS232::writeControlWord(uint8_t temp[], uint8_t ctrlwlb) {
    temp[0] = 'S';
    temp[1] = 0x06;
    temp[2] = 0x01;
    temp[3] = 0x04;
    temp[4] = ctrlwlb;
    temp[5] = 0x00;
    uint8_t CRC = 0xFF;
    for (uint8_t i = 1; i <6; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[6] = CRC;
    temp[7] = 'E';
}

//写控制模式
void RS232::writeOperationMode(uint8_t temp[],uint8_t type){
    uint8_t length = 0x08;
    temp[0] = 'S';
    temp[1] = 0x08;
    temp[2] = 0x01;
    temp[3] = 0x02;
    temp[4] = 0x60;
    temp[5] = 0x60;
    temp[6] = 0x00;
    if(type==1)
        temp[7]=0x01;//pv
    if(type==3)
        temp[7] =0X03;//pp
    if(type==0)
        temp[7]=0x09;//csv
    if(type==2)
        temp[7]=0x08;//csp
    if(type==4)
        temp[7]=0xfe;//apc
    if(type==5)
        temp[7]=0xfd;//avc
    uint8_t CRC = 0xFF;
    for (uint8_t i = 1; i <length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[8] =CRC;
    temp[9]='E';
}
//写目标数据
void RS232::getData(uint8_t temp[], int32_t data, uint8_t type) {
    uint8_t length = 0x0b;
    uint8_t command = 0x02;
    uint8_t NodeNum = 0x01;
    uint8_t indexHB;
    uint8_t indexLB;
    switch (type) {
        //速度
        case 1: {
            indexLB = 0xFF;
            indexHB = 0x60;
            break;
        }
            //位置
        case 2: {
            indexLB = 0x7A;
            indexHB = 0x60;
            break;
        }
        default: {
            printf("Erorr Data Type!");
            break;
        }
    }

    temp[0] = 'S';
    temp[1] = length;
    temp[2] = NodeNum;
    temp[3] = command;
    temp[4] = indexLB;
    temp[5] = indexHB;
    temp[6] = 0x00;//subindex
    /********************************************/
    /*  这里有个问题是写入数据是按低位写还是高位优先写？ */
    /*               问题解决，按低位写            */
    /********************************************/
    //先按照低位先的来
    temp[7] = data & 0xff;
    temp[8] = data >> 8 & 0xff;
    temp[9] = data >> 16 & 0xff;
    temp[10] = data >> 24 & 0xff;
    uint8_t CRC = 0xFF;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11] = CRC;
    temp[12] = 'E';
}

void RS232::wrtieSource(uint8_t temp[],uint16_t source,uint8_t type){
    uint8_t length = 0x0b;
    uint8_t command = 0x02;
    uint8_t NodeNum = 0x01;
    uint8_t indexHB;
    uint8_t indexLB;
    indexLB = source&0xFF;
    indexHB = source>>8&0xFF;
    uint8_t subindex;
    switch (type) {
        //速度
        case 1: {

            break;
        }
            //位置
        case 2: {
            indexLB = 0x7A;
            indexHB = 0x60;
            break;
        }
        default: {
            printf("Erorr Data Type!");
            break;
        }
    }

    temp[0] = 'S';
    temp[1] = length;
    temp[2] = NodeNum;
    temp[3] = command;
    temp[4] = indexLB;
    temp[5] = indexHB;
    temp[6] = 0x00;//subindex
    /********************************************/
    /*  这里有个问题是写入数据是按低位写还是高位优先写？ */
    /*               问题解决，按低位写            */
    /********************************************/
    //先按照低位先的来

    uint8_t CRC = 0xFF;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11] = CRC;
    temp[12] = 'E';

}

void RS232::writeVirtualAnalogData(uint8_t temp[],int16_t data){
    uint8_t length=0x09;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x13;
    uint8_t indexHB=0x23;
    uint8_t subindex=0x09;// use anln1 if anln2 0x19
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    temp[6]=subindex;
    temp[7]=data&0xff;
    temp[8]=data>>8&0xff;
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[9]=CRC;
    temp[10]='E';
}

void RS232::writeVirtualAnalogEnable(uint8_t temp[],uint8_t type){
    uint8_t length=0x08;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x13;
    uint8_t indexHB=0x23;
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    if(type==1)
        temp[6]=0x0A;//Anln1
    if(type==2)
        temp[6]=0x1A;//Anln2
    temp[7]=0x01;//enable
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[8]=CRC;
    temp[9]='E';
}

void RS232::writeTargetSource(uint8_t temp[],uint8_t type){
    uint8_t length=0x08;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x31;
    uint8_t indexHB=0x23;
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    if(type==1)
        temp[6]=0x03;//speed
    if(type==2)
        temp[6]=0x04;//pos
    temp[7]=0x01;//analog1  if use analog2 set 0x02
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[8]=CRC;
    temp[9]='E';
}

void RS232::writeTargetSourcePropotion(uint8_t temp[],int32_t p){
    uint8_t length=0x0b;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x16;
    uint8_t indexHB=0x23;
    uint8_t subindex=0x04;
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    temp[6]=subindex;//0x01 anln1 Gain if use anln2 Gain 0x11
    temp[7]=p&0xff;
    temp[8]=p>>8&0xff;
    temp[9]=p>>16&0xff;
    temp[10]=p>>24&0xff;
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11]=CRC;
    temp[12]='E';
}
void RS232::writeAnalogPropotion(uint8_t temp[],int32_t p){
    uint8_t length=0x0b;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x13;
    uint8_t indexHB=0x23;
    uint8_t subindex=0x01;
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    temp[6]=subindex;//0x01 anln1 Gain if use anln2 Gain 0x11
    temp[7]=p&0xff;
    temp[8]=p>>8&0xff;
    temp[9]=p>>16&0xff;
    temp[10]=p>>24&0xff;
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11]=CRC;
    temp[12]='E';
}
void RS232::setReductionRadio(uint8_t temp[],uint8_t type,uint32_t data){
    uint8_t length=0x0b;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x91;
    uint8_t indexHB=0x60;
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    if(type==1)
        temp[6]=0x01;//motor
    if(type==2)
        temp[6]=0x02;//gear radio
    temp[7]=data&0xff;
    temp[8]=data>>8&0xff;
    temp[9]=data>>16&0xff;
    temp[10]=data>>24&0xff;
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11]=CRC;
    temp[12]='E';
}
void RS232::writeAnalogOffset(uint8_t temp[],int16_t offset){
    uint8_t length=0x09;
    uint8_t command=0x02;
    uint8_t node=0x01;
    uint8_t indexLB=0x13;
    uint8_t indexHB=0x23;
    uint8_t subindex=0x02;//set anln1 offset ,if use anln2 offset 0x12
    temp[0]='S';
    temp[1]=length;
    temp[2]=node;
    temp[3]=command;
    temp[4]=indexLB;
    temp[5]=indexHB;
    temp[6]=subindex;
    temp[7]=offset&0xff;
    temp[8]=offset>>8&0xff;
    uint8_t CRC=0xff;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[9]=CRC;
    temp[10]='E';
}

int RS232::getActualPos(string& str) {
    int v = 999999999;
    if(str.length()==13){
        auto i=str.begin();
        uint8_t length = uint8_t(*(i+1));
        uint8_t node = uint8_t(*(i+2));
        uint8_t command = uint8_t(*(i+3));
        uint8_t indexLB=uint8_t(*(i+4));
        uint8_t indexHB=uint8_t(*(i+5));
        uint16_t index=indexLB+(indexHB<<8);
        uint8_t subindex=uint8_t(*(i+6));
        if(index==0x6064)
            v=uint8_t(*(i+7))+(uint8_t(*(i+8))<<8)+(uint8_t(*(i+9))<<16)+(uint8_t(*(i+10))<<24);
    }
    return v;
}

int RS232::getActualSpeed(string& str) {
    int v = 999999999;
    if(str.length()==13){
        auto i=str.begin();
        uint8_t length = uint8_t(*(i+1));
        uint8_t node = uint8_t(*(i+2));
        uint8_t command = uint8_t(*(i+3));
        uint8_t indexLB=uint8_t(*(i+4));
        uint8_t indexHB=uint8_t(*(i+5));
        uint16_t index=indexLB+(indexHB<<8);
        uint8_t subindex=uint8_t(*(i+6));
        if(index==0x60FF)
            v=uint8_t(*(i+7))+(uint8_t(*(i+8))<<8)+(uint8_t(*(i+9))<<16)+(uint8_t(*(i+10))<<24);
    }
    return v;
}

void RS232::dealRXbuf(string& s,int& pos,int& spd){
    string RXbuf;
    int numS;
    int numE;
    bool search(true);
    while(search){
        numS=s.find_first_of('S');
        numE=s.find_first_of('E');
        if(0<=numS&&numS<=s.size()&&0<=numE&&numE<=s.size()){
            for(int i=0;i<6;i++){
                //6的原因是最多int 4个 加CRC+E=6，其实不可能int4个0x45时的CRC是45
                string buf(s,numS,numE+1);
                if(uint8_t(buf[1])==numE-numS-1){
                    RXbuf=buf;
                    int datatemp=getActualPos(RXbuf);
                    int datatemp2=getActualSpeed(RXbuf);
                    if(datatemp!=999999999)
                        pos=datatemp;
                    if(datatemp2!=999999999)
                        spd=datatemp2;
                    s.erase(numS,numE-numS+1);
                    break;
                }
                else{
                    numE=s.find_first_of('E',numE+1);
                }
            }
        }
        else
            search= false;
    }
}

void RS232::setPosRequest(uint8_t temp[]){
    temp[0]='S';
    temp[1]=0x07;
    temp[2]=0x01;
    temp[3]=0x01;
    temp[4]=0x64;
    temp[5]=0x60;
    temp[6]=0x00;
    uint8_t CRC = 0xFF;
    for (int i = 1; i < 7; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[7]=CRC;
    temp[8]='E';
}

void RS232::setSpeedRequest(uint8_t temp[]){
    temp[0]='S';
    temp[1]=0x07;
    temp[2]=0x01;
    temp[3]=0x01;
    temp[4]=0x6C;
    temp[5]=0x60;
    temp[6]=0x00;
    uint8_t CRC = 0xFF;
    for (int i = 1; i < 7; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[7]=CRC;
    temp[8]='E';
}
void RS232::BufferPush(std::string & str) {
    auto it=str.begin();
    while(it!=str.end()){
        if(!Q.isFull())
            Q.push(uint8_t(*it));
        it++;
    }
}
void RS232::BufferPush(unsigned char temp[]) {
    for(int i=0;i<5;i++){
        if(!Q.isFull())
            Q.push(temp[i]);
    }
}

void RS232::DealQueue(void){
    int data=0;
    uint8_t d[4];
    uint8_t pop_num=0;
    uint8_t length=0;
    uint8_t n=0;
    uint8_t QueueStatu=0;
    uint8_t speedORpos=0;
    while(!Q.isEmpty()){
        switch (QueueStatu){
            case 0:{
                if(Q.top()==0x53){
                    QueueStatu=1;
                    n=0;
//                    printf("go to state 1..\n");
                }
                break;
            }
            case 1:{
                n=0;
                length=Q.top();
//                printf("buffer length is %d...\n",length);
                if(!Q.isEmpty()){
                    Q.pop();//remove length
                    pop_num++;
                }
                if(Q.top()==0x01){
                    QueueStatu=2;
                    n=0;
//                    printf("go to state 2..\n");
                }
                break;
            }
            case 2:{
                if(Q.top()==0x64){
                    if(!Q.isEmpty()){
                        Q.pop();//remove indexLB
                        pop_num++;
                        speedORpos=1;//pos
                    }
                    if(Q.top()==0x60){
                        QueueStatu=3;
                        n=0;
//                        printf("go to state 3 pos..\n");
                    }
                }
                else if(Q.top()==0x6C){
                    if(!Q.isEmpty()){
                        Q.pop();//remove indexLB
                        pop_num++;
                        speedORpos=2;//speed
                    }
                    if(Q.top()==0x60){
                        QueueStatu=3;
                        n=0;
//                        printf("go to state 3 speed..\n");
                    }
                }
                break;
            }
            case 3:{
                if(!Q.isEmpty()){
                    Q.pop();//remove subindex
                    pop_num++;
                }
                if(!Q.isEmpty()){
                    d[0]=Q.top();
                    Q.pop();//remove d0
                    pop_num++;
                }
                if(!Q.isEmpty()){
                    d[1]=Q.top();
                    Q.pop();//remove d1
                    pop_num++;
                }
                if(!Q.isEmpty()){
                    d[2]=Q.top();
                    Q.pop();//remove d2
                    pop_num++;
                }
                if(!Q.isEmpty()){
                    d[3]=Q.top();
                }
                data=(d[3]<<24)+(d[2]<<16)+(d[1]<<8)+d[0];
                //printf("data is:%d\n",data);
                QueueStatu=4;
                n=0;
                //printf("go to state 4..\n");
                break;
            }
            case 4:{
                if(!Q.isEmpty()){
                    Q.pop();//remove CRC
                    pop_num++;
//                    printf("remove CRC..\n");
//                    printf("%x\n",Q.top());
                }
                if(Q.top()==0x45)
                {
                    QueueStatu=5;
                    if(speedORpos==1)
                        PosData=data;
                    if(speedORpos==2){
                        SpeedData=data;
//                        printf("speed is : %d\n",SpeedData);
                    }

                }
                break;
            }
        }
        if(n>2){
//            printf("error buffer ,check again...\n");
            QueueStatu=0;
            n=0;
            pop_num=0;
            data=0;
            speedORpos=0;
        }
        if(QueueStatu==5){
            Q.pop();
            QueueStatu=0;
            pop_num=0;
            n=0;
            speedORpos=0;
        }
        else{
            Q.pop();
            pop_num++;
            n++;
        }
    }
}

int RS232::getPosData(void) {
    return PosData;
}
int RS232::getSpeedData(void) {
    return SpeedData;
}
