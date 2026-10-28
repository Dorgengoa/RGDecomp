/* rgp:protos */
#define RGP_SELF_MenuYesNoHighlightMaybe_380560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E00380560 {
    u8 pad0[8];
    s16 unk8;
    u8 padA[0x16];
} E00380560;

/*rgp*/
extern s16 D_00463B38[0x100];
extern s16 D_00463B3A[0x100];

void MenuYesNoHighlightMaybe_380560(s32 arg0, s32 arg1, s32 arg2)
{
    E00380560 *temp_2;
    s16 v;

    temp_2 = ((E00380560 *)UiGetWidgetSprite_28fe10(arg1, arg2, 0));
    if (temp_2 != NULL) {
        v = D_00463B38[0];
        temp_2[0].unk8 = v;
        temp_2[1].unk8 = v;
        temp_2[(s8)arg0].unk8 = D_00463B3A[0];
    }
}
