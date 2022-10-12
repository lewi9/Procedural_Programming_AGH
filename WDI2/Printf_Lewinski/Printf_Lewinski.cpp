#include <stdarg.h>
#include <stdio.h>
#include <iostream>

#define DO_PRE 8

void outDec( int x );
void outChar( char c );
void outStr( const char* s);
void outDouble( double x);
void outNum(int x);

void Printf( const char* sFormat, ... );
void PrintfV( const char* sFormat, va_list arg_list );


int main()
{
    int n = -0;
    char c = '$';
    double x = 120.345000000012;
    double y = -.12;
    double z = -0.5;
    const char* str = "To jest string";

    Printf( "%s\n%f%c n=%d \\ % /\ny=%f\n\n  ` ` `   z=%f\n\n%", str, x, c, n, y, z );

    return 0;
}

void Printf( const char* sFormat, ... )
{
    va_list args;
    va_start( args, sFormat );
    PrintfV( sFormat, args );
    va_end( args );

}

void PrintfV( const char* sFormat, va_list arg_list )
{
    char c;
    while(  c = *sFormat++ )
    {
        switch( c )
        {
            
            case '%':
                    switch( c = *sFormat++ )
                    {
                    case 'd': outDec( va_arg( arg_list, int ) ); break;
                    case 'f': outDouble( va_arg( arg_list, double ) ); break;
                    case 'c': outChar( va_arg( arg_list, char ) ); break;
                    case 's': outStr( va_arg( arg_list, const char* ) ); break;
                    default: outChar( '%' ); if( c ) outChar( c ); else *sFormat-- ;
                    }
                    break;
            case '`': c = '\'';
            default: outChar( c );
        }
    }

}
void outDec( int x )
{
    if( x<0 )
    {
        outChar( '-' );
        x = -x;
    }
    outNum( x );
}

void outChar( char c )
{
    putchar( c );
}

void outStr( const char* s )
{
    while( *s ) outChar( *s++ );
}

void outDouble( double x )
{
    if( x<0 )
    {
        outChar( '-' );
        x = -x;
    }
    outNum( int(x) );
    outChar( '.' );
    for( int i = 0; i<DO_PRE && ( ( x - int(x) ) > 1e-6 ); i++ )
    {
        outChar( int(x *= 10)%10 +'0' );
    }
}

void outNum(int x)
{
    if( x/10>0 ) outNum( x/10 );
    outChar( x%10 + '0' );
}
