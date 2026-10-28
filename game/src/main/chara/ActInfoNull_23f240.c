/* rgp:protos */
#define RGP_SELF_ActInfoNull_23f240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E23f240 {
    u8 b[8];
} E23f240;

extern u8 *D_004BCE48[4];
extern s16 D_004BCE80[8];
extern u8 D_0044C6F0[];
extern u8 D_004BCE20[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActInfoNull_23f240(u8 *p, s32 kind)
{
    s32 h;
    u8 *t;
    void *r;
    void *s;

    if (kind != 2) {
        return 0;
    }
    t = D_004BCE48[0];
    if (t == 0) {
        return 1;
    }
    h = D_004BCE80[0];
    if (h >= 0x20) {
        return 1;
    }
    t = t + h * 8;
    r = ScriptArgGetStr_23fba0(p);
    s = LookupNameValueNoCase_1cab50(r, D_0044C6F0, 0);
    r = ScriptArgGetStr_23fba0(p + 8);
    r = StrDupArena_23fc40(r);
    ActInfoNullInit_2313b0(t, s, r);
    ActCfgTableSetNullCount_223c80(D_004BCE20, D_004BCE80[0] + 1);
    return 1;
}
