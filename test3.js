// https://oeis.org/A000081
// Based on:
//   Comment from Joe Riel (joer(AT)san.rr.com), June 23, 2008:
//   (Start) Here is a much more efficient method for computing the result with Maple
//   a := proc(n) local k; a(n) := add(k*a*s(n-1, k), k=1..n-1)/(n-1) end proj:
//   a(0) := 0: a(1) = 1: s := proc(n, k) local j; s(n,k) := add(a(n+1-j*k), j=1..iqou(n, k)); (End)

function A000081( len ) {

    function s( n, k ) {
        var end = Math.floor( n/k );
        var sum = 0;
        for( var j = 1; j <= end; j++ )
            sum += a( n+1 - j*k );
        
        return sum;
    }

    var memo_a = [ 0, 1 ];
    function a( n ) {
        if( memo_a.hasOwnProperty(n) ) {
            return memo_a[n];   // #change
        }

        var sum = 0;
        for( var k = 1; k <= n-1; k++ ) 
            sum += k * a(k) * s( n-1, k );

        var result = sum/(n-1);
        memo_a[n] = result;         //  #change

        return result;
    }

    var result = [];
    for( var i = 0; i < len; i++ ) {
        result[i] = a(i);
    }

    return result;
}

var start  = process.hrtime();
var result = A000081( 20 );
var end    = process.hrtime(start);

console.log( result );

var time_sec = end[0];
var time_ms  = end[1] / 1000000;
console.log( time_sec + " s, " + time_ms.toFixed(3) + " ms" );

