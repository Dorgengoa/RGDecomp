/* rgp:protos */
#define RGP_SELF_DataTableGetKey_401f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

/* Head of a 3-member byte-identical group (72 B each):
   DataTableGetKey_401f60 / DataTableGetKey_40e910 / DataTableGetKey_418c00.
   DataTableGetKey_3ff280 with stride 52 (sll 1 / addu / sll 2 / addu / sll 2). */

s32 DataTableGetKey_401f60(Pool *p, s32 i)
{
    return (s16)(*(s16 *)((i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 52)
                                           : (void *)0));
}
