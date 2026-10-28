/* rgp:protos */
#define RGP_SELF_EvSubMachineIsIdle_251b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T3 {
    s32 f0;
    u8  pad4[0x48];
    s32 f4C;
} T3;

typedef struct Obj {
    u8  pad0[8];
    s32 f8;
    u8  padC[4];
    s32 f10;
    u8  pad14[4];
    T3  *f18;
    s32 f1C;
    s32 f20;
    u8  pad24[4];
    s32 f28;
    u8  pad2C[4];
    s32 f30;
    u8  pad34[4];
    s32 f38;
    u8  pad3C[0x60 - 0x3C];
    s32 f60;
} Obj;

/*rgp*/
extern s32 D_004BDDB0[];

s32 EvSubMachineIsIdle_251b60(Obj *arg0)
{
    T3 *temp_3;

    temp_3 = arg0->f18;
    if (temp_3 != 0) {
        if (temp_3->f4C == 0) {
            if (temp_3->f0 == 0x15) {
                if (EventCastMotionIsFinished_258340(D_004BDDB0, arg0->f60) != 0) {
                    arg0->f1C = 0;
                    arg0->f18 = 0;
                }
            }
        }
    }
    if (arg0->f8 == 0 && arg0->f10 == 0 && arg0->f18 == 0 && arg0->f20 == 0 &&
        arg0->f28 == 0 && arg0->f30 == 0 && arg0->f38 == 0) {
        return 1;
    }
    return 0;
}
