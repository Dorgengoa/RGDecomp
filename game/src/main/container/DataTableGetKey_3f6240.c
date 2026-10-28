/* rgp:protos */
#define RGP_SELF_DataTableGetKey_3f6240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (64 B each): DataTableGetKey_3f6240 /
   DataTableGetKey_419600.  The src/s25a/DataTableGetKey_4190d0.c pool index with a 28-byte
   stride -- retail spells 28 as `sll 3 / subu / sll 2` -- and an `lh` of the
   result in the `jr` delay slot. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    s16 *m8C;
} Pool;

s32 DataTableGetKey_3f6240(Pool *p, s32 i)
{
    return (s16)(*((i >= 0 && i < p->m7C) ? (s16 *)((u8 *)p->m8C + i * 28)
                                    : (s16 *)0));
}
