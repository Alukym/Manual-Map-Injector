#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

#include "resource.h"
#include "injector.h"

using namespace std;

typedef VOID(*Func)(VOID);

BOOL ReleaseLibrary(UINT uResourceId, CHAR *szResourceType, const char *szFileName)
{
	// 找到资源
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(uResourceId), c2w(szResourceType));
	if (hRsrc == NULL)
		return FALSE;

	// 获取资源大小
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (dwSize <= 0)
		return FALSE;

	// 载入资源
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	// 锁定资源，并返回指向资源第一字节的指针
	LPVOID lpRes = LockResource(hGlobal);
	if (lpRes == NULL)
		return FALSE;

	HANDLE hFile = CreateFile(c2w(szFileName), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL)
		return FALSE;

	DWORD dwWriten = 0;
	BOOL bRes = WriteFile(hFile, lpRes, dwSize, &dwWriten, NULL);
	if (bRes == FALSE || dwWriten <= 0)
		return FALSE;

	CloseHandle(hFile);
	CloseHandle(hGlobal);
	CloseHandle(hRsrc);
	return TRUE;
}