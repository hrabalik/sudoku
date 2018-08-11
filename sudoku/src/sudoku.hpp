#pragma once
#include "lsb_msb.hpp"
#include <cstdint>
#include <string>

struct value {
    uint16_t mask;
};

class value_set {
public:
    value_set() = default;
    value_set( const value_set& ) = default;
    value_set& operator=( const value_set& ) = default;

    void add( value v ) { m_mask |= v.mask; }
    void remove( value v ) { m_mask ^= v.mask; }

    bool all() const { return m_mask == 0x1ff; }
    uint8_t count() const { return uint8_t( popcnt( m_mask ) ); }

    value first_not_contained() const {
        return {uint16_t( 1 << lsb( ~m_mask ) )};
    }

    value_set union_( value_set vs ) const {
        return value_set( m_mask | vs.m_mask );
    }

private:
    constexpr value_set( uint16_t mask ) : m_mask( mask ) {}
    uint16_t m_mask = 0;
};

struct field {
    uint8_t row;
    uint8_t col;
    uint8_t square;
    uint8_t misc;

    int index() const { return 9 * row + col; }
};

struct state {
    field fields[ 81 ];
    value_set used_row[ 9 ];
    value_set used_col[ 9 ];
    value_set used_square[ 9 ];
    int filledCount;
    char solution[ 81 + 1 ];

    bool win() const { return filledCount == 81; }
    field* begin_empty() { return &fields[ filledCount ]; }
    field* end_empty() { return &fields[ 81 ]; }
};

struct params {
    int thresh;
};

bool solve( state& s );
void parse( const std::string& in, state& s );
