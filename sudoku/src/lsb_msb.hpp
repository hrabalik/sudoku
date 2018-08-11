#pragma once

#if defined( __GNUC__ ) // GCC, Clang

inline int lsb( unsigned int in ) { return __builtin_ctz( in ); }

inline int popcnt( unsigned int in ) { return __builtin_popcount( in ); }

#elif defined( _MSC_VER ) // Visual Studio

#include <intrin.h>

inline unsigned long lsb( unsigned __int32 in ) {
    unsigned long res;
    _BitScanForward( &res, in );
    return res;
}

inline unsigned long popcnt( unsigned __int32 in ) { return __popcnt( in ); }

#endif
