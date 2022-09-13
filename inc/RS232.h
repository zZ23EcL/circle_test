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

    void writeOperationMode(uint8_t temp[],uint8_t type);
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
    void wrtieSource(uint8_t temp[],uint16_t source,uint8_t type);
    /*******************************************/
    /** 生成向FaulHaber修改信源的字符串
    *   其中包括了模拟量的设置
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u16 source 需要修改的子索引
    *  u8 type 设置的种类
    *  @return:
    *  @note:
    *  @see:
    */
    void writeVirtualAnalogData(uint8_t temp[],int16_t data);
    /*******************************************/
    /** 生成向FaulHaber设制模拟量大小的函数
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  int16 source 需要修改模拟量大小
    *  @return:
    *  @note:默认0x09 analog1
    *  @see:
    */
    void writeVirtualAnalogEnable(uint8_t temp[],uint8_t type);
    /*******************************************/
    /** 生成向FaulHaber设制启用虚拟模拟信号输入使能
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8 type 势能anln1或者anln2
    *  @return:
    *  @note:默认0x09 analog1
    *  @see:
    */
    void writeTargetSource(uint8_t temp[],uint8_t type);
    /*******************************************/
    /** 生成向FaulHaber控制器选定需要的设定值信源
    *   这是由于在APC和AVC模式下，需要选定相对应的设定值为模拟信号
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8 type 设置的设定值对象，一般为speed or position
    *  @return:
    *  @note:默认0x09 analog1
    *  @see:
    */

    void writeTargetSourcePropotion(uint8_t temp[],int32_t p);
    void writeAnalogPropotion(uint8_t temp[],int32_t p);
    void setReductionRadio(uint8_t temp[],uint8_t type,uint32_t data);
    /*******************************************/
    /** 生成向FaulHaber控制器设定电机减速比
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8 type 设置的对象 01 减速器输入圈数 02减速器输出转速
    *  @return:
    *  @note:默认0x09 analog1
    *  @see:
    */
    void writeAnalogOffset(uint8_t temp[],int16_t offset);
    /*******************************************/
    /** 生成向FaulHaber控制器模拟量设置偏置大小
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  s16 offset 偏置量大小
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

    void setSpeedRequest(uint8_t temp[]);
    /*******************************************/
    /** get realtime Speed
    *
    *
    *  @param:
    *  @return:
    *  get the buffer str of PosRequest
    *  @note:
    *  @see:
    */
    int getPosData(void);
    int getSpeedData(void);

private:
    circlequeue<unsigned char> Q;
    int PosData=0;
    int SpeedData=0;
};

#endif //CIRCLE_TEST_RS232_H
