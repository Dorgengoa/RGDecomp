#include "types.h"

extern void EntryGetGridSize_323bb0(void *, s32 *, s32 *);

s32 EntryGridGetCell_323a60(s32 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 prod;

    EntryGetGridSize_323bb0(arg0, &a, &b);
    prod = a * b;
    if (arg1 < 0 || arg1 >= prod) {
        return 0;
    }
    return *arg0 + arg1 * 3;
}
