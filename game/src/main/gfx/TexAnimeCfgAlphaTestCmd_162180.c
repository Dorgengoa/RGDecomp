/* rgp:protos */
#define RGP_SELF_TexAnimeCfgAlphaTestCmd_162180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8_162180 { u8 pad[8]; };

/*rgp*/

extern struct { u8 v; u8 pad[15]; } D_00495EA2;
extern struct { u8 v; u8 pad[15]; } D_00495EA3;

s32 TexAnimeCfgAlphaTestCmd_162180(struct E8_162180 *p0, s32 p1)
{
    if (p1 > 0) {
        D_00495EA2.v = VariantGetInt_15f780(p0++);
    }
    if (1 < p1) {
        D_00495EA3.v = VariantGetInt_15f780(p0);
    }
    return 1;
}
