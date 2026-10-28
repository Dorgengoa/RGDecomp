/* rg-override: replaces game/src/main/movie/AudioDecDelete_1d31d0.c sha256 39cb5f92b55a5896e809654362d1156103c72e2b3721fc975a358abd076ad57d
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): frees the AudioDec ring and zero
 *      block where AudioDecCreate_1d3210 (override) put them: native engine stream buffers
 *      (native movie audio), IOP heap (hle), or both (compare). */
/* rgp:protos */
#define RGP_SELF_AudioDecDelete_1d31d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_audio.h"

extern void sceSifFreeSysMemory_11ea40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x44];
    s32 m44;
    u8 pad048[0x10];
    s32 m58;
};

s32 AudioDecDelete_1d31d0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m44;
    t1 = p0->m58;
    if (rg_audio_mode() != RG_AUDIO_HLE && rg_audio_movie_native()) {
        rg_audio_game_stream_free((unsigned)t0);
        rg_audio_game_stream_free((unsigned)t1);
        if (rg_audio_mode() == RG_AUDIO_NATIVE) {
            return 1;
        }
    }
    sceSifFreeSysMemory_11ea40(t0);
    sceSifFreeSysMemory_11ea40(t1);
    return 1;
}
