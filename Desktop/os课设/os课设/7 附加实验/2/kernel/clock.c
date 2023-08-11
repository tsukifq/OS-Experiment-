
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"



/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
	//int t = get_ticks();
	//disp_str("#");
	ticks++;
	p_proc_ready->ticks--;

	if (k_reenter != 0) {
		//disp_str("!");
		return;
	}

	if (p_proc_ready->ticks > 0) {
		return;
	}
	p_proc_ready->TurnaroundTick = get_ticks();	// p_proc_ready 进程结束
	schedule();
	p_proc_ready->WaitingTick = get_ticks();	// p_proc_ready 进程开始
}

/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec)
{
	int t = get_ticks();

	while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}
}


