#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptGetInt_26a2a0(struct S8 *);
extern s32 ScriptGetCodeAddr_26a200(struct S8 *);
extern s32 RecStackGetSlot_1c4330(s32, s32);
extern void MoviePlayModal_267c60(s32, s32, s32, s32, s32, s32);

extern s32 D_00481F78;
extern s32 D_004BD980[];

s32 EvCmdPlayMovie_268680(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    s32 rv8;
    s32 t0;
    s32 r9;

    r0 = ScriptGetInt_26a2a0(p0++);
    r1 = ScriptGetCodeAddr_26a200(p0++);
    rv4 = 1;
    rv8 = 1;
    if (p1 >= 3) {
        rv4 = ScriptGetInt_26a2a0(p0++);
    }
    if (p1 >= 4) {
        rv8 = ScriptGetInt_26a2a0(p0);
    }
    t0 = D_004BD980[r0];
    r9 = RecStackGetSlot_1c4330(D_00481F78, t0);
    MoviePlayModal_267c60(r1, r9, rv4, -1, rv8, 1);
    return 1;
}
