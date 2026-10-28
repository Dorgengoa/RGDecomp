/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void *GetGameData_1fede0(void);
extern s32 EvScriptSoundSlotPlay_302600(s32, s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);

class VC_0 {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER; s32 f(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
s32 EvScriptCmdBsPlay_302500(void *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    s32 t;
    s32 r;
    u8 *p;

    p = *(u8 **)((u8 *)arg0 + 4);
    if (p != NULL) {
        switch (((VC_0 *)p)->f((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3))) {
        case 9:
            if (StateFlagTest_3ccd70(*(s32 *)((u8 *)GetGameData_1fede0() + 0x10), 0x7EE) != 0) {
                return 1;
            }
            break;
        }
    }
    t = GetCurrentScene_1f5be0();
    if (t != 0) {
        r = EvScriptSoundSlotPlay_302600(GameSceneSoundSlot1GetHandle_1d07b0(t), arg1, arg2);
    } else {
        r = 1;
    }
    return r;
}

}
