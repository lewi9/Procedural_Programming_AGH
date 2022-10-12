#ifndef _GLOBAL_H

#define _GLOBAL_H

typedef struct
{
	int nKey;
	int* pTab;

}UserType;

#define LISTINFO UserType

int Compare( const void*, const void* );
void FreeMem( const void* );


#endif
