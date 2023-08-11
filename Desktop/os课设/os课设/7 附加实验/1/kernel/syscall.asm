
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               syscall.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

%include "sconst.inc"

_NR_get_ticks		equ	0	; Ҫ�� global.c �� sys_call_table �Ķ������Ӧ��
INT_VECTOR_SYS_CALL	equ	0x90
_NR_get_foo		equ	1       ; ����ϵͳ���ú�


; ��������
global	get_ticks
global	get_foo ; ����ȫ�ֺ���


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
