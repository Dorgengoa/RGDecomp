/* rgp:protos */
#define RGP_SELF_MapSkyResetModels_17f8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void MapSkyResetModels_17f8a0(u8 *p)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        u8 *q = p + i * 0x1C0;
        ModelInit_151d50(q + 0x10);
        ModelInit_151d50(q + 0x730);
        ModelInit_151d50(q + 0xE50);
        *(s32 *)(p + i * 4 + 0xE30) = 0;
        *(s32 *)(p + i * 4 + 0x710) = 0;
        *(s32 *)(p + i * 4 + 0xE40) = 0;
        *(s32 *)(p + i * 4 + 0x720) = 0;
        *(s32 *)(p + i * 4 + 0x1550) = -1;
    }
    for (i = 0; i < 0x10; i++) {
        *(s32 *)(p + i * 8 + 0x1728) = 0;
        *(s32 *)(p + i * 8 + 0x172C) = 0;
    }
    ModelInit_151d50(p + 0x1560);
    *(s32 *)(p + 0x1720) = 0;
    *(f32 *)(p + 0x1724) = 4000.0f;
    *(s32 *)(p + 0) = 1;
}
