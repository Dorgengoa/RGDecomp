#include "types.h"

extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern s32 EventRecGetAreaId_2e5700(s32);
extern s32 EventRecGetHeapBuf_2e5720(s32);
extern s32 MemStackHeapFree_14dcb0(s32, s32);
extern s32 DListRemove_42e4e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventRecListRemoveByArea_2eced0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 l1;
    s32 r2;
    s32 r3;
    s32 rv10;
    s32 rv8;
    s32 rv9;
    s32 rv6;
    s32 r4;
    s32 r5;
    s32 r7;

    if (p2 != 0) {
        r0 = DListGetHead_42ea60(p2);
        l1 = r0;
        while (l1 != 0) {
            r2 = DListGetNext_42eb30(l1);
            r3 = EventRecGetAreaId_2e5700((l1 + 0x10));
            rv10 = r3;
            if (p0 == r3) {
                rv8 = r3;
                rv9 = 0;
                if (l1 != 0) {
                    rv6 = r3;
                    if (p1 != 0) {
                        r4 = EventRecGetHeapBuf_2e5720((l1 + 0x10));
                        r5 = MemStackHeapFree_14dcb0(p1, r4);
                        rv6 = r5;
                    }
                    r7 = DListRemove_42e4e0(p2, l1);
                    rv8 = r7;
                    rv9 = l1;
                }
                rv10 = rv8;
            }
            l1 = r2;
        }
        return;
    }
}
