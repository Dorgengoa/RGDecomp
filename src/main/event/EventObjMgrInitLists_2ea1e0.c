#include "types.h"

extern void DListInit_42eae0(void *);
extern void MemStackHeapReinit_14de90(s32);

struct Obj0 {
    u8 pad000[0x150];
    s32 m150;
};

void EventObjMgrInitLists_2ea1e0(struct Obj0 *p0)
{
    s32 l5;
    s32 t0;

    DListInit_42eae0(p0);
    DListInit_42eae0((u8 *)p0 + 0x10);
    DListInit_42eae0((u8 *)p0 + 0x20);
    DListInit_42eae0((u8 *)p0 + 0x30);
    DListInit_42eae0((u8 *)p0 + 0x40);
    l5 = 0;
    do {
        DListInit_42eae0((u8 *)p0 + (l5 << 4) + 0x50);
        l5 = (l5 + 1);
    } while (l5 < 0x10);
    t0 = p0->m150;
    if (t0 != 0) {
        MemStackHeapReinit_14de90(t0);
    }
}
