/* rgp:protos */
#define RGP_SELF_AiCmdCharaMonographCtlMaybe_2c2dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCharaMonographCtlMaybe_2c2dc0(E8 *p0, s32 p1)
{
    f32 a;
    f32 b;
    s32 h;
    s32 k;
    s32 m;
    s32 o;

    if (p1 != 2 && p1 != 3 && p1 != 4) {
        return 0;
    }
    a = -1.0f;
    b = -1.0f;
    if (p1 > 2) {
        a = ScriptSlotGetFloat_2cc9a0(p0 + 2);
    }
    if (p1 > 3) {
        b = ScriptSlotGetFloat_2cc9a0(p0 + 3);
    }
    h = ((s32)GetEventObjMgr_2d1960());
    k = ScriptSlotGetInt_2cc9c0(p0 + 1);
    switch (k) {
    case 0:
        m = ScriptSlotGetInt_2cc9c0(p0);
        EvRemoveChrMonographs_2e9060(h, m);
        break;
    case 1:
        m = ScriptSlotGetInt_2cc9c0(p0);
        EvSpawnChrMonographs_2e91e0(h, m, a, b);
        break;
    case 2:
        m = ScriptSlotGetInt_2cc9c0(p0);
        o = ((s32)ActionMgrFindByIdGlobal_2cee10(m));
        if (o != 0) {
            CharaArmCollIgnoreTimer_238500(o);
        }
        break;
    }
    return 1;
}
