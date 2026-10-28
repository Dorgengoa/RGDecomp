/* rgp:protos */
#define RGP_SELF_EvMapObjInitByName_366e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Eight register arguments ($4-$11) plus five stack arguments; mwcc gives each
   stack argument an 8-byte slot, so a9..a13 land at +0x00/08/10/18/20. */
void EvMapObjInitByName_366e50(u8 *o, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12, s32 a13)
{
    EvMapObjResetMaybe_366f20(o);
    EvObjInitByName_2f9de0(o, a2, a3, a4);
    TargetRefSetMapObj_2e6470(o + 0xA0, a5, a6, 0.0f);
    *(s32 *)(o + 0x2F0) = a10;
    *(s16 *)(o + 0x2FA) = (s16)a11;
    *(s32 *)(o + 0x2F4) = a12;
    *(s16 *)(o + 0x2FC) = (s16)a13;
    *(s32 *)(o + 0x228) = a8;
    *(s32 *)(o + 0x224) = a7;
    *(s16 *)(o + 0x2FE) = (s16)a9;
}
