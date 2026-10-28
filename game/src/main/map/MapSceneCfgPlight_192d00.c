/* rgp:protos */
#define RGP_SELF_MapSceneCfgPlight_192d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Q_00192d00 { u8 b[8]; } Q_00192d00;

extern u8 *D_00481304;
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapSceneCfgPlight_192d00(Q_00192d00 *q)
{
    s32 i;
    s32 off;
    f32 v;
    if (D_00481304 == 0) return 0;
    i = VariantGetInt_15f780(q++);
    if (i < 0) goto zero;
    if (i <= 3) goto ok;
zero:
    return 0;
ok:
    off = 48 * i;
    v = VariantGetFloat_15f740(q++);
    *(f32 *)(off + (s32)D_00481304 + 0xE4) = v;
    VariantReadVec3_15f6c0((void *)((s32)D_00481304 + off + 0xC0), q);
    *(f32 *)(off + (s32)D_00481304 + 0xCC) = 1.0f;
    VariantReadVec3_15f6c0((void *)((s32)D_00481304 + off + 0xD0), (u8 *)q + 0x18);
    *(s32 *)(off + (s32)D_00481304 + 0xDC) = 0;
    *(s32 *)((s32)D_00481304 + 0xB0) = 1;
    return 1;
}
