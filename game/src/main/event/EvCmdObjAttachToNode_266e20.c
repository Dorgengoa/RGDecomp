/* rgp:protos */
#define RGP_SELF_EvCmdObjAttachToNode_266e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32 a, void *b);
extern u8 D_0045F0E0[0x400];

s32 EvCmdObjAttachToNode_266e20(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 c;
    s32 a2;
    s32 c2;
    void *p;
    void *q;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetCodeAddr_26a200((s32)arg0++);
    c = ScriptGetInt_26a2a0((s32)arg0++);
    if (arg1 > 3) {
        ScriptGetInt_26a2a0((s32)arg0++);
    }
    if (arg1 > 4) {
        ScriptGetInt_26a2a0((s32)arg0);
    }
    if ((a2 = ((s32)EventSceneGetObj_2676e0(a))) == 0) {
        return 0;
    }
    if ((c2 = ((s32)EventSceneGetObj_2676e0(c))) == 0) {
        return 0;
    }
    p = ModelGetRootFrame_1511a0(a2);
    if (p == NULL) {
        return 0;
    }
    if (strcmp(b, D_0045F0E0) != 0) {
        if ((p = FrameFindByName_149ed0(p, b)) == NULL) {
            return 0;
        }
    }
    if ((q = ModelGetRootFrame_1511a0(c2)) == NULL) {
        return 0;
    }
    *(u8 *)((u8 *)q + 0x28) = 1;
    *(void **)((u8 *)q + 4) = p;
    FrameSetDirty_14a5e0(q);
    return 1;
}
