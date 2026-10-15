#include "types.h"

typedef struct {
    u8 pad0[0x10];
    u8 *unk10;
    u8 *unk14;
    s16 unk18;
    s16 unk1A;
} Obj;

extern void *ConstructNewArray_100710(void *, void (*)(), s32, s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 EventPathRecGetPath_2e40e0(Obj *, s32);
extern void EventPathRecReset_2e43b0(void);
extern s32 EventPathClone_2e4580(u8 *, s32, s32);
extern s32 EventRecClone_2e5740(Obj *, s32, Obj *, s32, s32, s32);
extern void *memcpy(void *, const void *, s32);
extern void SrtCtor48_1c7510();
extern void EventPathCtor_2e4740();

s32 EventPathRecClone_2e41a0(Obj *arg0, s32 arg1, Obj *arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 n;
    s32 i;
    void *p;

    EventPathRecReset_2e43b0();
    if (arg2 == NULL || arg3 == 0) {
        return 0;
    }
    if (EventRecClone_2e5740(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    n = arg2->unk18;
    p = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x30 + 0x10, arg3), SrtCtor48_1c7510, 0, 0x30, n);
    arg0->unk10 = p;
    if (p == 0) {
        return 0;
    }
    n = arg2->unk1A;
    p = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x10 + 0x10, arg3), EventPathCtor_2e4740, 0, 0x10, n);
    arg0->unk14 = p;
    if (p == 0) {
        return 0;
    }
    arg0->unk18 = arg2->unk18;
    arg0->unk1A = arg2->unk1A;
    memcpy(arg0->unk10, arg2->unk10, arg0->unk18 * 0x30);
    for (i = 0; i < arg0->unk1A; i++) {
        if (EventPathClone_2e4580(arg0->unk14 + i * 0x10, EventPathRecGetPath_2e40e0(arg2, i), arg3) == 0) {
            return 0;
        }
    }
    return 1;
}
