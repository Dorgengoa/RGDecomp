/* rgp:protos */
#define RGP_SELF_MenuModelPageTextBoxFitWidthMaybe_359590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x134];
    s32 m134;
};

void MenuModelPageTextBoxFitWidthMaybe_359590(struct Obj0 *p0, s32 p1)
{
    s32 v2C;
    s32 v28;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 rv2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 t8;
    s32 t9;
    s32 t10;
    s32 t11;
    s32 t12;
    s32 t13;
    s32 t14;
    s32 t15;
    s32 t16;
    s32 t17;
    s32 t18;
    s32 t19;
    s32 t20;
    s32 t21;
    s32 t22;
    s32 t23;

    t0 = p0->m134;
    UiSetTextString_28f510(t0, 0x246, p1, 0);
    t1 = p0->m134;
    UiGetWidgetTextSize_28f430(t1, 0x246, &v2C, &v28, 0);
    if (*(volatile s32 *)&v2C < 0x28) {
        v2C = 0x28;
    }
    rv2 = *(volatile s32 *)&v2C;
    v2C = (rv2 - 0xC);
    t5 = p0->m134;
    UiSetSpriteW_28fbf0(t5, 0x246, v2C, 1);
    t6 = p0->m134;
    t7 = v2C;
    UiSetSpriteW_28fbf0(t6, 0x246, t7, 4);
    t8 = p0->m134;
    t9 = v2C;
    UiSetSpriteW_28fbf0(t8, 0x246, t9, 7);
    t10 = v2C;
    t11 = p0->m134;
    UiSetSpriteX_28fcd0(t11, 0x246, (0x17F - t10), 1);
    t12 = v2C;
    t13 = p0->m134;
    UiSetSpriteX_28fcd0(t13, 0x246, (0x17F - t12), 4);
    t14 = v2C;
    t15 = p0->m134;
    UiSetSpriteX_28fcd0(t15, 0x246, (0x17F - t14), 7);
    t16 = v2C;
    t17 = p0->m134;
    UiSetSpriteX_28fcd0(t17, 0x246, (0x16F - t16), 0);
    t18 = v2C;
    t19 = p0->m134;
    UiSetSpriteX_28fcd0(t19, 0x246, (0x16F - t18), 3);
    t20 = v2C;
    t21 = p0->m134;
    UiSetSpriteX_28fcd0(t21, 0x246, (0x16F - t20), 6);
    t22 = v2C;
    t23 = p0->m134;
    UiSetTextX_28f590(t23, 0x246, (0x179 - t22), 0);
}
