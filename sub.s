section .data                    	; data section, read-write
	an: DQ 0              	; this is a temporary var

section .text                    	; our code is always in the .text section
	global substraction         	    ; makes the function appear in global scope
	extern printf            	; tell linker that printf is defined elsewhere 							; (not used in the program)
;rdi->rsi->rdx->rcx->r8->r9
	substraction:                        	    ; functions are defined as labels
		push rbp              	; save Base Pointer (bp) original value
		mov rbp, rsp         	; use base pointer to access stack contents
		mov rcx, rdi			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;;
		mov	qword [an], 0		; initialize answer

		mov rax, rdi
		mov rbx, rsi
		mov rcx, rdx
		mov r15, rax; big arr
		mov r14, rbx; small arr
		dec r15  ;points to index -1
		dec r14  ;points to index -1
		mov r12, 0 ;carry
		mov r13, 0

                prepA:
			inc rax
			cmp byte [rax], 0
			jnz prepA
			dec rax
		prepB:
			inc rbx
			cmp byte [rbx], 0
			jnz prepB
			dec rbx

		subs:
			;mov r13, 0      ;r13=rolling
			;cmp rbx, r14
			;je continueSubs
			mov r13b, [rax]
			;sub  r13, '0'
                        
                        sub r13, r12 ;subs carry
			mov r12, 0
			 ;substract in order to calculate value
			cmp rbx, r14
			je continueSubs
			sub byte [rbx], '0'
			sub r13b, [rbx] ;the real substraction
			add byte [rbx], '0';adds what we substracted back
                continueSubs:
			cmp r13, '0' ;if needs borrow
			jnl assA;check if we need to borrow
			add r13, 10
			mov r12, 1;turn on the borrow flag
			assA:
				mov [rcx], r13b
                                inc rcx
			
			dec rax
			cmp rax, r15 ;if (rax!=r15) dec rax
			je breakLoop
			
			cmp rbx, r14 ;if (rbx!=r14) dec rbx
			je subs
			dec rbx
			
			jmp subs ;loop
                        



;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE ENDS HERE ;;;;;;;;;;;;;;;;
    breakLoop:
	;mov rax, [an]         ; return an (returned values are in rax)
	cmp r12, 0
        je notAddCarry
        mov byte [rcx], '_'
        inc rcx
    notAddCarry:
        mov byte [rcx], 0
        mov rsp, rbp
        pop rbp
        ret