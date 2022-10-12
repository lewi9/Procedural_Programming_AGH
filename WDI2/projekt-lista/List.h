#ifndef _LIST_H
#define _LIST_H

#include "Global.h"

typedef struct tagListItem
{
    LISTINFO* pInfo;
    tagListItem* pNext = NULL;
} ListItem;

ListItem* CreateList();

int InsertFront( ListItem* pList, LISTINFO* pInfo );
int Insert( ListItem* pAfter, LISTINFO* pInfo );

LISTINFO* RemoveFront( ListItem* pList );
LISTINFO* Remove( ListItem* pAfter );

LISTINFO* Front( ListItem* pList );

int IsEmpty( ListItem* pList );

void ClearList( ListItem* pList, void( __cdecl* FreeMem )( const void* ) );
void RemoveList( ListItem** pList, void( __cdecl* FreeMem )( const void* ) );

void SortList( ListItem* pList, int( __cdecl* Compare )( const void*, const void* ) );

ListItem* Find( ListItem* pList, LISTINFO* pItem, ListItem** pPrev,
    int( __cdecl* Compare )( const void*, const void* ) );

#endif

