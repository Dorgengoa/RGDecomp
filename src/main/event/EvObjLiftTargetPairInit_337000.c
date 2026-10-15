#include "types.h"

typedef struct { u8 pad[0x60]; void *f60; s32 f64; } T_00337000;

extern void TargetRefSetMapObj_2e6470(T_00337000 *, s32, s32, f32);
extern void TargetRefSetLocalNode_2e6330(void *, void *, f32);
extern void *GetEventObjMgr_2d1960(void);
extern void *EventObjMgrFindPathRecByName_2e9c90(void *, void *);

void EvObjLiftTargetPairInit_337000(T_00337000 *p, s32 a, s32 b, void *c, void *d, s32 e)
{
    void *r;

    TargetRefSetMapObj_2e6470(p, a, b, 0.0f);
    TargetRefSetLocalNode_2e6330((void *)((s32)p + 0x30), c, 0.0f);
    p->f64 = e;
    r = GetEventObjMgr_2d1960();
    p->f60 = EventObjMgrFindPathRecByName_2e9c90(r, d);
}
