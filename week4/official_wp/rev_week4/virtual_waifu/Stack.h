#include <Windows.h>

typedef struct VM_Stack *Stack;
struct VM_Stack
{
	int capacity; // 容量
	int TopOfStack; // 栈顶
	PDWORD vmStack; // 虚拟化堆栈
};

BOOL StartVM(PBYTE vmCode, PDWORD vmData);
Stack CreateVmStack(int MaxSize);
void Stack_Push(DWORD xxx, Stack S);
void Stack_Pop(PDWORD xxx, Stack S);
void Error(char* xxx);
