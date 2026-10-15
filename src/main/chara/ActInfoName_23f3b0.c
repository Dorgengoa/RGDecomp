#include "types.h"

typedef struct E23f3b0 {
    u8 b[8];
} E23f3b0;

extern u8 *D_004BCE40[4];
extern s16 D_004BCE7C[8];
extern u8 D_0044C590[];
extern u8 D_004BCE20[];

extern void *ScriptArgGetStr_23fba0(void *a);
extern void *LookupNameValueNoCase_1cab50(void *a, void *b, s32 c);
extern void *StrDupArena_23fc40(void *a);
extern void ActInfoNameInit_231530(void *a, void *b, void *c);
extern void ActCfgTableSetNameCount_223ca0(void *a, s32 b);

s32 ActInfoName_23f3b0(u8 *p, s32 kind)
{
    s32 h;
    u8 *t;
    void *r;
    void *s;

    if (kind != 2) {
        return 0;
    }
    t = D_004BCE40[0];
    if (t == 0) {
        return 1;
    }
    h = D_004BCE7C[0];
    if (h >= 0x20) {
        return 1;
    }
    t = t + h * 8;
    r = ScriptArgGetStr_23fba0(p);
    s = LookupNameValueNoCase_1cab50(r, D_0044C590, 0);
    r = ScriptArgGetStr_23fba0(p + 8);
    r = StrDupArena_23fc40(r);
    ActInfoNameInit_231530(t, s, r);
    ActCfgTableSetNameCount_223ca0(D_004BCE20, D_004BCE7C[0] + 1);
    return 1;
}
