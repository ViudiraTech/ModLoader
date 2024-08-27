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
	@echo ModLoader(DLL��ģ�������) -- �ű��������
	@echo Copyright 2020 ViudiraTech����������Ȩ����
	@echo.

res:
	@echo ���ڴ�����Դ�ļ�: $(RES_FILE)
	@$(WRS) $(RES_FLAGS)

ModLoader:
	@echo ���ڱ���Դ���ļ�: $(LOADER_C)
	@$(GCC) $(C_LOADER_FLAGS)

done:
	@echo ����������ɡ�

clean:
	@del $(LOADER_OUT_NAME)
	@del $(RES_O)
