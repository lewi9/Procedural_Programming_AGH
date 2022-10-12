#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "PQueue.h"

#define QSIZE 20
#define LIMIT 50
#define TABSIZE 2
#define ELEMENTS 6
#define FIND_ELEMENT 4
#define DOWN_INDEX 5
#define GET_PRIOR_INDEX 2

#define MACRO1 ELEMENTS+2

//#define DEBUG //w celu sprawdzania co się dzieje, jak dwa elementy mają ten sam prior

void PrintInfo( void const* );
int CompareInfo( void const*, void const* ); //Zwraca - 1 pierwszy mniejszy, 1 jesli pierwszy wiekszy else 0.
void FreeInfo( void const* );
PQINFO* CreateElement( int nKey, int nIndex );


int main()
{
    srand( unsigned int( time( NULL ) ) );

    PQueue* q = PQInit( QSIZE );
    if( q == NULL )
    {
        perror( "Error with create a queue" );
        return 1;
    }

    for( int i = 0; i < ELEMENTS; i++ )
        if( !PQEnqueue( q, rand() % LIMIT, CreateElement( i, i ) ) )
            printf( "Problem with adding element [key: %d] to the queue - overflow or allocation problem\n\n", i );  
            
        
    printf( "Kolejka po dodaniu %d elementow: \n", ELEMENTS );
    PQPrint( q, PrintInfo, 0 );

    PQINFO* p = PQDequeue( q );
    printf( "\nUsuniety element: " );
    PrintInfo( p );
    FreeInfo( p );

    for( int i = ELEMENTS; i < MACRO1; i++ )
        if( !PQEnqueue( q, rand() % LIMIT, CreateElement( i, i ) ) )
            printf( "Problem with adding element [key: %d] to the queue - overflow or allocation problem\n", i );

    printf( "\nKolejka po dodatniu dodatkowych %d elementow: \n", MACRO1 - ELEMENTS );
    PQPrint( q, PrintInfo, 0 );

    PQINFO* x = CreateElement( FIND_ELEMENT, FIND_ELEMENT );
    if( PQSetPrior( q, CompareInfo, x, PQMaxPrior( q ) + 1 ) != PRIOR_ERROR )
    {
        printf( "\nKolejka po zwiekszeniu priorytetu elementowi o kluczu %d: \n", FIND_ELEMENT );
        PQPrint( q, PrintInfo, 0 );
    }
    else
        printf( "\nElementu o kluczu %d nie ma w kolejce. Zmiana priorytetu zakonczona niepowodzeniem\n", FIND_ELEMENT );
    

    if( PQsetPrior( q, DOWN_INDEX, -PQMaxPrior( q ) ) != PRIOR_ERROR )
    {
        printf( "\nKolejka po zmniejszeniu priorytetu elementowi o indexie %d w tablicy kolejki: \n", DOWN_INDEX );
        PQPrint( q, PrintInfo, 0 );
    }
    else
        printf( "\nElementu o indexie %d nie ma w kolejce. Zmiana priorytetu zakonczona niepowodzeniem\n", DOWN_INDEX );
    

    printf( "\nPriorytet elementu o indexie %d w tablicy kolejki: %d\n", 
            GET_PRIOR_INDEX, PQgetPrior( q, GET_PRIOR_INDEX ) );

    x = CreateElement( DOWN_INDEX, DOWN_INDEX );
    printf( "\nPriorytet elementu o kluczu %d: %d\n", DOWN_INDEX, PQGetPrior( q, CompareInfo, x ) );
    

#ifdef DEBUG
    PQsetPrior( q, 3, PQMaxPrior( q ) + 1 );
    PQsetPrior( q, 4, PQMaxPrior( q ) + 1 );

    p = PQDequeue( q );
    printf( "\nUsuniety element: " );
    PrintInfo( p );
    FreeInfo( p );

    p = PQDequeue( q );
    printf( "\nUsuniety element: " );
    PrintInfo( p );
    FreeInfo( p );

    printf( "\nKolejka po zmianie priorytetu, aby dwa elementy mialy takie same oraz ich usunieciu: \n" );
    PQPrint( q, PrintInfo, 0 );
#endif

    PQRelease( &q, FreeInfo );

    return 0;
}

void PrintInfo( void const* pInfo )
{
    if( pInfo == NULL ) return;
    printf( "Klucz: %d, pT[0]: %d, pT[1]: %d\n", ( (PQINFO*)pInfo )->nKey, 
            *( (PQINFO*)pInfo )->pTab, ( (PQINFO*)pInfo )->pTab[1] );
}

int CompareInfo( const void* x, const void* y ) 
{
    if( ( (PQINFO*)x )->nKey > ( (PQINFO*)y )->nKey ) return 1;
    if( ( (PQINFO*)x )->nKey < ( (PQINFO*)y )->nKey ) return -1;
    return 0;
} 

void FreeInfo( void const* pT )
{
    if( pT == NULL ) return;
    int* p = ( (PQINFO*)pT )->pTab;
    free( p );
    free( (PQINFO*)pT );
}

PQINFO* CreateElement( int nKey, int nIndex )
{
    PQINFO* pInt = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
    if( pInt == NULL )
    {
        perror( "Memory Allocation problem - create pInt - CreateElement\n" );
        return NULL;
    }
    pInt->nKey = nKey;
    pInt->pTab = (int*)calloc( TABSIZE, sizeof( int ) );
    if( pInt->pTab == NULL )
    {
        perror( "Memory Allocation problem - create pInt->pTab - CreateElement\n" );
        return NULL;
    }
    pInt->pTab[0] = nIndex;
    return pInt;
}