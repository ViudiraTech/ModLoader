/*
 *
 *		ModLoader.h
 *		Mod加载器程序头文件
 *
 *		2024/8/26 By MicroFish
 *		基于 MIT 开源协议
 *		Copyright 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef MOD_LOADER_H_
#define MOD_LOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

#define MAX_PATH_LEN 260 // 最大路径长度

/* 模组标准参数类型 */
typedef int (*MOD_ENTRY)(void);

/* 模组加载 */
int RunMode(char *File);

/* 模组查找 */
int FindMods(const char *ModsPath, char **ModsPaths);

#endif // MOD_LOADER_H_
