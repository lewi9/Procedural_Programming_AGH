#include <stdlib.h>
#include <stdio.h>

#include "PQueue.h"

void UpdateDown( int l, int p, PQItem** tab );  
void UpdateUp( int l, int p, PQItem** tab );  
PQINFO* PQDeQueue( PQueue* q );
void PQEnQueue( PQueue* q, PQItem* p );

PQueue* PQInit( int nSize )
{
    PQueue* q = (PQueue*)calloc( 1, sizeof( PQueue ) );
    if( q == NULL )
        return NULL;
    q->nPQSize = nSize;
    q->nPQCurrSize = 0;
    q->pPQueue = (PQItem**)calloc( nSize, sizeof( PQItem* ) );

    if( q->pPQueue == NULL )
        return NULL;

    return q;
}

int PQisEmpty( PQueue* q )
{
    return !( q->nPQCurrSize );
}

int PQSize( PQueue* q )
{
    return q->nPQCurrSize;
}

int PQMaxPrior( PQueue* q ) 
{
    if( PQisEmpty( q ) ) return PRIOR_ERROR;
    return q->pPQueue[0]->nPrior;
}

int PQEnqueue( PQueue* q, int nPrior, PQINFO* pInfo )  
{
    if( PQSize( q ) == q->nPQSize ) return 0;
    PQItem* p = (PQItem*)calloc( 1, sizeof( PQItem ) );
    if( p == NULL )
        return 0;
    p->nPrior = nPrior;
    p->pInfo = pInfo;
    PQEnQueue( q, p );
    q->nPQCurrSize++;
    return 1;
}

PQINFO* PQDequeue( PQueue* q )
{
    return ( PQisEmpty( q ) ) ? NULL : PQDeQueue( q );
}

void PQClear( PQueue* q, void( __cdecl* FreeInfo )( const void* ) )
{
    while( !PQisEmpty( q ) )
        FreeInfo( PQDequeue( q ) );
}

void PQRelease( PQueue** q, void( __cdecl* FreeInfo )( const void* ) )
{
    PQClear( *q, FreeInfo );
    free( *q );
    *q = NULL;
}

void PQPrint( PQueue* q, void( __cdecl* PrintInfo )( const void* ), int nRoot )
{
    if( PQisEmpty( q ) ) return;
    printf( "(%d)[%d] ", q->pPQueue[nRoot]->nPrior, nRoot );
    PrintInfo( q->pPQueue[nRoot]->pInfo );
    if( nRoot * 2 + 1 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 1 );
    if( nRoot * 2 + 2 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 2 );
}

int PQSetPrior( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo, int nPrior )
{
    int i = PQFind( q, CompareInfo, pInfo );
    if( i == POS_ERROR ) return PRIOR_ERROR;
    int t = q->pPQueue[i]->nPrior;
    q->pPQueue[i]->nPrior = nPrior;
    ( q->pPQueue[i]->nPrior > q->pPQueue[ (i-1) / 2 ]->nPrior ) ? 
        UpdateUp( 0, i, q->pPQueue ) : UpdateDown( i, q->nPQCurrSize - 1, q->pPQueue );
    return t;
}
int PQsetPrior( PQueue* q, int nIndex, int nPrior )
{
    if( nIndex >= q->nPQCurrSize ) return PRIOR_ERROR;
    int t = q->pPQueue[nIndex]->nPrior;
    q->pPQueue[nIndex]->nPrior = nPrior;
    ( q->pPQueue[nIndex]->nPrior > q->pPQueue[ (nIndex-1) / 2 ]->nPrior ) ?
        UpdateUp( 0, nIndex, q->pPQueue ) : UpdateDown( nIndex, q->nPQCurrSize - 1, q->pPQueue );
    return t;
}

int PQGetPrior( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo )
{
    int i = PQFind( q, CompareInfo, pInfo );
    return ( i == POS_ERROR ) ? PRIOR_ERROR : q->pPQueue[i]->nPrior;
}

int PQgetPrior( PQueue* q, int nIndex )
{
    return (nIndex>=q->nPQCurrSize)? PRIOR_ERROR : q->pPQueue[nIndex]->nPrior;
}

int PQFind( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo )
{
    for( int i = 0; i < q->nPQCurrSize; i++ )
        if( !CompareInfo( pInfo, q->pPQueue[i]->pInfo ) ) return i;
    return POS_ERROR;
}

//===================================================================
//===================================================================

void UpdateDown( int l, int p, PQItem** tab )
{
    if( l == p ) return;
    int i = l;
    int j = 2 * i + 1;
    PQItem* temp = tab[i];
    while( j <= p )
    {
        if( j < p )
            if( tab[j]->nPrior <= tab[j + 1]->nPrior )
                j++;

        if( tab[j]->nPrior < temp->nPrior )
            break;
        tab[i] = tab[j];
        i = j;
        j = 2 * i + 1;
    }
    tab[i] = temp;
}

void UpdateUp(int l, int p, PQItem** tab )
{
    for( int i = p; p >= l; i = (i-1) / 2 )
    {
        if( tab[i]->nPrior > tab[ (i-1) / 2 ]->nPrior )
        {
            PQItem* temp = tab[ (i-1) / 2 ];
            tab[ (i-1) / 2 ] = tab[i];
            tab[i] = temp;
            continue;
        }
        break;
    }
}

PQINFO* PQDeQueue( PQueue* q )
{
    PQItem* p = q->pPQueue[0];
    PQINFO* pInfo = p->pInfo;
    free( p );
    q->nPQCurrSize--;
    q->pPQueue[0] = q->pPQueue[q->nPQCurrSize];
    UpdateDown( 0, q->nPQCurrSize-1, q->pPQueue );
    return pInfo;
}

void PQEnQueue( PQueue* q, PQItem* p )
{
    q->pPQueue[q->nPQCurrSize] = p;
    UpdateUp( 0, q->nPQCurrSize, q->pPQueue );
}