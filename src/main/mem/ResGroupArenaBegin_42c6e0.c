#include "types.h"

extern s32 ArenaCtxInit_370610(void *, void *);
extern void *ResGroupGetStack_42c720(void *, s32);

void *ResGroupArenaBegin_42c6e0(void *arg0) {
    void *v = ResGroupGetStack_42c720(arg0, *(u16 *)((u8 *)arg0 + 0x164));
    ArenaCtxInit_370610((u8 *)arg0 + 0x168, v);
    return (void *)((u32)arg0 + 0x168);
}
