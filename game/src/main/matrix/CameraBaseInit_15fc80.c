/* rgp:protos */
#define RGP_SELF_CameraBaseInit_15fc80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/

void CameraBaseInit_15fc80(u8 *p)
{
    *(f32 *)(p + 0x00) = 45.0f;
    MtxIdentity_13d2e0(p + 0x10);
    *(s32 *)(p + 0x70) = 0;
    *(u128 *)(p + 0x50) = 0;
    *(u128 *)(p + 0x60) = 0;
    *(f32 *)(p + 0x68) = -1.0f;
    MtxIdentity_13d2e0(p + 0x80);
}
