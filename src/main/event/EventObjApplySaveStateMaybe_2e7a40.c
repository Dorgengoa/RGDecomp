#include "types.h"

typedef struct {
    u8 pad0[0xD0];
    u32 w;
} N;

extern s32 GetGameData_1fede0(void);
extern s32 EventRecGetAreaId_2e5700(N *);
extern s32 EventRecGetKey_2e5730(N *);
extern N *EventObjMgrGetObjAt_2e9d90(s32, s32, s32);
extern void EvSwitchObjSetState_2f83e0(N *, s32);
extern void EvObjSwitchSetState_2f89d0(N *, s32);
extern s32 WorldSavedFlagTestMaybe_3ed400(s32, s32, s32, s32);

void EventObjApplySaveStateMaybe_2e7a40(s32 arg0)
{
    N *p;
    s32 j;
    s32 g;
    N *n;
    s32 i;
    s32 t;
    N *m;
    s32 k;

    g = GetGameData_1fede0();
    i = 0;
    while ((n = EventObjMgrGetObjAt_2e9d90(arg0, i, 0xC)) != NULL) {
        i++;
        t = EventRecGetAreaId_2e5700(n);
        EvObjSwitchSetState_2f89d0(n, WorldSavedFlagTestMaybe_3ed400(g, t, 5, EventRecGetKey_2e5730(n)));
    }
    j = 0;
    while ((p = EventObjMgrGetObjAt_2e9d90(arg0, j, 0xB)) != NULL) {
        j++;
        t = EventRecGetAreaId_2e5700(p);
        EvSwitchObjSetState_2f83e0(p, WorldSavedFlagTestMaybe_3ed400(g, t, 4, EventRecGetKey_2e5730(p)));
    }
    k = 0;
    while ((m = EventObjMgrGetObjAt_2e9d90(arg0, k, 9)) != NULL) {
        k++;
        t = EventRecGetAreaId_2e5700(m);
        m->w = (u8)WorldSavedFlagTestMaybe_3ed400(g, t, 1, EventRecGetKey_2e5730(m)) ? (m->w & 0x7FFFFFFF) : (m->w | 0x80000000);
    }
}
