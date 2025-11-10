#include <assert.h>
#include "stack.h"


void test_stack(void) {
	puts("stack test started");
	stack* myStack = initStack(10);
	pileUp(myStack, "décembre");
	pileUp(myStack, "novembre");
	pileUp(myStack, "octobre");
	pileUp(myStack, "septembre");
	pileUp(myStack, "aout");
	pileUp(myStack, "juillet");
	pileUp(myStack, "juin");
	pileUp(myStack, "mai");
	pileUp(myStack, "avril");
	pileUp(myStack, "mars");
	pileUp(myStack, "février");
	pileUp(myStack, "janvier");
	printStack(myStack);
	assert(myStack->size == 40);
	assert(myStack->indexOfNext == 12);
	puts("test ended successfully :)");


}

int main(void){
	test_stack();
}
