#include "types.h"

typedef unsigned __int128 u128;

extern void SplineInit_257860(void *);

struct Obj0 {
    u128 m000[0x10];
    u128 m100[0x10];
    s32 m200;
    s32 m204;
    u8 m208[0x39C];
    u8 m5A4[0x39C];
    s32 m940;
};

void SplinePathPairReset_257030(struct Obj0 *p0)
{
    s32 i;

    for (i = 0; i < 0x10; i++) {
        p0->m000[i] = 0;
        p0->m100[i] = 0;
    }
    p0->m200 = 0;
    p0->m940 = 0;
    p0->m204 = 0;
    SplineInit_257860(p0->m208);
    SplineInit_257860(p0->m5A4);
}
