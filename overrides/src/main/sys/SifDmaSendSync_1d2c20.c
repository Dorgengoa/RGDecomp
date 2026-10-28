/* rg-override: replaces game/src/main/sys/SifDmaSendSync_1d2c20.c sha256 677ddaf513b90d3e0512c55b497196e48933d24c7e08323151eafc1b0357b278
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): this SIF DMA helper's only callers
 *      move movie audio into the AudioDec ring (AudioDecSendToIop2Area_1d2ca0,
 *      AudioDecCreate_1d3210).  With native movie audio the bytes are copied into the
 *      engine's stream buffer (rg_audio_game_stream_write) and no DMA happens; compare
 *      mode does both. */
/* rgp:protos */
#define RGP_SELF_SifDmaSendSync_1d2c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_audio.h"

typedef struct SifDma_FUN_001d2c20 {
    void *data;
    void *addr;
    s32 size;
    s32 mode;
} SifDma_FUN_001d2c20;

extern void FlushCache(s32 n);
extern s32 sceSifSetDma(SifDma_FUN_001d2c20 *d, s32 n);
extern s32 sceSifDmaStat(s32 id);
extern void DelayThread_117618(s32 n);

s32 SifDmaSendSync_1d2c20(void *addr, void *data, s32 size)
{
    SifDma_FUN_001d2c20 d __attribute__((aligned(16)));
    s32 id;

    if (size <= 0) {
        return 0;
    }
    if (rg_audio_mode() != RG_AUDIO_HLE && rg_audio_movie_native()) {
        rg_audio_game_stream_write((unsigned)addr, data, size);
        if (rg_audio_mode() == RG_AUDIO_NATIVE) {
            return size;
        }
    }
    d.addr = addr;
    d.data = data;
    d.size = size;
    d.mode = 0;
    FlushCache(0);
    id = sceSifSetDma(&d, 1);
    while (sceSifDmaStat(id) >= 0) {
        DelayThread_117618(10);
    }
    return size;
}
