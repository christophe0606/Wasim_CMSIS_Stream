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
#define NODE_2_INTERNAL_ID 2
#define DUP0_INTERNAL_ID 3



CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 1
#define FIFOSIZE1 64
#define FIFOSIZE2 64
#define FIFOSIZE3 64

#define BUFFERSIZE0 4
CG_BEFORE_BUFFER
uint8_t buf0[BUFFERSIZE0]={0};

#define BUFFERSIZE1 256
CG_BEFORE_BUFFER
uint8_t buf1[BUFFERSIZE1]={0};



CG_BEFORE_SCHEDULER_FUNCTION
uint32_t scheduler(int *error,dsp_context *context)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;


    CG_BEFORE_FIFO_INIT;
    /*
    Create FIFOs objects
    */
    FIFO<float,FIFOSIZE0,1,0> fifo0(buf0);
    FIFO<float,FIFOSIZE1,1,0> fifo1(buf1);
    FIFO<float,FIFOSIZE2,1,0> fifo2(buf1);
    FIFO<float,FIFOSIZE3,1,0> fifo3(buf1);

    CG_BEFORE_NODE_INIT;
    /* 
    Create node objects
    */
    AUSink<float,64,float,64,float,1> Node_0(fifo2,fifo3,fifo0,context); /* Node ID = 0 */
    Sam<float,64> Node_1(fifo1); /* Node ID = 1 */
    NullSource<float,1> Node_2(fifo0); /* Node ID = 2 */
    Duplicate<float,64,float,64> dup0(fifo1,{}); /* Node ID = 3 */

    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
    while(cgStaticError==0)
    {
       /* Run a schedule iteration */
       CG_BEFORE_ITERATION;
       CG_BEFORE_NODE_EXECUTION(2);
       cgStaticError = Node_2.run();
       CG_AFTER_NODE_EXECUTION(2);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(1);
       cgStaticError = Node_1.run();
       CG_AFTER_NODE_EXECUTION(1);
       CHECKERROR;
       CG_BEFORE_NODE_EXECUTION(3);
       cgStaticError = dup0.run();
       CG_AFTER_NODE_EXECUTION(3);
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
