#include "types.h"

typedef struct E8_FUN_002666d0 {
    s32 a;
    s32 b;
} E8_FUN_002666d0;

extern void *ScriptGetInt_26a2a0(E8_FUN_002666d0 *p);
extern void *MesMgrGetSlotWin_266af0(void *a);
extern f32 TaggedGetFloat_26a280(E8_FUN_002666d0 *p);
extern s32 MesWinGetFlush_2775e0(void *r);
extern void MesWinScrollToPage_270650(void *r);
extern void MesWinSetFlush_2775f0(void *r, s32 f);
extern void MesWinSetTextSpeed_277580(void *r, f32 v);

s32 EvCmdMesWinSetTextSpeed_2666d0(E8_FUN_002666d0 *q)
{
    void *a;
    void *r;
    f32 v;

    a = ScriptGetInt_26a2a0(q++);
    r = MesMgrGetSlotWin_266af0(a);
    if (r == 0) return 0;
    v = TaggedGetFloat_26a280(q);
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
