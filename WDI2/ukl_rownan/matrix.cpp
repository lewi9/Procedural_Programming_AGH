#include "matrix.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( double** pTabD, double** pTab, int nDim );


int CreateMatrix( double*** pTab, int nDim )
{
	*pTab = (double**)malloc( nDim * sizeof( double* ) );
	if( *pTab == NULL ) return 0;
	memset( *pTab, 0, nDim * sizeof( double* ) );

	double** pT = *pTab;

	for( int i = 0; i < nDim; i++, pT++)
	{
		*pT = (double*)malloc( nDim * sizeof( double ) );
		if( *pT == NULL ) return 0;
		memset( *pT , 0, nDim * sizeof( double ) );
	}
	return 1;
}

void DeleteMatrix( double*** pTab, int nDim )
{
	double** pT = *pTab;
	for( int i = 0; i < nDim; i++, pT++ )
		free( *pT );
	free( *pTab );
	*pTab = NULL;
}

void TransMatrix( double** pTab, int nDim )
{
	double** pT = pTab;
	for( int i = 0; i < nDim-1; i++, pT++ )
	{ 
		double* pTT = *pT + i + 1;
		for( int j = i+1; j < nDim; j++, pTT++ )
		{
			double temp = *pTT;
			*pTT = pTab[j][i];
			pTab[j][i] = temp;
		}
	}
}

void InverseMatrix( double** pInv, double** pTab, int nDim, double det )
{
	ComplMatrix( pInv, pTab, nDim );
	TransMatrix( pInv, nDim );

	for( int i = 0; i < nDim; i++, pInv++ )
	{
		double* pTInv = *pInv;
		for( int j = 0; j < nDim; j++, pTInv++ )
			*pTInv /= det;
	}
}

double Det( double** pTab, int nDim )
{
	if( nDim == 1 ) return **pTab;
	if( nDim == 2 ) return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];


	double** pTabO = NULL;
	if( !CreateMatrix( &pTabO, nDim - 1 ) )
	{
		perror( "Error create matrix in det calc!!\n" );
		return 0;
	}

	double det = 0;
	double* pT = *pTab;
	int sgn = 1;
	for( int j = 0; j < nDim; j++, pT++ )
	{
		Complement( pTabO, pTab, 0, j, nDim );

		det += *pT * Det( pTabO, nDim-1)*sgn;
		sgn = -sgn;
	}
	DeleteMatrix( &pTabO, nDim - 1 );
	return det;
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim )
{
	for( int i = 0; i < nDim; i++, pInv++, pRes++ )
	{
		double* pTInv = *pInv;
		double *pTB = pB;
		for( int j = 0; j < nDim; j++, pTInv++, pTB++ )
			*pRes += *pTInv * *pTB;
	}
}

void PrintMatrix( double** pTab, int nDim )
{
	for( int i = 0; i < nDim; i++, pTab++ )
	{
		double* pT = *pTab;
		for( int j = 0; j < nDim; j++, pT++ )
			printf( "%0.3lf\t", *pT );
		printf( "\n" );
	}
}

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{
	for( int i = 0; i < nDim; i++, pTabI++ )
	{
		if( i == nRow ) continue;
		double* pTI = *pTabI;
		double* pTO = *pTabO++;
		for( int j = 0; j < nDim; j++, pTI++ )
		{
			if( j == nCol ) continue;
			*pTO++ = *pTI;
		}
	}
}

void ComplMatrix( double** pTabD, double** pTab, int nDim )
{

	double** pTabO = NULL;
	if( !CreateMatrix( &pTabO, nDim - 1 ) )
	{
		perror( "Error create matrix in ComplMatrix!!\n" );
		return;
	}

	for( int i = 0; i < nDim; i++, pTabD++ )
	{
		double* pTD = *pTabD;
		
		int sgn = ( i % 2 ) ? -1 : 1;

		for( int j = 0; j < nDim; j++, pTD++ )
		{
			Complement( pTabO, pTab, i, j, nDim );

			*pTD = Det( pTabO, nDim - 1 ) * sgn;
			sgn = -sgn;
		}
		
	}

	DeleteMatrix( &pTabO, nDim - 1 );
}

