#include "FQueue.h"
#include <stdlib.h>

void  QFDel( QFIFO* q );

// kreowanie dynamiczne kolejki                                  
QFIFO* QFCreate()
{
    QFIFO* q = (QFIFO*)calloc( 1, sizeof( QFIFO ) );

    if( q == NULL )
        return NULL;

    q->pHead = (FQItem*)calloc( 1, sizeof( FQItem ) );
    if( q->pHead == NULL )
        return NULL;

    return q;
}

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
    return !q->pHead->pNext || !q;
}

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
    if( QFEmpty( q ) )
    {
        q->pTail = (FQItem*)calloc( 1, sizeof( FQItem ) );

        if( q->pTail == NULL )
            return 0;
        //
        FQItem* p = (FQItem*)calloc( 1, sizeof( FQItem ) );
        if( p == NULL )
            return 0;

        p->pInfo = pItem;
        q->pHead->pNext = q->pTail = p;

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
    QINFO* pInfo = q->pHead->pNext->pInfo;
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
    free( (*q)->pHead );
    free( *q );
    *q = NULL;
}


//-------------------------------------
// usuniecie elemenu z listy (nie info)
void  QFDel( QFIFO* q )
{
    FQItem* p = q->pHead->pNext;
    q->pHead->pNext = p->pNext;
    free( p );
}