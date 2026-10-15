#include "types.h"
/* normal 0x004F9540 -- one of the SIX 68 B func_290690 twins (0x44 = 17 words).
 * One shape x six ids: guard on p->f378, one func_290690 with the float
 * triple (0.0f, gp literal, -1.0f) exactly as the settled seed
 * src/wf/normal/normal_ShopMenuSellMsgCloseState_50f880.c, then one s16 clear through the
 * callee-saved copy of the parameter.
 */
typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x49C - 0x37A];
    s16 f49C;
    s16 f49E;
    s16 f4A0;
    s16 f4A2;
    s16 f4A4;
    s16 f4A6;
} Obj;

extern f32   D_0047DB60;
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

void normal_FieldHudWidget83Close_4f9540(Obj *p)
{
    if (p->f378 != 0) {
        func_290690(p, 0x83, 0.0f, D_0047DB60, -1.0f);
        p->f49E = 0;
    }
}
