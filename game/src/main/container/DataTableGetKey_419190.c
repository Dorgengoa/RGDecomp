/* rgp:protos */
#define RGP_SELF_DataTableGetKey_419190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 3-member BYTE-IDENTICAL group headed by DataTableGetKey_4190d0; the shape and
   every lever are documented there.  Same bounds-checked pool index as
   src/s19a/DataTableGetEntry_3ff2d0.c -- a ternary is the only route to the plain `b`
   over the two-arm value -- with the result DEREFERENCED at the `jr` delay
   slot, so the out-of-range arm loads through a null pointer. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    s32 *m8C;
} Pool;

s32 DataTableGetKey_419190(Pool *p, s32 i)
{
    return *((i >= 0 && i < p->m7C) ? (s32 *)((u8 *)p->m8C + i * 8)
                                    : (s32 *)0);
}
