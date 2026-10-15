#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Ctx0034DC90;

Ctx0034DC90 *GetGameData_1fede0();
s32 MsgTableLookup_28aa30(s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
s32 StateFlagTest_3ccd70(s32, s16);
extern s32 D_00482360;
extern s32 D_004823D8;
extern s32 D_00482E98;
extern u8 *D_00482E9C;

s32 HelpBoardFillList_34dc90(s32 arg0) {
    Ctx0034DC90 *ctx;
    s32 i;
    s32 row;
    s32 cnt;
    s32 off;
    s32 w;
    s32 h;

    ctx = GetGameData_1fede0();
    i = 0;
    do {
        UiSetTextString_28f510(D_00482360, 0x216, 0, i);
        UiSetTextString_28f510(D_00482360, 0x214, 0, i + 1);
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x218, 0, 0, 0, 0, i);
        i += 1;
    } while (i < 9);
    row = 0;
    cnt = 0;
    for (i = 0; i < D_00482E98; i++) {
        if (StateFlagTest_3ccd70(ctx->unk10, *(s16 *)(D_00482E9C + i * 0x7A + 6)) == 0) {
            continue;
        }
        cnt++;
        if (arg0 <= 0) {
            if (row >= 10) {
                continue;
            }
            UiSetTextString_28f510(D_00482360, 0x216, MsgTableLookup_28aa30(D_004823D8, 0x1FA4), row);
            off = i * 0x7A;
            UiSetTextString_28f510(D_00482360, 0x214, (s32)(D_00482E9C + off + 0xA), row + 1);
            if (StateFlagTest_3ccd70(ctx->unk10, *(s16 *)(D_00482E9C + off + 8)) == 0) {
                w = 0x1C;
                h = 0xE;
                UiSetSpriteSizeUvSize_28f670(D_00482360, 0x218, w, h, w, h, row);
            }
            row++;
        }
        arg0--;
    }
    return cnt;
}
