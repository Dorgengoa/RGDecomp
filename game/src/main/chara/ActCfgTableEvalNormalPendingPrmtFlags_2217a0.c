/* rgp:protos */
#define RGP_SELF_ActCfgTableEvalNormalPendingPrmtFlags_2217a0 1
#define RGP_SELF_find002217a0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x19C vs retail 0x194, close. */
#include "types.h"
#pragma opt_repositioncode off

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s8 **find002217a0(void *e, s8 *name)
{
    s8 **p;
    s32 i;
    s8 *t;

    if (name == NULL) {
        return NULL;
    }
    p = PTR(e, 0x28);
    if (p == NULL) {
        return NULL;
    }
    for (i = 0; i < S16(e, 0x2C); i++, p = (s8 **)((u8 *)p + 0x34)) {
        t = *p;
        if (*name == *t && StrNotEqual_1f5300(t + 1, name + 1) == 0) {
            return p;
        }
    }
    return NULL;
}

long long ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32 arg0, s32 arg1, s8 *arg2, f32 fparg0)
{
    long long var_22;
    void *var_21;
    void *var_20;
    s32 var_19;
    s32 temp_2_3;
    s8 **var_20_2;
    s8 *temp_4;
    void *temp_2;
    s32 var_19_2;
    void *var_18;
    s32 temp_16;
    void *temp_2_2;

    var_22 = 0;
    temp_2 = DListGetHead_42ea60(arg0 + 0x7C);
    var_20 = temp_2;
    if (temp_2 == NULL) {
        var_21 = NULL;
    } else {
        var_21 = NULL;
        var_19 = ((unsigned short)DListGetCountPow2_42ea70(arg0 + 0x7C));
        while (var_19 > 0) {
            var_19 = var_19 >> 1;
            temp_2_2 = DListNodeAdvance_42eb00(var_20, var_19);
            if (temp_2_2 != NULL) {
                temp_2_3 = IntCompare_42ca30(arg1, S16(temp_2_2, 0x3E));
                if (temp_2_3 == 0) {
                    var_21 = temp_2_2;
                    break;
                }
                if (temp_2_3 > 0) {
                    var_20 = temp_2_2;
                }
            }
        }
    }
    if (var_21 == NULL) {
        var_18 = NULL;
    } else {
        var_18 = (u8 *)var_21 + 0x10;
    }
    if (var_18 != NULL) {
        var_20_2 = find002217a0(var_18, arg2);
        if (var_20_2 != NULL) {
            var_22 |= CharaTableDataCollectPendingPrmtFlags_2267f0(var_20_2, fparg0);
            var_22 |= ActCfgTableEvalPendingPrmtFlagsRefs_221040(arg0, S32(var_20_2, 4), S16(var_20_2, 0x24), fparg0);
        }
    }
    return var_22;
}
