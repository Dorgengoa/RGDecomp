/* rgp:protos */
#define RGP_SELF_MeshMaterialReset_14b230 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz14b230_t; /* rg:vu0bind vf0 */
#define vz14b230 RG_VU0_BIND_VF(0, rgvb_vz14b230_t)


void MeshMaterialReset_14b230(u8 *p)
{ RG_VU0_FRAME;
    *(s16 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x0) = 0;
    *(s32 *)(p + 0xC) = 0;
    *(s8 *)(p + 0x6) = 0;
    *(s16 *)(p + 0x8) = 0;
    *(s16 *)(p + 0xA) = 0;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(rg_s128 *)(p + 0x20) = vz14b230;
    *(u128 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x14) = 0;
}
