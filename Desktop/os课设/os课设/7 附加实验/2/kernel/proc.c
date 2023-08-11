
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
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
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS*	p;
	int		greatest_ticks = 0;

	for (p=proc_table; p<proc_table+NR_TASKS; p++) {
		if (p->ticks > greatest_ticks) {
			greatest_ticks = p->ticks;
			p_proc_ready = p;
		}
	}
	
	if (greatest_ticks == 0) {
		disp_str("\n###END###\n");
		disp_str("turnaround time of a:");
		disp_int(proc_table[0].TurnaroundTick /  10);
		disp_str("ms\n");
		disp_str("turnaround time of b:");
		disp_int(proc_table[1].TurnaroundTick /  10);
		disp_str("ms\n");
		disp_str("turnaround time of c:");
		disp_int(proc_table[2].TurnaroundTick /  10);
		disp_str("ms\n");
		disp_str("waiting time of a:");
		disp_int(proc_table[0].WaitingTick /  10);
		disp_str("ms\n");
		disp_str("waiting time of b:");
		disp_int(proc_table[1].WaitingTick /  10);
		disp_str("ms\n");
		disp_str("waiting time of c:");
		disp_int(proc_table[2].WaitingTick /  10);
		disp_str("ms\n");
		disp_str("average turnaround time:");
		disp_int((proc_table[0].TurnaroundTick + proc_table[1].TurnaroundTick + proc_table[2].TurnaroundTick) / 30);
		disp_str("ms\n");
		disp_str("average waiting time:");
		disp_int((proc_table[0].WaitingTick + proc_table[1].WaitingTick + proc_table[2].WaitingTick) / 30);
		disp_str("ms\n");
		disp_str("throughput:");
		int timeOfThree = proc_table[0].TurnaroundTick > proc_table[1].TurnaroundTick ? proc_table[0].TurnaroundTick : proc_table[1].TurnaroundTick;
		timeOfThree = timeOfThree > proc_table[2].TurnaroundTick ? timeOfThree : proc_table[2].TurnaroundTick;
		disp_int(30000 / timeOfThree);
		disp_str("/s\n");
		while(1) {}
	}
}


/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

