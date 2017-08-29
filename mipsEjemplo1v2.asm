lw $t1,0($sp)
addi $t1,$t1,3
addi $t2,$zero,3
beq $t1,$t2,ZERO
add $t1,$sp,$t1
mul $t3,$t1,$t2
div $t5,$t1,$t2
j END
ZERO:
sw $t1,0($sp)
END:
