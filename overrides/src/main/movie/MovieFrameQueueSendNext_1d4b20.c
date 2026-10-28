/* rg-override: replaces game/src/main/movie/MovieFrameQueueSendNext_1d4b20.c sha256 99923581f8fe1892f379597bb4bd0a957c63b64e6a872c3f77b790104da02b96
 * why: movie layer replaced by the port's movie service (docs/MOVIE.md "Override list"):
 * the frame due now comes from rg_movie_g_take_frame, written into the next VoBuf slot in
 * the CSC block layout; the retail GIF upload of that slot follows unchanged. */
/* rgp:protos */
#define RGP_SELF_MovieFrameQueueSendNext_1d4b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Struct001d4b20 {
    s32 unk0;
    u8 pad4[0x40 - 0x4];
    s32 unk40;
} Struct001d4b20;

/* src/movie/movie_game.h (CC0 port service) */
extern int rg_movie_g_take_frame(void *dst);

extern void sceDmaSend_10a040(s32 a, s32 b);
extern s32 sceDmaGetChan(s32 a);

extern s32 D_004817A0;
extern volatile u8 D_004817D8;
extern u8 D_004B3330[0x20];

void MovieFrameQueueSendNext_1d4b20(void)
{
    s32 temp_17;
    Struct001d4b20 *temp_2;
    s32 slot;

    /* VoBuf: +0 data base, +0xC write index; one slot = 0xE0000 bytes (512x448 RGBA32) */
    slot = *(s32 *)(D_004B3330 + 0xC);
    if (VoBufIsFull_1d4a90(D_004B3330) == 0 &&
        rg_movie_g_take_frame((void *)(*(s32 *)D_004B3330 + slot * 0xE0000)) != 0) {
        VoBufIncCount_1d4a10(D_004B3330); /* tag state 2 = ready, as VideoDecDecodeBs did */
    }
    temp_2 = ((Struct001d4b20 *)VoBufGetTag_1d4940(D_004B3330));
    if (temp_2 == NULL) {
        D_004817A0 += 1; /* no new frame: the one already in GS memory stays */
        return;
    }
    DrawCtxVif1HandlerStop_15dc40();
    temp_17 = sceDmaGetChan(2);
    if (temp_2->unk0 == 2) {
        sceDmaSend_10a040(temp_17, temp_2->unk40);
        sceDmaSync_10a2e0(temp_17, 0);
        temp_2->unk0 = 3;
        D_004817D8 = 1;
        if (D_004817D8 != 0) {
            VoBufDecCount_1d48a0(D_004B3330);
            D_004817D8 = 0;
        }
    }
}
