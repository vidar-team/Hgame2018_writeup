#include "stdafx.h"
#include "Stack.h"
#include <stdio.h>
//¼ÇµÃfree
Stack CreateVmStack(int MaxSize)
{
	Stack S;
	if (MaxSize < 1)
		Error("Error the Stack is too small\n");
	S = (VM_Stack *)malloc(sizeof(struct VM_Stack)); // 1. 分配一个VM_Stack
	if (S == NULL)
		Error("Create Stack Malloc Fail CODE 1");
	S->vmStack = (PDWORD)malloc(sizeof(DWORD)*MaxSize); // 2. 分配一个PVM_Stack->vmStack
	if (S->vmStack == NULL)
		Error("Create Stack Malloc Fail CODE 2");
	memset(S->vmStack, sizeof(DWORD)*MaxSize, 0); // 3. vmstack全置零
	S->capacity = MaxSize; // 4. VM_Stack->capacity 设为 Size
	S->TopOfStack = 0; // 5. VM_Stack->TopOfStack 设为 栈底为0
	return S;
	
}
void Stack_Push(DWORD xxx, Stack S)
{
	S->vmStack[++S->TopOfStack] = xxx; // 栈顶升1后，栈顶位置被xxx赋值
}
void Stack_Pop(PDWORD xxx, Stack S)
{
	*xxx = S->vmStack[S->TopOfStack--]; // xxx被栈顶赋值，栈顶降1
}
void Error(char* xxx)
{
	printf("%s,LastError = %d", xxx,GetLastError());
	exit(-1);
}