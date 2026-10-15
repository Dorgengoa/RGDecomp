#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad[0x30];
} Rec;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Grp;

extern s32 MapSlotsFindById_1e4b90(s32, s32, s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 GetMapMgr_201a90(void);
extern void TargetRefSetMapObj_2e6470(Rec *, s32, s32, s32, f32);
extern void TargetRefSetMapArea_2e64f0(Rec *, s32, s32);
extern s32 ScriptArgGetStr_301a00(s64 *);
extern s32 EventStrDup_301aa0(s32);
extern void EventRefListSetCount_304790(Grp *, s32, s32);
extern Rec *EventRefListGetRefs_3047b0(Grp *);
extern void EventRefListInit_304950(Grp *, s32, Rec *, s32);
extern s32 strcmp(s32, void *);

extern u8 D_004620F8[];
extern s16 *D_00482850;
extern s32 D_00482854;
extern Rec *D_00482858;
extern s32 D_0048285C;
extern Grp *D_00482860;
extern s32 D_00482864;

s32 EvScriptCmdDoorObjAddRefList_2ff160(s64 *arg0, s32 arg1) {
    Grp *g;
    s32 i;
    s32 s;
    s32 t;
    s32 v;
    Rec *r;

    if (arg1 <= 0) {
        return 0;
    }
    if (D_00482860 == NULL || D_00482864 >= 0x40) {
        return 1;
    }
    if (D_00482850 == NULL || D_00482854 < arg1 - 1) {
        return 1;
    }
    g = &D_00482860[D_00482864];
    EventRefListInit_304950(g, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)), &D_00482858[D_0048285C], 0);
    for (i = 1; i < arg1; i++, D_0048285C++) {
        if (D_0048285C >= 0x40) {
            break;
        }
        s = ScriptArgGetStr_301a00(&arg0[i]);
        if (s != 0 && strcmp(s, D_004620F8) == 0) {
            t = MapSlotsFindById_1e4b90(GetMapMgr_201a90(), D_00482850[i - 1], 0);
            if (t != 0) {
                v = MapDataGetId_1e7bd0(t);
            } else {
                v = -1;
            }
            TargetRefSetMapArea_2e64f0(&D_00482858[D_0048285C], v, s);
        } else {
            TargetRefSetMapObj_2e6470(&D_00482858[D_0048285C], D_00482850[i - 1], s, D_0048285C, 0.0f);
        }
    }
    r = EventRefListGetRefs_3047b0(g);
    EventRefListSetCount_304790(g, &D_00482858[D_0048285C] - r, D_0048285C);
    D_00482864++;
    return 1;
}
