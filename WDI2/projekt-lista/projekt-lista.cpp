#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "List.h"
#include "Global.h"

#define TABSIZE 2
#define MAXKEY 50
#define ELEMENTS 33
#define SPECIALELEMENT 9
#define FINDELEMENT 20
#define INSERTELEMENT 30
#define LINESIZE 10

void PrintList( ListItem* pList, int nLineSize );
LISTINFO* CreateElement( int nKey, int nIndex );

int main()
{
	srand( (unsigned int)time( NULL ) );

	ListItem* pList = CreateList();
	for( int i = 0; i < ELEMENTS; i++ )
	{
		int key = ( i == SPECIALELEMENT ) ? FINDELEMENT : rand() % MAXKEY;
		int index = i + 1;
		
		LISTINFO* pInt = CreateElement( key, index );
		if( !InsertFront( pList, pInt ) )
		{
			perror( "Dodanie elemnetu do tablicy się nie powiodło 1" );
			FreeMem( pInt );
			return 1;
		}
	}

	printf( "Utworzona lista z %d elementow. Klucze sa w nawiasach:\n", ELEMENTS );
	PrintList( pList, LINESIZE );

	printf( "\n\nPosortowana lista:\n" );
	SortList( pList, Compare );
	PrintList( pList, LINESIZE );

	ListItem* pPrev = NULL;
	LISTINFO* x = CreateElement( FINDELEMENT, NULL );
	Find( pList, x, &pPrev, Compare);
	FreeMem( x );

	LISTINFO* pInt = CreateElement( INSERTELEMENT, ELEMENTS+1 );
	if( !Insert( pPrev, pInt ) )
	{
		perror( "Dodanie elemnetu do tablicy się nie powiodło 2" );
		FreeMem( pInt );
		return 2;
	}

	printf( "\n\nLista ze wstawionym elementem o kluczy 30 przed kluczem 20:\n" );
	PrintList( pList, LINESIZE );

	printf( "\n\nUsuniety element: " );
	x = Remove( pPrev->pNext );
	printf( "%d(%d)", x->pTab[0], x->nKey );
	FreeMem( x );

	printf( "\n\nLista po usunieciu elementu:\n" );
	PrintList( pList, LINESIZE );

	ClearList( pList, FreeMem );

	x = CreateElement( 9, 21 );
	if( !InsertFront( pList, x ) )
	{
		perror( "Dodanie elemnetu do tablicy się nie powiodło 3" );
		FreeMem( x );
		return 3;
	}
	x = CreateElement( 21, 9 );
	if( !InsertFront( pList, x ) )
	{
		perror( "Dodanie elemnetu do tablicy się nie powiodło 4" );
		FreeMem( x );
		return 4;
	}

	printf( "\n\nLista po czyszczeniu i dodaniu nowych elementow:\n" );
	PrintList( pList, LINESIZE );

	RemoveList( &pList, FreeMem );
	printf( "\n\nUsunieta lista\n" );
	PrintList( pList, LINESIZE );

    return 0;
}

int Compare( const void* x, const void* y)
{
	if( ( (LISTINFO*)x )->nKey > ( (LISTINFO*)y )->nKey ) return 1;
	if( ( (LISTINFO*)x )->nKey < ( (LISTINFO*)y )->nKey ) return -1;
	return 0;
}

void FreeMem( const void* pT )
{
	int* p = ( (LISTINFO*)pT )->pTab;
	free( p );
	free( ( (LISTINFO*)pT ) );
}

void PrintList( ListItem* pList, int nLineSize )
{
	if( pList == NULL )
	{
		printf( "Lista jest pusta!!\n" );
		return;
	}

	int i = 0;
	for( int i = 1; !IsEmpty( pList ); i++)
	{
		printf( "%d(%d)\t", pList->pNext->pInfo->pTab[0], pList->pNext->pInfo->nKey );
		if( !(i % nLineSize) ) printf( "\n" );
		pList = pList->pNext;
	}
}

LISTINFO* CreateElement( int nKey, int nIndex )
{
	LISTINFO* pInt = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	if( pInt == NULL )
	{
		perror( "Memory Allocation problem - create pInt" );
		return NULL;
	}
	pInt->nKey = nKey;
	pInt->pTab = (int*)calloc( TABSIZE, sizeof( int ) );
	if( pInt->pTab == NULL )
	{
		perror( "Memory Allocation problem - create pInt->pTab" );
		return NULL;
	}
	pInt->pTab[0] = nIndex;
	return pInt;
}