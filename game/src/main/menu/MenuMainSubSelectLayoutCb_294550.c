/* rgp:protos */
#define RGP_SELF_MenuMainSubSelectLayoutCb_294550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern u8 D_004DB1B0[0x400];

s32 MenuMainSubSelectLayoutCb_294550(void *arg0) {
    u8 *p;
    s32 i;
    u8 *temp_2;

    p = (u8 *)arg0;
    i = 0;
    do {
        if (i == *(s16 *)(p + 0x12)) {
            UiSetSpriteSizeUvSize_28f670(&(*(u8 *)D_004DB1B0), 0x1AF, 0, 0, 0, 0, i);
        } else {
            UiSetSpriteSizeUvSize_28f670(&(*(u8 *)D_004DB1B0), 0x1AF, 0x46, 0x1C, 4, 4, i);
        }
        i += 1;
    } while (i < 2);
    temp_2 = (u8 *)UiGetWidgetSprite_28fe10(&(*(u8 *)D_004DB1B0), 0x1AE, 0);
    if (temp_2 == NULL) {
        return 0;
    }
    *(s16 *)(temp_2 + 2) = (*(s16 *)(p + 2) + (*(s16 *)(p + 0x12) * *(s16 *)(p + 6)));
    return 1;
    return 0;
}
