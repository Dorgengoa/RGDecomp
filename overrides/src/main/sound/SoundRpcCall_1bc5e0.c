/* rg-override: replaces game/src/main/sound/SoundRpcCall_1bc5e0.c sha256 04783036063fc6e0e48d258b6a87ad6febc026777d25f9a982b3341f73a27311
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): this is the game's only caller
 *      of its PCM stream mixer (init, free blocks, start, stop, volume, shutdown).  With
 *      the native engine and RG_AUDIO_PCM not "hle" the call goes to the engine's PCM
 *      ports (rg_audio_game_pcm) instead of a SIF RPC; block mixing comes from
 *      SoundStreamSlotSendToIopMaybe_1bd760 (override) with the block in game memory.
 *      hle: the original; compare: both (the HLE's reply is returned). */
/* rgp:protos */
#define RGP_SELF_SoundRpcCall_1bc5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_audio.h"
#pragma opt_propagation off
#include <stdarg.h>


s32 SignalSema(s32);
s32 WaitSema(s32);
s32 sceSifCallRpc(void *, s32, s32, void *, s32, void *, s32, s32, s32);
extern s32 D_0047E218;
extern u8 D_004A2580[0x40];
extern u8 D_004A25C0[0x400];

static s32 rpc_hle(s32 arg0, s32 count, const s32 *a)
{
    s32 i;
    s32 r;

    WaitSema(D_0047E218);
    for (i = 0; i < count; i++) {
        ((s32 *)D_004A2580)[i] = a[i];
    }
    sceSifCallRpc(D_004A25C0, arg0, 0, D_004A2580, 0x40, D_004A2580, 0x40, 0, 0);
    r = *(s32 *)D_004A2580;
    SignalSema(D_0047E218);
    return r;
}

s32 SoundRpcCall_1bc5e0(s32 arg0, s32 count, ...) {
    va_list ap __attribute__((aligned(16)));
    s32 a[16];
    s32 i;
    s32 r;
    s32 mode;

    if (count >= 0x10) {
        return 0;
    }
    va_start(ap, count);
    for (i = 0; i < 16; i++) {
        a[i] = i < count ? va_arg(ap, s32) : 0;
    }
    va_end(ap);
    mode = rg_audio_mode();
    if (mode == RG_AUDIO_HLE || !rg_audio_pcm_native()) {
        return rpc_hle(arg0, count, a);
    }
    if (mode == RG_AUDIO_NATIVE) {
        return rg_audio_game_pcm(arg0 & 0xFFF0, a);
    }
    r = rpc_hle(arg0, count, a);
    if ((arg0 & 0xFFF0) != 0x8090) {
        rg_audio_game_pcm(arg0 & 0xFFF0, a);
    }
    return r;
}
