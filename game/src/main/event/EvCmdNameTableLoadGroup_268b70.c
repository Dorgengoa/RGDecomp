/* rgp:protos */
#define RGP_SELF_EvCmdNameTableLoadGroup_268b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 size;
    s32 max;
} Info;

typedef struct {
    u8 pad0[0x5CF0];
    s32 base;
    s32 n;
} G;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memcpy(s32 arg0, s32 arg1, s32 arg2);
extern G *D_00481F78;
extern s32 D_004BD980[];

s32 EvCmdNameTableLoadGroup_268b70(s64 *arg0, s32 arg1)
{
    Info info __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;
    s32 n;
    s32 dst;
    s32 p;
    s32 h;
    s32 v;
    G *g;
    s32 base;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetCodeAddr_26a200((s32)arg0++);
    c = ScriptGetInt_26a2a0((s32)arg0++);
    g = D_00481F78;
    n = g->n;
    base = g->base;
    info.max = n;
    if (n <= 0 || n < c) {
        return 0;
    }
    dst = base + c;
    p = FileLoadCached_26a6c0(b, &info);
    if (p == 0) {
        return 0;
    }
    h = ((s32)RecStackGetSlot_1c4330(D_00481F78, D_004BD980[a]));
    v = MemStackPeekQw_14d9d0(h, info.size / 16 + 1);
    if (v == 0) {
        return 0;
    }
    MemStackAllocAligned64_14da10(h, info.size / 16 + 1);
    memcpy(v, p, info.size);
    NameTableRegisterImArchive_1594d0(GetDrawCtxNameTable_15de40(), v, dst, h, 0);
    if (arg1 == 4) {
        ScriptSetRefInt_26a1e0((s32)arg0, dst);
    }
    return 1;
}
