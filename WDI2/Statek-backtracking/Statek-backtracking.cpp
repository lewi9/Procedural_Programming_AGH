#include "Statek.h"

#include <stdio.h>
#include <stdlib.h>
#include<memory.h>



int** CreateMatrix( int nRow, int nCol );
void DeleteMatrix( int*** pTab, int nRow, int nCol );
void PrintMatrix( int** pTab, int nRow, int nCol );

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        printf( "Usage: %s <input_file>\n", argv[0] );
        return 1;
    }

    int** pTab = NULL;
    if( !( pTab = CreateMatrix( ROWS, COLS ) ) )
    {
        perror( "Error allocation memory" );
        return 2;
    }

    int** pRoot = NULL;
    if( !( pRoot = CreateMatrix( ROWS, COLS ) ) )
    {
        perror( "Error allocation memory" );
        return 3;
    }

    if( !setTab( argv[1], pTab, ROWS, COLS ) )
    {
        perror( "Error open input file!!\n" );
        return 4;
    }

    printf( "Map of depths: \n" );
    PrintMatrix( pTab, ROWS, COLS );
    printf( "\n" );


    if( root( pTab, ROWS, COLS, DEPTH_MIN, 0, 0, pRoot, ROWS - 1, COLS - 1 ) )
    {
        printf( "Route to port: \n" );
        PrintMatrix( pRoot, ROWS, COLS );
    }
    else
        printf( "It's not possible to arrive to port" );

    DeleteMatrix( &pTab, ROWS, COLS );
    DeleteMatrix( &pRoot, ROWS, COLS );

    return 0;
}

int** CreateMatrix( int nRow, int nCol )
{
    int** pTab = (int**)malloc( nRow * sizeof( int* ) );
    if( !pTab ) return NULL;
    memset( pTab, 0, nRow * sizeof( int* ) );

    *pTab = (int*)malloc( nRow * nCol * sizeof( int ) );
    if( *pTab == NULL ) return NULL;
    //memset( *pTab, 0, nRow * nCol * sizeof( int ) );
    clearRoot( pTab, nRow, nCol );

    int** pT = pTab + 1;
    int* p = *pTab + nCol;
    for( int i = 1; i < nRow; i++, pT++, p+=nCol)
        *pT = p;

    return pTab;
}

void DeleteMatrix( int*** pTab, int nRow, int nCol )
{
    free( **pTab );
    free( *pTab );
    *pTab = NULL;
}

void PrintMatrix( int** pTab, int nRow, int nCol )
{
    for( int i = 0; i < ROWS; i++, pTab++ )
    {
        int* pT = *pTab;
        for( int j = 0; j < COLS; j++, pT++ )
        {
            if( *pT > 99 )
                printf( "%d ", *pT );
            else if( *pT > 9 )
                printf( "%d  ", *pT );
            else
                printf( "%d   ", *pT );
        }

        printf( "\n" );
    }
}

