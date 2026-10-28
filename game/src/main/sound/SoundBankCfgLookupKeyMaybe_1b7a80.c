/* rgp:protos */
#define RGP_SELF_SoundBankCfgLookupKeyMaybe_1b7a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct E0C {
    s32 name;
    s32 a;
    s32 b;
} E0C;

typedef struct Tb {
    u8 pad0[0x20];
    s32 n20;
    s32 *m24;
    u8 pad28[4];
    s32 *m2C;
    s32 n30;
    E0C *m34;
} Tb;

/*rgp*/
s32 strcmp(const char *, const char *);
extern char D_0045ABD0[];

s32 SoundBankCfgLookupKeyMaybe_1b7a80(Tb *t, s8 *s, s32 *idx, s32 *val)
{
    s32 i;
    s32 j;
    s32 k;
    s32 nm;
    E0C *e;
    s8 c;

    if (s == 0 || *s == 0) {
        return 0;
    }
    if (strcmp((const char *)s, D_0045ABD0) == 0) {
        return 1;
    }
    *val = -1;
    for (i = 0; i < t->n20; i++) {
        if (Strcasecmp_1345b8(t->m24[i], (const char *)s) == 0) {
            *idx = i;
            *val = t->m2C[i];
            return 2;
        }
    }
    for (j = 0; j < t->n30; j++) {
        e = t->m34;
        nm = e[j].name;
        if (nm != 0 && Strcasecmp_1345b8(nm, (const char *)s) == 0) {
            *idx = j;
            return 3;
        }
    }
    for (k = 0; s[k] != 0; k++) {
        c = s[k];
        if (c == 0x2E) {
            return 0;
        }
    }
    return 1;
}
