#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (60 B each): DataTableViewGetAt_40a370 /
   DataTableGetEntry_40a3f0.  The same bounds-checked pool index as
   src/s19a/DataTableGetEntry_3ff2d0.c with a 0x754 stride -- not a power of two, so
   retail spends a real `mult` instead of a shift chain. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

void *DataTableViewGetAt_40a370(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 0x754) : (void *)0;
}
