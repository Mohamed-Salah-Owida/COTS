#ifndef KERNEL_PRV_H
#define KERNEL_PRV_H



typedef struct
{
	uint16 periodicity ;
	void (*Taskhandler)(void);
	uint8 IsSuspended;
	uint16 FirstDelay;

}Task_t;


#define  TASK_SUSPENDED    1u
#define  TASK_RESUMED      0u

static void VoidScheduler (void);




#endif
