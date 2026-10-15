#include "types.h"

extern s32 DListRemove_42e4e0(s32, void *);
extern s32 ToBool_42cac0(s32);
extern void * DListGetHead_42ea60(s32);
extern s32 StrCmpNullSafe_42ca40(s32, s32);
extern s32 DListGetCountPow2_42ea70(s32);
extern void * DListNodeAdvance_42eb00(void *, s32);
extern s32 DListGetNext_42eb30(void *);
extern s32 DListInsertBefore_42e860(s32, void *, void *);
extern s32 DListPushBack_42e5a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x38];
    s32 m38;
};

struct Obj1 {
    u8 pad000[0x38];
    s32 m38;
};

struct Obj2 {
    u8 pad000[0x38];
    s32 m38;
};

s32 DListInsertSortedByName_227240(s32 p0, struct Obj0 *p1)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv20;
    s32 t1;
    struct Obj1 *r2;
    struct Obj1 * rv15;
    struct Obj1 * rv16;
    s32 t2;
    s32 r3;
    s32 rv13;
    struct Obj1 * rv14;
    s32 r4;
    s32 l5;
    struct Obj1 * l6;
    struct Obj2 *r7;
    struct Obj2 * rv10;
    struct Obj2 * rv11;
    s32 t3;
    s32 r8;
    struct Obj2 * rv9;
    s32 r12;
    s32 rv19;
    s32 r17;
    s32 r18;

    if (p1 == 0) {
        return 0;
    }
    r0 = DListRemove_42e4e0(p0, p1);
    t0 = p1->m38;
    r1 = ToBool_42cac0(t0);
    if (r1 == 0) {
        rv20 = 0;
    } else {
        t1 = p1->m38;
        r2 = DListGetHead_42ea60(p0);
        if (r2 == 0) {
            rv15 = (struct Obj1 *)r2;
            rv16 = 0;
        } else {
            t2 = r2->m38;
            r3 = StrCmpNullSafe_42ca40(t1, t2);
            if (r3 < 0) {
                rv13 = r3;
                rv14 = (struct Obj1 *)r2;
            } else {
                r4 = DListGetCountPow2_42ea70(p0);
                l5 = r4;
                l6 = (struct Obj1 *)r2;
                while (l5 > 0) {
                    l5 = (l5 >> 1);
                    r7 = DListNodeAdvance_42eb00(l6, l5);
                    if (r7 == 0) {
                        continue;
                    }
                    t3 = r7->m38;
                    r8 = StrCmpNullSafe_42ca40(t1, t3);
                    if (r8 < 0) {
                        continue;
                    }
                    l6 = (struct Obj1 *)r7;
                }
                r12 = DListGetNext_42eb30(l6);
                rv13 = r12;
                rv14 = (struct Obj1 *)r12;
            }
            rv15 = (struct Obj1 *)rv13;
            rv16 = (struct Obj1 *)rv14;
        }
        if (rv16 != 0) {
            r17 = DListInsertBefore_42e860(p0, rv16, p1);
            rv19 = (r17 & 0xFF);
        } else {
            r18 = DListPushBack_42e5a0(p0, p1);
            rv19 = (r18 & 0xFF);
        }
        rv20 = rv19;
    }
    return rv20;
}
