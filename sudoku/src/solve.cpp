#include "sudoku.hpp"
#include <algorithm>

uint8_t get_contention( const state& s, const field& f ) {
    auto row = s.used_row[ f.row ];
    auto col = s.used_col[ f.col ];
    auto square = s.used_square[ f.square ];
    return row.union_( col ).union_( square ).count();
}

void sort_empty_fields_by_contention( state& s ) {
    auto* first = s.begin_empty();
    auto* last = s.end_empty();
    std::for_each( first, last,
                   [&s]( field& f ) { f.misc = get_contention( s, f ); } );
    std::sort( first, last,
               []( field l, field r ) { return l.misc > r.misc; } );
}

bool solve( state& s ) {
    if ( s.win() ) {
        return true;
    }

    // candidate select
    sort_empty_fields_by_contention( s );
    field* f = s.begin_empty();
    s.filledCount++;

    // loop non-contended values for candidate
    auto* row = &s.used_row[ f->row ];
    auto* col = &s.used_col[ f->col ];
    auto* square = &s.used_square[ f->square ];
    value_set value_set = row->union_( *col ).union_( *square );
    while ( !value_set.all() ) {
        value v = value_set.first_not_contained();

        row->add( v );
        col->add( v );
        square->add( v );

        if ( solve( s ) ) {
            s.solution[ f->index() ] = '1' + char( lsb( v.mask ) );
            return true;
        }

        row->remove( v );
        col->remove( v );
        square->remove( v );

        value_set.add( v );
    }

    // add candidate back into empty fields
    s.filledCount--;
    return false;
}
