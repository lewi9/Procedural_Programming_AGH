#ifndef _STATEK_H
#define _STATEK_H

#define DEPTH_MIN 5
#define ROWS 10
#define COLS 10

typedef enum{ UP, RIGHT, DOWN, LEFT } direction;

int move( int** pTab, int nRow, int nCol, int nDepth,
    int move, int x, int y, int* px, int* py, int** pRoot );

int root( int** pTab, int nRow, int nCol, int nDepth,
	int x, int y, int** pRoot, int x_dest, int y_dest );

void clearRoot( int** pRoot, int nRow, int nCol );

int setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif
