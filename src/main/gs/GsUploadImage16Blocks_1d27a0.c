#include "types.h"

typedef unsigned __int128 u128;

typedef struct Pk { s32 i0; s32 i4; u8 pad[8]; } Pk;
typedef union Tag { u128 q; u64 d[2]; } Tag;
typedef struct Tex0 {
    u64 TBP0 : 14;
    u64 TBW : 6;
    u64 PSM : 6;
    u64 TW : 4;
    u64 TH : 4;
    u64 TCC : 1;
    u64 TFX : 2;
    u64 CBP : 14;
    u64 CPSM : 4;
    u64 CSM : 1;
    u64 CSA : 5;
    u64 CLD : 3;
} Tex0;
typedef struct Tex { u8 pad[0x38]; Tex0 tex0; } Tex;

void sceGifPkInit_10a400(Pk *, u64);
void sceGifPkReset_10a410(Pk *);
void sceGifPkTerminate_10a420(Pk *);
void GetDrawCtxNameTable_15de40(void);
void sceGifPkAddGsAD(Pk *, s32, u64);
void sceGifPkCloseGifTag(Pk *);
void sceGifPkCnt(Pk *, s32, s32, s32);
void sceGifPkEnd(Pk *, s32, s32, s32);
void sceGifPkOpenGifTag(Pk *, u128);
void sceGifPkRef(Pk *, u64, s32, s32, s32, s32);
u64 *sceGifPkReserve(Pk *, s32);
extern u64 D_0047E310;
extern u64 D_0047E318;
extern u64 D_0047E320;
extern u64 D_0047E328;
extern Tex *D_004817A8;

void GsUploadImage16Blocks_1d27a0(s32 dst, s32 src, s32 arg2, s32 w, s32 h) {
    Pk pk;
    Tag t1;
    Tag t2;
    Tex0 tex0;
    s32 i;
    s32 nw;
    s32 nh;
    s32 j;
    u64 *p;

    t1.d[0] = D_0047E310;
    t1.d[1] = D_0047E318;
    sceGifPkInit_10a400(&pk, ((u64)(u32)dst & 0x0FFFFFFF) | 0x20000000);
    sceGifPkReset_10a410(&pk);
    GetDrawCtxNameTable_15de40();
    tex0 = D_004817A8->tex0;
    sceGifPkCnt(&pk, 0, 0, 0);
    sceGifPkOpenGifTag(&pk, t1.q);
    sceGifPkAddGsAD(&pk, 0x50, ((u64)tex0.TBP0 << 32) | ((u64)(u32)(s32)tex0.TBW << 48));
    sceGifPkAddGsAD(&pk, 0x52, (u64)0x10 | ((u64)0x10 << 32));
    sceGifPkCloseGifTag(&pk);
    nw = w >> 4;
    nh = h >> 4;
    for (i = 0; i < nw; i++) {
        for (j = 0; j < nh; j++) {
            sceGifPkCnt(&pk, 0, 0, 0);
            sceGifPkOpenGifTag(&pk, t1.q);
            sceGifPkAddGsAD(&pk, 0x51, ((u64)(u32)(i * 16) << 32) | ((u64)(u32)(j * 16) << 48));
            sceGifPkAddGsAD(&pk, 0x53, 0);
            sceGifPkCloseGifTag(&pk);
            p = sceGifPkReserve(&pk, 4);
            p[0] = 0x40 | ((u64)0x08000000 << 32);
            p[1] = 0;
            sceGifPkRef(&pk, (u64)(u32)src & 0x0FFFFFFF, 0x40, 0, 0, 0);
            src += 0x400;
        }
    }
    t2.d[0] = D_0047E320;
    t2.d[1] = D_0047E328;
    sceGifPkEnd(&pk, 0, 0, 0);
    sceGifPkOpenGifTag(&pk, t2.q);
    sceGifPkAddGsAD(&pk, 0x3F, 0);
    sceGifPkCloseGifTag(&pk);
    sceGifPkTerminate_10a420(&pk);
}
