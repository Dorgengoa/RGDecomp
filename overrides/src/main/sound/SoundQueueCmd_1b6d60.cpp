/* rg-override: replaces game/src/main/sound/SoundQueueCmd_1b6d60.cpp sha256 0abc1b7a640862be6335860b081fcbfdc8cebcbc0cd4a70499e49154603026a9
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): this queue is the game's single
 *      entry into its sound driver (38 commands, D_0044AE10).  RG_AUDIO=native runs the
 *      note/bank/sequence commands on the native engine directly on the caller's thread
 *      (no worker thread, no SK blocks, no SIF RPC); mixer settings and the movie's raw
 *      libsd commands also still go the original way (the HLE serves what is not native
 *      yet).  RG_AUDIO=hle is the original body unchanged (queue_hle); compare runs both
 *      and checks that the ids the game keeps agree.  Below: the original, renamed. */
#include "types.h"
#include "port/native_audio.h"

struct Blk28 {
    s32 w[10];
};

struct Msg001b6d60 {
    s32 len;
    Blk28 data;
};

extern "C" {
s32 WaitSema(s32);
s32 SignalSema(s32);
s32 PollSema(s32);
void memcpy(void *, const void *, s32);
extern s32 D_0048142C;
extern s32 D_00481430;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_00481448;
extern s32 D_0048144C;
extern s32 D_00481450;
extern u8 D_0049D510[];
extern u8 D_0049D540[];
extern u8 D_0049DD70[];
extern volatile s32 D_0049DD74[];
extern volatile s32 D_0049DD78[];
}

static s32 queue_hle(s32 arg0, void *arg1, s32 arg2)
{
    Msg001b6d60 msg __attribute__((aligned(16)));
    Msg001b6d60 *slot;
    u8 r;
    bool ok;
    bool pushed;
    s32 res;
    s32 t;
    s32 x;

    if (arg0 > 0 && arg0 < 0x28 && D_0049D540[arg0] != 0) {
        msg.len = arg0;
        memcpy(&msg.data, arg1, arg2);
        r = 0;
        while (!r) {
            WaitSema(D_0048144C);
            pushed = false;
            if (D_0049DD70[0] != 0 && D_0049DD74[0] == D_0049DD78[0]) {
                pushed = true;
            }
            if (D_0049DD70[0] == 0 && D_0049DD74[0] == D_0049DD78[0]) {
                ok = false;
            } else {
                slot = (Msg001b6d60 *)(D_0049DD70 + D_0049DD78[0] * 0x2C + 0xC);
                slot->len = msg.len;
                slot->data = msg.data;
                t = D_0049DD78[0];
                ok = true;
                D_0049DD78[0] = (t + 1) & 0x3F;
                D_0049DD70[0] = 0;
            }
            r = ok;
            if (ok && pushed && PollSema(D_00481450) < 0) {
                SignalSema(D_00481450);
            }
            SignalSema(D_0048144C);
        }
        return r;
    }
    if (WaitSema(D_00481430) >= 0) {
        D_00481440 = arg0;
        if (arg1 != 0 && arg2 > 0) {
            memcpy(D_0049D510, arg1, arg2);
        }
        SignalSema(D_0048142C);
        WaitSema(D_00481434);
        res = D_00481448;
        SignalSema(D_00481430);
    } else {
        x = -1;
        goto out;
    }
    x = res;
out:
    return x;
}

extern "C" s32 SoundQueueCmd_1b6d60(s32 arg0, void *arg1, s32 arg2)
{
    s32 a[10];
    s32 i;
    s32 r;
    s32 n;
    s32 mode;
    s32 route;

    mode = rg_audio_mode();
    if (mode == RG_AUDIO_HLE) {
        return queue_hle(arg0, arg1, arg2);
    }
    for (i = 0; i < 10; i++) {
        a[i] = (arg1 != 0 && i * 4 < arg2) ? ((s32 *)arg1)[i] : 0;
    }
    route = rg_audio_game_route(arg0);
    if (mode == RG_AUDIO_NATIVE) {
        if (route == RG_AUDIO_ROUTE_NATIVE) {
            return rg_audio_game_cmd(arg0, a);
        }
        r = queue_hle(arg0, arg1, arg2);
        if (route == RG_AUDIO_ROUTE_BOTH) {
            rg_audio_game_cmd(arg0, a);
        }
        return r;
    }
    r = queue_hle(arg0, arg1, arg2);
    if (route != RG_AUDIO_ROUTE_HLE) {
        n = rg_audio_game_cmd(arg0, a);
        rg_audio_game_compare(arg0, r, n);
    }
    return r;
}
