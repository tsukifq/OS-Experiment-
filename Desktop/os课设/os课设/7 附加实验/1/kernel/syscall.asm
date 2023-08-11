
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               syscall.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

%include "sconst.inc"

_NR_get_ticks		equ	0	; 要跟 global.c 中 sys_call_table 的定义相对应！
INT_VECTOR_SYS_CALL	equ	0x90
_NR_get_foo		equ	1       ; 定义系统调用号


; 导出符号
global	get_ticks
global	get_foo ; 申明全局函数


bits 32
[section .text]

; ====================================================================================
;                                    get_ticks
; ====================================================================================
get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret
get_foo:
	mov	eax, _NR_get_foo
	int	INT_VECTOR_SYS_CALL
	ret
