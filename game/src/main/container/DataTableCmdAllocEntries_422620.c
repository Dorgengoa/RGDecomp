/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocEntries_422620 1
#include "port/game_protos.h"
#line 1
/* DataTableCmdAllocEntries_422620 -- byte-identical clone of DataTableCmdAllocEntries_421a20 (124 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 4-member byte-identical group (124 B each):
   DataTableCmdAllocEntries_422620 / DataTableCmdAllocEntries_421da0 / DataTableCmdAllocEntries_4221e0 / DataTableCmdAllocEntries_422620. */

struct G21a20 {
    u8   pad000[0x6C];
    u8   m6C[0x10];             /* +0x6C, an allocator/arena handle */
    s16  m7C;                   /* +0x7C */
    u8   pad07E[0x8C - 0x7E];
    void *m8C;                  /* +0x8C */
};

extern struct G21a20 *D_004830F8;

/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocEntries_422620(void *rgp_a0)
{
    struct G21a20 *g;
    s16 n;
    void *p;

    g = D_004830F8;
    n = (s16)VariantGetInt_15f780((void *)rgp_a0);
    g->m7C = n;
    if (n > 0) {
        p = ArenaNew_4235b0(n * 8 + 0x10, &g->m6C, 4, -1);
        g->m8C = ConstructNewArray_100710(p, 0, 0, 8, n);
    } else {
        g->m8C = 0;
    }
    return 1;
}
