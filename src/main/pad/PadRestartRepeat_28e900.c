#include "types.h"

typedef struct Buf_FUN_0028e900 {
    s32 f000;
    u8 pad004[0x100];
    u8 f104;
    u8 pad105[0xB];
} Buf_FUN_0028e900;

typedef struct Obj_FUN_0028e900 Obj_FUN_0028e900;

extern void PadSaveRepeatConfig_1838f0(Obj_FUN_0028e900 *o, Buf_FUN_0028e900 *b);
extern void PadClearRepeatState_183e20(Obj_FUN_0028e900 *o, s32 *p);
extern void PadApplyRepeatConfig_183800(Obj_FUN_0028e900 *o, Buf_FUN_0028e900 *b);

void PadRestartRepeat_28e900(s32 unused, Obj_FUN_0028e900 *o, s32 *p)
{
    Buf_FUN_0028e900 b;

    b.f000 = 0;
    b.f104 = 0;
    PadSaveRepeatConfig_1838f0(o, &b);
    PadClearRepeatState_183e20(o, p);
    PadApplyRepeatConfig_183800(o, &b);
}
