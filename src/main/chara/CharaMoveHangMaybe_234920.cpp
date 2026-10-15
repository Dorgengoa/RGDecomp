#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

typedef struct {
    V4 r[4];
} M4;

typedef struct {
    V4 r[3];
} M3;

extern "C" {
f32 Atan2f_1291a8(f32, f32);
void FrameCalcWorldMatrix_148ff0(s32, M3 *);
void ModelSetRot_151080(u8 *, u8 *);
void ModelSetPos_151110(u8 *, u8 *);
s32 ModelGetFrame_1511f0(u8 *, s32);
s32 ModelFindFrameIndexByName_151220(u8 *, s32);
void MatFromRotPos_1caf90(void *, V4 *, V4 *);
void MtxInverseAffine_1cb640(M4 *, M3 *);
void MatMul_1cb700(M4 *, void *, M4 *);
void VecAdd_1cbdc0(u8 *, u8 *, u8 *);
void MtxCopy_1cbde0(M3 *, M4 *);
void VecCopy_1cbe30(u8 *, V4 *);
void CharaMoveRolloverMaybe_236930(void);
void CharaProbeWaterSurfaceMaybe_237520(u8 *, s32, s32, s32);
void CharaGroundSnapMaybe_237990(u8 *, s32, s32, f32);
void CharaHangLedgeFind_238a70(u8 *, u8 *, s32, s32, s32, s32, s32, f32, f32);
void CharaHangLedgeMoveMaybe_2399f0(u8 *, u8 *, s32, s32, s32, f32, V4 *, V4 *, V4 *, f32, f32);
extern const f32 D_0045B080[];
extern f32 D_0047DAC0;
extern f32 D_0047DB14;
void CharaMoveHangMaybe_234920(u8 *arg0, u8 *arg1);
}

void CharaMoveHangMaybe_234920(u8 *arg0, u8 *arg1)
{
    M4 m;
    V4 v1;
    V4 v2;
    V4 w;
    M3 n;
    M4 k;
    M4 j;
    V4 a;
    V4 b;
    f32 r;
    f32 t;
    u8 *p;
    u8 *q;
    s32 id;
    s32 id2;
    s32 h;
    bool ok;
    f32 d;

    CharaMoveRolloverMaybe_236930();
    r = 0.0f;
    *(s32 *)(arg0 + 0x3DC) = 0;
    if (arg1 != 0 && (p = *(u8 **)(arg0 + 0x3F4)) != 0 && (((*(u32 *)(arg0 + 0x3CC) & 0x80000000) != 0) ^ 1)) {
        id = *(s32 *)(arg1 + 0xC);
        id2 = *(s32 *)(arg1 + 0x10);
        t = D_0047DAC0 * *(f32 *)&D_0045B080[0];
        if (p != 0) {
            r = *(f32 *)(p + 0x4C8) * (D_0047DB14 * *(f32 *)&D_0045B080[0]);
        }
        r = (r > t) ? r : t;
        *(u128 *)&v1 = *(u128 *)(p + 0x180);
        *(u128 *)&v2 = *(u128 *)(*(u8 **)(arg0 + 0x3F4) + 0x190);
        MatFromRotPos_1caf90(&m, &v2, &v1);
        q = *(u8 **)(arg0 + 0x3F4);
        h = *(s32 *)(arg1 + 0x38);
        if (q == 0) {
            ok = false;
        } else {
            h = ModelGetFrame_1511f0(q, ModelFindFrameIndexByName_151220(q, h));
            if (h == 0) {
                ok = false;
            } else {
                FrameCalcWorldMatrix_148ff0(h, &n);
                ok = true;
            }
        }
        if (!ok) {
            MtxCopy_1cbde0(&n, &m);
        }
        MtxInverseAffine_1cb640(&k, &n);
        MatMul_1cb700(&j, &k, &m);
        CharaHangLedgeMoveMaybe_2399f0(arg0 + 0x350, *(u8 **)(arg0 + 0x3F4), id, id2, *(s16 *)(arg0 + 0x40E), r, &a, &b, &w, r, *(f32 *)(arg0 + 0xB0));
        MatFromRotPos_1caf90(&n, &a, &b);
        MatMul_1cb700(&m, &n, &j);
        *(f32 *)(arg0 + 0x64) = Atan2f_1291a8(m.r[2].x, m.r[2].z);
        VecCopy_1cbe30(arg0 + 0x70, &m.r[3]);
        ModelSetRot_151080(*(u8 **)(arg0 + 0x3F4), arg0 + 0x60);
        ModelSetPos_151110(*(u8 **)(arg0 + 0x3F4), arg0 + 0x70);
        CharaProbeWaterSurfaceMaybe_237520(arg0, id, id2, *(s32 *)(arg1 + 0x34));
        CharaGroundSnapMaybe_237990(arg0, id, id2, *(f32 *)(arg0 + 0x74));
        CharaHangLedgeFind_238a70(arg0 + 0x350, *(u8 **)(arg0 + 0x3F4), id, id2, *(s16 *)(arg0 + 0x40E), *(s32 *)(arg1 + 0x38), 0, r, *(f32 *)(arg0 + 0x3F0));
    } else {
        *(u32 *)(arg0 + 0x3CC) = 0x80000000;
    }
    VecAdd_1cbdc0(arg0 + 0x80, arg0 + 0x80, arg0 + 0xE0);
    d = D_0045B080[0];
    *(s32 *)(arg0 + 0xA0) = 0;
    *(s32 *)(arg0 + 0xA4) = 0;
    *(s32 *)(arg0 + 0xA8) = 0;
    *(s32 *)(arg0 + 0xAC) = 0;
    *(s32 *)(arg0 + 0xB0) = 0;
    *(s32 *)(arg0 + 0xB4) = 0;
    *(s32 *)(arg0 + 0xB8) = 0;
    *(s32 *)(arg0 + 0xBC) = 0;
    *(s32 *)(arg0 + 0xC0) = 0;
    *(s32 *)(arg0 + 0xC4) = 0;
    *(s32 *)(arg0 + 0xC8) = 0;
    *(s32 *)(arg0 + 0xCC) = 0;
    *(s32 *)(arg0 + 0xD0) = 0;
    *(s32 *)(arg0 + 0xD4) = 0;
    *(s32 *)(arg0 + 0xD8) = 0;
    *(s32 *)(arg0 + 0xDC) = 0;
    if (*(f32 *)(arg0 + 0x74) < -1100 * d) {
        *(f32 *)(arg0 + 0x74) = 100.0f * d;
    }
}
