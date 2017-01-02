bits 		32
section 	.text
	align 	4
	dd 	0x1BADB002			; This is the magic number to make this a bootable kernel
	dd	0x00				; Set flags to zero
	dd 	- (0x1BADB002 +0x00)		; Checksum 
global start
extern kmain					; This function will be executed from our c program
start:
	cli					; Clears the interrupts 
	call kmain				; Executes the kmain function in the kernel.c file 
	hlt					; Halts the CPU pausing it from executing from this address 


; Author: Ernesto Maldonado Thomas 
; Operating System Name: ErnestoOS 
