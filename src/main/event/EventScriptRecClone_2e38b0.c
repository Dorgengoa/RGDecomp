#include "types.h"

typedef struct Obj {
    u8 pad0[0x10];
    u8 *x10;
    s32 x14;
} Obj;

extern void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 EventScriptRecGetEntry_2e3840(s32, s32);
extern s32 EventScriptRecGetEntries_2e3890(s32);
extern s32 EventScriptRecGetEntryCount_2e38a0(s32);
extern void EventScriptRecReset_2e3a90(void);
extern s32 EventRecClone_2e5740(Obj *, s32, s32, s32, s32, s32);
extern s32 VariantArrayClone_3027d0(void *, s32, s32, s32);

s32 EventScriptRecClone_2e38b0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 n;
    s32 i;

    EventScriptRecReset_2e3a90();
    if (arg2 == 0 || arg3 == 0) {
        return 0;
    }
    if (EventRecClone_2e5740(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    if (EventScriptRecGetEntries_2e3890(arg2) != 0 && EventScriptRecGetEntryCount_2e38a0(arg2) > 0) {
        n = EventScriptRecGetEntryCount_2e38a0(arg2);
        arg0->x10 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 12 + 0x10, arg3), 0, 0, 12, n);
        if (arg0->x10 == 0) {
            return 0;
        }
        arg0->x14 = EventScriptRecGetEntryCount_2e38a0(arg2);
        for (i = 0; i < arg0->x14; i++) {
            if (VariantArrayClone_3027d0(arg0->x10 + i * 12, EventScriptRecGetEntry_2e3840(arg2, i), arg3, 0) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
