/* rgp:protos */
#define RGP_SELF_GameStartRecFillPresetMaybe_3e7440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s16 x1C;
    s16 x1E;
    s16 x20;
} S3e7440;

s32 GameStartRecFillPresetMaybe_3e7440(s32 pad0, S3e7440 *arg1)
{
    if (arg1->x0 == 4) {
        arg1->x6 = 0;
        switch (arg1->x4) {
        case 0x64:
            arg1->x8 = 0xF;
            arg1->x6 = 0;
            arg1->xA = 0x64;
            arg1->xC = 0;
            arg1->x10 = 0;
            arg1->x14 = 0;
            arg1->x18 = 0;
            arg1->x1C = 0;
            arg1->x1E = 0;
            arg1->x20 = 0;
            break;
        case 0xC8:
            arg1->x8 = 0xF;
            arg1->x6 = 0x10;
            arg1->xA = 0x64;
            arg1->xC = 0;
            arg1->x10 = 0;
            arg1->x14 = 0;
            arg1->x18 = 0;
            arg1->x1C = 4;
            arg1->x1E = 0;
            arg1->x20 = 0xA;
            break;
        }
    }

    return 1;
}
