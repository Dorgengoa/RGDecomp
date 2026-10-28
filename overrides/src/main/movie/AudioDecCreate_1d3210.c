/* rg-override: replaces game/src/main/movie/AudioDecCreate_1d3210.c sha256 11c3b45da064004beeb9a156bbf67cc942ac2e7bce6bbbb1d273a242f8766e76
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): with native movie audio the AudioDec
 *      ring and its zero block are native engine stream buffers (rg_audio_game_stream_alloc:
 *      a handle the ring arithmetic runs on) instead of IOP heap; compare mode keeps the
 *      IOP ones and maps engine buffers to them.  The rest is the original. */
/* rgp:protos */
#define RGP_SELF_AudioDecCreate_1d3210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_audio.h"

extern s32 sceSifAllocIopHeap(s32);
extern void memset(s32, s32, s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004817C4;

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x28];
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    s32 m50;
    s32 m54;
    s32 m58;
};

s32 AudioDecCreate_1d3210(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 r1;
    s32 rv5;
    s32 t0;
    s32 t1;
    s32 t2;

    s32 nat;
    p0->m00 = 0;
    p0->m2C = 0;
    p0->m30 = p1;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = p2;
    p0->m40 = 0;
    p0->m54 = 0;
    p0->m48 = p3;
    p0->m4C = 0;
    p0->m50 = 0;
    nat = rg_audio_mode() != RG_AUDIO_HLE && rg_audio_movie_native();
    if (nat && rg_audio_mode() == RG_AUDIO_NATIVE) {
        r0 = (s32)rg_audio_game_stream_alloc((unsigned)p3);
    } else {
        r0 = sceSifAllocIopHeap(p3);
        if (nat && r0 > 0) {
            rg_audio_game_stream_map((unsigned)r0, (unsigned)p3);
        }
    }
    p0->m44 = r0;
    if (r0 <= 0) {
        return 0;
    }
    if (nat && rg_audio_mode() == RG_AUDIO_NATIVE) {
        r1 = (s32)rg_audio_game_stream_alloc(0x800);
    } else {
        r1 = sceSifAllocIopHeap(0x800);
        if (nat && r1 > 0) {
            rg_audio_game_stream_map((unsigned)r1, 0x800);
        }
    }
    p0->m58 = r1;
    rv5 = 1;
    if (r1 <= 0) {
        rv5 = 0;
    } else {
        t0 = D_004817C4;
        memset(t0, 0, 0x800);
        t1 = p0->m58;
        t2 = D_004817C4;
        SifDmaSendSync_1d2c20(t1, t2, 0x800);
        AudioDecSetMasterVolume_1d2c00(0x3FFF);
        rv5 = 1;
    }
    return rv5;
}
