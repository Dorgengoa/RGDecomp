#include "types.h"

struct E8 {
    s32 a;
    s32 b;
};

extern s32 ScriptSlotGetInt_2cc9c0(struct E8 *);
extern s32 CharaActiveSlotRecIdInRange_2cc9f0(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(struct E8 *, s32);

extern const s32 D_004DB928;

s32 AiCmdCharaActiveSlotRecIdInRange_2c5f80(struct E8 *p0, s32 p1)
{
    struct E8 *q;
    s32 rv1;
    s32 r0;
    s32 r3;
    s32 r4;

    q = p0;
    rv1 = D_004DB928;
    if (p1 == 3) {
        r0 = ScriptSlotGetInt_2cc9c0(q++);
        rv1 = r0;
    }
    r3 = ScriptSlotGetInt_2cc9c0(q++);
    r4 = CharaActiveSlotRecIdInRange_2cc9f0(rv1, r3);
    ScriptSlotStoreIntRef_2cc900(q, r4);
    return 1;
}
