#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

/* Head of a 4-member byte-identical group (64 B each):
   DataTableGetEntry_3f6280 / DataTableGetEntry_4050d0 / DataTableGetEntry_4107b0 / DataTableViewGetAt_410950.
   Same shape as merged DataTableGetEntry_3ff2d0, stride 28 (sll 4 / subu / sll 2). */

void *DataTableGetEntry_3f6280(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 28) : (void *)0;
}
