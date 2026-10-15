#include "types.h"

extern void NodeRefReset_3193d0(void *p);
extern s32 NodeRefSet_319390(void *p, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void NodeRefListFindOrAdd_318e30(s32 arg0, void *p);

void NodeRefListAdd_318d50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u8 sp70[0x50];
    f32 t0;
    f32 t1;
    f32 t2;

    NodeRefReset_3193d0(sp70);
    NodeRefSet_319390(sp70, arg1, arg2, arg3, arg4);
    t2 = *(f32 *)((u8 *)arg5 + 8);
    t1 = *(f32 *)((u8 *)arg5 + 4);
    t0 = *(f32 *)((u8 *)arg5 + 0);
    *(f32 *)(sp70 + 0x28) = t0;
    *(f32 *)(sp70 + 0x2C) = t1;
    *(f32 *)(sp70 + 0x30) = t2;
    NodeRefListFindOrAdd_318e30(arg0, sp70);
}
