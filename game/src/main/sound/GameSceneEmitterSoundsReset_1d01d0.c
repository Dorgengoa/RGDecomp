/* rgp:protos */
#define RGP_SELF_GameSceneEmitterSoundsReset_1d01d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem001d01d0 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Elem001d01d0;

void GameSceneEmitterSoundsReset_1d01d0(void *arg0)
{
    Elem001d01d0 *cur;
    s32 i;

    i = 0;
    cur = (Elem001d01d0 *) ((u8 *) arg0 + 0xB4BC);
    do {
        cur->unk0 = -1;
        i += 1;
        cur->unk2 = 0;
        cur->unk4 = 0;
        cur->unk8 = 0;
        cur->unkC = 0xBF800000;
        cur->unk10 = 0xBF800000;
        cur = (Elem001d01d0 *) ((u8 *) cur + 0x14);
    } while (i < 8);
}
