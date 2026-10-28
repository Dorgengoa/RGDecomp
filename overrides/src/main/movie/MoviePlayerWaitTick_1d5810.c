/* rg-override: replaces game/src/main/movie/MoviePlayerWaitTick_1d5810.c sha256 18d12f0ea7c6fa5de8c652b3efe1444bb43938cba974e194857c682468d46b91
 * why: movie layer replaced by the port's movie service (docs/MOVIE.md "Override list"):
 * this per-game-frame call now does MovieReadThread_1d4f50's job (audio feed, display
 * start, pause) and VideoDecMain_1d5240's completion, synchronously on the virtual clock. */
/* rgp:protos */
#define RGP_SELF_MoviePlayerWaitTick_1d5810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* src/movie/movie_game.h (CC0 port service) */
extern int rg_movie_g_update(int may_start);
extern unsigned rg_movie_g_frames_decoded(void);
extern unsigned rg_movie_g_read_ss(void *dst, unsigned n);
extern void rg_movie_g_pause(int paused);
#define RG_MOVIE_G_STARTED 1
#define RG_MOVIE_G_FINISHED 2

struct T1D5810 { u8 pad000[0x17900]; u8 f17900; };

/* AudioDec ring (D_004B32D0, AudioDecCreate_1d3210 / AudioDecEndPut_1d24c0): +0 state
 * (0 = still collecting the 0x28-byte SShd/SSbd header), +0x2C header bytes, +0x38 bytes
 * held, +0x3C ring size */
typedef struct AudioDecRing {
    s32 state;
    u8 hdr[0x28];
    s32 hdr_n;
    s32 base;
    s32 wpos;
    s32 held;
    s32 size;
} AudioDecRing;

/* the PES descriptor AudioDecPcmCallback_1d4ca0 reads: +8 payload address, +0xC length; it
 * skips the 4 private-stream framing bytes, so address - 4 and length + 4 are passed */
typedef struct PesDesc {
    u8 pad[8];
    u32 addr;
    u32 len;
} PesDesc;

extern u32 D_004817AC;
extern u8 D_004817B8;
extern s8 D_004817BC;
extern s32 D_004817E8;
extern u8 D_004B3210[];
extern u8 D_004B32D0[];

static s32 audio_space(void)
{
    AudioDecRing *a = (AudioDecRing *)D_004B32D0;
    if (a->state == 0) return (0x28 - a->hdr_n) + a->size - a->held;
    return a->size - a->held;
}

/* SS stream bytes -> the AudioDec ring (through the game's own callback) -> the IOP ring
 * (AudioDecSendToIop), until neither side takes more. Copy2Area is all-or-nothing, so
 * only what fits is read. */
static void audio_feed(void)
{
    s32 round;
    s32 n;
    u32 got;
    PesDesc d;

    for (round = 0; round < 16; round++) {
        n = audio_space();
        if (n > 0x4000) n = 0x4000; /* one 0x4000 read, as MovieReadThread did */
        got = 0;
        if (n > 0) got = rg_movie_g_read_ss((void *)D_004817AC, (unsigned)n);
        if (got > 0) {
            d.addr = D_004817AC - 4;
            d.len = got + 4;
            AudioDecPcmCallback_1d4ca0(0, &d, (void *)D_004817AC);
        }
        if (AudioDecSendToIop_1d2e90(D_004B32D0) <= 0 && got == 0) break;
    }
}

void MoviePlayerWaitTick_1d5810(struct T1D5810 *p)
{
    static s32 paused;
    s32 i;
    s32 fl;

    if (p->f17900 == 0) return;
    if (D_004817B8 != 0) audio_feed();
    if ((D_004817E8 != 0) != paused) { /* MoviePause_1d5b40 / MovieResume_1d5b30 */
        paused = D_004817E8 != 0;
        rg_movie_g_pause(paused);
        if (D_004817B8 != 0 && D_004817BC != 0) {
            if (paused) AudioDecPause_1d3140(D_004B32D0);
            else AudioDecStart_1d30d0(D_004B32D0);
        }
    }
    /* retail start condition: VoBuf full (the service's preroll) && MovieAudioIsPreset */
    fl = rg_movie_g_update(D_004817BC != 0 || MovieAudioIsPreset_1d2490() != 0);
    if (D_004817BC == 0 && (fl & RG_MOVIE_G_STARTED)) {
        MovieDisplayStart_1d2b80();
        if (D_004817B8 != 0) AudioDecStartThunk_1d30d0((int)D_004B32D0);
        D_004817BC = 1;
    }
    *(s32 *)(D_004B3210 + 8) = (s32)rg_movie_g_frames_decoded();
    if (fl & RG_MOVIE_G_FINISHED) {
        VideoDecSetState_1d2b60(D_004B3210, 3);
        D_004817BC = 1; /* a movie that never started must not hold a MovieIsStarted wait */
    }
    for (i = 0; i < 4; i++) {
        ThreadYield_1d2b70();
    }
}
