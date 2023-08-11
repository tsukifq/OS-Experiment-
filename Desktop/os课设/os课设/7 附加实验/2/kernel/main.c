
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
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
                            tinix_main
 *======================================================================*/
PUBLIC int tinix_main()
{
	disp_str("-----\"tinix_main\" begins-----\n");

	TASK*		p_task		= task_table;
	PROCESS*	p_proc		= proc_table;
	char*		p_task_stack	= task_stack + STACK_SIZE_TOTAL;
	t_16		selector_ldt	= SELECTOR_LDT_FIRST;
	int i;
	for(i=0;i<NR_TASKS;i++){
		strcpy(p_proc->name, p_task->name);	
		p_proc->pid	= i;			

		p_proc->ldt_sel	= selector_ldt;
		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(DESCRIPTOR));
		p_proc->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5;	
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(DESCRIPTOR));
		p_proc->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;	
		p_proc->regs.cs		= ((8 * 0) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
		p_proc->regs.ds		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
		p_proc->regs.es		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
		p_proc->regs.fs		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
		p_proc->regs.ss		= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
		p_proc->regs.gs		= (SELECTOR_KERNEL_GS & SA_RPL_MASK) | RPL_TASK;
		p_proc->regs.eip	= (t_32)p_task->initial_eip;
		p_proc->regs.esp	= (t_32)p_task_stack;
		p_proc->regs.eflags	= 0x1202;	

		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 1 << 3;
	}
	//���ȼ�����
	proc_table[0].priority = 150;
	proc_table[1].priority =  50;
	proc_table[2].priority =  30;
	//����ʱ������
	proc_table[0].ticks = 100;
	proc_table[1].ticks = 60;
	proc_table[2].ticks = 30;
	
	proc_table[0].WaitingTick = proc_table[0].TurnaroundTick = 0;
	proc_table[1].WaitingTick = proc_table[1].TurnaroundTick = 0;
	proc_table[2].WaitingTick = proc_table[2].TurnaroundTick = 0;
	
	k_reenter	= 0;
	ticks		= 0;

	p_proc_ready	= proc_table;
	
	out_byte(TIMER_MODE, RATE_GENERATOR);
	out_byte(TIMER0, (t_8) (TIMER_FREQ/HZ) );
	out_byte(TIMER0, (t_8) ((TIMER_FREQ/HZ) >> 8));

	
	put_irq_handler(CLOCK_IRQ, clock_handler);	
	enable_irq(CLOCK_IRQ);				
	
	disp_pos = 0;
	for (i = 0; i < 80*25; i++) {
		disp_str(" ");
	}
	disp_pos = 0;


	restart();

	while(1){}
}

/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
	while(1){
		disp_str("A.");
		milli_delay(50);	// milli_delay(10000) = 1s
	}
}


/*======================================================================*
                               TestB
 *======================================================================*/
void TestB()
{
	while(1){
		disp_str("B.");
		milli_delay(50);
	}
}


/*======================================================================*
                               TestC
 *======================================================================*/
void TestC()
{
	while(1){
		disp_str("C.");
		milli_delay(50);
	}
}

