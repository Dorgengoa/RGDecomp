#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

/* Head of a 3-member byte-identical group (72 B each):
   DataTableGetKey_3ff280 / DataTableGetKey_41d5b0 / DataTableGetKey_428470.
   The merged DataTableGetEntry_3ff2d0 accessor with an s16 read at +0 bolted on -- the
   lh at 0x0 sits in the epilogue's delay slot, so the load is
   unconditional and happens on the null arm too.  Stride 0x58. */

s16 DataTableGetKey_3ff280(Pool *p, s32 i)
{
    return *(s16 *)((i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 0x58)
                                           : (void *)0);
}
