/* rgp:protos */
#define RGP_SELF_EventCameraCmdShakeAt_254df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    u8 unk10[0x20];
    s32 unk30;
} A0;

typedef struct {
    u8 pad0[0x44];
    s32 unk44;
    u8 pad48[0x50 - 0x48];
    u8 unk50[0x10];
    u8 unk60[0x10];
    u8 pad70[0x180 - 0x70];
    s32 unk180;
    u8 pad184[0x190 - 0x184];
    u8 unk190[0x10];
    u8 unk1A0[0x10];
    u8 unk1B0[0x10];
} A1;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventCameraCmdShakeAt_254df0(A0 *arg0, A1 *arg1) {
    s32 n;
    s32 m;

    if (arg0->unk30 <= -1) {
        arg1->unk180 = 1;
        sceVu0CopyVector(arg1->unk190, arg0->unk10);
        sceVu0CopyVector(arg1->unk1A0, arg1->unk50);
        sceVu0CopyVector(arg1->unk1B0, arg1->unk60);
        if (arg1->unk44 % 2 == 0) {
            VecAdd_13be20(arg1->unk60, arg1->unk1B0, arg1->unk190);
        } else {
            VecSub_13be40(arg1->unk60, arg1->unk1B0, arg1->unk190);
        }
        arg1->unk44++;
        if (arg1->unk44 > 100) {
            arg1->unk44 = 0;
        }
    } else {
        if (arg1->unk44 <= 0) {
            arg1->unk180 = 1;
            sceVu0CopyVector(arg1->unk190, arg0->unk10);
            sceVu0DivVector(arg0->unk10, arg0->unk10, (f32)arg0->unk30);
        }
        sceVu0CopyVector(arg1->unk1A0, arg1->unk50);
        sceVu0CopyVector(arg1->unk1B0, arg1->unk60);
        m = arg1->unk44 % 2;
        if (m == 0) {
            VecAdd_13be20(arg1->unk60, arg1->unk1B0, arg1->unk190);
        } else if (m == 1) {
            VecSub_13be40(arg1->unk60, arg1->unk1B0, arg1->unk190);
        }
        VecSub_13be40(arg1->unk190, arg1->unk190, arg0->unk10);
        n = arg1->unk44;
        if (n >= arg0->unk30) {
            arg1->unk44 = 0;
            arg1->unk180 = 0;
            return 0;
        }
        arg1->unk44 = n + 1;
    }
    return 1;
}
