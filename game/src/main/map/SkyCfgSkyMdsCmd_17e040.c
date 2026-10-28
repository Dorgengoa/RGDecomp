/* rgp:protos */
#define RGP_SELF_SkyCfgSkyMdsCmd_17e040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_0017e040 {
    s32 a;
    s32 b;
} E8_FUN_0017e040;

typedef struct B_FUN_0017e040 {
    u8 pad000[0x84];
    char names[4][0x20];
    f32 vals[4];
} B_FUN_0017e040;

extern B_FUN_0017e040 *D_004811AC;
extern f32 D_0047D1FC;

/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *d, const char *s);

s32 SkyCfgSkyMdsCmd_17e040(E8_FUN_0017e040 *q)
{
    char *name;
    f32 v;
    s32 ok;
    s32 idx;

    idx = VariantGetInt_15f780(q++);
    if (idx < 0 || idx >= 4) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (ok == 0) return 0;
    name = ((char *)SlotGetInt_15f720(q++));
    if (name != 0) {
        strcpy(D_004811AC->names[idx], name);
    }
    v = VariantGetFloat_15f740(q);
    D_004811AC->vals[idx] = D_0047D1FC * v / 180.0f;
    return 1;
}
