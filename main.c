#define UNICODE

#include <windows.h>
#include <locale.h>
#include <wchar.h>
#include "include/resource.h"
#pragma comment(lib,"Comdlg32.lib")

HINSTANCE hInstance;
  
LRESULT CALLBACK wndproc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE preInstance,LPSTR pCmd,int nCmdShow)
{
	setlocale(LC_ALL,"");


	hInstance = hInstance; //应用程序实例
	WNDCLASS wndclass = {0};// 窗口结构体
	LPCTSTR className = TEXT("mywindow");// 窗口类名
	HWND hwnd; //窗口句柄
	MSG msg; //消息结构体


	wndclass.style = CS_VREDRAW|CS_HREDRAW; //窗口类的基本样式 CS_HREDRAW|CS_VREDRAW 代表移动窗口时，重新绘制窗口(横向和纵向)
	wndclass.lpfnWndProc = wndproc;//窗口过程处理函数
	wndclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wndclass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = className;


	//注册窗口类
	RegisterClass(&wndclass); 
	//创建窗口
	hwnd = CreateWindow(className,TEXT("Tiger的窗口"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	//显示窗口
	ShowWindow(hwnd,nCmdShow);
	//更新窗口
	UpdateWindow(hwnd);
	//获取消息----- > 转换消息 ------> 分发消息
	while(GetMessage(&msg,hwnd,0,0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}


LRESULT CALLBACK wndproc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

	switch(uMsg)
	{
		case WM_CREATE:
			{
				
			}
		break;
		case WM_COMMAND:
			{
				WORD id = LOWORD(wParam);
				switch(id)
				{
					case ID_FILE_NEW:
						MessageBox(hwnd,TEXT("你要新建文件"),TEXT("哈哈哈"),MB_OKCANCEL);
					break;
					case ID_FILE_SAVE:
						//MessageBox(hwnd,TEXT("你要保存文件"),TEXT("哈哈哈"),MB_OKCANCEL);
						{
							OPENFILENAME ofn = {0};
						    TCHAR szFileName[MAX_PATH] = TEXT("D:\\elikebefore\\后端\\c\\windows\\window\\main.c");

						    ZeroMemory(&ofn, sizeof(ofn));

						    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						    ofn.hwndOwner = hwnd;
						    ofn.lpstrFile = szFileName;
						    ofn.nMaxFile = MAX_PATH;
						    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						    if(GetOpenFileName(&ofn) != 0)
						    {
						     	MessageBox(hwnd, TEXT("打开成功!"), TEXT("YEAH"), MB_OKCANCEL);
						    }
						    else
						    {
						    	MessageBox(hwnd, TEXT("打开失败!"), TEXT("YEAH"), MB_OKCANCEL);
						    }
						}
					break;
					case ID_OP_OPEN_DLG:
			        {
			            int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
			            if(ret == IDOK){
			                MessageBox(hwnd, TEXT("Dialog exited with IDOK."), TEXT("Notice"), MB_OK | MB_ICONINFORMATION);
			            }
			            else if(ret == IDCANCEL){
			                MessageBox(hwnd, TEXT("Dialog exited with IDCANCEL."), TEXT("Notice"), MB_OK | MB_ICONINFORMATION);
			            }
			            else if(ret == -1){
			                MessageBox(hwnd, TEXT("Dialog failed!"), TEXT("Error"), MB_OK | MB_ICONINFORMATION);
			            }
			        }
			        break;
				}
			}
		break;
		case WM_DESTROY:
			{
		    	PostQuitMessage(0);
			}
		break;
		default:
			return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return 0;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}