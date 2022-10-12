#include "matrix.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

//#define DEBUG

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
int CreateVector( double** pTab, int nSize );
void DeleteVector( double** pTab );
void PrintVector( double* pX, int nSize );

int main( int argc, char* argv[] )
{
    if( argc!=2 )
    {
        printf( "Usage: %s <input_file>\n", argv[0] );
        return 1;
    }

    FILE* fin = NULL;
    if( ( fin=fopen( argv[1], "rt" ) ) == NULL )
    {
        perror( "Error open input file!!\n" );
        return 2;
    }

    int nDim = 0;
    fscanf( fin, "%d", &nDim );
#ifdef DEBUG
    printf( "Matrix dim: %d\n", nDim );
#endif 
    double** pMatrix = NULL;
    double* b = NULL;
    
    if( !CreateMatrix( &pMatrix, nDim ) )
    {
        perror( "Error create matrix!!\n" );
        return 3;
    }    
    if( !CreateVector( &b, nDim ) )
    {
        perror( "Error create vector!!\n" );
        return 4;
    }

    ReadData( fin, pMatrix, b, nDim );

#ifdef DEBUG
    printf( "\nWczytana macierz: \n" );
    PrintMatrix( pMatrix, nDim );
    printf( "\nWczytany wektor wyrazow wolnych: \n" );
    PrintVector( b, nDim );
#endif 

    double det = Det( pMatrix, nDim );

#ifdef DEBUG
    printf( "\nDet(A): %0.2lf\n", det );
#endif 

    if( fabs( det ) < 1e-300 )
    {
        printf( "det(A) = 0" );
        return 7;
    }

    double** pMatrixI = NULL;
    if( !CreateMatrix( &pMatrixI, nDim ) )
    {
        perror( "Error create matrixI!!\n" );
        return 5;
    }
        
    InverseMatrix( pMatrixI, pMatrix, nDim, det );

#ifdef DEBUG
    printf("\nMacierz odwrotna: \n");
    PrintMatrix( pMatrixI, nDim );
#endif 

    double* x = NULL;
    if( !CreateVector( &x, nDim ) )
    {
        perror( "Error create vectorX!!\n" );
        return 6;
    }
        
    LayoutEqu( pMatrixI, b, x, nDim );

    printf( "\nWektor rozwiazan: \n" );
    PrintVector( x, nDim );

    DeleteVector( &x );   
    DeleteMatrix( &pMatrixI, nDim );
    
    DeleteMatrix( &pMatrix, nDim );
    DeleteVector( &b );   
    
    return 0;
}

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
    for( int i = 0; i < nDim; i++, pMatrix++ )
    {
        double* pT = *pMatrix;
        for( int j = 0; j < nDim; j++, pT++)
            fscanf( fin, "%lf", pT );
        fscanf( fin, "%lf", b++ );
    }
    fclose( fin );
}

int CreateVector( double** pTab, int nSize )
{
    *pTab = (double*)malloc( nSize * sizeof( double ) );
    if( !*(pTab) ) return 0;
    memset( *pTab, 0, nSize * sizeof( double ) );

    return 1;
}

void DeleteVector( double** pTab )
{
    free( *pTab );
    *pTab = NULL;
}

void PrintVector( double* pX, int nSize )
{
    for( int i = 0; i < nSize; i++, pX++ )
        printf( "x%d = %0.2lf\n", i + 1, *pX );
}


