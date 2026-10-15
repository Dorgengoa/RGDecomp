#include "types.h"

class Obj411db0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(s32 a, s32 b, s32 c);
};

struct T411db0 {
    s32 f0;             /* 0x00 */
    s32 f4;             /* 0x04 */
    Obj411db0 *f8;      /* 0x08 */
    Obj411db0 *fC;
    Obj411db0 *f10;
    Obj411db0 *f14;
    Obj411db0 *f18;
    Obj411db0 *f1C;
    u8 pad20[4];
    Obj411db0 *f24;
    u8 pad28[4];
    Obj411db0 *f2C;
    u8 pad30[4];
    Obj411db0 *f34;
};

extern struct Big00465688 { s32 v; s32 pad[3]; } D_00465688;
extern struct Big00465690 { s32 v; s32 pad[3]; } D_00465690;
extern struct Big00465698 { s32 v; s32 pad[3]; } D_00465698;
extern struct Big004656A0 { s32 v; s32 pad[3]; } D_004656A0;
extern struct Big004656A8 { s32 v; s32 pad[3]; } D_004656A8;
extern struct Big004656B0 { s32 v; s32 pad[3]; } D_004656B0;
extern struct Big004656B8 { s32 v; s32 pad[3]; } D_004656B8;
extern struct Big004656E8 { s32 v; s32 pad[3]; } D_004656E8;
extern struct Big004656F0 { s32 v; s32 pad[3]; } D_004656F0;

extern "C" s32 WorldSubsysLoad_411db0(T411db0 *self, s32 a1, s32 a2, s32 a3)
{
    Obj411db0 *p;

    if (a1 == 0) {
        return 0;
    }
    if (self->f0 == 0) {
        return 0;
    }
    self->f4 = a3;
    p = self->f8;
    if (p != 0 && a2 != 0) {
        p->v5(a1, D_00465688.v != 0, 0);
    }
    p = self->fC;
    if (p != 0 && a2 != 0) {
        p->v5(a1, D_00465690.v != 0, 0);
    }
    p = self->f10;
    if (p != 0 && a2 != 0) {
        p->v5(a1, D_00465698.v != 0, 0);
    }
    p = self->f14;
    if (p != 0) {
        p->v5(a1, D_004656A0.v != 0, 0);
    }
    p = self->f18;
    if (p != 0) {
        p->v5(a1, D_004656A8.v != 0, 0);
    }
    p = self->f1C;
    if (p != 0) {
        p->v5(a1, D_004656B0.v != 0, 0);
    }
    p = self->f24;
    if (p != 0) {
        p->v5(a1, D_004656B8.v != 0, 0);
    }
    p = self->f2C;
    if (p != 0) {
        p->v5(a1, D_004656E8.v != 0, 0);
    }
    p = self->f34;
    if (p != 0) {
        p->v5(a1, D_004656F0.v != 0, 0);
    }
    return 1;
}
