#include "types.h"
/* normal 0x004F1380 -- arms the 0x25 widget's counter and clears the 0x430
 * flag once the widget's animation phase has run past D_0047D90C. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x430 - 0x37A];
    u8  f430;
    u8  pad431[0x4A8 - 0x431];
    s16 f4A8;
} Obj;

extern f32 D_0047D90C;            /* gp - 0x7864 */

extern f32 func_290770(void *p, u16 id);

extern void normal_FieldHudRadarFadeInCheck_4f1380(Obj *p);

void normal_FieldHudRadarFadeInCheck_4f1380(Obj *p)
{
    if (p->f378 != 0) {
        p->f4A8 = 1;
        if (func_290770(p, 0x25) >= D_0047D90C) {
            p->f430 = 0;
        }
    }
}
