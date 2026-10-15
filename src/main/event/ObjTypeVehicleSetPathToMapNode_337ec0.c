#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { Vec4 r[4]; } Mtx4;
typedef struct { u8 d[0x30]; } Sub;
typedef struct { Sub a; Sub b; } Node;
typedef struct { u8 d[0x30]; } Cam;

typedef struct {
    u8   pad00[0xE0];
    u8   fE0[0x3C];
    s32  f11C;
} Obj;

extern s32 EventPathRecGetPointCount_2e4190(s32);
extern Node *EventPathRecGetPoints_2e4180(s32);
extern s32 TargetRefGetObj_2e7110(void *);
extern void TargetRefCtor_2e71f0(Cam *);
extern void TargetRefSetMapNode_2e6370(Cam *, s32, s32, f32);
extern s32 TargetRefResolve_2e5ed0(Cam *, s32);
extern void TargetRefGetMatrix_2e6870(void *, Mtx4 *);
extern void MatToRotPos_1cade0(Vec4 *, Vec4 *, Mtx4 *);
extern void SrtInit_1c74d0(void *);
extern void SrtSetRot_1c73d0(void *, f32, f32, f32);
extern void SrtSetPosFromVec_1c7410(void *, Vec4 *);

/* stack locals in REVERSE declaration order:
   cam -> 0x110, m1 -> 0xD0, c -> 0xC0, b -> 0xB0, m2 -> 0x70,
   a -> 0x60, z -> 0x50 */
s32 ObjTypeVehicleSetPathToMapNode_337ec0(Obj *self, s32 a1, s32 a2)
{
    Cam cam;
    Mtx4 m1;
    Vec4 c;
    Vec4 b;
    Mtx4 m2;
    Vec4 a;
    Vec4 z;
    Node *t;

    if (self->f11C == 0 || EventPathRecGetPointCount_2e4190(self->f11C) < 2) {
        return 0;
    }
    t = EventPathRecGetPoints_2e4180(self->f11C);
    if (t == 0) {
        return 0;
    }
    if (TargetRefGetObj_2e7110(self->fE0) == 0) {
        return 0;
    }
    TargetRefCtor_2e71f0(&cam);
    TargetRefSetMapNode_2e6370(&cam, a1, a2, 0.0f);
    if (TargetRefResolve_2e5ed0(&cam, 0) == 0) {
        return 0;
    }
    TargetRefGetMatrix_2e6870(self->fE0, &m1);
    MatToRotPos_1cade0(&c, &b, &m1);
    SrtInit_1c74d0(&t->a);
    SrtSetRot_1c73d0(&t->a, 0.0f, c.y, 0.0f);
    SrtSetPosFromVec_1c7410(&t->a, &b);
    TargetRefGetMatrix_2e6870(&cam, &m2);
    MatToRotPos_1cade0(&a, &z, &m2);
    SrtInit_1c74d0(&t->b);
    SrtSetRot_1c73d0(&t->b, 0.0f, a.y, 0.0f);
    SrtSetPosFromVec_1c7410(&t->b, &z);
    return 1;
}
