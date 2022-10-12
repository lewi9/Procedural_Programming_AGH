#include "FQueue.h"
#include <stdlib.h>

void  QFDel( QFIFO* q );

// kreowanie dynamiczne kolejki                                  
QFIFO* QFCreate()
{
    return (QFIFO*)calloc( 1, sizeof( QFIFO ) );
}

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
    return !q->pHead || !q; //Sprawdza czy g³owa jest, czyli czy jest jakiœ element w kolejsce 
    //i czy kolejka istnieje
}

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
    if( QFEmpty( q ) )
    {
        q->pHead = (FQItem*)calloc( 1, sizeof( FQItem ) );
        q->pTail = (FQItem*)calloc( 1, sizeof( FQItem ) );

        if( q->pHead == NULL || q->pTail == NULL )
            return 0;

        q->pHead->pInfo = pItem;
        q->pTail = q->pHead;

        return 1;
    }

    FQItem* p = (FQItem*)calloc( 1, sizeof( FQItem ) );
    if( p == NULL )
        return 0;
    p->pInfo = pItem;
    q->pTail->pNext = p;
    q->pTail = p;
    return 1;
}

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta)
QINFO* QFDequeue( QFIFO* q )
{
    if( QFEmpty( q ) ) return NULL;
    QINFO* pInfo = q->pHead->pInfo;
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
    free( *q );
    *q = NULL;
}


//-------------------------------------
// usuniecie elemenu z listy (nie info)
void  QFDel( QFIFO* q )
{
    FQItem* p = q->pHead;
    q->pHead = p->pNext;
    free( p );
}