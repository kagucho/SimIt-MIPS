#include <stdio.h>


int main()
{

asm( "$TOP:\n"
	 "addu $8, $0, $0\n"
	 "addi $8, 1\n"
	 "lui $9, 0x1000\n"
	 "addiu $9, 0x0006\n"
	 "sw $9, $TOP($0)\n"
	 "beq $0, $0, $TOP\n"
	 "$END:\n"
	);


return 0;
}


