//
// Created by graphite on 22-9-5.
//

#ifndef CIRCLE_TEST_RS232_H
#define CIRCLE_TEST_RS232_H

#include"circleQueue.h"
#include <iostream>

class RS232{
public:
    RS232(){}
    ~RS232(){}
    uint8_t CalcCRCByte(uint8_t u8Byte,uint8_t u8CRC);
    /** CRC计算
    *
    *
    *  @param:  u8 Byte CRC
    *  @return: u8  CRC
    *  @note:
    *  @see:
    */

    void writeControlWord(uint8_t temp[],uint8_t );
    /*******************************************/
    /** 生成向FaulHaber写控制字的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8   controlword  0f 0d 06 07....
    *  @return:
    *  @note:
    *  @see:
    */

    void writeOperationMode(uint8_t temp[],int8_t type);
    /*******************************************/
    /** 生成向FaulHaber修改控制模式的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8  type 控制模式的种类
    *               1：PP
    *               3：PV
    *  @return:
    *  @note:
    *  @see:
    */

    void getData(uint8_t temp[],int32_t data,uint8_t type);
    /*******************************************/
    /** 生成向FaulHaber写数据的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  int data 需要写入的数据
    *  u8  type 数据类型
    *               1：目标速度
    *               2：目标位置
    *  @return:
    *  @note:
    *  @see:
    */

    void dealRXbuf(string&,int& pos,int& spd);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :to get the RXbuf in pattern from the str
    *  int&v       :to get the data from in RXbuf
    *  @return:
    *  void
    *  @note:
    *  @see:
    */

    void dealRXbuf(string&,int& pos);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :to get the RXbuf in pattern from the str
    *  int&v       :to get the data from in RXbuf
    *  @return:
    *  void
    *  @note:
    *  @see:
    */

    void BufferPush(string&);
    void BufferPush(unsigned char temp[]);
    /*******************************************/
    /** to get the RXbuf into the Queue
    *
    *
    *  @param:
    *  @return:
    *  void
    *  @note:
    *  @see:
    */
    void DealQueue(void);
    int getActualPos(string&);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :the RXbuf which need to deal with
    *  @return:
    *  int the actual position
    *  @note:
    *  @see:
    */

    int getActualSpeed(string&);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :the RXbuf which need to deal with
    *  @return:
    *  int the actual position
    *  @note:
    *  @see:
    */

    string setPosRequest(void);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  @return:
    *  get the buffer str of PosRequest
    *  @note:
    *  @see:
    */

    void setPosRequest(uint8_t temp[]);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  @return:
    *  get the buffer str of PosRequest
    *  @note:
    *  @see:
    */

    string setSpeedRequest(void);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  @return:
    *  get the buffer str of SpeedRequest
    *  @note:
    *  @see:
    */
    int getPosData(void);

private:
    circlequeue<unsigned char> Q;
    int PosData=0;


};

#endif //CIRCLE_TEST_RS232_H
