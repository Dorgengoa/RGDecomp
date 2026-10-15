#include "types.h"

struct E8 { u8 b[8]; };
struct Obj0 { u8 pad000[0x20]; s32 m20; u8 pad024[0x4]; s32 m28; };

extern s32 VariantGetInt_15f780(struct E8 *);
extern s32 CfgVmFindOp_42f650(s32, s32, s32);
extern s32 SlotGetInt_15f720(struct E8 *);
extern s32 NpcTalkTextCacheString_41db10(struct Obj0 *, s32);
extern void CfgVmSkipToEnd_42f600(s32);

extern struct Obj0 *D_00483E78;

s32 NpcTalkTextCmdEntryText_41da90(struct E8 *p0)
{
    struct E8 *q;
    struct Obj0 *g;
    s32 r0;
    s32 r2;

    q = p0;
    g = D_00483E78;
    r0 = VariantGetInt_15f780(q++);
    if (r0 != g->m20) {
        CfgVmFindOp_42f650(g->m28, 0x12C, 1);
        return 1;
    }
    r2 = SlotGetInt_15f720(q);
    NpcTalkTextCacheString_41db10(g, r2);
    CfgVmSkipToEnd_42f600(g->m28);
    return 0;
}
