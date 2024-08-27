/*
 *
 *		ModLoader.c
 *		Mod加载器程序
 *
 *		2024/8/26 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright 2020 ViudiraTech，保留所有权利。
 *
 */

#include "ModLoader.h"

/* 查找模组(DLL入口) */
__declspec(dllexport) int ModFind(const char *ModsPath, char **ModsPaths)
{
	memset(ModsPaths, 0, sizeof(ModsPaths));
	return FindMods(ModsPath, ModsPaths);
}

/* 运行模组(DLL入口) */
__declspec(dllexport) int ModLoad(char **ModsPaths, int index)
{
	return RunMode(ModsPaths[index]);
}

/* 模组加载 */
int RunMode(char *File)
{
	HMODULE hMod = LoadLibrary(File);
	if (!hMod) {
		printf("由于找不到%s，无法继续执行代码，重新安装程序可能会解决此问题。\n", File);
		FreeLibrary(hMod);
		return -100;
	}
	MOD_ENTRY ModMain = (MOD_ENTRY)GetProcAddress(hMod, "ModMain");
	if (!ModMain) {
		printf("无法定位程序输入点 ModMain 于动态链接库 %s 上。\n", File);
		FreeLibrary(hMod);
		return -101;
	}
	int result = ModMain();
	FreeLibrary(hMod);
	return result;
}

/* 模组查找 */
int FindMods(const char *ModsPath, char **ModsPaths)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	int count = 0;
	char searchPath[MAX_PATH_LEN];

	// 构造搜索路径
	snprintf(searchPath, sizeof(searchPath), "%s\\*.dll", ModsPath);

	// 搜索文件夹中的第一个文件
	hFind = FindFirstFile(searchPath, &findFileData);

	// 循环遍历找到的文件
	do {
		// 检查文件是否是DLL文件
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue; // 跳过目录
		}
	
		// 为每个找到的DLL文件分配内存并复制文件名
		ModsPaths[count] = (char *)malloc(MAX_PATH_LEN * sizeof(char));
		if (!ModsPaths[count]) {
			printf("分配 %d 字节内存失败\n", MAX_PATH_LEN * sizeof(char));
			break;
		}
		snprintf(ModsPaths[count], MAX_PATH_LEN, "%s\\%s", ModsPath, findFileData.cFileName);
		count++;
	} while (FindNextFile(hFind, &findFileData) != 0);
	FindClose(hFind);
	return count; // 返回找到的DLL文件数量
}
