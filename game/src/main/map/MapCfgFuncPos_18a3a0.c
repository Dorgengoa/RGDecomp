/* rgp:protos */
#define RGP_SELF_MapCfgFuncPos_18a3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
typedef rg_u128 u128;

typedef union {
    u128 q;
    f32 f[4];
    s32 i[4];
} V4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047D464;
extern f32 D_0047DADC;
extern f32 D_00481240;
extern f32 D_00481244;
extern f32 D_00481248;
extern u8 *D_004812D8;
extern u8 *D_004812DC;
extern s32 D_004812E4;

s32 MapCfgFuncPos_18a3a0(u8 *arg0) {
    V4 pos __attribute__((aligned(16)));
    V4 rot __attribute__((aligned(16)));
    V4 scl __attribute__((aligned(16)));
    V4 off __attribute__((aligned(16)));
    V4 mat[4] __attribute__((aligned(16)));
    s32 *flags;

    if (D_004812D8 == NULL) {
        return 0;
    }
    VariantReadVec3_15f6c0(&pos, arg0);
    pos.f[3] = 1.0f;
    VariantReadVec3_15f6c0(&rot, arg0 + 0x18);
    rot.i[3] = 0;
    VariantReadVec3_15f6c0(&scl, arg0 + 0x30);
    scl.i[3] = 0;
    if (D_004812E4 == 0) {
        pos.f[0] += D_00481240;
        pos.f[1] += D_00481244;
        pos.f[2] += D_00481248;
    }
    NodeSetTranslation_1866b0(D_004812D8, &pos);
    rot.f[0] = WrapAngle_13c050(rot.f[0]);
    rot.f[1] = WrapAngle_13c050(rot.f[1]);
    rot.f[2] = WrapAngle_13c050(rot.f[2]);
    NodeSetRotation_186620(D_004812D8, &rot);
    NodeSetScale_1865b0(D_004812D8, &scl);
    if (D_004812DC != NULL && *(s32 *)(D_004812DC + 0x40) == 6) {
        flags = (s32 *)(D_004812DC + 0x60);
        if ((*flags & 0x40) || (*flags & 0x20)) {
            { f32 x = scl.f[0]; if (x <= D_0047D464 && scl.f[1] <= D_0047D464 && scl.f[2] <= D_0047D464) {
                scl.f[2] = 25.0f;
                scl.f[1] = 25.0f;
                scl.f[0] = 25.0f;
            } }
        } else if (*flags & 0x200) {
            scl.f[2] = 20.0f;
            scl.f[1] = 20.0f;
            scl.f[0] = 20.0f;
        } else {
            s32 b = D_0047DADC + scl.f[1];
            s32 c = D_0047DADC + scl.f[2];
            s32 a = D_0047DADC + scl.f[0];
            if (a == 1 && b == 1 && c == 1) {
            scl.f[2] = 15.0f;
            scl.f[1] = 15.0f;
            scl.f[0] = 15.0f;
            }
        }
        NodeSetScale_1865b0(D_004812DC, &scl);
        off.q = 0;
        if (*flags & 8) {
            off.f[0] = -2.0f;
            off.f[2] = -12.0f;
        }
        MtxIdentity_13d2e0(mat);
        sceVu0RotMatrixY(mat, mat, rot.f[1]);
        MtxMulVec4_13c900(&off, mat, &off);
        VecAddInPlace_13e070(&pos, &off);
        NodeSetTranslation_1866b0(D_004812DC, &pos);
    }
    return 1;
}
