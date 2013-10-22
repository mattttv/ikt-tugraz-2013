.section .init @defined in linker-file
.global _start 
_start:
	bl main @branch and link
		
.section .text @will hold code

tloop$:
	b tloop$
	
