#include "types.h"

extern s32 MpegDemuxPssRing_115340(void *, s32, s32, void *, s32);
extern void DelayThread_117618(s32);
extern s32 MovieAudioIsPreset_1d2490(void);
extern void ThreadYield_1d2b70(void);
extern void MovieDisplayStart_1d2b80(s32);
extern void AudioDecSetInputVolume_1d2b90(s32);
extern void AudioDecSendToIop_1d2e90(void *);
extern void AudioDecStart_1d30d0(void *);
extern void AudioDecStartThunk_1d30d0(void *);
extern void AudioDecPause_1d3140(void *);
typedef struct { u8 pad[0x14004]; s32 b; } O32c;
static s32 ReadBufEndGet_1d32c0(O32c *arg0, s32 arg1) {
    s32 n;

    n = (arg1 < arg0->b) ? arg1 : arg0->b;
    arg0->b = arg0->b - n;
    return n;
}
extern s32 ReadBufBeginGet_1d3300(void *, s32 *);
extern void ReadBufEndPut_1d3360(void *, s32);
extern s32 ReadBufBeginPut_1d33c0(void *, s32 *);
extern s32 MovieStreamReadSectors_1d3430(void *, s32, s32);
extern void MovieStreamRewind_1d36f0(void *);
extern s32 VoBufIsFull_1d4a90(void *);
extern u8 *D_004817AC;
extern s32 D_004817B0;
extern s32 D_004817B4;
extern u8 D_004817B8;
extern u8 D_004817BC;
extern u8 D_004817C8;
extern s32 D_004817E0;
extern s32 D_004817E4;
extern s32 D_004817E8;
extern s32 D_004817EC;
extern u8 D_004B3210[0x40];
extern u8 D_004B32D0[0x60];
extern u8 D_004B3330[0x20];
extern u8 D_004B3350[0x10];
extern u8 D_004B3358[0x10];
#define V3358 (*(s32 *)D_004B3358)

static inline s32 on(void) { return D_004817C8 != 0; }

void MovieReadThread_1d4f50(void)
{
    u8 *ctx;
    s32 sp8C;
    s32 n;
    s32 got;
    s32 stalled;
    s32 total;
    s32 buf;
    s32 left;
    s32 sp88;
    u8 *strm;
    u8 *dec;



    ctx = D_004817AC;
    D_004817E0 = 0;
    D_004817E8 = 0;
    dec = D_004B3210;
    strm = D_004B3350;
    for (;;) {
        stalled = 0;
        if (!on() == 0 && D_004817B4 < 0x14001) {
            MovieStreamRewind_1d36f0(strm);
            D_004817B4 = V3358;
        }
        n = ReadBufBeginPut_1d33c0(ctx, &sp8C);
        if (D_004817B4 > 0 && n >= 0x4000) {
            buf = sp8C;
            total = 0;
            left = 0x4000;
            for (;;) {
                got = MovieStreamReadSectors_1d3430(strm, buf, left);
                left -= got;
                total += got;
                buf += got;
                if (left == 0 || left < 0 || D_004817B4 - total <= 0) break;
                if (got == 0) {
                    stalled = 1;
                    D_004817EC = stalled;
                    AudioDecSetInputVolume_1d2b90(0);
                }
                ThreadYield_1d2b70();
                if (D_004817B8 != 0) AudioDecSendToIop_1d2e90(D_004B32D0);
                DelayThread_117618(100);
            }
            ReadBufEndPut_1d3360(ctx, total);
            D_004817B4 -= total;
        }
        D_004817EC = 0;
        if (stalled != 0) AudioDecSetInputVolume_1d2b90(0x7FFF);
        if (D_004817B8 != 0) AudioDecSendToIop_1d2e90(D_004B32D0);
        ThreadYield_1d2b70();
        n = ReadBufBeginGet_1d3300(ctx, &sp88);
        if (n > 0) {
            n = MpegDemuxPssRing_115340(dec, sp88, n, ctx, *(s32 *)(ctx + 0x14008));
            ReadBufEndGet_1d32c0((O32c *)ctx, n);
            if ((D_004817B0 -= n) <= 0) D_004817B0 = V3358;
        }
        if (D_004817B8 != 0) AudioDecSendToIop_1d2e90(D_004B32D0);
        if (D_004817BC == 0 && VoBufIsFull_1d4a90(D_004B3330) != 0 && MovieAudioIsPreset_1d2490() != 0) {
            MovieDisplayStart_1d2b80(1);
            if (D_004817B8 != 0) AudioDecStartThunk_1d30d0(D_004B32D0);
            D_004817BC = 1;
        }
        if (D_004817E4 != 0) break;
        if (D_004817E8 != 0) {
            AudioDecPause_1d3140(D_004B32D0);
            while (D_004817E8 != 0) {
                ThreadYield_1d2b70();
                DelayThread_117618(100);
            }
            AudioDecStart_1d30d0(D_004B32D0);
        }
        DelayThread_117618(100);
    }
    D_004817E0 = 1;
}
