/* rgp:protos */
#define RGP_SELF_CharaMoveApplyMaybe_234bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct Obj {
    u8 pad0[0x50];
    V4 v50;
    V4 v60;
    V4 v70;
    V4 v80;
    V4 v90;
    V4 vA0;
    V4 vB0;
    V4 vC0;
    V4 vD0;
    V4 vE0;
    u8 padF0[0x3CC - 0xF0];
    s32 x3CC;
    u8 pad3D0[0x3D8 - 0x3D0];
    s32 x3D8;
    s32 x3DC;
    u8 pad3E0[0x3F4 - 0x3E0];
    s32 x3F4;
} Obj;

typedef struct Arg {
    u8 pad0[0xC];
    s32 xC;
    s32 x10;
    u8 pad14[0x34 - 0x14];
    s32 x34;
} Arg;

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
extern f32 D_0045B080[];

void CharaMoveApplyMaybe_234bf0(Obj *o, Arg *arg1)
{
    V4 m[4] __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 *z;

    CharaMoveRolloverMaybe_236930((void *)o, (void *)arg1);
    o->x3DC = 0;
    if (arg1 != NULL && o->x3F4 != 0) {
        SrtToMatrix_1c7450(&o->v50, m);
        MtxMulDir_1cb910(&o->vA0, m, &o->vA0);
        MtxMulDir_1cb910(&o->vB0, m, &o->vB0);
        VecAdd_1cbdc0(&o->vC0, &o->vC0, &o->vA0);
        VecAdd_1cbdc0(&o->vD0, &o->vD0, &o->vB0);
        VecAdd_1cbdc0(&o->v80, &o->v80, &o->vC0);
        VecAdd3_1cbd60(&o->v70, &o->v70, &o->v80, &o->vD0);
        VecAdd_1cbdc0(&o->v60, &o->v60, &o->v90);
        VecWrapAngle_1cbe90(&o->v60, &o->v60);
        ModelSetRot_151080(o->x3F4, &o->v60);
        ModelSetPos_151110(o->x3F4, &o->v70);
        a = arg1->xC;
        b = arg1->x10;
        CharaProbeWaterSurfaceMaybe_237520(o, a, b, arg1->x34);
        CharaGroundSnapMaybe_237990(o, a, b, o->v70.y);
        o->x3D8 |= 4;
    } else {
        o->x3CC = 0x80000000;
    }
    VecAdd_1cbdc0(&o->v80, &o->v80, &o->vE0);
    o->vA0.x = 0.0f;
    o->vA0.y = 0.0f;
    o->vA0.z = 0.0f;
    o->vA0.w = 0.0f;
    o->vB0.x = 0.0f;
    o->vB0.y = 0.0f;
    o->vB0.z = 0.0f;
    o->vB0.w = 0.0f;
    o->vC0.x = 0.0f;
    o->vC0.y = 0.0f;
    o->vC0.z = 0.0f;
    o->vC0.w = 0.0f;
    o->vD0.x = 0.0f;
    o->vD0.y = 0.0f;
    o->vD0.z = 0.0f;
    o->vD0.w = 0.0f;
    {
    f32 d = D_0045B080[0];
    if (o->v70.y < -1100 * d) {
        o->v70.y = 100.0f * d;
    }
    }
}
