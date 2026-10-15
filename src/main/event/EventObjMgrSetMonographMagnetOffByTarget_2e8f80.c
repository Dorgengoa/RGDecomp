#include "types.h"

extern void *EventObjMgrGetTypeList_2e9d60(void *, s32);
extern void *DListGetHead_42ea60(void *);
extern void ObjTypeMonographSetMagnetOffIfTarget_3726b0(void *, void *, f32);
extern void *DListGetNext_42eb30(void *);

void EventObjMgrSetMonographMagnetOffByTarget_2e8f80(void *p, void *b, s32 n)
{
    void *l;
    void *e;

    l = EventObjMgrGetTypeList_2e9d60(p, 5);
    e = DListGetHead_42ea60(l);
    while (e != 0) {
        ObjTypeMonographSetMagnetOffIfTarget_3726b0((void *)((s32)e + 0x10), b, (f32)n);
        e = DListGetNext_42eb30(e);
    }
}
