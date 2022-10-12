#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FQueue.h"

#define ADD_ELEMENT 4
#define BUFFER 32
#define REMOVE_ELEMENT 3
#define LINE_SIZE 2
#define NAME_CON 2

#define MACRO1 i + ADD_ELEMENT
#define MACRO2 i + ADD_ELEMENT + ( ADD_ELEMENT >> 1 )

QINFO* CreateElement( int nKey, char* sName );
void PrintElement( QINFO* pInfo );

int main()
{
	printf( "Uruchomiono LHFIFO_2\n\n" );
	QFIFO* q = QFCreate();
	if( q == NULL || q->pHead == NULL )
	{
		perror( "Memory Allocation problem - q create" );
		return 1;
	}
	char buffer[BUFFER];

	QINFO* y;

	for( int i = 1; i <= ADD_ELEMENT; i++ )
		if( !QFEnqueue( q, y = CreateElement( i, _itoa( i, buffer, NAME_CON ) ) ) )
		{
			printf( "Error - add element %d to the Queue\n", i );
			FreeInfo( y );
		}

	for( int i = 1; i <= REMOVE_ELEMENT; i++ )
	{
		QINFO* p = QFDequeue( q );
		PrintElement( p );
		FreeInfo( p );
	}

	for( int i = 1; i <= ADD_ELEMENT >> 1; i++ )
		if( !QFEnqueue( q, y = CreateElement( MACRO1, _itoa( MACRO1, buffer, NAME_CON ) ) ) )
		{
			printf( "Error - add element %d to the Queue\n", MACRO1 );
			FreeInfo( y );
		}

	QFClear( q, FreeInfo );

	for( int i = 1; i <= REMOVE_ELEMENT; i++ )
		if( !QFEnqueue( q, y = CreateElement( MACRO2, _itoa( MACRO2, buffer, NAME_CON ) ) ) )
		{
			printf( "Error - add element %d to the Queue\n", MACRO2 );
			FreeInfo( y );
		}

	QINFO* p = QFDequeue( q );
	PrintElement( p );
	FreeInfo( p );

	QFRemove( &q, FreeInfo );

	return 0;
}

void FreeInfo( const void* str )
{
	free( ( (QINFO*)str )->sName );
	free( (QINFO*)str );
}


QINFO* CreateElement( int nKey, char* sName )
{
	QINFO* pInt = (QINFO*)calloc( 1, sizeof( QINFO ) );
	if( pInt == NULL )
	{
		perror( "Memory Allocation problem - create pInt" );
		return NULL;
	}

	pInt->nKey = nKey;

	pInt->sName = (char*)calloc( ( strlen( sName ) + 1 ), sizeof( char ) );
	if( pInt->sName == NULL )
	{
		perror( "Memory Allocation problem - create sName" );
		return NULL;
	}

	strcpy( pInt->sName, sName );

	return pInt;
}

void PrintElement( QINFO* pInfo )
{
	static int i = 0;
	if( pInfo == NULL ) return;
	printf( "Key: %d Name: %s  \t", pInfo->nKey, pInfo->sName );
	if( ++i % LINE_SIZE == 0 ) printf( "\n" );
}