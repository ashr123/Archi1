section .data                    	; data section, read-write
	an: DQ 0              	; this is a temporary var

section .text                    	; our code is always in the .text section
	global divisionBy2         	    ; makes the function appear in global scope
	extern printf            	; tell linker that printf is defined elsewhere 							; (not used in the program)
;rdi->rsi->rdx->rcx->r8->r9
	divisionBy2:                        	    ; functions are defined as labels
		push rbp              	; save Base Pointer (bp) original value
		mov rbp, rsp         	; use base pointer to access stack contents
		;mov rcx, rdi			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;;
                
        Looper:
                sub byte [rdi], '0'
                 cmp byte [rdi], 0
                je divs
                cmp byte [rdi], 2
                je divs
                cmp byte [rdi], 4
                je divs
                cmp byte [rdi], 6
                je divs   
                cmp byte [rdi], 8
                je divs
                 cmp byte [rdi], 10
                je divs
                 cmp byte [rdi], 12
                je divs
                 cmp byte [rdi], 14
                je divs
                 cmp byte [rdi], 16
                je divs
                 cmp byte [rdi], 18
                je divs
                cmp byte [rdi+1], 0
                je divs
                add byte [rdi+1], 10
        divs:
                shr byte [rdi], 1
                add byte [rdi], '0'
                inc rdi
                cmp byte [rdi], 0
                je breakLoop
                jmp Looper

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE ENDS HERE ;;;;;;;;;;;;;;;;
    breakLoop:
        mov rsp, rbp
        pop rbp
        ret