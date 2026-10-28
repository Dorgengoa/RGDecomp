/* rgp:protos */
#define RGP_SELF_ScriptCallBuildCharaCmd_23f980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* slti $1,$18,0x22 -> $at destination = the OR-EQUAL operator: `n >= 0x22`
 * slti $2,$2,0x800 -> GPR destination = the strict one: `count > 0x7FF`
 * The 2/1/0 compare chain is a switch (case order reversed). */

typedef struct {
    s32 tag;
    s32 val;
} EvArg;

extern s32 D_00481E70;
extern s32 D_00481E74;
extern u8 D_0044C8A0[];

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
/*rgp*/

s32 ScriptCallBuildCharaCmd_23f980(void *p, EvArg *a, s32 n)
{
    u8 *q;
    s32 i;
    s32 r;
    u8 b;

    if (n <= 0 || n > 0x21) {
        return 0;
    }
    if (p == 0) {
        return 0;
    }
    r = CharaCmdFindByName_228ac0(ScriptArgGetStr_23fba0(a));
    if (r == 0) {
        return 0;
    }
    a++;
    ScriptCallInit_302ad0(p, r, D_00481E70 + D_00481E74 * 5, 0);
    q = ((u8 *)ScriptCallGetArgs_302ab0(p));
    for (i = 1; i < n; i++) {
        if (D_00481E74 >= 0x800) {
            return 0;
        }
        switch (a->tag) {
        case 0:
            r = ParseFlagNames_1ca940(*(void **)&a->val, D_0044C8A0, &b);
            if (b != 0) {
                VariantSetInt_302e80(q, r);
            } else {
                VariantSetString_302e00(q, StrDupArena_23fc40(*(void **)&a->val));
            }
            break;
        case 1:
            VariantSetInt_302e80(q, a->val);
            break;
        case 2:
            VariantSetFloat_302e40(q, *(f32 *)&a->val);
            break;
        }
        a++;
        q += 5;
        ScriptCallSetArgc_302a90(p, ScriptCallGetArgc_302aa0(p) + 1);
        D_00481E74 = D_00481E74 + 1;
    }
    return 1;
}
