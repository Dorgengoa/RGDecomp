/* rg-override: replaces game/src/main/movie/MovieOpen_1d5cf0.c sha256 346488154a586daf4cda6e2add685eea4d2416aef3b72986f816de963a823bfa
 * why: movie layer replaced by the port's movie service (docs/MOVIE.md "Override list"):
 * no DMAC pokes, no libmpeg/IPU, no scrambled-MVI reads; the converted movie is opened
 * with rg_movie_g_open and the player globals the rest of the game reads are filled in. */
/* rgp:protos */
#define RGP_SELF_MovieOpen_1d5cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pair {
    s32 a;
    s32 b;
    u8 pad8[0x40];
} Pair;

typedef struct Self {
    u8 pad0[4];
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
    u32 a14[2];
    u32 a1C[2];
    u8 pad24[0x1C];
    u8 f40[0x40];
    Pair pairs[2];
} Self;

/* src/movie/movie_game.h (CC0 port service) */
extern int rg_movie_g_open(const char *path, int audio, int loop);
extern void rg_movie_g_size(int *w, int *h);

extern u32 D_004817AC;
extern s32 D_004817B0;
extern s32 D_004817B4;
extern u8 D_004817B8;
extern s8 D_004817BC;
extern s8 D_004817C0;
extern u32 D_004817C4;
extern volatile s8 D_004817C8;
extern volatile s32 D_004817CC;
extern volatile s32 D_004817D0;
extern volatile s8 D_004817D4;
extern volatile s8 D_004817D8;
extern s32 D_004817DC;
extern u8 D_004B3210[];
extern u8 D_004B32D0[];
extern u8 D_004B3330[];
extern u32 D_004B3360[];
extern u32 D_004B3364[];

#define F(T, o) (*(T *)(self + (o)))
#define S ((Self *)self)

void MovieOpen_1d5cf0(u8 *self, s32 arg1, s32 arg2, s32 *heaps, s32 arg4, s32 arg5, u8 arg6, s8 arg7) {
    s32 i;
    u32 t;
    int w;
    int h;

    (void)arg1;
    D_004817B8 = arg6;
    D_004817C0 = 0;
    D_004817BC = 0;
    F(s8, 0x17900) = 0;
    D_004817D4 = 0;
    D_004817D8 = 0;
    D_004817CC = arg4;
    D_004817D0 = arg5;
    D_004817C8 = arg7;
    D_004817DC = 0;
    F(s32, 0x17974) = 0;
    F(s32, 0x17970) = 0;
    F(s32, 0x17910) = CdDiskWatchSetEnabled_17fe80(0);
    ScreenFadeBlockInit_178490(self + 0x17920);
    /* the same allocations as retail, so the scene heaps are laid out identically; the
     * ViBuf / tag / MPEG-work blocks are simply unused now */
    F(u32, 4) = MemStackAllocAligned64_14da10(heaps[0], VoBufDataSize_1d5630() / 16);
    F(u32, 8) = MemStackAllocAligned64_14da10(heaps[1], ViBufDataSize_1d5620() / 16);
    F(u32, 0xC) = MemStackAllocAligned64_14da10(heaps[2], ViBufTagSize_1d5610() / 16);
    F(u32, 0x10) = MemStackAllocAligned64_14da10(heaps[3], MpegWorkSize_1d55e0(self, D_004817CC, D_004817D0) / 16 + 4);
    D_004817AC = MemStackAllocAligned64_14da10(heaps[4], MovieReadBufSize_1d55d0() / 16);
    D_004B3364[0] = 0xA0000;
    D_004B3360[0] = MemStackAllocAligned64_14da10(heaps[4], (D_004B3364[0] >> 4) + 4);
    for (i = 0; i < 2; i++) {
        t = MemStackAllocAligned64_14da10(heaps[5], MovieFrameBufSize_1d5570(self, D_004817CC, D_004817D0) / 16);
        S->a14[i] = t;
        S->a1C[i] = MemStackAllocAligned64_14da10(heaps[5], MovieFrameBufSize_1d5570(self, D_004817CC, D_004817D0) / 16);
    }
    D_004817C4 = MemStackAllocAligned64_14da10(heaps[5], 0x80);
    /* retail here: D_CTRL |= 3, D_STAT = 4, MpegStopDma, VideoDecCreate (libmpeg + IPU),
     * VideoDecSetStream x2 -- all gone with the IPU */
    ReadBufCreate_1d3400(D_004817AC); /* the read buffer now stages audio for the AudioDec feed */
    if (D_004817B8 != 0) {
        AudioDecCreate_1d3210(D_004B32D0, self + 0x8900, 0xC000, 0x6000);
        AudioDecSetInputVolumeF_1d52e0(0.0f);
    }
    for (i = 0; i < 2; i++) {
        S->pairs[i].a = S->a14[i];
        S->pairs[i].b = S->a1C[i];
    }
    /* retail: (f4 & 0x0FFFFFFF) | 0x20000000 -- the segment bits are the identity on the host */
    VoBufCreate_1d4ac0(D_004B3330, F(u32, 4), self + 0x40, 2);

    /* the movie service: data/converted/MOVIE/<dir>/<name>.{mpg,wav} */
    i = rg_movie_g_open((const char *)arg2, D_004817B8 != 0, D_004817C8 != 0);
    rg_movie_g_size(&w, &h);
    /* the sceMpeg context fields the game reads: +0 width, +4 height (MovieDrawFrame_1d5870),
     * +8 frame count (MovieGetFrameCount_1d52d0), +0xA8 VideoDec state (3 = finished) */
    *(s32 *)(D_004B3210 + 0) = w;
    *(s32 *)(D_004B3210 + 4) = h;
    *(s32 *)(D_004B3210 + 8) = 0;
    *(s32 *)(D_004B3210 + 0xA8) = 0;
    /* MovieIsFinished_1d5680 looks at the VideoDec state only while D_004817B0 >= 5: keep it
     * there while a movie plays, 0 (finished at once) when it cannot be played */
    D_004817B4 = D_004817B0 = (i == 0) ? 0x7FFFFFFF : 0;
}
