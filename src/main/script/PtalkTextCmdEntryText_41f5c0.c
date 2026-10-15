#include "types.h"

struct E8_41f5c0 { u8 pad[8]; };

struct Obj0 {
    u8 pad000[0x1C];
    s16 m1C;
    u8 pad01E[0x6];
    s32 m24;
};

extern s32 VariantGetInt_15f780(struct E8_41f5c0 *);
extern s32 CfgVmFindOp_42f650(s32, s32, s32);
extern s32 SlotGetInt_15f720(struct E8_41f5c0 *);
extern s32 PtalkTextCacheString_41f640(struct Obj0 *, s32);
extern void CfgVmSkipToEnd_42f600(s32);

extern struct Obj0 *D_00483EA8;

s32 PtalkTextCmdEntryText_41f5c0(struct E8_41f5c0 *p0)
{
    struct Obj0 *g;
    s32 r0;

    g = D_00483EA8;
    r0 = VariantGetInt_15f780(p0++);
    if (r0 != g->m1C) {
        CfgVmFindOp_42f650(g->m24, 0x12C, 1);
        return 1;
    }
    PtalkTextCacheString_41f640(g, SlotGetInt_15f720(p0));
    CfgVmSkipToEnd_42f600(g->m24);
    return 0;
}
