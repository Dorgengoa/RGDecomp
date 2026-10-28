/* rgp:protos */
#define RGP_SELF_SkyCfgSkybAnimeCmd_17dcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S17d {
    u8   pad000[0x4C8];
    s32  a4C8[16];
    char a508[16][32];
    f32  a708[16];
} S17d;

typedef struct E8d { u8 b[0x8]; } E8d;

extern S17d *D_004811AC;
extern s32 D_004811B4;
extern f32 D_0047D1FC;
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);

s32 SkyCfgSkybAnimeCmd_17dcd0(E8d *a0)
{
    E8d *q;
    s32 r;
    char *s;
    s32 ok;
    f32 f;

    q = a0;
    if (D_004811B4 >= 0x10) {
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
    D_004811AC->a4C8[D_004811B4] = r;
    s = ((char *)SlotGetInt_15f720(q++));
    if (s != 0) {
        strcpy(D_004811AC->a508[D_004811B4], s);
    }
    f = VariantGetFloat_15f740(q);
    D_004811AC->a708[D_004811B4] = D_0047D1FC * f / 180.0f;
    D_004811B4 = D_004811B4 + 1;
    return 1;
}
