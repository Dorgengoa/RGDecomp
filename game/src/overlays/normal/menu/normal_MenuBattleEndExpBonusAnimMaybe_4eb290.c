/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndExpBonusAnimMaybe_4eb290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EB290 -- widget 0x11's two phases: phase 1 ramps 0xA0 toward
 * 0x9C and pushes the integer via func_290F60; phase 2 reads the current
 * scale back with func_2904B0 and drives the two transform setters. */

typedef struct Eb2Obj {
    u8  pad000[0x14];
    u8  f014[0x9C - 0x14];
    f32 f09C;
    f32 f0A0;
    f32 f0A4;
    s16 f0A8;
} Eb2Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndExpBonusAnimMaybe_4eb290(Eb2Obj *p)
{
    f32 v;

    if (p->f0A8 == 1) {
        if (p->f0A0 == p->f09C) {
            return;
        }
        p->f0A0 = p->f0A0 + p->f0A4;
        p->f0A4 = p->f0A4 + 1.2f;
        if (p->f0A0 >= p->f09C) {
            p->f0A0 = p->f09C;
            p->f0A4 = 0.0f;
            p->f0A8 = 2;
        }
        UiSetWidgetPos_290f60(p->f014, 0x11, 0, (s32)p->f0A0);
    } else if (p->f0A8 == 2) {
        v = *((f32 *)UiGetWidgetColor_2904b0(p->f014, 0x11));
        if (v <= 1.0f) {
            UiSetWidgetColor_2905b0(p->f014, 0x11, 1.0f, 1.0f, 1.0f, -1.0f);
            UiFadeWidgetColor_2904e0(p->f014, 0x11, 1.7f, 1.7f, 1.7f, -1.0f, 0.075f);
        } else if (v >= 1.7f) {
            UiSetWidgetColor_2905b0(p->f014, 0x11, 1.7f, 1.7f, 1.7f, -1.0f);
            UiFadeWidgetColor_2904e0(p->f014, 0x11, 1.0f, 1.0f, 1.0f, -1.0f, -0.045f);
        }
    }
}
