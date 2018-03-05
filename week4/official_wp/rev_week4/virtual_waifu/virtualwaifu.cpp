// virtualwaifu.cpp: 定义控制台应用程序的入口点。
//
// 改自hctf2015 Pev-45
#include "stdafx.h"
#include <cstdio>
#include <Windows.h>
#include "Stack.h"
#include "VM.h"

BYTE enc_data[] = {134, 92, 184, 70, 76, 189, 74, 163, 190, 76, 141, 163, 186, 243, 161, 171, 162, 250, 249, 164, 174, 128, 253, 174};
int main()
{
	printf("Input your flag: \n");
	unsigned char input_s[32] = { 0 };
	scanf_s("%s", input_s, 32);
#ifdef _DEBUG
	printf("addr = %x \n", input_s);
#endif
		BYTE CODE[] =
	{
		VM_X00_START,
		VM_PUSH_NUM,	//NUM1  push addr of input Str

		VM_POP_EBX,
		VM_PUSH_EBX,	//EBX = ADDR STR

		VM_STRLEN_CALL, //pop addr, call strlen, push result

		VM_PUSH_NUM,	//NUNM2 push 0x0 i = 0
		VM_CMP,			//cmp <-----
		VM_PUSH_NUM,	//push NUM3 is jum to exit
		VM_JZ,			//pop NUM3 JZ  (18)

		VM_POP_EAX,		//pop eax  ;eax = i


		VM_PUSH_EBX,	//EBX: push addr of input Str
		VM_PUSH_EAX,	//PUSH i

		VM_ADD,			//Pop i ,add i str
		VM_BYTE_MEM_GET, //POP STR, FIND BYTE STR, PUSH result
		 /////////////////////
		VM_PUSH_NUM,	// push length
		VM_PUSH_EAX,	// push i
		VM_SUB,			// len - i
		VM_ADD,			// input_s[i] + (len-i)
		/////////////////////
		VM_PUSH_NUM,    //num push 6 (6)
		VM_XOR,			//pop 6,top xor 6

		VM_PUSH_EBX,	//EBX: push addr of input Str
		VM_PUSH_EAX,	//PUSH i
		VM_ADD,			//Pop i ,add i str
		VM_BYTE_MEM_SET,//pop addr,pop result, Set That addr

		VM_PUSH_EAX,	//EAX = i
		VM_PUSH_NUM,	//NUM = 1
		VM_ADD,			//I = I+1
		VM_POP_EAX,		//eax = i
		VM_PUSH_EAX,	//push to jmp

		VM_PUSH_NUM,	//NUM5  jmp code
		VM_JMP,			//circle jmp
		VM_EXIT };
	DWORD CODE_DATA[] =
	{
		(DWORD)input_s,
		0x000,
		0x016, //1
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //2
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //3
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //4
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //5
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //6
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //7
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //8
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //9
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //10
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //11
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //12
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //13
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //14
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //15
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //16
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //17
		0x017,
		0x0cc,
		0x001,
		-0x19,
			 
		0x016, //18
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //19
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //20
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //21
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //22
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //23
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //24
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //25
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //26
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //27
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //28
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //29
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //30
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //31
		0x017,
		0x0cc,
		0x001,
		-0x19,

		0x016, //32
		0x017,
		0x0cc,
		0x001,
		-0x19,
};

	StartVM(CODE, CODE_DATA);
	for (int i = 0; i < 24; i++) {
		if (input_s[i] != enc_data[i]) {
			printf("Never Give Up\n");
			break;
		}
	}
#ifdef _DEBUG
	for (int i = 0; i < 24; i++) {
		printf("%d\n", input_s[i]);
	}
#endif
	system("pause");
	return 0;
}