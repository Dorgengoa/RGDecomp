/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x19C vs retail 0x194, close. */
#include "types.h"
#pragma opt_repositioncode off

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 StrNotEqual_1f5300(void *, void *);
extern s64 ActCfgTableEvalPrmtFlagsRefs_220fa0(s32, s32, s32, f32);
extern s64 CharaTableDataCollectPrmtFlags_226710(s8 **, f32);
extern s32 IntCompare_42ca30(s32, s16);
extern void *DListGetHead_42ea60(s32);
extern s32 DListGetCountPow2_42ea70(s32);
extern void *DListNodeAdvance_42eb00(void *, s32);

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

s64 ActCfgTableEvalNormalPrmtFlags_221600(s32 arg0, s32 arg1, s8 *arg2, f32 fparg0)
{
    s64 var_22;
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
        var_19 = DListGetCountPow2_42ea70(arg0 + 0x7C);
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
        var_22 |= *(s64 *)((u8 *)var_18 + 8);
        var_20_2 = find002217a0(var_18, arg2);
        if (var_20_2 != NULL) {
            var_22 |= CharaTableDataCollectPrmtFlags_226710(var_20_2, fparg0);
            var_22 |= ActCfgTableEvalPrmtFlagsRefs_220fa0(arg0, S32(var_20_2, 4), S16(var_20_2, 0x24), fparg0);
        }
    }
    return var_22;
}
