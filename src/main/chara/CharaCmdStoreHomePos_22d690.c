#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetPlacedPosMaybe_238280(s32, f32 *);
extern void CharaSetHomePos_214330(s32, f32 *);

struct Obj0 {
    s32 m00;
};

s32 CharaCmdStoreHomePos_22d690(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 v[4];
    s32 r0;
    s32 o;

    if (argc != 0 && argc != 3) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    CharaGetPlacedPosMaybe_238280(o, v);
    CharaSetHomePos_214330(o, v);
    return 1;
}
