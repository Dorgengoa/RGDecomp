/* rgp:protos */
#define RGP_SELF_DynFrameStartCmd_168d90 1
#define RGP_SELF_blocks 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *memset(void *, s32, u32);
extern u8 *D_00481154;
extern u8 *D_00481158;

typedef struct {
    u8 pad0[0x90];
    s32 n;
    s32 *a;
    s32 b;
    s32 c;
} Mgr;

static inline u32 blocks(u32 sz) {
    if (!(sz & 0xF)) {
        return sz >> 4;
    }
    return (sz >> 4) + 1;
}

s32 DynFrameStartCmd_168d90(s8 *arg0) {
    s32 n;
    u8 *heap;
    Mgr *m;
    s32 i;

    n = VariantGetInt_15f780(arg0);
    heap = D_00481158;
    m = (Mgr *)D_00481154;
    if (heap != NULL) {
        m->n = n;
        m->a = (s32 *)MemStackAllocQw_14d950(heap, blocks(n * 4));
        m->b = MemStackAllocQw_14d950(heap, blocks(m->n * 0x50));
        m->c = ((s32)MemStackNew_14e1b0(m->n << 6, heap));
        for (i = 0; i < m->n; i++) {
            m->a[i] = 0;
            memset((void *)(m->b + i * 0x50), 0, 0x50);
            MtxIdentity_13d2e0(m->c + (i << 6));
        }
    }
    return 1;
}
