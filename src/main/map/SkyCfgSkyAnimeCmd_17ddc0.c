#include "types.h"

typedef struct S17d {
    u8   pad000[0x248];
    s32  a248[16];
    char a288[16][32];
    f32  a488[16];
} S17d;

typedef struct E8d { u8 b[0x8]; } E8d;

extern S17d *D_004811AC;
extern s32 D_004811B0;
extern f32 D_0047D1FC;
s32 VariantGetInt_15f780(E8d *);
char *SlotGetInt_15f720(E8d *);
f32 VariantGetFloat_15f740(E8d *);
char *strcpy(char *, const char *);

s32 SkyCfgSkyAnimeCmd_17ddc0(E8d *a0)
{
    E8d *q;
    s32 r;
    char *s;
    s32 ok;
    f32 f;

    q = a0;
    if (D_004811B0 >= 0x10) {
        return 0;
    }
    r = VariantGetInt_15f780(q++);
    if (r >= 0) {
        if (r >= 4) {
            ok = 0;
        } else {
            ok = 1;
        }
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return 0;
    }
    D_004811AC->a248[D_004811B0] = r;
    s = SlotGetInt_15f720(q++);
    if (s != 0) {
        strcpy(D_004811AC->a288[D_004811B0], s);
    }
    f = VariantGetFloat_15f740(q);
    D_004811AC->a488[D_004811B0] = D_0047D1FC * f / 180.0f;
    D_004811B0 = D_004811B0 + 1;
    return 1;
}
