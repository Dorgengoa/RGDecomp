/* rg-override: replaces game/src/main/ui/MesWinAdvanceTypeout_275f00.c sha256 1669605887f7d6972bef6b00616a49f0291a3bbf0dd524c82df2be55ea7c1937
 * why: gameplay.text_speed (docs/SETTINGS.md "Gameplay options"): the type-out cursor advances
 * by the window's char speed times rg_text_speed_mult() (1 = Original: the generated body
 * unchanged; fast 2x; instant: the page up to its next pause / page wait at once) */
/* rgp:protos */
#define RGP_SELF_MesWinAdvanceTypeout_275f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern float rg_text_speed_mult(void);   /* src/settings/rg_aspect.c */

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
        f32 rg_m = rg_text_speed_mult();
        f = MesWinGetTypeCursor_272b00(o);
        if (rg_m == 1.0f)
            MesWinSetTypeCursor_272b10(o, f + MesWinGetCharSpeed_277620(o));
        else
            MesWinSetTypeCursor_272b10(o, f + MesWinGetCharSpeed_277620(o) * rg_m);
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
