/* rgp:protos */
#define RGP_SELF_TargetMngStep_31f330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 u0;
    f32 u4;
    s32 u8;
    s32 uC;
    u8 u10[0xB0];
    u8 uC0[0x34];
    f32 uF4;
    f32 uF8;
} T31f330;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DB10;
extern f32 D_0047DC44;
extern f32 D_0047DC4C;
extern f32 D_0047DC50;
extern f32 D_0047DC54;

void TargetMngStep_31f330(T31f330 *arg0) {
    s32 old;
    s32 h;
    f32 f;
    f32 lim;

    if (arg0->u8 != 0) {
        arg0->u4 = WrapAngle_13c050(D_0047DC44 + arg0->u4);
        TargetMngSyncLeaderPose_320850(arg0);
        old = ((short)TargetRefGetId_2e7120(arg0->uC0));
        if (arg0->u8 == 2 && arg0->uC == 0) {
            arg0->u0 = 0;
            if (((unsigned char)TargetMngPickAttachPoint_31f860(arg0)) != 0) {
                arg0->u0 = 1;
            }
        }
        if (arg0->u8 == 1) {
            arg0->u0 = 0;
            if (TargetMngPickTarget_31faf0(arg0) != 0) {
                arg0->u0 = 1;
            }
        }
        if (old != ((short)TargetRefGetId_2e7120(arg0->uC0))) {
            h = GetCurrentScene_1f5be0();
            ObjRecSetFlags_1c3e00(h, 1, ((short)TargetRefGetId_2e7120(arg0->uC0)), 0x40000);
            arg0->uF4 = D_0047DC4C;
            arg0->uF8 = 1.0f;
        }
        if (arg0->u0 == 0) {
            arg0->uF4 = D_0047DC4C;
            arg0->uF8 = 1.0f;
        }
        f = arg0->uF4 + D_0047DB10;
        lim = D_0047DC50;
        arg0->uF4 = f;
        if (!(f <= lim)) {
            arg0->uF4 = f - lim;
        }
        f = arg0->uF8 - D_0047DC54;
        arg0->uF8 = f;
        if (f < 0.0f) {
            arg0->uF8 = 0.0f;
        }
        TargetSlotAnimUpdate_320a40(arg0->u10);
        TargetMngAimTimerTick_31ecf0(arg0);
    }
}
