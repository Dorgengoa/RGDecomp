/* main s27m: CLOSED as a C++ STRUCT ASSIGNMENT. The five lh/sh, two lb/sb, the
   16-trip pair loop and the two trailing lh/sh are ONE implicit copy of a
   0x30-byte struct whose fields are five SEPARATE s16s (an s16[5] array is
   copied as a loop), two s8s, a 16-element array of {s8,s8} and two s16s. */
#include "types.h"

struct P1E42A0 {
    s8 a;
    s8 b;
};

struct S1E42A0 {
    s16 h0;
    s16 h1;
    s16 h2;
    s16 h3;
    s16 h4;
    s8 c0;
    s8 c1;
    P1E42A0 pr[16];
    s16 t0;
    s16 t1;
};

extern "C" void MapAreaTreeFlagsPush_1db700(void *arg0);

extern "C" void MapSaveState_1e42a0(void *arg0) {
    u8 *p;
    u8 *rec;
    s32 i;
    p = (u8 *)arg0;
    *(S1E42A0 *)(p + 0x30) = *(S1E42A0 *)(p + 0x0);
    *(s32 *)(p + 0xD0) = *(s32 *)(p + 0xCC);
    rec = p + 0x1928;
    i = 0;
    do {
        MapAreaTreeFlagsPush_1db700(rec);
        i += 1;
        rec += 0x1CC;
    } while (i < 4);
}
