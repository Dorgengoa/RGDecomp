/* rgp:protos */
#define RGP_SELF_EvMapObjNodeApplyPartMatrixMaybe_367230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Mat4 { f32 m[16]; } Mat4;
typedef struct Mat34 { f32 m[12]; } Mat34;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvMapObjNodeApplyPartMatrixMaybe_367230(u8 *o, int rgp_a1, int rgp_a2)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Mat34)]; char m1[0x30 + sizeof(Vec4)]; char m2[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Mat34) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    Mat4 m30 __attribute__((aligned(16)));
    Vec4 v20 __attribute__((aligned(16)));

    if (*(s32 *)(o + 0x144) == 0) {
        return 0;
    }
    EvMapObjPartStep_363ba0((void *)o, (int)rgp_a1, (int)rgp_a2);
    EvMapObjPartCalcMatrix_363a70(o, &(*(Mat34 *)(rgp_blk1 + 0x0)));
    v20.q = *(u128 *)(o + 0xF0);
    FrameCalcWorldMatrix_148ff0(*(void **)(*(u8 **)(o + 0x144) + 4), &m30);
    sceVu0InversMatrix(&m30, &m30);
    sceVu0CopyVector(&(*(Vec4 *)(rgp_blk1 + 0x30)), &v20);
    (*(Vec4 *)(rgp_blk1 + 0x30)).f[3] = 1.0f;
    MtxMul_13d240(&(*(Mat34 *)(rgp_blk1 + 0x0)), &m30, &(*(Mat34 *)(rgp_blk1 + 0x0)));
    ModelFrameSetMatrix_14a190(*(void **)(o + 0x144), &(*(Mat34 *)(rgp_blk1 + 0x0)));
    return *(s32 *)(o + 0x138);
}
