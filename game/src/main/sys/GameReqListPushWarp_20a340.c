/* rgp:protos */
#define RGP_SELF_GameReqListPushWarp_20a340 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: mechanical conversion; length OK (49w) but 32/49 words bad -- likely a structural mismatch (early-return polarity or field width), not chased further. */
#include "types.h"

/*rgp*/

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} T20a340_arg0;

s32 GameReqListPushWarp_20a340(T20a340_arg0 *arg0, s16 arg1, s32 arg2, s16 arg3, s16 arg4)
{
    s16 temp_3;
    s32 temp_4;
    void *temp_16;

    if (arg0->unk0 == 0 || arg0->unk4 >= arg0->unk6) {
        return 0;
    }
    temp_16 = (u8 *)arg0->unk0 + (arg0->unk4 * 0x14);
        GameReqInit_20a570(temp_16);
        *(s32 *)((u8 *)temp_16 + 0x0) = 0xB;
        *(s32 *)((u8 *)temp_16 + 0x4) = -1;
        *(s16 *)((u8 *)temp_16 + 0xC) = arg1;
        *(s32 *)((u8 *)temp_16 + 0x8) = arg2;
        *(s16 *)((u8 *)temp_16 + 0xE) = arg3;
        *(s16 *)((u8 *)temp_16 + 0x10) = arg4;
        *(u8 *)((u8 *)temp_16 + 0x12) = 0;
        arg0->unk4 = (s16)(arg0->unk4 + 1);
    return 1;

}
