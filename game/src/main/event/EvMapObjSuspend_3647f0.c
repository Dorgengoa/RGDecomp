/* rgp:protos */
#define RGP_SELF_EvMapObjSuspend_3647f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EvMapObjSuspend_3647f0(void *arg0)
{
    u8 sp20[0x10] __attribute__((aligned(16)));
    u8 *v3;
    u32 n;
    void *v2;
    void *v2b;
    s32 cond;

    if (((short)EvMapObjGetMode_366b80((void *)arg0)) == 1) {
        v3 = sp20;
        n = 0x10;
        if (v3 != NULL) {
            do {
                *v3 = 0;
                n -= 1;
                v3 += 1;
            } while (n != 0);
        }
        v2 = HandleRegistryLookup_314aa0(((s32)GetObjRefTable_313de0()), *(s32 *)((u8 *)arg0 + 0x338));
        if (v2 != NULL) {
            *(s16 *)((u8 *)v2 + 0xB6) = 1;
        }
        v2b = TargetRefGetMapObj_2e7050((u8 *)arg0 + 0xA0);
        if (v2b != NULL) {
            *(s16 *)((u8 *)v2b + 0x32) = 0;
            *(s32 *)((u8 *)v2b + 0x3C) |= 1;
        }
        *(s16 *)((u8 *)arg0 + 0x300) = 0;
    }
    cond = *(u8 *)((u8 *)arg0 + 0x334) != 0;
    EvMapObjSetReverseRateFromFrames_366970(arg0, 0, !cond);
}
