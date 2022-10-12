#pragma once

typedef struct
{
	char* sName;
	int   nKey;
} QInfo;

#define QINFO QInfo

void FreeInfo( const void* );