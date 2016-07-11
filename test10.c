// https://oeis.org/A000081
// Based on:
//   Comment from Joe Riel (joer(AT)san.rr.com), June 23, 2008:
//   (Start) Here is a much more efficient method for computing the result with Maple
//   a := proc(n) local k; a(n) := add(k*a*s(n-1, k), k=1..n-1)/(n-1) end proj:
//   a(0) := 0: a(1) = 1: s := proc(n, k) local j; s(n,k) := add(a(n+1-j*k), j=1..iqou(n, k)); (End)

#include <stdio.h>
#include <stdint.h>
#include <string.h> // MSVC malloc.h: alloca()
#include <string.h>
#ifdef _MSC_VER
    #include <intrin.h>
#else
    #include <x86intrin.h>
#endif
#include <time.h> // missing?
void
A000081( int len, uint64_t* a )
{
    size_t size = sizeof( uint64_t) * len * len;
    uint64_t* ak = (uint64_t*) alloca( size );
    memset( ak, 0, size );

    a[0] = 0;
    a[1] = 1;

    int c0_ndx = len+1;
    int d0_ndx = c0_ndx +   len;
    int sh_len = len-1;

    for( int n = 2; n < len; n++ )
    {
        uint64_t sum   = 0;
        int      end   = n-1;
        int      a_ndx = end;
        int      c_ndx = c0_ndx;
        int      d_ndx = d0_ndx;

        for( int k = 1; k <= end; k++ )
        {
            uint64_t A  = a[ a_ndx ];
            uint64_t B  = a[ k ];
            uint64_t C  = ak[ c_ndx ];
            uint64_t D  = (A * B) + C;

            ak[ d_ndx ] = D;
            sum        += (D * k);

            a_ndx--;
            d_ndx++;
            c_ndx -= sh_len;

        }
        a[n] = sum / end;
        c0_ndx += len;
        d0_ndx += len;
    }
}

int
main( const int nArg, const char* aArg[] )
{
    int    len  = (nArg > 1) ? atoi( aArg[1] ) : 45;
    size_t size = sizeof( uint64_t) * len;
    uint64_t* p = alloca( size );

    clock_t start = clock();

        A000081( len, p );

    clock_t end   = clock();
    clock_t ticks = end - start;
    float   ms    = ticks * 1000 / (float) CLOCKS_PER_SEC;

    for( int i = 0; i < len; i++ )
        printf( "%d: %0llX\n", i, p[i] );

printf( "%lu ticks; %f ms  (Ticks/Sec) = %d\n", ticks, ms, CLOCKS_PER_SEC );

    return 0;
}

