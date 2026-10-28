/* rgp:protos */
#define RGP_SELF_EffDefCmdEmitIntp_19bb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct S19bb70 {
    u8  pad00[0x4C];
    s32 f4C;
    f32 f50;
    s32 f54;
} S19bb70;

typedef struct T19bb70 {
    u8  pad00[0x2C];
    S19bb70 *f2C;
} T19bb70;

extern char D_0045A4A8[];
extern char D_0045A4B0[];
extern f32 D_0047D1DC;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);

s32 EffDefCmdEmitIntp_19bb70(Cur8 *q, s32 unused, T19bb70 **h)
{
    T19bb70 *t;
    char *s;
    s32 kind;
    f32 v;
    s32 n;
    S19bb70 *r;

    t = *h;
    if (t->f2C == 0) {
        return 0;
    }
    s = ((char *)SlotGetInt_15f720(q));
    if (s == 0) {
        return 0;
    }
    kind = 0;
    v = VariantGetFloat_15f740(q + 1);
    n = VariantGetInt_15f780(q + 2);
    if (strcmp(s, D_0045A4A8) == 0) {
        kind = 1;
    } else if (strcmp(s, D_0045A4B0) == 0) {
        kind = 2;
    }
    if (v < D_0047D1DC) {
        v = D_0047D1DC;
    }
    r = t->f2C;
    r->f4C = kind;
    r->f50 = v;
    r->f54 = n;
    return 1;
}
