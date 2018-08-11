#include "sudoku.hpp"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <stdexcept>

void parse( const std::string& in, state& s ) {
    std::memset( &s, 0, sizeof( state ) );

    if ( in.size() != 81 ) {
        throw std::runtime_error( "unexpected input string length" );
    }

    int idx = 0;
    for ( int row = 0; row < 9; row++ ) {
        for ( int col = 0; col < 9; col++, idx++ ) {
            int square = 3 * ( row / 3 ) + ( col / 3 );
            char c = in[ idx ];
            field* f = &s.fields[ idx ];
            f->row = uint8_t( row );
            f->col = uint8_t( col );
            f->square = uint8_t( square );

            if ( c == '.' || c == '0' ) {
                f->misc = 0;
            } else if ( std::isdigit( c ) ) {
                f->misc = c - '0';
                value v;
                v.mask = 1 << ( f->misc - 1 );
                s.used_row[ row ].add( v );
                s.used_col[ col ].add( v );
                s.used_square[ square ].add( v );
                s.solution[ idx ] = c;
            } else {
                throw std::runtime_error(
                    "unexpected character in the input string" );
            }
        }
    }

    field* first_empty = std::partition(
        s.fields, s.fields + 81, []( field f ) { return f.misc != 0; } );
    s.filledCount = int( first_empty - s.fields );
}
