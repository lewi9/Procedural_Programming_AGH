#pragma once

#include "global.h"

typedef struct
{
	int nHead;
	int nTail;
	QINFO** pFQItems;
	int nNoElem;
	int nMaxElem;
} QFIFO;

QFIFO* QFCreate( int nSize );

int QFEmpty( QFIFO* q );

int QFEnqueue( QFIFO* q, QINFO* pItem );

QINFO* QFDequeue( QFIFO* q );

void  QFClear( QFIFO* q, void( __cdecl* FreeInfo )( const void* ) );

void  QFRemove( QFIFO** q, void( __cdecl* FreeInfo )( const void* ) );



