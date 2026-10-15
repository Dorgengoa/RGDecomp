#include "types.h"

typedef struct E8_FUN_00242380 {
    s32 a;
    s32 b;
} E8_FUN_00242380;

extern void *ScriptGetInt_2490f0(E8_FUN_00242380 *p);
extern void *MesMgrGetSlotWin_24fcc0(void *a);
extern f32 TaggedGetFloat_2490d0(E8_FUN_00242380 *p);
extern s32 MesWinGetFlush_2775e0(void *r);
extern void MesWinScrollToPage_270650(void *r);
extern void MesWinSetFlush_2775f0(void *r, s32 f);
extern void MesWinSetTextSpeed_277580(void *r, f32 v);

s32 EvCmdMesWinSetTextSpeed_242380(E8_FUN_00242380 *q)
{
    void *a;
    void *r;
    f32 v;

    a = ScriptGetInt_2490f0(q++);
    r = MesMgrGetSlotWin_24fcc0(a);
    if (r == 0) return 0;
    v = TaggedGetFloat_2490d0(q);
    if (v < 0.0f) {
        if (MesWinGetFlush_2775e0(r) == 0) {
            MesWinScrollToPage_270650(r);
        }
        MesWinSetFlush_2775f0(r, 1);
    } else {
        MesWinSetTextSpeed_277580(r, v);
    }
    return 1;
}
