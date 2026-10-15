#include "types.h"
typedef unsigned __int128 u128;
typedef struct A1449F0 { u8 pad000[0x160]; u128 m160; } A1449F0;
typedef struct B1449F0 { u8 pad000[0x270]; A1449F0 *m270; } B1449F0;
void DrawEnvSetClearColor_1449f0(B1449F0 *b, u128 *src)
{
    A1449F0 *d;

    /* pinned: a plain hoist of the destination pointer is propagated back and
       mwcc issues the source `lq` first. */
    d = *(A1449F0 * volatile *)&b->m270;
    d->m160 = *src;
}
