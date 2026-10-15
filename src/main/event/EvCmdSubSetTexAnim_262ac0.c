#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptGetInt_26a2a0(struct S8 *);
extern s32 ScriptGetCodeAddr_26a200(struct S8 *);
extern s32 EvtGetSubMachine_26abb0(s32);
extern void EventSubNodeAddSetTexAnim_251000(s32, s32, s32);

s32 EvCmdSubSetTexAnim_262ac0(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    s32 r5;

    r0 = ScriptGetInt_26a2a0(p0++);
    r1 = ScriptGetInt_26a2a0(p0++);
    rv4 = 0;
    if (p1 >= 3) {
        rv4 = ScriptGetCodeAddr_26a200(p0);
    }
    r5 = EvtGetSubMachine_26abb0(r0);
    if (r5 == 0) {
        return 0;
    }
    EventSubNodeAddSetTexAnim_251000(r5, rv4, r1);
    return 1;
}
