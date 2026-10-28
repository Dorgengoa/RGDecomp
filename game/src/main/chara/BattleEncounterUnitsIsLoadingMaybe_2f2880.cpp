/* rgp:protos */
#line 1
#include "types.h"

struct E { u8 pad[0xC]; s32 xc; };
class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 n3EC() { return VCM0(s32, 0x3EC); }
    
    E * get3F4(s32 a0) { return VCM(E *, (void *, s32), 0x3F4, a0); }
};

extern "C" {
extern s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void GetActionMgr_1fdb50(void);
extern void GetCharaResMgr_1fdb60(void);
extern void *GetGameData_1fede0(void);

s32 BattleEncounterUnitsIsLoadingMaybe_2f2880(void)
{
    u8 *g;
    s32 k;
    u8 *list;
    s32 i;
    V *o;
    E *oe;
    s32 n;
    s32 j;
    E *e;

    g = (u8 *)GetGameData_1fede0();
    GetActionMgr_1fdb50();
    GetCharaResMgr_1fdb60();
    k = GetCurrentScene_1f5be0();
    list = *(u8 **)(*(u8 **)(g + 0x20) + 0x238);
    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(list + 0x44); i++) {
        o = *(V **)(list + i * 8 + 0x4C);
        oe = (E *)o;
        if (ObjRecGetLiveObject_1c4a90(k, oe->xc) == 0) {
            return 1;
        }
        if (((unsigned char)ObjRecHasFlags6_1c3eb0(k, 1, oe->xc)) == 0) {
            return 1;
        }
        n = o->n3EC();
        for (j = 0; j < n; j++) {
            e = o->get3F4(j);
            if (ObjRecGetLiveObject_1c4a90(k, e->xc) == 0) {
                return 1;
            }
            if (((unsigned char)ObjRecHasFlags6_1c3eb0(k, 1, e->xc)) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
}
