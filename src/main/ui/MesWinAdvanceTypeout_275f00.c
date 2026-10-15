#include "types.h"

typedef struct Obj {
    u8 pad0[0x18C4];
    s16 tbl[0x10];
    s32 cnt[8];
} Obj;

extern f32 MesWinGetOpenRate_277540(Obj *);
extern s32 MesWinIsPageWait_2721f0(Obj *);
extern s32 MesWinFindDuePause_276190(Obj *);
extern void MesWinSetTypeCursor_272b10(Obj *, f32);
extern void MesWinSetShownEnd_271690(Obj *, s32);
extern s32 MesWinGetInstant_277600(Obj *);
extern s32 MesWinGetFlush_2775e0(Obj *);
extern f32 MesWinGetTypeCursor_272b00(Obj *);
extern f32 MesWinGetCharSpeed_277620(Obj *);
extern s32 MesWinGetShownEnd_271680(Obj *);
extern s32 MesWinGetCharCount_274c70(Obj *);
extern s32 MesWinStepCmd_2761f0(Obj *);
extern void MesWinSetFlush_2775f0(Obj *, s32);

void MesWinAdvanceTypeout_275f00(Obj *o)
{
    s32 k;
    s16 *p;
    f32 f;
    s32 s;

    if (MesWinGetOpenRate_277540(o) < 1.0f) return;
    if (MesWinIsPageWait_2721f0(o) != 0) return;
    k = MesWinFindDuePause_276190(o);
    if (k >= 0) {
        o->cnt[k]--;
        p = (s16 *)((u8 *)o + 0x18C4) + k;
        MesWinSetTypeCursor_272b10(o, (f32)*p);
        MesWinSetShownEnd_271690(o, *p);
    } else if (MesWinGetInstant_277600(o) == 0 && MesWinGetFlush_2775e0(o) == 0) {
        f = MesWinGetTypeCursor_272b00(o);
        MesWinSetTypeCursor_272b10(o, f + MesWinGetCharSpeed_277620(o));
    }
    if (MesWinGetInstant_277600(o) == 1) {
        k = MesWinGetShownEnd_271680(o);
        if (!(k < MesWinGetCharCount_274c70(o))) return;
    }
    f = MesWinGetTypeCursor_272b00(o);
    if (!(f <= (f32)MesWinGetCharCount_274c70(o))) {
        MesWinSetTypeCursor_272b10(o, (f32)MesWinGetCharCount_274c70(o));
    }
    while (MesWinGetInstant_277600(o) == 1 || (MesWinGetInstant_277600(o) == 0 && MesWinGetFlush_2775e0(o) != 0) ||
           !(MesWinGetTypeCursor_272b00(o) - (f32)MesWinGetShownEnd_271680(o) < 1.0f)) {
        s = MesWinStepCmd_2761f0(o);
        if (s == 1 || s == 2) return;
        k = MesWinGetShownEnd_271680(o);
        if (!(k < MesWinGetCharCount_274c70(o))) {
            MesWinSetFlush_2775f0(o, 0);
            MesWinSetTypeCursor_272b10(o, (f32)MesWinGetShownEnd_271680(o));
            return;
        }
        if (MesWinGetInstant_277600(o) == 1) {
            k = MesWinGetShownEnd_271680(o);
            if (!(k < MesWinGetCharCount_274c70(o))) return;
        }
    }
}
