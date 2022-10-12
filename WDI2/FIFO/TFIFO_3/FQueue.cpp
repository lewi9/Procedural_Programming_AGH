#include "FQueue.h"
#include <stdlib.h>

void  QFDel( QFIFO* q );

// kreowanie dynamiczne kolejki                                  
QFIFO* QFCreate( int nSize )
{
    if( nSize < 1 )
        return NULL;

    QFIFO* q = (QFIFO*)calloc( 1, sizeof( QFIFO ) );

    if( q == NULL )
        return NULL;
    
    q->nTail = 0;
    q->nNoElem = 0;
    q->nMaxElem = nSize;
    q->pFQItems = (QINFO**)calloc( nSize, sizeof( QINFO* ) );

    if( q->pFQItems == NULL )
        return NULL;

    return q;
}

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
    return !q->nNoElem || !q;
}

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
int QFEnqueue( QFIFO* q, QINFO* pItem )
{

    if( q->nNoElem == q->nMaxElem ) return 0;

    if( QFEmpty( q ) )
    {
        q->pFQItems[q->nTail] = pItem;
        q->nHead = q->nTail;
        q->nNoElem++;
        ( q->nTail == q->nMaxElem - 1 ) ? q->nTail = 0 : q->nTail++;

        return 1;
    }

    q->pFQItems[q->nTail] = pItem;
    q->nNoElem++;
    ( q->nTail == q->nMaxElem - 1 ) ? q->nTail = 0 : q->nTail++;

    return 1;
}

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta)
QINFO* QFDequeue( QFIFO* q )
{
    if( QFEmpty( q ) ) return NULL;
    QINFO* pInfo = q->pFQItems[q->nHead];
    QFDel( q );
    return pInfo;
}

// czyszczenie kolejki, kolejke mozna uzywac dalej
void  QFClear( QFIFO* q, void( __cdecl* FreeInfo )( const void* ) )
{
    while( !QFEmpty( q ) )
        FreeInfo( QFDequeue( q ) );
}

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie kolejki
void  QFRemove( QFIFO** q, void( __cdecl* FreeInfo )( const void* ) )
{
    QFClear( *q, FreeInfo );
    free( (*q)->pFQItems );
    free( *q );
    *q = NULL;
}


//-------------------------------------
// usuniecie elemenu z listy (nie info)
//  - wstawia NULL do pozycji tablicy, skad pobierany jest element
//  - przesuwa cyklinie indeks glowy kolejki
//  - zmniejsza ilosc elementow w kolejce
void  QFDel( QFIFO* q )
{
    q->pFQItems[q->nHead] = NULL;
    ( q->nHead == q->nMaxElem - 1 ) ? q->nHead = 0 : q->nHead++;
    q->nNoElem--;
}