#include "stackPointer.h"

stackPointer::stackPointer(){
	value = 0;
}

void stackPointer::setValue(int v){
	value = v;
}

int stackPointer::getValue(){
	return value;
}
