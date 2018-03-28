section .data                    	; data section, read-write
	an: DQ 0              	; this is a temporary var

section .text                    	; our code is always in the .text section
	global addition          	    ; makes the function appear in global scope
	extern printf            	; tell linker that printf is defined elsewhere 							; (not used in the program)
;rdi->rsi->rdx->rcx->r8->r9
	addition:                        	    ; functions are defined as labels
		push rbp              	; save Base Pointer (bp) original value
		mov rbp, rsp         	; use base pointer to access stack contents
		mov rcx, rdi			    ; get function argument

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE STARTS HERE ;;;;;;;;;;;;;;;;
		mov	qword [an], 0		; initialize answer

		mov rax, rdi
		mov rbx, rsi
		mov rcx, rdx
		mov r15, rax
		mov r14, rbx
		mov r12, 0 ;carry

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
			
		adds:
			mov r13, 0
			cmp rbx, r14
			jne continueAdds
			mov r13, [rbx]
		continueAdds:
			sub  r13, '0'
			add r13, r12 ;add carry
			mov r12, 0
			add  r13, [rax]
			cmp r13, '9'
			jng assA
			sub r13, 10
			mov r12, 1
			assA:
				mov byte [rcx], r13
			inc rcx
			cmp rax, r15 ;if (rax!=r15) dec rax
			je breakLoop
			dec rax
			cmp rbx, r14 ;if (rbx!=r14) dec rbx
			je adds
			dec rbx
			jmp adds ;loop
			
				
				
			

;;;;;;;;;;;;;;;; FUNCTION EFFECTIVE CODE ENDS HERE ;;;;;;;;;;;;;;;;
	mov rax, [an]         ; return an (returned values are in rax)
	mov rsp, rbp
	pop rbp
	ret