/* rgp:protos */
#define RGP_SELF_EventSceneSysResetMaybe_26b080 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *dst, s32 val, s32 n);
extern u8 *D_00481F78;
extern s32 D_00482044;
extern s32 D_00482048;
extern s32 D_0048204C;
extern s32 D_00482050;
extern s32 D_0048205C;
extern s32 D_00482060;
extern s32 D_00482064;
extern s32 D_00482068;
extern s32 D_0048206C;
extern s32 D_004BD9A4[0x100];
extern s32 D_004BD9E4[0x100];
extern u8 D_004BDFB0[0x400];
extern u8 D_004BDFF0[0x400];
extern u8 D_004BE030[0x400];
extern u8 D_004BE070[0x400];

void EventSceneSysResetMaybe_26b080(void)
{
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    u8 *p;
    u8 *q;
    s32 k;

    EventCameraInit_254be0(D_00482060, D_0048205C, 0x20);
    var_16 = 0;
    do {
        EvSubMachineInit_251ff0(D_00482068 + (var_16 * 0x5F0), D_00482064, 0x80);
        var_16 += 1;
    } while (var_16 < 0x20);
    var_16_2 = 0;
    do {
        MenuWinInit_26c450(D_0048206C + (var_16_2 * 0xE0));
        var_16_2 += 1;
    } while (var_16_2 < 8);
    var_16_3 = 0;
    do {
        MenuWinInit_26c450(D_0048206C + (var_16_3 * 0xE0));
        var_16_3 += 1;
    } while (var_16_3 < 8);
    D_00482044 = -1;
    memset(&(*(u8 *)D_004BDFB0), 0, 0x40);
    memset(&(*(u8 *)D_004BDFF0), 0, 0x40);
    D_00482048 = -1;
    memset(&(*(u8 *)D_004BE030), 0, 0x40);
    D_0048204C = 0;
    memset(&(*(u8 *)D_004BE070), 0, 0x40);
    D_004BD9E4[0] = 0;
    D_00482050 = 0;
    GameSceneDofReset_1cf200(D_00481F78);
    ScreenFadeSetOverlayMaybe_1cf540(D_00481F78, 0, 0, 0);
    p = D_00481F78;
    k = 0x10000;
    q = p + k;
    *(u32 *)(q - 0x4AA4) = 0xBF800000;
    if (D_004BD9A4[0] != 0) {
        D_004BD9A4[0] = 0;
        CameraPopModeReset_30a0b0();
    }
}
