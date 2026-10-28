/* rgp:protos */
#define RGP_SELF_ActInfoVert_23ec60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* switch (kind) over 1..6 -> compiled jump table jtbl_0045E940 (7 entries,
 * entry 0 = default).  Guards read off the listing:
 *   blez $5            -> `n <= 0`
 *   slti $1,$5,0x7     -> $at destination = the OR-EQUAL operator: `n >= 7`
 *   slti $2,$3,0x40    -> GPR destination = the strict one: `cnt > 0x3F`
 * The two entry guards both land on the shared `return 0`, so they are one `||`.
 */

typedef struct { u8 d[0x18]; } Ent;

extern Ent *D_004BCE54[];
extern s16 D_004BCE86[];
extern u8 D_004BCE20[];
extern u8 D_0044C750[];

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
/*rgp*/

s32 ActInfoVert_23ec60(u8 *p, s32 n)
{
    Ent *e;
    void *h;
    s32 v;
    u8 f3;
    u8 f4;
    u8 f5;
    u8 f6;

    if (n <= 0 || n > 6) {
        return 0;
    }
    if (D_004BCE54[0] == 0) {
        return 1;
    }
    if (D_004BCE86[0] >= 0x40) {
        return 1;
    }
    e = D_004BCE54[0] + D_004BCE86[0];

    switch (n) {
    case 1:
        ActInfoVertInitName_231050(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)));
        break;
    case 4:
        ActInfoVertInitNameVec_231010(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)), ScriptArgGetFloat_23fbc0(p + 8),
                     ScriptArgGetFloat_23fbc0(p + 0x10), ScriptArgGetFloat_23fbc0(p + 0x18));
        break;
    case 2:
        h = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(p + 8), D_0044C750, &f3);
        if (f3 == 0) {
            h = ScriptArgGetInt_23fc00(p + 8);
        }
        ActInfoVertInitNameId_230fc0(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)), h);
        break;
    case 5:
        h = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(p + 8), D_0044C750, &f4);
        if (f4 == 0) {
            h = ScriptArgGetInt_23fc00(p + 8);
        }
        ActInfoVertInitNameIdVec_230f80(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)), h, ScriptArgGetFloat_23fbc0(p + 0x10),
                     ScriptArgGetFloat_23fbc0(p + 0x18), ScriptArgGetFloat_23fbc0(p + 0x20));
        break;
    case 3:
        h = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(p + 8), D_0044C750, &f5);
        if (f5 == 0) {
            h = ScriptArgGetInt_23fc00(p + 8);
        }
        ActInfoVertInitNameIdSub_230f30(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)), h,
                     StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10)));
        break;
    case 6:
        v = *(s32 *)(p + 8);
        if (v == 0) {
            h = LookupNameValueNoCase_1cab50(ScriptArgGetStr_23fba0(p + 8), D_0044C750, &f6);
        } else if (v == 1) {
            h = ScriptArgGetInt_23fc00(p + 8);
        }
        ActInfoVertInitNameIdSubVec_230ef0(e, StrDupArena_23fc40(ScriptArgGetStr_23fba0(p)), h,
                     StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10)), ScriptArgGetFloat_23fbc0(p + 0x18),
                     ScriptArgGetFloat_23fbc0(p + 0x20), ScriptArgGetFloat_23fbc0(p + 0x28));
        break;
    }

    ActCfgTableSetVertCount_223c50(D_004BCE20, D_004BCE86[0] + 1);
    return 1;
}
