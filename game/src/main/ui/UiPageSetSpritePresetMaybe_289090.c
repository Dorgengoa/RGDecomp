/* rgp:protos */
#define RGP_SELF_UiPageSetSpritePresetMaybe_289090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 v[6];
} S6;

/*rgp*/
extern s16 D_0047EAC8[6] __attribute__((section(".sdata")));
extern s16 D_0047EAD8[6] __attribute__((section(".sdata")));
extern s16 D_0047EAE8[6] __attribute__((section(".sdata")));
extern s16 D_0047EAF8[6] __attribute__((section(".sdata")));

s32 UiPageSetSpritePresetMaybe_289090(s32 arg0, void *arg1, s32 arg2, s32 arg3)
{
    S6 sp60 __attribute__((aligned(16)));
    S6 sp50 __attribute__((aligned(16)));
    S6 sp40 __attribute__((aligned(16)));
    S6 sp30 __attribute__((aligned(16)));
    void *temp_2;

    sp60 = *(S6 *)D_0047EAC8;
    sp50 = *(S6 *)D_0047EAD8;
    sp40 = *(S6 *)D_0047EAE8;
    sp30 = *(S6 *)D_0047EAF8;
    temp_2 = UiPageGetWidgetSprites_289ad0(arg0, arg1);
    if (temp_2 == NULL) {
        return 0;
    }
    *(s16 *)((u8 *)temp_2 + 0x0) = 0;
    *(s16 *)((u8 *)temp_2 + 0x2) = 0;
    if (arg3 != 0) {
        *(s16 *)((u8 *)temp_2 + 0xC) = sp40.v[arg2];
        *(s16 *)((u8 *)temp_2 + 0x4) = sp40.v[arg2];
        *(s16 *)((u8 *)temp_2 + 0xE) = sp30.v[arg2];
        *(s16 *)((u8 *)temp_2 + 0x6) = sp30.v[arg2];
    } else {
        *(s16 *)((u8 *)temp_2 + 0xC) = 0;
        *(s16 *)((u8 *)temp_2 + 0x4) = 0;
        *(s16 *)((u8 *)temp_2 + 0xE) = 0;
        *(s16 *)((u8 *)temp_2 + 0x6) = 0;
    }
    *(s16 *)((u8 *)temp_2 + 0x8) = sp60.v[arg2];
    *(s16 *)((u8 *)temp_2 + 0xA) = sp50.v[arg2];
    return 0;
}
