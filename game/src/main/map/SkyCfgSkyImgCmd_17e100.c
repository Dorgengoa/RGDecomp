/* rgp:protos */
#define RGP_SELF_SkyCfgSkyImgCmd_17e100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct E17e100 { s32 a; s32 b; };
/*rgp*/
/*rgp*/
extern u8 *D_004811AC;
extern void strcpy(char *d, const char *s);
s32 SkyCfgSkyImgCmd_17e100(struct E17e100 *p)
{
    s32 n;
    s32 ok;
    char *s;

    n = VariantGetInt_15f780(p++);
    if (n >= 0) {
        if (n >= 4) { ok = 0; } else { ok = 1; }
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return 0;
    }
    s = ((char *)SlotGetInt_15f720(p));
    if (s != 0) {
        strcpy((char *)(D_004811AC + n * 32 + 0x4), s);
    }
    return 1;
}
