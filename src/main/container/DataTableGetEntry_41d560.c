#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

/* Bounds-checked index into the 0x58-stride pool.  Both guards are EARLY
   RETURNS: the second one's `bnel` jumps PAST the `return 0`, which is the
   `if (i >= p->m7C) return 0;` shape, not a guarded body. */

void *DataTableGetEntry_41d560(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 0x58) : (void *)0;
}
