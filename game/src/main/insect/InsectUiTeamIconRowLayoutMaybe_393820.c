/* rgp:protos */
#define RGP_SELF_InsectUiTeamIconRowLayoutMaybe_393820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void InsectUiTeamIconRowLayoutMaybe_393820(s32 pd0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 *p;
    s32 i;
    s32 z;

    if (arg1 == NULL) {
        return;
    }
    p = *(u8 **)(arg1 + 0x20);
    if (p == NULL) {
        return;
    }
    for (i = 0; i < 5; i++) {
        *(s16 *)(p + 0x0) = 0;
        *(s16 *)(p + 0x2) = arg2 * i;
        *(s16 *)(p + 0x4) = 0x18;
        *(s16 *)(p + 0xC) = 0x18;
        *(s16 *)(p + 0x6) = 0x18;
        *(s16 *)(p + 0xE) = 0x18;
        switch (arg3) {
        case 0:
            *(s16 *)(p + 0x8) = 0x90;
            *(s16 *)(p + 0xA) = 0x62;
            break;
        case 1:
            *(s16 *)(p + 0x8) = 0xC0;
            *(s16 *)(p + 0xA) = 0x62;
            break;
        case 2:
            *(s16 *)(p + 0x8) = 0xA8;
            *(s16 *)(p + 0xA) = 0x62;
            break;
        }
        if (arg4 == i) {
            *(s16 *)(p + 0x8) = 0xD8;
            *(s16 *)(p + 0xA) = 0x62;
        }
*(f32 *)(p+0x10) = *(f32 *)(p+0x14) = *(s16 *)(p+0x18) = *(s16 *)(p+0x1A) = 0;
        p += 0x20;
    }
}
