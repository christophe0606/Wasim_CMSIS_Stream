/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/


#include "arm_math.h"
#include "custom.h"
#include "cg_status.h"
#include "GenericNodes.h"
#include "AppNodes.h"
#include "scheduler.h"

#if !defined(CHECKERROR)
#define CHECKERROR       if (cgStaticError < 0) \
       {\
         goto errorHandling;\
       }

#endif


#if !defined(CG_BEFORE_ITERATION)
#define CG_BEFORE_ITERATION
#endif 

#if !defined(CG_AFTER_ITERATION)
#define CG_AFTER_ITERATION
#endif 

#if !defined(CG_BEFORE_SCHEDULE)
#define CG_BEFORE_SCHEDULE
#endif

#if !defined(CG_AFTER_SCHEDULE)
#define CG_AFTER_SCHEDULE
#endif

#if !defined(CG_BEFORE_BUFFER)
#define CG_BEFORE_BUFFER
#endif

#if !defined(CG_BEFORE_FIFO_BUFFERS)
#define CG_BEFORE_FIFO_BUFFERS
#endif

#if !defined(CG_BEFORE_FIFO_INIT)
#define CG_BEFORE_FIFO_INIT
#endif

#if !defined(CG_BEFORE_NODE_INIT)
#define CG_BEFORE_NODE_INIT
#endif

#if !defined(CG_AFTER_INCLUDES)
#define CG_AFTER_INCLUDES
#endif

#if !defined(CG_BEFORE_SCHEDULER_FUNCTION)
#define CG_BEFORE_SCHEDULER_FUNCTION
#endif

#if !defined(CG_BEFORE_NODE_EXECUTION)
#define CG_BEFORE_NODE_EXECUTION(ID)
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION(ID)
#endif





CG_AFTER_INCLUDES


using namespace arm_cmsis_stream;


/*

Internal ID identification for the nodes

*/
#define NODE_0_INTERNAL_ID 0
#define NODE_1_INTERNAL_ID 1
#define NODE_10_INTERNAL_ID 2
#define NODE_11_INTERNAL_ID 3
#define NODE_12_INTERNAL_ID 4
#define NODE_13_INTERNAL_ID 5
#define NODE_14_INTERNAL_ID 6
#define NODE_15_INTERNAL_ID 7
#define NODE_16_INTERNAL_ID 8
#define NODE_17_INTERNAL_ID 9
#define NODE_18_INTERNAL_ID 10
#define NODE_19_INTERNAL_ID 11
#define NODE_2_INTERNAL_ID 12
#define NODE_20_INTERNAL_ID 13
#define NODE_21_INTERNAL_ID 14
#define NODE_22_INTERNAL_ID 15
#define NODE_23_INTERNAL_ID 16
#define NODE_24_INTERNAL_ID 17
#define NODE_25_INTERNAL_ID 18
#define NODE_26_INTERNAL_ID 19
#define NODE_27_INTERNAL_ID 20
#define NODE_28_INTERNAL_ID 21
#define NODE_29_INTERNAL_ID 22
#define NODE_3_INTERNAL_ID 23
#define NODE_30_INTERNAL_ID 24
#define NODE_31_INTERNAL_ID 25
#define NODE_32_INTERNAL_ID 26
#define NODE_33_INTERNAL_ID 27
#define NODE_34_INTERNAL_ID 28
#define NODE_4_INTERNAL_ID 29
#define NODE_5_INTERNAL_ID 30
#define NODE_6_INTERNAL_ID 31
#define NODE_7_INTERNAL_ID 32
#define NODE_8_INTERNAL_ID 33
#define NODE_9_INTERNAL_ID 34
#define DUP0_INTERNAL_ID 49
#define DUP1_INTERNAL_ID 50
#define DUP10_INTERNAL_ID 51
#define DUP11_INTERNAL_ID 52
#define DUP12_INTERNAL_ID 53
#define DUP13_INTERNAL_ID 54
#define DUP14_INTERNAL_ID 55
#define DUP15_INTERNAL_ID 56
#define DUP2_INTERNAL_ID 57
#define DUP3_INTERNAL_ID 58
#define DUP4_INTERNAL_ID 59
#define DUP5_INTERNAL_ID 60
#define DUP6_INTERNAL_ID 61
#define DUP7_INTERNAL_ID 62
#define DUP8_INTERNAL_ID 63
#define DUP9_INTERNAL_ID 64



CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 1
#define FIFOSIZE1 64
#define FIFOSIZE2 64
#define FIFOSIZE3 64
#define FIFOSIZE4 64
#define FIFOSIZE5 64
#define FIFOSIZE6 64
#define FIFOSIZE7 64
#define FIFOSIZE8 64
#define FIFOSIZE9 64
#define FIFOSIZE10 64
#define FIFOSIZE11 64
#define FIFOSIZE12 64
#define FIFOSIZE13 64
#define FIFOSIZE14 64
#define FIFOSIZE15 64
#define FIFOSIZE16 64
#define FIFOSIZE17 64
#define FIFOSIZE18 64
#define FIFOSIZE19 64
#define FIFOSIZE20 64
#define FIFOSIZE21 64
#define FIFOSIZE22 64
#define FIFOSIZE23 64
#define FIFOSIZE24 64
#define FIFOSIZE25 64
#define FIFOSIZE26 64
#define FIFOSIZE27 64
#define FIFOSIZE28 64
#define FIFOSIZE29 64
#define FIFOSIZE30 64
#define FIFOSIZE31 64
#define FIFOSIZE32 64
#define FIFOSIZE33 64
#define FIFOSIZE34 64
#define FIFOSIZE35 64
#define FIFOSIZE36 64
#define FIFOSIZE37 64
#define FIFOSIZE38 64
#define FIFOSIZE39 64
#define FIFOSIZE40 64
#define FIFOSIZE41 64
#define FIFOSIZE42 64
#define FIFOSIZE43 64
#define FIFOSIZE44 64
#define FIFOSIZE45 64
#define FIFOSIZE46 64
#define FIFOSIZE47 1
#define FIFOSIZE48 1
#define FIFOSIZE49 1
#define FIFOSIZE50 1
#define FIFOSIZE51 1
#define FIFOSIZE52 1
#define FIFOSIZE53 1
#define FIFOSIZE54 1
#define FIFOSIZE55 1
#define FIFOSIZE56 1
#define FIFOSIZE57 1
#define FIFOSIZE58 1
#define FIFOSIZE59 1
#define FIFOSIZE60 1
#define FIFOSIZE61 1
#define FIFOSIZE62 1
#define FIFOSIZE63 1
#define FIFOSIZE64 1
#define FIFOSIZE65 1
#define FIFOSIZE66 1
#define FIFOSIZE67 1
#define FIFOSIZE68 1
#define FIFOSIZE69 1
#define FIFOSIZE70 1
#define FIFOSIZE71 1
#define FIFOSIZE72 1
#define FIFOSIZE73 1
#define FIFOSIZE74 1
#define FIFOSIZE75 1
#define FIFOSIZE76 1
#define FIFOSIZE77 1
#define FIFOSIZE78 1
#define FIFOSIZE79 1
#define FIFOSIZE80 1
#define FIFOSIZE81 1
#define FIFOSIZE82 1
#define FIFOSIZE83 1
#define FIFOSIZE84 1
#define FIFOSIZE85 1
#define FIFOSIZE86 1
#define FIFOSIZE87 1
#define FIFOSIZE88 1
#define FIFOSIZE89 1
#define FIFOSIZE90 1
#define FIFOSIZE91 1
#define FIFOSIZE92 1
#define FIFOSIZE93 1
#define FIFOSIZE94 1

#define BUFFERSIZE0 4
CG_BEFORE_BUFFER
uint8_t buf0[BUFFERSIZE0]={0};

#define BUFFERSIZE1 256
CG_BEFORE_BUFFER
uint8_t buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 256
CG_BEFORE_BUFFER
uint8_t buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 256
CG_BEFORE_BUFFER
uint8_t buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 256
CG_BEFORE_BUFFER
uint8_t buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
uint8_t buf5[BUFFERSIZE5]={0};

#define BUFFERSIZE6 256
CG_BEFORE_BUFFER
uint8_t buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 256
CG_BEFORE_BUFFER
uint8_t buf7[BUFFERSIZE7]={0};

#define BUFFERSIZE8 256
CG_BEFORE_BUFFER
uint8_t buf8[BUFFERSIZE8]={0};

#define BUFFERSIZE9 256
CG_BEFORE_BUFFER
uint8_t buf9[BUFFERSIZE9]={0};

#define BUFFERSIZE10 256
CG_BEFORE_BUFFER
uint8_t buf10[BUFFERSIZE10]={0};

#define BUFFERSIZE11 256
CG_BEFORE_BUFFER
uint8_t buf11[BUFFERSIZE11]={0};

#define BUFFERSIZE12 256
CG_BEFORE_BUFFER
uint8_t buf12[BUFFERSIZE12]={0};

#define BUFFERSIZE13 256
CG_BEFORE_BUFFER
uint8_t buf13[BUFFERSIZE13]={0};

#define BUFFERSIZE14 256
CG_BEFORE_BUFFER
uint8_t buf14[BUFFERSIZE14]={0};

#define BUFFERSIZE15 256
CG_BEFORE_BUFFER
uint8_t buf15[BUFFERSIZE15]={0};

#define BUFFERSIZE16 256
CG_BEFORE_BUFFER
uint8_t buf16[BUFFERSIZE16]={0};

#define BUFFERSIZE17 256
CG_BEFORE_BUFFER
uint8_t buf17[BUFFERSIZE17]={0};

#define BUFFERSIZE18 16
CG_BEFORE_BUFFER
uint8_t buf18[BUFFERSIZE18]={0};



CG_BEFORE_SCHEDULER_FUNCTION
uint32_t scheduler(int *error,struct FreeQueue* output_queue,
                              int32_t *atomic)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;


    CG_BEFORE_FIFO_INIT;
    /*
    Create FIFOs objects
    */
    FIFO<float,FIFOSIZE0,1,0> fifo0(buf0);
    FIFO<float,FIFOSIZE1,1,0> fifo1(buf17);
    FIFO<float,FIFOSIZE2,1,0> fifo2(buf17);
    FIFO<float,FIFOSIZE3,1,0> fifo3(buf14);
    FIFO<float,FIFOSIZE4,1,0> fifo4(buf11);
    FIFO<float,FIFOSIZE5,1,0> fifo5(buf12);
    FIFO<float,FIFOSIZE6,1,0> fifo6(buf12);
    FIFO<float,FIFOSIZE7,1,0> fifo7(buf6);
    FIFO<float,FIFOSIZE8,1,0> fifo8(buf5);
    FIFO<float,FIFOSIZE9,1,0> fifo9(buf2);
    FIFO<float,FIFOSIZE10,1,0> fifo10(buf1);
    FIFO<float,FIFOSIZE11,1,0> fifo11(buf17);
    FIFO<float,FIFOSIZE12,1,0> fifo12(buf17);
    FIFO<float,FIFOSIZE13,1,0> fifo13(buf17);
    FIFO<float,FIFOSIZE14,1,0> fifo14(buf17);
    FIFO<float,FIFOSIZE15,1,0> fifo15(buf10);
    FIFO<float,FIFOSIZE16,1,0> fifo16(buf9);
    FIFO<float,FIFOSIZE17,1,0> fifo17(buf13);
    FIFO<float,FIFOSIZE18,1,0> fifo18(buf15);
    FIFO<float,FIFOSIZE19,1,0> fifo19(buf8);
    FIFO<float,FIFOSIZE20,1,0> fifo20(buf12);
    FIFO<float,FIFOSIZE21,1,0> fifo21(buf14);
    FIFO<float,FIFOSIZE22,1,0> fifo22(buf13);
    FIFO<float,FIFOSIZE23,1,0> fifo23(buf7);
    FIFO<float,FIFOSIZE24,1,0> fifo24(buf4);
    FIFO<float,FIFOSIZE25,1,0> fifo25(buf16);
    FIFO<float,FIFOSIZE26,1,0> fifo26(buf17);
    FIFO<float,FIFOSIZE27,1,0> fifo27(buf2);
    FIFO<float,FIFOSIZE28,1,0> fifo28(buf10);
    FIFO<float,FIFOSIZE29,1,0> fifo29(buf6);
    FIFO<float,FIFOSIZE30,1,0> fifo30(buf4);
    FIFO<float,FIFOSIZE31,1,0> fifo31(buf12);
    FIFO<float,FIFOSIZE32,1,0> fifo32(buf13);
    FIFO<float,FIFOSIZE33,1,0> fifo33(buf7);
    FIFO<float,FIFOSIZE34,1,0> fifo34(buf8);
    FIFO<float,FIFOSIZE35,1,0> fifo35(buf11);
    FIFO<float,FIFOSIZE36,1,0> fifo36(buf12);
    FIFO<float,FIFOSIZE37,1,0> fifo37(buf4);
    FIFO<float,FIFOSIZE38,1,0> fifo38(buf3);
    FIFO<float,FIFOSIZE39,1,0> fifo39(buf15);
    FIFO<float,FIFOSIZE40,1,0> fifo40(buf16);
    FIFO<float,FIFOSIZE41,1,0> fifo41(buf1);
    FIFO<float,FIFOSIZE42,1,0> fifo42(buf9);
    FIFO<float,FIFOSIZE43,1,0> fifo43(buf5);
    FIFO<float,FIFOSIZE44,1,0> fifo44(buf3);
    FIFO<float,FIFOSIZE45,1,0> fifo45(buf2);
    FIFO<float,FIFOSIZE46,1,0> fifo46(buf1);
    FIFO<midi_cmd_t,FIFOSIZE47,1,0> fifo47(buf13);
    FIFO<midi_cmd_t,FIFOSIZE48,1,0> fifo48(buf13);
    FIFO<midi_cmd_t,FIFOSIZE49,1,0> fifo49(buf18);
    FIFO<midi_cmd_t,FIFOSIZE50,1,0> fifo50(buf12);
    FIFO<midi_cmd_t,FIFOSIZE51,1,0> fifo51(buf12);
    FIFO<midi_cmd_t,FIFOSIZE52,1,0> fifo52(buf18);
    FIFO<midi_cmd_t,FIFOSIZE53,1,0> fifo53(buf14);
    FIFO<midi_cmd_t,FIFOSIZE54,1,0> fifo54(buf15);
    FIFO<midi_cmd_t,FIFOSIZE55,1,0> fifo55(buf16);
    FIFO<midi_cmd_t,FIFOSIZE56,1,0> fifo56(buf11);
    FIFO<midi_cmd_t,FIFOSIZE57,1,0> fifo57(buf13);
    FIFO<midi_cmd_t,FIFOSIZE58,1,0> fifo58(buf15);
    FIFO<midi_cmd_t,FIFOSIZE59,1,0> fifo59(buf8);
    FIFO<midi_cmd_t,FIFOSIZE60,1,0> fifo60(buf8);
    FIFO<midi_cmd_t,FIFOSIZE61,1,0> fifo61(buf13);
    FIFO<midi_cmd_t,FIFOSIZE62,1,0> fifo62(buf7);
    FIFO<midi_cmd_t,FIFOSIZE63,1,0> fifo63(buf7);
    FIFO<midi_cmd_t,FIFOSIZE64,1,0> fifo64(buf13);
    FIFO<midi_cmd_t,FIFOSIZE65,1,0> fifo65(buf6);
    FIFO<midi_cmd_t,FIFOSIZE66,1,0> fifo66(buf12);
    FIFO<midi_cmd_t,FIFOSIZE67,1,0> fifo67(buf13);
    FIFO<midi_cmd_t,FIFOSIZE68,1,0> fifo68(buf5);
    FIFO<midi_cmd_t,FIFOSIZE69,1,0> fifo69(buf8);
    FIFO<midi_cmd_t,FIFOSIZE70,1,0> fifo70(buf12);
    FIFO<midi_cmd_t,FIFOSIZE71,1,0> fifo71(buf2);
    FIFO<midi_cmd_t,FIFOSIZE72,1,0> fifo72(buf7);
    FIFO<midi_cmd_t,FIFOSIZE73,1,0> fifo73(buf8);
    FIFO<midi_cmd_t,FIFOSIZE74,1,0> fifo74(buf1);
    FIFO<midi_cmd_t,FIFOSIZE75,1,0> fifo75(buf4);
    FIFO<midi_cmd_t,FIFOSIZE76,1,0> fifo76(buf6);
    FIFO<midi_cmd_t,FIFOSIZE77,1,0> fifo77(buf4);
    FIFO<midi_cmd_t,FIFOSIZE78,1,0> fifo78(buf4);
    FIFO<midi_cmd_t,FIFOSIZE79,1,0> fifo79(buf18);
    FIFO<midi_cmd_t,FIFOSIZE80,1,0> fifo80(buf3);
    FIFO<midi_cmd_t,FIFOSIZE81,1,0> fifo81(buf3);
    FIFO<midi_cmd_t,FIFOSIZE82,1,0> fifo82(buf18);
    FIFO<midi_cmd_t,FIFOSIZE83,1,0> fifo83(buf16);
    FIFO<midi_cmd_t,FIFOSIZE84,1,0> fifo84(buf16);
    FIFO<midi_cmd_t,FIFOSIZE85,1,0> fifo85(buf18);
    FIFO<midi_cmd_t,FIFOSIZE86,1,0> fifo86(buf15);
    FIFO<midi_cmd_t,FIFOSIZE87,1,0> fifo87(buf15);
    FIFO<midi_cmd_t,FIFOSIZE88,1,0> fifo88(buf18);
    FIFO<midi_cmd_t,FIFOSIZE89,1,0> fifo89(buf10);
    FIFO<midi_cmd_t,FIFOSIZE90,1,0> fifo90(buf17);
    FIFO<midi_cmd_t,FIFOSIZE91,1,0> fifo91(buf18);
    FIFO<midi_cmd_t,FIFOSIZE92,1,0> fifo92(buf9);
    FIFO<midi_cmd_t,FIFOSIZE93,1,0> fifo93(buf16);
    FIFO<midi_cmd_t,FIFOSIZE94,1,0> fifo94(buf17);

    CG_BEFORE_NODE_INIT;
    /* 
    Create node objects
    */
    WebAudioSink<float,64,float,64,float,1> Node_0(fifo45,fifo46,fifo0,output_queue,atomic); /* Node ID = 0 */
    NullSource<float,1> Node_1(fifo0); /* Node ID = 1 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_10(fifo58,fifo4,fifo32); /* Node ID = 2 */
    MIDIWav<midi_cmd_t,1,float,64> Node_11(fifo60,fifo5); /* Node ID = 3 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_12(fifo61,fifo5,fifo19); /* Node ID = 4 */
    MIDIWav<midi_cmd_t,1,float,64> Node_13(fifo63,fifo6); /* Node ID = 5 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_14(fifo64,fifo6,fifo33); /* Node ID = 6 */
    MIDIWav<midi_cmd_t,1,float,64> Node_15(fifo66,fifo7); /* Node ID = 7 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_16(fifo67,fifo7,fifo20); /* Node ID = 8 */
    MIDIWav<midi_cmd_t,1,float,64> Node_17(fifo69,fifo8); /* Node ID = 9 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_18(fifo70,fifo8,fifo34); /* Node ID = 10 */
    MIDIWav<midi_cmd_t,1,float,64> Node_19(fifo72,fifo9); /* Node ID = 11 */
    MIDISeq<midi_cmd_t,1> Node_2({&fifo50,&fifo53,&fifo56,&fifo59,&fifo62,&fifo65,&fifo68,&fifo71,&fifo74,&fifo77,&fifo80,&fifo83,&fifo86,&fifo89,&fifo92},empire); /* Node ID = 12 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_20(fifo73,fifo9,fifo23); /* Node ID = 13 */
    MIDIWav<midi_cmd_t,1,float,64> Node_21(fifo75,fifo10); /* Node ID = 14 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_22(fifo76,fifo10,fifo37); /* Node ID = 15 */
    MIDIWav<midi_cmd_t,1,float,64> Node_23(fifo78,fifo11); /* Node ID = 16 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_24(fifo79,fifo11,fifo24); /* Node ID = 17 */
    MIDIWav<midi_cmd_t,1,float,64> Node_25(fifo81,fifo12); /* Node ID = 18 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_26(fifo82,fifo12,fifo38); /* Node ID = 19 */
    MIDIWav<midi_cmd_t,1,float,64> Node_27(fifo84,fifo13); /* Node ID = 20 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_28(fifo85,fifo13,fifo25); /* Node ID = 21 */
    MIDIWav<midi_cmd_t,1,float,64> Node_29(fifo87,fifo14); /* Node ID = 22 */
    MIDIWav<midi_cmd_t,1,float,64> Node_3(fifo48,fifo1); /* Node ID = 23 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_30(fifo88,fifo14,fifo39); /* Node ID = 24 */
    MIDIWav<midi_cmd_t,1,float,64> Node_31(fifo90,fifo15); /* Node ID = 25 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_32(fifo91,fifo15,fifo26); /* Node ID = 26 */
    MIDIWav<midi_cmd_t,1,float,64> Node_33(fifo93,fifo16); /* Node ID = 27 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_34(fifo94,fifo16,fifo40); /* Node ID = 28 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_4(fifo49,fifo1,fifo17); /* Node ID = 29 */
    MIDIWav<midi_cmd_t,1,float,64> Node_5(fifo51,fifo2); /* Node ID = 30 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_6(fifo52,fifo2,fifo31); /* Node ID = 31 */
    MIDIWav<midi_cmd_t,1,float,64> Node_7(fifo54,fifo3); /* Node ID = 32 */
    MIDIEnv<midi_cmd_t,1,float,64,float,64> Node_8(fifo55,fifo3,fifo18); /* Node ID = 33 */
    MIDIWav<midi_cmd_t,1,float,64> Node_9(fifo57,fifo4); /* Node ID = 34 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup0(fifo47,{&fifo49}); /* Node ID = 49 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup1(fifo50,{&fifo52}); /* Node ID = 50 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup10(fifo77,{&fifo79}); /* Node ID = 51 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup11(fifo80,{&fifo82}); /* Node ID = 52 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup12(fifo83,{&fifo85}); /* Node ID = 53 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup13(fifo86,{&fifo88}); /* Node ID = 54 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup14(fifo89,{&fifo90,&fifo91}); /* Node ID = 55 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup15(fifo92,{&fifo93,&fifo94}); /* Node ID = 56 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup2(fifo53,{&fifo54,&fifo55}); /* Node ID = 57 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup3(fifo56,{&fifo57,&fifo58}); /* Node ID = 58 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup4(fifo59,{&fifo61}); /* Node ID = 59 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup5(fifo62,{&fifo64}); /* Node ID = 60 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup6(fifo65,{&fifo66,&fifo67}); /* Node ID = 61 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup7(fifo68,{&fifo69,&fifo70}); /* Node ID = 62 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup8(fifo71,{&fifo72,&fifo73}); /* Node ID = 63 */
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> dup9(fifo74,{&fifo75,&fifo76}); /* Node ID = 64 */

    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
    while(cgStaticError==0)
    {
       /* Run a schedule iteration */
       CG_BEFORE_ITERATION;
       CG_BEFORE_NODE_EXECUTION(1);
       cgStaticError = Node_1.run();
       CG_AFTER_NODE_EXECUTION(1);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(12);
       cgStaticError = Node_2.run();
       CG_AFTER_NODE_EXECUTION(12);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(49);
       cgStaticError = dup0.run();
       CG_AFTER_NODE_EXECUTION(49);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(23);
       cgStaticError = Node_3.run();
       CG_AFTER_NODE_EXECUTION(23);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(29);
       cgStaticError = Node_4.run();
       CG_AFTER_NODE_EXECUTION(29);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(50);
       cgStaticError = dup1.run();
       CG_AFTER_NODE_EXECUTION(50);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(30);
       cgStaticError = Node_5.run();
       CG_AFTER_NODE_EXECUTION(30);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(31);
       cgStaticError = Node_6.run();
       CG_AFTER_NODE_EXECUTION(31);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(51);
       cgStaticError = dup10.run();
       CG_AFTER_NODE_EXECUTION(51);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(16);
       cgStaticError = Node_23.run();
       CG_AFTER_NODE_EXECUTION(16);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(17);
       cgStaticError = Node_24.run();
       CG_AFTER_NODE_EXECUTION(17);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(52);
       cgStaticError = dup11.run();
       CG_AFTER_NODE_EXECUTION(52);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(18);
       cgStaticError = Node_25.run();
       CG_AFTER_NODE_EXECUTION(18);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(19);
       cgStaticError = Node_26.run();
       CG_AFTER_NODE_EXECUTION(19);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(53);
       cgStaticError = dup12.run();
       CG_AFTER_NODE_EXECUTION(53);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(20);
       cgStaticError = Node_27.run();
       CG_AFTER_NODE_EXECUTION(20);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(21);
       cgStaticError = Node_28.run();
       CG_AFTER_NODE_EXECUTION(21);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(54);
       cgStaticError = dup13.run();
       CG_AFTER_NODE_EXECUTION(54);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(22);
       cgStaticError = Node_29.run();
       CG_AFTER_NODE_EXECUTION(22);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(24);
       cgStaticError = Node_30.run();
       CG_AFTER_NODE_EXECUTION(24);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(55);
       cgStaticError = dup14.run();
       CG_AFTER_NODE_EXECUTION(55);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(25);
       cgStaticError = Node_31.run();
       CG_AFTER_NODE_EXECUTION(25);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(26);
       cgStaticError = Node_32.run();
       CG_AFTER_NODE_EXECUTION(26);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(46);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo25.getReadBuffer(64);
                   i1=fifo26.getReadBuffer(64);
                   o2=fifo28.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(46);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(56);
       cgStaticError = dup15.run();
       CG_AFTER_NODE_EXECUTION(56);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(27);
       cgStaticError = Node_33.run();
       CG_AFTER_NODE_EXECUTION(27);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(28);
       cgStaticError = Node_34.run();
       CG_AFTER_NODE_EXECUTION(28);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(40);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo39.getReadBuffer(64);
                   i1=fifo40.getReadBuffer(64);
                   o2=fifo42.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(40);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(57);
       cgStaticError = dup2.run();
       CG_AFTER_NODE_EXECUTION(57);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(32);
       cgStaticError = Node_7.run();
       CG_AFTER_NODE_EXECUTION(32);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(33);
       cgStaticError = Node_8.run();
       CG_AFTER_NODE_EXECUTION(33);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(42);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo17.getReadBuffer(64);
                   i1=fifo18.getReadBuffer(64);
                   o2=fifo21.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(42);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(58);
       cgStaticError = dup3.run();
       CG_AFTER_NODE_EXECUTION(58);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(34);
       cgStaticError = Node_9.run();
       CG_AFTER_NODE_EXECUTION(34);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(2);
       cgStaticError = Node_10.run();
       CG_AFTER_NODE_EXECUTION(2);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(36);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo31.getReadBuffer(64);
                   i1=fifo32.getReadBuffer(64);
                   o2=fifo35.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(36);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(59);
       cgStaticError = dup4.run();
       CG_AFTER_NODE_EXECUTION(59);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(3);
       cgStaticError = Node_11.run();
       CG_AFTER_NODE_EXECUTION(3);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(4);
       cgStaticError = Node_12.run();
       CG_AFTER_NODE_EXECUTION(4);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(60);
       cgStaticError = dup5.run();
       CG_AFTER_NODE_EXECUTION(60);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(5);
       cgStaticError = Node_13.run();
       CG_AFTER_NODE_EXECUTION(5);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(6);
       cgStaticError = Node_14.run();
       CG_AFTER_NODE_EXECUTION(6);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(61);
       cgStaticError = dup6.run();
       CG_AFTER_NODE_EXECUTION(61);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(7);
       cgStaticError = Node_15.run();
       CG_AFTER_NODE_EXECUTION(7);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(8);
       cgStaticError = Node_16.run();
       CG_AFTER_NODE_EXECUTION(8);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(43);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo19.getReadBuffer(64);
                   i1=fifo20.getReadBuffer(64);
                   o2=fifo22.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(43);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(41);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo21.getReadBuffer(64);
                   i1=fifo22.getReadBuffer(64);
                   o2=fifo29.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(41);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(62);
       cgStaticError = dup7.run();
       CG_AFTER_NODE_EXECUTION(62);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(9);
       cgStaticError = Node_17.run();
       CG_AFTER_NODE_EXECUTION(9);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(10);
       cgStaticError = Node_18.run();
       CG_AFTER_NODE_EXECUTION(10);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(37);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo33.getReadBuffer(64);
                   i1=fifo34.getReadBuffer(64);
                   o2=fifo36.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(37);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(48);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo35.getReadBuffer(64);
                   i1=fifo36.getReadBuffer(64);
                   o2=fifo43.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(48);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(63);
       cgStaticError = dup8.run();
       CG_AFTER_NODE_EXECUTION(63);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(11);
       cgStaticError = Node_19.run();
       CG_AFTER_NODE_EXECUTION(11);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(13);
       cgStaticError = Node_20.run();
       CG_AFTER_NODE_EXECUTION(13);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(45);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo23.getReadBuffer(64);
                   i1=fifo24.getReadBuffer(64);
                   o2=fifo27.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(45);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(44);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo27.getReadBuffer(64);
                   i1=fifo28.getReadBuffer(64);
                   o2=fifo30.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(44);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(35);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo29.getReadBuffer(64);
                   i1=fifo30.getReadBuffer(64);
                   o2=fifo45.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(35);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(64);
       cgStaticError = dup9.run();
       CG_AFTER_NODE_EXECUTION(64);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(14);
       cgStaticError = Node_21.run();
       CG_AFTER_NODE_EXECUTION(14);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(15);
       cgStaticError = Node_22.run();
       CG_AFTER_NODE_EXECUTION(15);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(39);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo37.getReadBuffer(64);
                   i1=fifo38.getReadBuffer(64);
                   o2=fifo41.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(39);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(38);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo41.getReadBuffer(64);
                   i1=fifo42.getReadBuffer(64);
                   o2=fifo44.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(38);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(47);
       
                  {

                   float* i0;
                   float* i1;
                   float* o2;
                   i0=fifo43.getReadBuffer(64);
                   i1=fifo44.getReadBuffer(64);
                   o2=fifo46.getWriteBuffer(64);
                   arm_add_f32(i0,i1,o2,64);
                   cgStaticError = 0;
                  }
       CG_AFTER_NODE_EXECUTION(47);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(0);
       cgStaticError = Node_0.run();
       CG_AFTER_NODE_EXECUTION(0);
       CHECKERROR;

       CG_AFTER_ITERATION;
       nbSchedule++;
    }
    
errorHandling:
    CG_AFTER_SCHEDULE;
    *error=cgStaticError;
    return(nbSchedule);
}
