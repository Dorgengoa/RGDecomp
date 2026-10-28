/* rgp:protos */
#define RGP_SELF_ParticleSwirlReset_17d750 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz17d750_t; /* rg:vu0bind vf0 */
#define vz17d750 RG_VU0_BIND_VF(0, rgvb_vz17d750_t)


extern s32 memset(void *, s32, s32);

void * ParticleSwirlReset_17d750(s32 *arg0)
{ RG_VU0_FRAME; void * rgp_v0 = 0;
    s32 i;

    *arg0 = 1;
    if (arg0) { arg0 = (s32 *)(s32)(u32)arg0; }
    *(rg_s128 *)(arg0 + 4) = vz17d750;
    i = 0;
    do {
        (rgp_v0 = memset((u8 *)arg0 + (i << 5) + 0x90, 0, 0x20));
        i++;
    } while (i < 0x14);
return rgp_v0; }
