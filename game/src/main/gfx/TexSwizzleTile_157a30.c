/* rgp:protos */
#define RGP_SELF_TexSwizzleTile_157a30 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: texture/tile blit with s128 locals, raw "(x*4)+sp" stack
 * arithmetic, and a nested 4-level loop; 0 round trips spent. Needs
 * asm/matchings/main/TexSwizzleTile_157a30.s read by hand -- the s128 quadword
 * locals should follow the Quad/{u32 w[4]} struct-assignment pattern used
 * in EvTargetCarryPosMaybe_3527f0.c in this lane, but the sp-array indexing needs the
 * listing to pin exact strides. Not attempted. */
/* s49m: 24-bad */
#include "types.h"

extern s32 D_0044A090[32];
extern s32 D_0044A010[];
extern void *memset(void *, s32, s32);
extern void *memcpy(void *, const void *, u32);
/*rgp*/

s32 TexSwizzleTile_157a30(s32 w, s32 h, u8 *src, u8 *dst)
{
    u8 *bp2;
    s32 col[32] __attribute__((aligned(16)));
    s32 row[32] __attribute__((aligned(16)));
    u8 out[0x100] __attribute__((aligned(16)));
    u8 in[0x100] __attribute__((aligned(16)));
    u8 *bp;
    u8 *ip2;
    s32 k;
    s32 x;
    s32 bh;
    u8 *ip;
    s32 bw;
    s32 i;
    s32 y;
    s32 j;
    s32 k2;

    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            col[D_0044A090[k]] = j;
            row[D_0044A090[k]] = i;
            k++;
        }
    }
    bw = w / 16;
    bh = h / 16;
    memset(out, 0, 0x100);
    memset(in, 0, 0x100);
    for (y = 0; y < bh; y++) {
        for (i = 0; i < bw; i++) {
            s32 t = D_0044A010[y * bw + i];
            bp = in;
            ip = src + (row[t] << 11) + (col[t] << 5);
            for (k = 0; k < 8; k++) {
                memcpy(bp, ip, 0x20);
                bp += 0x20;
                ip += 0x100;
            }
            TexSwizzleBlock_157c20(in, out);
            ip2 = dst + (y << 11) + (i << 4);
            bp2 = out;
            for (j = 0; j < 16; j++) {
                memcpy(ip2, bp2, 0x10);
                bp2 += 0x10;
                ip2 += 0x80;
            }
        }
    }
    return 0;
}
