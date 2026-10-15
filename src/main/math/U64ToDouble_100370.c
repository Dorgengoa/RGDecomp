#include "types.h"
extern f64 S64ToDouble_13a998(s64);
f64 U64ToDouble_100370(u64 x) {
    f64 r;
    if ((s64)x > 0) return S64ToDouble_13a998(x);
    r = S64ToDouble_13a998((x >> 1) | (x & 1));
    return r + r;
}
