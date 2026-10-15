#include "types.h"

extern void EventRecListRemoveById_2ed290(s32, s32, void *);
extern void EventRecListRemoveById_2ed350(s32, s32, void *);
extern void EventRecListRemoveById_2ed410(s32, s32, void *);
extern void EventRecListRemoveById_2ed4d0(s32, s32, void *);
extern void EventRecListRemoveById_2ed590(s32, s32, void *);
extern s32 EventRecListRemoveById_2ea290(s32, s32, void *);
extern void EventObjMgrResolveAllTargets_2e8840(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x150];
    s32 m150;
};

void EventObjMgrRemoveById_2e9df0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 l5;
    s32 l6;
    s32 t5;
    s32 r7;

    if (p1 >= 0) {
        t0 = p0->m150;
        EventRecListRemoveById_2ed290(p1, t0, p0);
        t1 = p0->m150;
        EventRecListRemoveById_2ed350(p1, t1, (struct Obj0 *)((u8 *)p0 + 0x10));
        t2 = p0->m150;
        EventRecListRemoveById_2ed410(p1, t2, (struct Obj0 *)((u8 *)p0 + 0x20));
        t3 = p0->m150;
        EventRecListRemoveById_2ed4d0(p1, t3, (struct Obj0 *)((u8 *)p0 + 0x30));
        t4 = p0->m150;
        EventRecListRemoveById_2ed590(p1, t4, (struct Obj0 *)((u8 *)p0 + 0x40));
        l6 = 0;
        do {
            t5 = p0->m150;
            r7 = EventRecListRemoveById_2ea290(p1, t5, (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l6 << 4)) + 0x50));
            l5 = ((l6 + 1) < 0x10);
            l6 = (l6 + 1);
        } while (l5 != 0);
        EventObjMgrResolveAllTargets_2e8840(p0);
        return;
    }
}
