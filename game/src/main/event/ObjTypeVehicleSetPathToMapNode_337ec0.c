/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleSetPathToMapNode_337ec0 1
#include "port/game_protos.h"
#line 1
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

/* stack locals in REVERSE declaration order:
   cam -> 0x110, m1 -> 0xD0, c -> 0xC0, b -> 0xB0, m2 -> 0x70,
   a -> 0x60, z -> 0x50 */
s32 ObjTypeVehicleSetPathToMapNode_337ec0(Obj *self, s32 a1, s32 a2)
{
    Cam cam __attribute__((aligned(16)));
    Mtx4 m1 __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Mtx4 m2 __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 z __attribute__((aligned(16)));
    Node *t;

    if (self->f11C == 0 || ((short)EventPathRecGetPointCount_2e4190(self->f11C)) < 2) {
        return 0;
    }
    t = ((Node *)EventPathRecGetPoints_2e4180(self->f11C));
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
