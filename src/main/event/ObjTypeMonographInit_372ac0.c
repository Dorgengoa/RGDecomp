#include "types.h"

typedef struct S_00372ac0 {
    u8 pad0[0xE0];
    s32 fE0;
    s32 fE4;
} S_00372ac0;

extern void ObjTypeMonographReset_372cd0(S_00372ac0 *);
extern s32 ObjTypeMonographGetVolumeRec_372ab0(s32);
extern s32 ObjTypeMonographGetParamRec_372aa0(s32);
extern s32 EvObjInit_2f9cf0(S_00372ac0 *, s32, s32, s32, s32, s32);

s32 ObjTypeMonographInit_372ac0(S_00372ac0 *self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r;
    ObjTypeMonographReset_372cd0(self);
    if (p2 == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    r = ObjTypeMonographGetVolumeRec_372ab0(p2);
    self->fE0 = r;
    if (r == 0) return 0;
    r = ObjTypeMonographGetParamRec_372aa0(p2);
    self->fE4 = r;
    if (r == 0) return r != 0;
    return EvObjInit_2f9cf0(self, p1, p2, p3, p4, p5);
}
