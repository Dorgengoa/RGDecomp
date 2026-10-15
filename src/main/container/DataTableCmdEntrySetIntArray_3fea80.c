#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

extern Pool *D_004830F8;
extern s16 D_004830FC;
extern s32 VariantGetInt_15f780(void *);

typedef struct R8 {
    u8 b[8];
} R8;

/* Fill the eight bytes at +0x2A of the current 0x58-stride entry, one per
   0x8-byte record of the incoming stream.  No `b` to the test => do/while.
   The cursor is an 8-byte-element pointer POST-INCREMENTED INSIDE the
   argument: that is the only spelling that puts the advance in the
   call's own delay slot. */

s32 DataTableCmdEntrySetIntArray_3fea80(R8 *p)
{
    Pool *g;
    s32 k;
    s32 i;
    u8 *e;

    g = D_004830F8;
    if (g->m7C <= 0) {
        return 1;
    }
    k = D_004830FC - 1;
    if (k >= g->m7C) {
        return 1;
    }
    e = g->m8C + k * 0x58;
    i = 0;
    do {
        *(s8 *)(e + i + 0x25) = VariantGetInt_15f780(p++);
        i++;
    } while (i < 5);
    return 1;
}
