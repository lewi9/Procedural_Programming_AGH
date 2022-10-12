#include "Statek.h"

#include <memory.h>
#include <stdio.h>
#include <iostream>

int move( int** pTab, int nRow, int nCol, int nDepth,
    int move, int x, int y, int* px, int* py, int** pRoot )
{
    switch( move )
    {
        case UP: *px = --x; *py = y ; break;
        case RIGHT: *px = x;  *py = ++y; break;
        case DOWN: *px = ++x; *py = y; break;
        case LEFT: *px = x; *py = --y; break;
        default: perror( "Wrong direction of move" ); break;
    }

    if( *px<0 || *px>=nRow ) return 0;
    if( *py<0 || *py>=nCol ) return 0;
    if( pTab[*px][*py] <= nDepth ) return 0;
    if( pRoot[*px][*py] != 0 ) return 0;
    /*
    *px = x;
    *py = y;
    */
    return 1;
}

int root( int** pTab, int nRow, int nCol, int nDepth,
    int x, int y, int** pRoot, int x_dest, int y_dest )
{
    static int no = 1;
    pRoot[x][y] = no++;

    if( pRoot[x_dest][y_dest] != 0 ) return 1;

    int px = 0;
    int py = 0;

    for( int i = UP; i <= LEFT; i++ )
    {
        
        if( move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
        {
            if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )
                return 1;
        }
    }
    
    pRoot[x][y] = 0;
    no--;
    return 0;
}

void clearRoot( int** pRoot, int nRow, int nCol )
{
	memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
    
    FILE* fin = NULL;
    if( ( fin = fopen( sFile, "rt" ) ) == NULL )
        return 0;

    for( int i = 0; i < nRow; i++, pTab++ )
    {
        int* pT = *pTab;
        for( int j = 0; j < nCol; j++, pT++ )
            fscanf( fin, "%d", pT );
    }
    fclose( fin );
    return 1;
}

