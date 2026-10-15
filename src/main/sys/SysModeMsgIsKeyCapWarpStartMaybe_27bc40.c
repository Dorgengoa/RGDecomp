#include "types.h"

extern s32 GetKeyCapModeMaybe_1c3540(void);
extern void *SysGetModeMsg_1c39b0(void);

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void)
{
    s32 r0;
    struct Obj0 *r1;

    r0 = GetKeyCapModeMaybe_1c3540();
    if (r0 == 0) {
        return 0;
    }
    r1 = (struct Obj0 *)SysGetModeMsg_1c39b0();
    if (r1 == 0) {
        goto zero;
    }
    if (r1->m00 == 6) {
        return 1;
    }
zero:
    return 0;
}
