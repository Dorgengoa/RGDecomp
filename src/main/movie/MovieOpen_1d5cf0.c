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

void MpegStopDmaMaybe_111050(void);
u32 MemStackAllocAligned64_14da10(s32, s32);
void ScreenFadeBlockInit_178490(u8 *);
s32 CdDiskWatchSetEnabled_17fe80(s32);
void AudioDecCreate_1d3210(void *, u8 *, s32, s32);
void ReadBufEndPut_1d3360(u32, s32);
void ReadBufBeginPut_1d33c0(u32, s32 *);
void ReadBufCreate_1d3400(u32);
s32 MovieStreamReadSectors_1d3430(void *, s32, s32);
s32 MovieStreamOpen_1d3700(void *, s32, s32);
void VoBufCreate_1d4ac0(void *, u32, u8 *, s32);
void AudioDecPcmCallback_1d4ca0(void);
void VideoDecStrCallback_1d4d50(void);
void AudioDecSetInputVolumeF_1d52e0(u8 *, f32);
void VideoDecSetStream_1d5430(u8 *, void *, s32, s32, void *, u32);
void VideoDecCreate_1d5470(u8 *, void *, u32, s32, u32, u32, s32, u8 *, s64);
s32 MovieFrameBufSize_1d5570(u8 *, s32, s32);
s32 MovieReadBufSize_1d55d0(u8 *);
s32 MpegWorkSize_1d55e0(u8 *, s32, s32);
s32 ViBufTagSize_1d5610(u8 *);
s32 ViBufDataSize_1d5620(u8 *);
s32 VoBufDataSize_1d5630(u8 *);
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
extern u8 D_004B3350[];
extern s32 D_004B3358[];
extern u32 D_004B3360[];
extern u32 D_004B3364[];

#define F(T, o) (*(T *)(self + (o)))
#define S ((Self *)self)

void MovieOpen_1d5cf0(u8 *self, s32 arg1, s32 arg2, s32 *heaps, s32 arg4, s32 arg5, u8 arg6, s8 arg7) {
    s32 got;
    s32 i;
    s32 total;
    s32 p;
    s32 left;
    s32 r;
    u32 sz;
    u32 t;

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
    F(u32, 4) = MemStackAllocAligned64_14da10(heaps[0], VoBufDataSize_1d5630(self) / 16);
    F(u32, 8) = MemStackAllocAligned64_14da10(heaps[1], ViBufDataSize_1d5620(self) / 16);
    F(u32, 0xC) = MemStackAllocAligned64_14da10(heaps[2], ViBufTagSize_1d5610(self) / 16);
    F(u32, 0x10) = MemStackAllocAligned64_14da10(heaps[3], MpegWorkSize_1d55e0(self, D_004817CC, D_004817D0) / 16 + 4);
    D_004817AC = MemStackAllocAligned64_14da10(heaps[4], MovieReadBufSize_1d55d0(self) / 16);
    D_004B3364[0] = 0xA0000;
    D_004B3360[0] = MemStackAllocAligned64_14da10(heaps[4], (D_004B3364[0] >> 4) + 4);
    for (i = 0; i < 2; i++) {
        t = MemStackAllocAligned64_14da10(heaps[5], MovieFrameBufSize_1d5570(self, D_004817CC, D_004817D0) / 16);
        S->a14[i] = t;
        S->a1C[i] = MemStackAllocAligned64_14da10(heaps[5], MovieFrameBufSize_1d5570(self, D_004817CC, D_004817D0) / 16);
    }
    D_004817C4 = MemStackAllocAligned64_14da10(heaps[5], 0x80);
    *(volatile s32 *)0x1000E000 |= 3;
    *(volatile s32 *)0x1000E010 = 4;
    ReadBufCreate_1d3400(D_004817AC);
    MpegStopDmaMaybe_111050();
    sz = F(u32, 0x10);
    if (sz & 0x7F) {
        sz = ((sz >> 7) + 1) << 7;
    }
    VideoDecCreate_1d5470(self, D_004B3210, sz, MpegWorkSize_1d55e0(self, D_004817CC, D_004817D0), F(u32, 8), F(u32, 0xC), 0x100, self + 0x14900, 0x200);
    if (D_004817B8 != 0) {
        AudioDecCreate_1d3210(D_004B32D0, self + 0x8900, 0xC000, 0x6000);
    }
    VideoDecSetStream_1d5430(self, D_004B3210, 0, 0, VideoDecStrCallback_1d4d50, D_004817AC);
    if (D_004817B8 != 0) {
        AudioDecSetInputVolumeF_1d52e0(self, 0.0f);
        VideoDecSetStream_1d5430(self, D_004B3210, 2, 0, AudioDecPcmCallback_1d4ca0, D_004817AC);
    }
    for (i = 0; i < 2; i++) {
        S->pairs[i].a = S->a14[i];
        S->pairs[i].b = S->a1C[i];
    }
    VoBufCreate_1d4ac0(D_004B3330, (F(u32, 4) & 0x0FFFFFFF) | 0x20000000, self + 0x40, 2);
    while ((MovieStreamOpen_1d3700(D_004B3350, arg2, arg1) != 0) ^ 1) {
    }
    D_004817B4 = D_004817B0 = D_004B3358[0];
    ReadBufBeginPut_1d33c0(D_004817AC, &got);
    p = got;
    total = 0;
    left = 0x14000;
    do {
        r = MovieStreamReadSectors_1d3430(D_004B3350, p, left);
        left -= r;
        total += r;
        p += r;
        if (left == 0) {
            break;
        }
        if (r < 0) {
            break;
        }
    } while (D_004817B4 - total > 0);
    ReadBufEndPut_1d3360(D_004817AC, total);
    D_004817B4 -= total;
}
