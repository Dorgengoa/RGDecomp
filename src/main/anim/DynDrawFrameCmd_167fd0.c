#include "types.h"

typedef struct S00481154 {
    u8 pad0[0xCC];
    s32 unkCC;
    s32 *unkD0;
} S00481154;

extern s32 MemStackAllocQw_14d950(s32 arg0, u32 arg1);
extern s32 VariantGetInt_15f780(s32 arg0);
extern S00481154 *D_00481154;
extern s32 D_00481158;

s32 DynDrawFrameCmd_167fd0(s64 *arg0, s32 arg1)
{
    S00481154 *p;
    S00481154 *q;
    u32 n;
    s32 i;
    s32 v;
    s32 h;

    p = D_00481154;
    n = arg1 * 4;
    h = D_00481158;
    p->unkCC = arg1;
    p->unkD0 = (s32 *)MemStackAllocQw_14d950(h, (n & 0xF) ? (n >> 4) + 1 : n >> 4);
    for (i = 0; i < p->unkCC; i++) {
        p->unkD0[i] = -1;
    }
    for (i = 0; i < arg1; i++) {
        v = VariantGetInt_15f780((s32)arg0++);
        q = D_00481154;
        if (i >= 0 && i < q->unkCC) {
            q->unkD0[i] = v;
        }
    }
    return 1;
}
