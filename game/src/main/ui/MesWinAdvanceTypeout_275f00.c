/* rgp:protos */
#define RGP_SELF_MesWinAdvanceTypeout_275f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x18C4];
    s16 tbl[0x10];
    s32 cnt[8];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinAdvanceTypeout_275f00(Obj *o)
{
    s32 k;
    s16 *p;
    f32 f;
    s32 s;

    if (MesWinGetOpenRate_277540(o) < 1.0f) return;
    if (((signed char)MesWinIsPageWait_2721f0(o)) != 0) return;
    k = MesWinFindDuePause_276190(o);
    if (k >= 0) {
        o->cnt[k]--;
        p = (s16 *)((u8 *)o + 0x18C4) + k;
        MesWinSetTypeCursor_272b10(o, (f32)*p);
        MesWinSetShownEnd_271690(o, *p);
    } else if (((short)MesWinGetInstant_277600(o)) == 0 && ((signed char)MesWinGetFlush_2775e0(o)) == 0) {
        f = MesWinGetTypeCursor_272b00(o);
        MesWinSetTypeCursor_272b10(o, f + MesWinGetCharSpeed_277620(o));
    }
    if (((short)MesWinGetInstant_277600(o)) == 1) {
        k = MesWinGetShownEnd_271680(o);
        if (!(k < MesWinGetCharCount_274c70(o))) return;
    }
    f = MesWinGetTypeCursor_272b00(o);
    if (!(f <= (f32)MesWinGetCharCount_274c70(o))) {
        MesWinSetTypeCursor_272b10(o, (f32)MesWinGetCharCount_274c70(o));
    }
    while (((short)MesWinGetInstant_277600(o)) == 1 || (((short)MesWinGetInstant_277600(o)) == 0 && ((signed char)MesWinGetFlush_2775e0(o)) != 0) ||
           !(MesWinGetTypeCursor_272b00(o) - (f32)MesWinGetShownEnd_271680(o) < 1.0f)) {
        s = MesWinStepCmd_2761f0(o);
        if (s == 1 || s == 2) return;
        k = MesWinGetShownEnd_271680(o);
        if (!(k < MesWinGetCharCount_274c70(o))) {
            MesWinSetFlush_2775f0(o, 0);
            MesWinSetTypeCursor_272b10(o, (f32)MesWinGetShownEnd_271680(o));
            return;
        }
        if (((short)MesWinGetInstant_277600(o)) == 1) {
            k = MesWinGetShownEnd_271680(o);
            if (!(k < MesWinGetCharCount_274c70(o))) return;
        }
    }
}
