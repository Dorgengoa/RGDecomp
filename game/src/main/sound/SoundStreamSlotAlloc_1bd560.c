/* rgp:protos */
#define RGP_SELF_SoundStreamSlotAlloc_1bd560 1
#define RGP_SELF_get_1bd560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                        /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                    /* extern */
/*rgp*/                             /* extern */
/*rgp*/                              /* extern */
/*rgp*/                           /* extern */
extern f32 D_0047D248;
extern s32 D_004814F0;
extern u8 D_004A25F0[0x400];

static inline u8 *get_1bd560(s32 i) {
    if (i < 0 || i >= 4) {
        return 0;
    }
    return D_004A25F0 + i * 0x128;
}

s32 SoundStreamSlotAlloc_1bd560(int rgp_a0, void *rgp_a1, unsigned int rgp_a2) {
    s32 sp3C;
    s32 sp38;
    s32 temp_5;
    s32 var_16;
    u8 *var_17;
    s32 u1;
    s32 u2;

    for (var_16 = 0; var_16 < 4; var_16++) {
        if ((&D_004814F0)[var_16] == 0) {
            break;
        }
    }

    var_17 = get_1bd560(var_16);
    if (var_17 == 0) {
        return -1;
    }
    SoundStreamSlotInitBuffers_1be390(var_17, (void *)rgp_a1, (unsigned int)rgp_a2, var_16);
    temp_5 = ((s32)GetSoundStreamTable_1bf7c0());
    sp38 = (*(s32 *)((u8 *)var_17 + 0x4));
    SoundStreamHandleResolve_1bfa50((u8 *)&sp3C, temp_5, &sp38);
    SoundStreamSetFillThreshold_1bfd50(((s32)SoundStreamLockAcquire_1bfb40((u8 *)&sp3C)), D_0047D248);
    SoundStreamLockDtor_1bfab0((u8 *)&sp3C, -1);
    (&D_004814F0)[var_16] = 1;
    return var_16;
}
