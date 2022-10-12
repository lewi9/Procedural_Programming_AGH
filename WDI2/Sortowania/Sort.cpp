#include "Sort.h"

void sort( int* tab, int l, int p );
void update( int l, int p, int* tab );

void InsertSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int temp = tab[i];
		int j = i - 1;

		while( tab[j] > temp && j>=0 )
			tab[j + 1] = tab[j--];

		tab[j + 1] = temp;
	}
}

void SelectionSort( int* tab, int nSize )
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		int k = i;
		int temp = tab[i];
		for( int j = i + 1; j < nSize; j++ )
			if( tab[j] < temp )
			{
				k = j;
				temp = tab[j];
			}
		tab[k] = tab[i];
		tab[i] = temp;
	}
}

void BubbleSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
		for( int j = nSize - 1; j >= i; j-- )
			if( tab[j - 1] > tab[j] )
			{
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
			}
}

void MixSort( int* tab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize - 1;
	do
	{
		for( int j = p; j >= l; j-- )
			if( tab[j - 1] > tab[j] )
			{
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
				k = j;
			}
		l = k + 1;
		for( int j = l; j < p; j++ )
			if( tab[j - 1] > tab[j] )
			{
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
				k = j;
			}
		p = k - 1;

	}while( l <= p );
}

void HalfSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int temp = tab[i];
		int l = 0;
		int p = i - 1;

		while( l <= p )
		{
			int m = ( l + p ) / 2;
			if( tab[m] > temp )
				p = m - 1;
			else
				l = m + 1;
		}

		for( int j = i - 1; j >= l; j-- )
			tab[j + 1] = tab[j];

		tab[l] = temp;
	}
}

void QuickSort( int* tab, int nSize )
{
	sort( tab, 0, nSize - 1 );
}

void sort( int* tab, int l, int p )
{
	int i = l;
	int j = p;
	int temp = tab[ ( l + p ) / 2 ];
	do
	{
		while( tab[i] < temp ) i++;
		while( temp < tab[j] ) j--;
		if( i <= j )
		{
			int w = tab[i];
			tab[i] = tab[j];
			tab[j] = w;
			i++;
			j--;
		}
		
	} while( j >= i );

	if( l < j ) sort( tab, l, j );
	if( i < p ) sort( tab, i, p );
}

void HeapSort( int* tab, int nSize )
{
	int l = nSize / 2;
	int p = nSize - 1;

	/*while( l-- > 0 )
		update( l, p, tab );
	*/

	for( int i = l-1; i > 0; i-- )
		update( i, p, tab );

	for( int i = p; i>0; i-- )
	{
		int temp = tab[0];
		tab[0] = tab[i];
		tab[i] = temp;
		update( 0, i-1, tab );
	}
}

void update( int l, int p, int* tab )
{
	if( l==p ) return;
	int i = l;
	int j = 2 * i + 1;
	int temp = tab[i];
	while( j <= p )
	{
		if( j < p )
			if( tab[j] <= tab[j + 1] ) 
				j++;

		if( tab[j] < temp )
			break;
		tab[i] = tab[j];
		i = j;
		j = 2 * i + 1;
	}
	tab[i] = temp;
}