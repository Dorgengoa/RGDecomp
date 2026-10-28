/* rgp:protos */
#define RGP_SELF_InfoEdgeFillList_398d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[6];
    s16 id;
    s16 id2;
    char name[0x40];
} Rec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern s32 D_004823D8;
extern s32 D_004835A8;
extern Rec *D_004835AC;

s32 InfoEdgeFillList_398d90(s32 skip)
{
    u8 *ctx;
    s32 i;
    s32 row;
    s32 count;
    s32 off;

    ctx = ((u8 *)GetGameData_1fede0());
    for (i = 0; i < 9; i++) {
        UiSetTextString_28f510(D_00482360, 0x216, 0, i);
        UiSetTextString_28f510(D_00482360, 0x214, 0, i + 1);
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x218, 0, 0, 0, 0, i);
    }
    UiSetTextString_28f510(D_00482360, 0x215, 0, 0);
    UiSetTextString_28f510(D_00482360, 0x214, MsgTableLookup_28aa30(D_004823D8, 0), 0);
    row = 0;
    count = 0;
    for (i = 0; i < D_004835A8; i++) {
        if (StateFlagTest_3ccd70(*(s32 *)(ctx + 0x10), D_004835AC[i].id) == 0) {
            continue;
        }
        count++;
        if (skip <= 0) {
            if (row >= 10) {
                continue;
            }
            UiSetTextString_28f510(D_00482360, 0x216, MsgTableLookup_28aa30(D_004823D8, 0x1FA4), row);
            off = (u32)i * 0x4A;
            UiSetTextString_28f510(D_00482360, 0x214, (s32)((u8 *)D_004835AC + off + 0xA), row + 1);
            if (StateFlagTest_3ccd70(*(s32 *)(ctx + 0x10), *(s16 *)((u8 *)D_004835AC + off + 8)) == 0) {
                UiSetSpriteSizeUvSize_28f670(D_00482360, 0x218, 0x1C, 0xE, 0x1C, 0xE, row);
            }
            row++;
        }
        skip--;
    }
    UiSetWidgetsVisibleById_291110(D_00482360, 0x213, 1, 1);
    return count;
}
