/* PARKED: 1 round trip: mechanical conversion using real sceGsSetDefStoreImage/sceGsExecStoreImage prototypes from libgraph.h; length 0xE4 vs retail 0xD4 (9 words too long). */
#include "types.h"

extern void sceGsSyncPath_109030(s32, s32);
extern void Vif1DmaHandlerShutdown_15dfb0(void);
extern void FlushCache(s32);
extern void sceGsExecStoreImage(void *, void *);
extern void sceGsSetDefStoreImage(void *, s16, s16, s16, s16, s16, s16, s16);

typedef struct {
    u8 pad0[0x2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[0x30];
    u16 unk38;
    u16 unk3A;
} T140f20_arg1;

s32 GsDownloadImage_140f20(void *arg0, T140f20_arg1 *arg1, void *arg2)
{
    u8 sp40[0x70];
    s16 temp_10;
    s32 var_2;

    Vif1DmaHandlerShutdown_15dfb0();
    *(s32 *)((u8 *)arg0 + 0xF1C) = 0;
    temp_10 = arg1->unk2;
    var_2 = temp_10 >> 6;
    if (temp_10 < 0) {
        var_2 = (s32)(temp_10 + 0x3F) >> 6;
    }
    if (var_2 == 0) {
        var_2 = 1;
    }
    sceGsSetDefStoreImage(sp40,
        (s16)(arg1->unk38 & 0x3FFF),
        (s16)var_2,
        (s16)((u64)((u64) arg1->unk3A << 54) >> 58),
        0, 0, temp_10, arg1->unk4);
    FlushCache(0);
    sceGsExecStoreImage(sp40, arg2);
    sceGsSyncPath_109030(0, 0);
    return arg1->unk6 * (arg1->unk2 * arg1->unk4);
}
