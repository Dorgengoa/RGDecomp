/* rgp:protos */
#define RGP_SELF_DataTableViewGetAt_410950 1
#include "port/game_protos.h"
#line 1
/* DataTableViewGetAt_410950 -- byte-identical clone of DataTableViewGetAt_405050 (64 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

/* Head of a 4-member byte-identical group (64 B each):
   DataTableViewGetAt_410950 / DataTableGetEntry_4050d0 / DataTableGetEntry_4107b0 / DataTableViewGetAt_410950.
   Same shape as merged DataTableGetEntry_3ff2d0, stride 60 (sll 4 / subu / sll 2). */

void *DataTableViewGetAt_410950(Pool *p, s32 i)
{
    return (i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 60) : (void *)0;
}
