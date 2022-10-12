#include <stdlib.h>
#include <stdio.h>

#include "List.h"

ListItem* CreateList()
{
	return (ListItem*)calloc( 1, sizeof( ListItem ) );
}

int InsertFront( ListItem* pList, LISTINFO* pInfo )
{
    return Insert( pList, pInfo );
}

int Insert( ListItem* pAfter, LISTINFO* pInfo )
{
    ListItem* p = (ListItem*)calloc( 1, sizeof( ListItem ) );
    if( p == NULL ) return 0;
    p->pInfo = pInfo;
    p->pNext = pAfter->pNext;
    pAfter->pNext = p;
    return 1;
}

LISTINFO* RemoveFront( ListItem* pList )
{
    return Remove( pList );
    
}

LISTINFO* Remove( ListItem* pAfter )
{
    if( IsEmpty( pAfter ) )
        return NULL;
    ListItem* p = pAfter->pNext;
    LISTINFO* pInfo = p->pInfo;
    pAfter->pNext = p->pNext;
    free( p );
    return pInfo;
}

LISTINFO* Front( ListItem* pList )
{
    if( IsEmpty( pList ) )
    {
        return NULL;
    }
    return pList->pNext->pInfo;
}

int IsEmpty( ListItem* pList )
{
    return !( pList->pNext );
}

void ClearList( ListItem* pList, void( __cdecl* FreeMem )( const void* ) )
{
    while( !IsEmpty( pList ) )
        FreeMem( RemoveFront( pList ) );
}

void RemoveList( ListItem** pList, void( __cdecl* FreeMem )( const void* ) )
{
    ClearList( *pList, FreeMem );
    free( *pList );
    *pList = NULL;
}

void SortList( ListItem* pList, int( __cdecl* Compare )( const void*, const void* ) )
{
    ListItem* pFirst = pList;

    while( pFirst->pNext )
    {
        ListItem* pCurrent = pFirst->pNext;
        ListItem* pMin = pFirst;
        while( pCurrent->pNext )
        {
            if( Compare( pMin->pNext->pInfo, pCurrent->pNext->pInfo ) == 1 )
                pMin = pCurrent;
            pCurrent = pCurrent->pNext;
        } 

        if( pMin != pFirst )
        {
            pCurrent = pMin->pNext->pNext;
            pMin->pNext->pNext = pFirst->pNext;
            pFirst->pNext = pMin->pNext;
            pMin->pNext = pCurrent;
        }

        pFirst = pFirst->pNext;
    }
}

ListItem* Find( ListItem* pList, LISTINFO* pItem, ListItem** pPrev,
    int( __cdecl* Compare )( const void*, const void* ) )
{
    *pPrev = pList;
    while( !IsEmpty( *pPrev ) )
    {
        if( !Compare( pItem, ( *pPrev )->pNext->pInfo ) )
            return ( *pPrev )->pNext;
        *pPrev = ( *pPrev )->pNext;
    }
    return *pPrev = NULL;
}