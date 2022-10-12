#include "Sort.h"
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>


#define DEBUG

#define DEBUG_PRINT_VAR 40
#define NLINE 10

int CreateTab( int** pTab, int nSize );
void DeleteTab( int** pTab );
void InitTab( int* pTab, int nSize );
void PrintTab( int* pTab, int nSize );

typedef void ( *pFun )( int*, int );

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        printf( "Usage: %s <Size of table>\n", argv[0] );
        return 1;
    }

    int size = atoi( argv[1] );

    int* pTab = NULL;
    if( !CreateTab( &pTab, size ) )
    {
        perror( "Memory allocation error - pTab" );
        return 2;
    }

    pFun pSortTab[] = { InsertSort , SelectionSort, BubbleSort, MixSort, HalfSort, QuickSort, HeapSort };
    const char* pNames[] = { "InsertSort", "SelectionSort", "BubbleSort", "MixSort", "HalfSort", "QuickSort", "HeapSort" };

    InitTab( pTab, size );

    printf( "Ilosc elementow do posortowania: %d\n", size );

#ifdef DEBUG
    printf( "Pierwsze %d elementow tablicy do posortowania: ", ( DEBUG_PRINT_VAR > size ) ? ( size ) : ( DEBUG_PRINT_VAR ) );
    PrintTab( pTab, ( DEBUG_PRINT_VAR > size ) ? ( size ) : ( DEBUG_PRINT_VAR ) );
#endif 

    int* pCpTable = NULL;
    if( !CreateTab( &pCpTable, size ) )
    {
        perror( "Memory allocation error - pCpTable" );
        return 3;
    }


    int iterations = sizeof( pSortTab ) / sizeof( pFun );
    for( int i = 0; i < iterations ; i++ )
    {
        memcpy( pCpTable, pTab, sizeof( int ) * size );
        clock_t start = clock();
        pSortTab[i]( pCpTable, size );
        clock_t end = clock();
        printf( "\nCzas sortowania tablicy za pomoca metody %s: %lf sekund\n", pNames[i], (double)( end - start ) / CLOCKS_PER_SEC );
        printf( "Czas sortowania tablicy za pomoca metody %s: %0.2lf ms\n", pNames[i], (double)( end - start ) / CLOCKS_PER_SEC * 1000 );

#ifdef DEBUG
        printf( "Pierwsze %d elementow posortowane metoda %s: ", ( DEBUG_PRINT_VAR > size ) ? ( size ) : ( DEBUG_PRINT_VAR ), pNames[i] );
        PrintTab( pCpTable, ( DEBUG_PRINT_VAR > size ) ? ( size ) : ( DEBUG_PRINT_VAR ) ); 
#endif 

    }

    DeleteTab( &pTab );
    DeleteTab( &pCpTable );
    return 0;
}

int CreateTab( int** pTab, int nSize )
{
    *pTab = (int*)malloc( nSize * sizeof( int ) );
    if( !*( pTab ) ) return 0;
    memset( *pTab, 0, nSize * sizeof( int ) );

    return 1;
}

void DeleteTab( int** pTab )
{
    free( *pTab );
    pTab = NULL;
}

void InitTab( int* pTab, int nSize )
{
    srand( (unsigned int)time( NULL ) );
    for( int i = 0; i < nSize; i++, pTab++ )
        *pTab = rand();
}

void PrintTab( int* pTab, int nSize )
{
    for( int i = 0; i < nSize; i++, pTab++ )
    {
        if( !( i % NLINE ) ) printf( "\n" );  
        printf( "%d\t", *pTab );
    }
    printf( "\n" );
}