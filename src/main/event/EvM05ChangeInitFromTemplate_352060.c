#include "types.h"

typedef struct {
    f32 x;
    f32 y;
} V2_00352060;

typedef struct S00352060 {
    u8 pad0[0xE0];
    V2_00352060 unkE0;
    s32 unkE8;
    s32 unkEC;
    u8 padF0[0x140 - 0xF0];
    s32 unk140;
    s32 unk144;
} S00352060;

typedef struct Src00352060 {
    u8 pad0[0xE0];
    V2_00352060 unkE0;
    u8 padE8[0x140 - 0xE8];
    s32 unk140;
    s32 unk144;
} Src00352060;

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 MemStackStrDup_14cff0(s32 arg0, s32 arg1);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern s32 EvObjInit_2f9cf0(S00352060 *arg0, s32 arg1, Src00352060 *arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 EvObjSubGetTargetCount_351fb0(Src00352060 *arg0);
extern s32 EvObjSubGetTargets_351fc0(Src00352060 *arg0);
extern void EvM05ChangeReset_3522b0(void);
extern s32 EvTargetCopy_3529a0(s32 arg0, s32 arg1, s32 arg2);
extern void EvTargetCtor_352c50(void);

s32 EvM05ChangeInitFromTemplate_352060(S00352060 *arg0, s32 arg1, Src00352060 *arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 n;
    s32 p;
    s32 i;
    s32 r;

    EvM05ChangeReset_3522b0();
    if (arg2 == NULL || arg3 == 0) {
        return 0;
    }
    if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    arg0->unkE0 = arg2->unkE0;
    n = EvObjSubGetTargetCount_351fb0(arg2);
    arg0->unkE8 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x140 + 0x10, arg3), EvTargetCtor_352c50, 0, 0x140, n);
    if (arg0->unkE8 == 0) {
        return 0;
    }
    arg0->unkEC = EvObjSubGetTargetCount_351fb0(arg2);
    p = arg0->unkE8;
    for (i = 0; i < arg0->unkEC; i++, p += 0x140) {
        if (EvTargetCopy_3529a0(p, (s32)((u8 *)EvObjSubGetTargets_351fc0(arg2) + i * 0x140), arg3) == 0) {
            return 0;
        }
    }
    arg0->unk140 = MemStackStrDup_14cff0(arg2->unk140, arg3);
    if (arg0->unk140 == 0) {
        return 0;
    }
    arg0->unk144 = r = MemStackStrDup_14cff0(arg2->unk144, arg3);
    return r != 0;
}
