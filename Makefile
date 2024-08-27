LOADER_OUT_NAME	= ModLoader.dll
LOADER_C		= .\src\ModLoader.c

RES_FILE		= .\src\resource.rc
RES_O			= .\src\resource.o

GCC				= gcc
WRS				= windres

RES_FLAGS		= -i $(RES_FILE) -o $(RES_O)
C_LOADER_FLAGS	= -shared -o $(LOADER_OUT_NAME) $(LOADER_C) $(RES_O) -lcomdlg32

all: info res ModLoader done

info:
	@echo ModLoader(DLL型模组加载器) -- 脚本编译程序。
	@echo Copyright 2020 ViudiraTech，保留所有权利。
	@echo.

res:
	@echo 正在处理资源文件: $(RES_FILE)
	@$(WRS) $(RES_FLAGS)

ModLoader:
	@echo 正在编译源码文件: $(LOADER_C)
	@$(GCC) $(C_LOADER_FLAGS)

done:
	@echo 编译任务完成。

clean:
	@del $(LOADER_OUT_NAME)
	@del $(RES_O)
