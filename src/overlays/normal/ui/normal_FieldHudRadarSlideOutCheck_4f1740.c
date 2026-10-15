#include "types.h"
/* normal 0x004F1740 -- while the 0x430 flag is armed, compare the 0x25
 * widget's current X against its target X and, once it has caught up, run the
 * reset in normal_FieldHudRadarReset_4f17c0 and drop the flag.  The four out-parameters sit
 * at sp+0x2C/0x28/0x24/0x20, i.e. REVERSE declaration order. */

typedef struct Obj {
    u8  pad000[0x430];
    u8  f430;
    u8  pad431[0x4A8 - 0x431];
    s16 f4A8;
} Obj;

extern void func_2910A0(void *p, u16 id, s32 *x, s32 *y);
extern void func_290D90(void *p, u16 id, s32 *x, s32 *y);
extern void normal_FieldHudRadarReset_4f17c0(Obj *p);

extern void normal_FieldHudRadarSlideOutCheck_4f1740(Obj *p);

void normal_FieldHudRadarSlideOutCheck_4f1740(Obj *p)
{
    s32 x;
    s32 y;
    s32 tx;
    s32 ty;

    if (p->f430 == 1) {
        func_2910A0(p, 0x25, &x, &y);
        func_290D90(p, 0x25, &tx, &ty);
        if (x >= tx) {
            normal_FieldHudRadarReset_4f17c0(p);
            p->f430 = 0;
            p->f4A8 = 0;
        }
    }
}
