/* rgp:protos */
#define RGP_SELF_EffDefDestroy_1a0a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED LEVER: `volatile` on a scalar PARAMETER homes it at entry
   (`sw $5,0x3C($29)`) and re-loads it at every use instead of promoting it
   to a callee-saved register.  The plain s32 parameter is 2 words long
   ($18 save/restore); a 4-byte by-value struct is worse still (mwcc adds a
   dsll32/dsra32 pair at each pass). */
extern void **HandleTableGet_1a1d50(void *, int);
/*rgp*/
/*rgp*/
extern void EffHdlRemove_1a3900(void *, s32);
void EffDefDestroy_1a0a90(u8 *o, volatile s32 k)
{
    void **r;
    void *y;
    r = HandleTableGet_1a1d50(o + 0xB0, (int)k);
    y = r ? r[0] : 0;
    if (y != 0) {
        EffDefUnlinkByHandle_1a0040(o, k);
        EffDefReleaseHandles_1a0840(o, y);
        EffHdlRemove_1a3900(o + 0xB0, k);
    }
}
