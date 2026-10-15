#include "types.h"

struct E8_242280 { u8 pad[8]; };

extern s32 ScriptGetInt_2490f0(struct E8_242280 *);
extern s32 MesMgrGetSlotWin_24fcc0(s32);
extern void TaggedGetFloat_2490d0(struct E8_242280 *);

s32 EvCmdMesWinNop_242280(struct E8_242280 *p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_2490f0(p0++);
    r1 = MesMgrGetSlotWin_24fcc0(r0);
    if (r1 == 0) {
        return 0;
    }
    if (p1 == 2) {
        ScriptGetInt_2490f0(p0);
        goto one;
    }
    if (p1 != 3) {
        goto one;
    }
    TaggedGetFloat_2490d0(p0++);
    TaggedGetFloat_2490d0(p0);
one:
    return 1;
}
