/* rgp:protos */
#define RGP_SELF_normal_FieldHudBtlEscChoiceBlink_4f0a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F0A60 -- the 0x58-offset widget's fade/blink driver. */

typedef struct Obj {
    u8  pad000[0x386];
    s16 f386;
    u8  pad388[0x38C - 0x388];
    f32 f38C;
    f32 f390;
    s16 f394;
    s16 f396;
} Obj;

extern f32 D_0047DA44;          /* gp - 0x772C */
extern f32 D_0047D288;          /* gp - 0x7EE8 */

/*rgp*/

s32 normal_FieldHudBtlEscChoiceBlink_4f0a60(Obj *p)
{
    u16 id = p->f394 + 0x58;
    s16 v;

    if (p->f386 != 2) {
        return 0;
    }
    v = p->f396;
    if (v == 0) {
        p->f390 = D_0047DA44;
        p->f396 = 1;
    } else if (v != 0) {
        if (p->f38C >= 1.0f) {
            p->f390 = -p->f390;
        } else if (p->f38C <= D_0047D288) {
            p->f396 = v + 1;
            p->f390 = 0.0f;
            if (p->f396 > 0xA) {
                p->f386 = 3;
                return 1;
            }
        }
    }
    p->f38C = p->f38C + p->f390;
    UiSetTextColorScaled_290850(p, id, 0xFF606060, 0, p->f38C);
    return 0;
}
