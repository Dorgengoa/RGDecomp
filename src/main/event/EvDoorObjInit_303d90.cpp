#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern "C" {

extern s32 ConstructNewArray_100710(s32, void (*)(void), s32, s32, s32);
extern s32 MemStackStrDup_14cff0(s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern s32 EvObjInit_2f9cf0(void *, s32, void *, s32, s32, s32);
extern s32 EvDoorObjGetRefIndexCount_303fb0(void *);
extern s32 EvDoorObjGetRefIndices_303fc0(void *);
extern s32 EvDoorObjGetRefListCount_303fe0(void *);
extern s32 EvDoorObjGetRefList_303ff0(void *, s32);
extern void EvDoorObjReset_304440(void);
extern s32 EventRefListClone_304650(s32, s32, s32, s32);
extern s32 EventRefListGetCount_3047a0(s32);
extern void *memcpy(void *, const void *, s32);
extern void EventRefListCtor_3049d0(void);

}

class VC_0 {
public:
    u8 pad[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void f();
};

extern "C" s32 EvDoorObjInit_303d90(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 p;
    s32 i;
    s32 bones;
    s32 n;
    s32 t;

    EvDoorObjReset_304440();
    if (arg2 == NULL || arg3 == 0) {
        return 0;
    }
    if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    t = MemStackNew_14e1b0(EvDoorObjGetRefIndexCount_303fb0(arg2) * 2, arg3);
    *(s32 *)((u8 *)arg0 + 0x184) = t;
    if (t == 0) {
        return 0;
    }
    *(s16 *)((u8 *)arg0 + 0x18A) = EvDoorObjGetRefIndexCount_303fb0(arg2);
    memcpy(*(void **)((u8 *)arg0 + 0x184), (void *)EvDoorObjGetRefIndices_303fc0(arg2), *(s16 *)((u8 *)arg0 + 0x18A) * 2);
    n = EvDoorObjGetRefListCount_303fe0(arg2);
    t = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, arg3), EventRefListCtor_3049d0, 0, 0xC, n);
    *(s32 *)((u8 *)arg0 + 0x180) = t;
    if (t == 0) {
        return 0;
    }
    *(s16 *)((u8 *)arg0 + 0x188) = EvDoorObjGetRefListCount_303fe0(arg2);
    p = *(s32 *)((u8 *)arg0 + 0x180);
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x188)) {
        bones = EvDoorObjGetRefList_303ff0(arg2, i);
        if (bones == 0) {
            return 0;
        }
        if (*(s16 *)((u8 *)arg0 + 0x18A) < EventRefListGetCount_3047a0(bones)) {
            return 0;
        }
        if (EventRefListClone_304650(p, bones, *(s32 *)((u8 *)arg0 + 0x184), arg3) == 0) {
            return 0;
        }
        i++;
        p += 0xC;
    }
    *(f32 *)((u8 *)arg0 + 0x170) = *(f32 *)((u8 *)arg2 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x174) = *(f32 *)((u8 *)arg2 + 0x174);
    *(f32 *)((u8 *)arg0 + 0x178) = *(f32 *)((u8 *)arg2 + 0x178);
    ((VC_0 *)arg0)->f();
    *(s32 *)((u8 *)arg0 + 0x1A4) = MemStackStrDup_14cff0(*(s32 *)((u8 *)arg2 + 0x1A4), arg3);
    return 1;
}
