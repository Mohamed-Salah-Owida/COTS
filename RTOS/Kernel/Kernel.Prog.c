#include "STD_TYPES.h"
#include "ErrorType.h"

#include "GIE_Interface.h"
#include "TIMER_Interface.h"

#include "Kernel.Cfg.h"
#include "Kernel.Interface.h"
#include "Kernel.Prv.h"


Timer0_2Cfg_t  Timer = {
		T0_2CTC,
		T0_2Disconnected_Non,
		T0_2Disconnected_Fast,
		T0_2Disconnected_Phase,
		CLK_64
};

static Task_t SystemTasks[NumberOfTasks] = {{0}};

extern uint8 Kernel_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16periodicity , void (*Copy_pvTaskHandler)(void) , uint16 Copy_u16FirstDelay )
{
	uint8 Local_u8ErrorStat = OK;

	if (Copy_pvTaskHandler != NULL)
	{
		if(SystemTasks[Copy_u8Priority].Taskhandler == NULL)
		{
			SystemTasks[Copy_u8Priority].periodicity = Copy_u16periodicity ;
			SystemTasks[Copy_u8Priority].Taskhandler = Copy_pvTaskHandler ;
			SystemTasks[Copy_u8Priority].IsSuspended = TASK_RESUMED ;
			SystemTasks[Copy_u8Priority].FirstDelay  = Copy_u16FirstDelay;

		}
		else
		{
			/*priority is used, Don't overwrite */
		}

	}
	else
	{
		Local_u8ErrorStat =NULL_PTR_ERR ;
	}

	return Local_u8ErrorStat ;
}



void Kernel_VoidStartScheduler(void)
{
	Timers_SetCallBack(T0_2Com_Int ,&VoidScheduler);
	GIE_voidEnableGlobal();
	TIMER0_u8IntEnable(T0_2Com_Int);
	Timer0_VoidSetCompareMatchVal(250);
	Timer0_u8Init(&Timer);

}


void Kernel_VoidSuspendTask(uint8 Copy_u8Periority)
{
	SystemTasks[Copy_u8Periority].IsSuspended = TASK_SUSPENDED;

}


void Kernel_VoidResumeTask(uint8 Copy_u8Periority)
{
	SystemTasks[Copy_u8Periority].IsSuspended = TASK_RESUMED;

}


void Kernel_VoidDeleteTask(uint8 Copy_u8Periority)
{
	SystemTasks[Copy_u8Periority].Taskhandler = NULL;
}








static void VoidScheduler (void)
{
	uint8 Local_u8TaskIndex;

	for(Local_u8TaskIndex =0u; Local_u8TaskIndex < NumberOfTasks ; Local_u8TaskIndex++)
	{
		/*check if the task suspended or resumed */
		if(SystemTasks[Local_u8TaskIndex].IsSuspended == TASK_RESUMED)
		{

			if (SystemTasks[Local_u8TaskIndex].FirstDelay == 0)
			{
				/*check if the task handler = null -> task deleted or not initialized */
				if (SystemTasks[Local_u8TaskIndex].Taskhandler != NULL)
				{
					/*invoke  the task handler */
					SystemTasks[Local_u8TaskIndex].Taskhandler();
					SystemTasks[Local_u8TaskIndex].FirstDelay = SystemTasks[Local_u8TaskIndex].periodicity -1u;
				}
				else
				{
				   /*task not found or deleted , Don't invoke */
				}

			}
			else
			{
				SystemTasks[Local_u8TaskIndex].FirstDelay--;
			}
		}
		else
		{
			/*Task is suspended */
		}

	}

}



















