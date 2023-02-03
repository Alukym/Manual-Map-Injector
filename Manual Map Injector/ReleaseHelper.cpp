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
	// �ҵ���Դ
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(uResourceId), c2w(szResourceType));
	if (hRsrc == NULL)
		return FALSE;

	// ��ȡ��Դ��С
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (dwSize <= 0)
		return FALSE;

	// ������Դ
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	// ������Դ��������ָ����Դ��һ�ֽڵ�ָ��
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