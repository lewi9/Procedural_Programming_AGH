#pragma once

#include "Global.h"

#define PRIOR_ERROR  -2147483648
#define POS_ERROR   -1

typedef struct tagPQItem   
{
    PQINFO* pInfo;       
    int nPrior;      
} PQItem;         

typedef struct   
{
    PQItem** pPQueue;     
    int nPQSize;     
    int nPQCurrSize;  

} PQueue;

PQueue* PQInit( int nSize );    
              //zwraca wskasnik do utworzonej kolejki lub NULL jesli kreacja sie nie powiedzie

int PQisEmpty( PQueue* q ); 
              // zwraca 1 lub 0 - kolejka pusta/nie pusta

int PQSize( PQueue* q );    
              // zwraca ilosc elementow w kolejce

int PQMaxPrior( PQueue* q ); 
              // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR

int PQEnqueue( PQueue* q, int nPrior, PQINFO* pInfo ); 
              // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)

PQINFO* PQDequeue( PQueue* q );  
              // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie

void PQClear( PQueue* q, void( __cdecl* FreeInfo )( const void* ) );    
              // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura do zwolnienia 
              // dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 

void PQRelease( PQueue** q, void( __cdecl* FreeInfo )( const void* ) );  
              // zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto wczesniej (czyszczenie kolejki)

void PQPrint( PQueue* q, void( __cdecl* PrintInfo )( const void* ), int nRoot );
              // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika przekazac 
              // trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach oraz pozycje w 
              // kolejce w kwadratowych nawiasach

int PQSetPrior( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo, int nPrior );
              // ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba wyszukac
              // dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR 
int PQsetPrior( PQueue* q, int nIndex, int nPrior );
              // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce (indeks w tablicy),
              // Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 

int PQGetPrior( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo );
              // zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która trzeba wyszukac
              // dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  

int PQgetPrior( PQueue* q, int nIndex ); 
              // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR

int PQFind( PQueue* q, int( __cdecl* CompareInfo )( const void*, const void* ), PQINFO* pInfo );
              // zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
              // przekazac trzeba funkjce porownujaca informacje uzytkownika
              // Zwaraca POS_ERROR jesli nie ma info w kolejce