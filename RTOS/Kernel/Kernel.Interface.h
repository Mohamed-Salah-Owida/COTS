#ifndef KERNEL_INTERFACE_H
#define KERNEL_INTERFACE_H



extern uint8 Kernel_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16periodicity , void (*Copy_pvTaskHandler)(void) , uint16 Copy_u16FirstDelay );


extern void Kernel_VoidSuspendTask(uint8 Copy_u8Periority);
extern void Kernel_VoidResumeTask(uint8 Copy_u8Periority);
extern void Kernel_VoidDeleteTask(uint8 Copy_u8Periority);


extern void Kernel_VoidStartScheduler(void);


#endif
