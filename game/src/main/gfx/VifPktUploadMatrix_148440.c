/* rgp:protos */
#define RGP_SELF_VifPktUploadMatrix_148440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

s32 VifPktUploadMatrix_148440(void *p0, u8 *p1, u128 *p2)
{
    *(u32 *)(p1 + 0x0) = 0x60000005;
    *(u32 *)(p1 + 0x4) = 0;
    *(u32 *)(p1 + 0x8) = 0x1000101;
    *(u32 *)(p1 + 0xC) = 0x6C04003C;
    *(u128 *)(p1 + 0x10) = p2[0];
    *(u128 *)(p1 + 0x20) = p2[1];
    *(u128 *)(p1 + 0x30) = p2[2];
    *(u128 *)(p1 + 0x40) = p2[3];
    *(u128 *)(p1 + 0x50) = 0;
    *(u32 *)(p1 + 0x50) = 0x14000000;
    return 6;
}
