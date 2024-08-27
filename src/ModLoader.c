/*
 *
 *		ModLoader.c
 *		Mod����������
 *
 *		2024/8/26 By MicroFish
 *		���� GPL-3.0 ��ԴЭ��
 *		Copyright 2020 ViudiraTech����������Ȩ����
 *
 */

#include "ModLoader.h"

/* ����ģ��(DLL���) */
__declspec(dllexport) int ModFind(const char *ModsPath, char **ModsPaths)
{
	memset(ModsPaths, 0, sizeof(ModsPaths));
	return FindMods(ModsPath, ModsPaths);
}

/* ����ģ��(DLL���) */
__declspec(dllexport) int ModLoad(char **ModsPaths, int index)
{
	return RunMode(ModsPaths[index]);
}

/* ģ����� */
int RunMode(char *File)
{
	HMODULE hMod = LoadLibrary(File);
	if (!hMod) {
		printf("�����Ҳ���%s���޷�����ִ�д��룬���°�װ������ܻ��������⡣\n", File);
		FreeLibrary(hMod);
		return -100;
	}
	MOD_ENTRY ModMain = (MOD_ENTRY)GetProcAddress(hMod, "ModMain");
	if (!ModMain) {
		printf("�޷���λ��������� ModMain �ڶ�̬���ӿ� %s �ϡ�\n", File);
		FreeLibrary(hMod);
		return -101;
	}
	int result = ModMain();
	FreeLibrary(hMod);
	return result;
}

/* ģ����� */
int FindMods(const char *ModsPath, char **ModsPaths)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	int count = 0;
	char searchPath[MAX_PATH_LEN];

	// ��������·��
	snprintf(searchPath, sizeof(searchPath), "%s\\*.dll", ModsPath);

	// �����ļ����еĵ�һ���ļ�
	hFind = FindFirstFile(searchPath, &findFileData);

	// ѭ�������ҵ����ļ�
	do {
		// ����ļ��Ƿ���DLL�ļ�
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue; // ����Ŀ¼
		}
	
		// Ϊÿ���ҵ���DLL�ļ������ڴ沢�����ļ���
		ModsPaths[count] = (char *)malloc(MAX_PATH_LEN * sizeof(char));
		if (!ModsPaths[count]) {
			printf("���� %d �ֽ��ڴ�ʧ��\n", MAX_PATH_LEN * sizeof(char));
			break;
		}
		snprintf(ModsPaths[count], MAX_PATH_LEN, "%s\\%s", ModsPath, findFileData.cFileName);
		count++;
	} while (FindNextFile(hFind, &findFileData) != 0);
	FindClose(hFind);
	return count; // �����ҵ���DLL�ļ�����
}
