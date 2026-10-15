#include "types.h"
#pragma no_branch_likely on
extern void MotionListUpdateAll_171e40(s32, f32);
extern void MotionListSetPhase_171f50(s32, f32);
extern void ModelObjPlayMotionByName_1867a0(s32, s32, s32);
extern s32 EvM05ChangeGetPlayState_352020(void);
extern s32 EvM05ChangeGetMotionName_352030(void *);
extern char *strcpy(char *, const char *);
extern char D_00462998[];
static inline s32 ok(u8 *p) { return !(*(u32 *)(p + 0xD0) & 0x80000000); }
s32 EvM05ChangePlayStart_351de0(u8 *arg0)
{
    s32 a;
    s32 b;

    if (!ok(arg0)) {
        return 0;
    }
    if (*(u8 **)(arg0 + 0x13C) == NULL) {
        return 0;
    }
    if (EvM05ChangeGetPlayState_352020() == -1) {
        a = *(s32 *)(*(u8 **)(arg0 + 0x13C) + 0x6C);
        ModelObjPlayMotionByName_1867a0(a, EvM05ChangeGetMotionName_352030(arg0), 4);
        b = *(s32 *)(*(u8 **)(arg0 + 0x13C) + 0x6C) + 0x1F0;
        MotionListUpdateAll_171e40(b, 1.0f);
        MotionListSetPhase_171f50(b, 0.25f);
    }
    strcpy((char *)(arg0 + 0x148), D_00462998);
    *(s16 *)(arg0 + 0x15A) = 0;
    *(s16 *)(arg0 + 0x158) = 1;
    return 1;
}
