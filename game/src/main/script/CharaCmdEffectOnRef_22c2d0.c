/* rgp:protos */
#define RGP_SELF_CharaCmdEffectOnRef_22c2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* slti $1,$16,0x4 -> $at destination = the OR-EQUAL operator: `mode <= 3` */

typedef struct { s32 d[6]; } Blk;
typedef struct { f32 x, y, z; } V3;
typedef struct { s16 a, b, c; } S3;

typedef struct {
    Blk m00;    /* 0x00 */
    Blk m18;    /* 0x18 */
    V3 m30;     /* 0x30 */
    V3 m3C;
    V3 m48;
    s32 m54;
    s32 m58;
    s32 m5C;
    u16 m60;
    s16 m62;
    S3 m64;
    S3 m6A;
    S3 m70;
    S3 m76;
} Big;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdEffectOnRef_22c2d0(s32 *p, u8 *name, s32 mode)
{
    void *rec;
    void *h;
    Big *src;
    s32 ok;
    Big loc __attribute__((aligned(16)));

    if (mode != 3 && mode != 4) {
        return 0;
    }
    rec = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *p);
    if (rec == 0) {
        return 1;
    }
    ok = 0;
    if (mode > 3) {
        ok = ScriptArgGetInt_302d70(name + 0xF) != 0;
    }
    if (ok != 0 && CharaGetActAbortCodeMaybe_2149b0(rec) != 0) {
        return 1;
    }
    h = CharaGetActionTable_214cd0(rec);
    if (h == 0) {
        return 1;
    }
    src = ((Big *)ActCfgTableFindEfctByName_222a50(h, ScriptArgGetStr_302cb0(name)));
    if (src == 0) {
        return 1;
    }

    loc.m00 = src->m00;
    loc.m18 = src->m18;
    loc.m30 = src->m30;
    loc.m3C = src->m3C;
    loc.m48 = src->m48;
    loc.m54 = src->m54;
    loc.m58 = src->m58;
    loc.m5C = src->m5C;
    loc.m60 = src->m60;
    loc.m62 = src->m62;
    loc.m64 = src->m64;
    loc.m6A = src->m6A;
    loc.m70 = src->m70;
    loc.m76 = src->m76;

    CharaEffEntrySetRefPos_230120(&loc, ScriptArgGetInt_302d70(name + 5), ScriptArgGetStr_302cb0(name + 0xA));
    CharaEffEntrySetRefRot_230100(&loc, ScriptArgGetInt_302d70(name + 5), ScriptArgGetStr_302cb0(name + 0xA));
    CharaEffEntrySpawn_22fad0(&loc, *p);
    return 1;
}
