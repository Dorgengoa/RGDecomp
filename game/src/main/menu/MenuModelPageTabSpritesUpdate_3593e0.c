/* rgp:protos */
#define RGP_SELF_MenuModelPageTabSpritesUpdate_3593e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"





/*rgp*/



void MenuModelPageTabSpritesUpdate_3593e0(u8 *o)
{
    s32 i;
    s32 k;

    for (i = 0; i < 2; i++) {
        if (*(volatile u8 *)(o + 0x16D + o[0x175]) == i) {
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, i * 3);
            k = (s32)((u32)i * 3);
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, k + 1);
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, k + 2);
        } else {
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x19, -0x270F, 0x1B, -0x270F, 0x2B,
                        -0x270F, 0x1B, i * 3);
            k = (s32)((u32)i * 3);
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x19, -0x270F, 0x1B, -0x270F, 0x2B,
                        -0x270F, 0x1B, k + 1);
            UiSetSpritePosSizeUv_28f710(*(void **)(o + 0x134), 0x247, -0x270F, -0x19, -0x270F, 0x1B, -0x270F, 0x2B,
                        -0x270F, 0x1B, k + 2);
        }
    }

}
