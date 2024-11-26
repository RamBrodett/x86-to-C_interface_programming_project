; Brodett, Ram David M. - O'Neil, Samantha Erica R. [MP2-Group 8] - LBYARCH - S18
section .text
bits 64
default rel
global imgCvtGrayIntToDouble
; height@rcx, width@rdx, src@r8, dest@r9
imgCvtGrayIntToDouble:
    ;row counter r10 
    ;column counter r11
    ;current row r12
    ;pointer to the start of current row of input r13 
    ;pointer to the start of current row of output r14
    xor r10, r10
    
    row_loop:
        cmp r10, rcx
        je done
        mov r12, r10
        imul r12, rdx
        lea r13, [r8 + r12*4]
        lea r14, [r9 + r12*8]

        xor r11, r11
        column_loop:
            cmp r11, rdx
            je next_row
            mov eax, dword[r13 + r11*4]
            cvtsi2sd xmm0, rax

            mov rax, __float64__(255.0)
            movq xmm1, rax
            divsd xmm0, xmm1

            movsd qword[r14 + r11*8], xmm0

            inc r11
            jmp column_loop

    next_row:
        inc r10
        jmp row_loop
    done:
        ret
    
