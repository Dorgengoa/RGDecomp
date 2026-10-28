/* rgp:protos */
#define RGP_SELF_ActInfoClsnLin_23e4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* slti $2,$4,0x40 -> GPR destination = the strict operator: `cnt > 0x3F`.
 * The 6/5/4/3 compare chain is a switch (case order reversed). */

typedef struct { u8 d[0x18]; } Ent;

extern Ent *D_00481E98;
extern s32 D_00481E9C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActInfoClsnLin_23e4f0(u8 *p, s32 n)
{
    Ent *e;
    void *a;
    void *b;
    f32 t0;
    f32 t1;
    f32 t2;
    f32 t3;

    if (n != 3 && n != 4 && n != 5 && n != 6) {
        return 0;
    }
    if (D_00481E98 == 0 || D_00481E9C >= 0x40) {
        return 1;
    }
    e = D_00481E98 + D_00481E9C;

    switch (n) {
    case 3:
        t0 = ScriptArgGetFloat_23fbc0(p);
        a = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 8));
        b = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10));
        ActInfoClsnLinInitShort_230d80(e, a, b, 0.0f, t0);
        break;
    case 4:
        t1 = ScriptArgGetFloat_23fbc0(p + 0x18);
        t0 = ScriptArgGetFloat_23fbc0(p);
        a = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 8));
        b = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10));
        ActInfoClsnLinInitShort_230d80(e, a, b, t1, t0);
        break;
    case 5:
        t0 = ScriptArgGetFloat_23fbc0(p);
        a = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 8));
        b = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10));
        t2 = ScriptArgGetFloat_23fbc0(p + 0x18);
        t3 = ScriptArgGetFloat_23fbc0(p + 0x20);
        ActInfoClsnLinInitFull_230d30(e, a, b, 0.0f, t0, t2, t3);
        break;
    case 6:
        t1 = ScriptArgGetFloat_23fbc0(p + 0x28);
        t0 = ScriptArgGetFloat_23fbc0(p);
        a = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 8));
        b = StrDupArena_23fc40(ScriptArgGetStr_23fba0(p + 0x10));
        t2 = ScriptArgGetFloat_23fbc0(p + 0x18);
        t3 = ScriptArgGetFloat_23fbc0(p + 0x20);
        ActInfoClsnLinInitFull_230d30(e, a, b, t1, t0, t2, t3);
        break;
    }

    D_00481E9C = D_00481E9C + 1;
    return 1;
}
