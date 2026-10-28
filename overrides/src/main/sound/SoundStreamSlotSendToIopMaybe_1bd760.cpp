/* rg-override: replaces game/src/main/sound/SoundStreamSlotSendToIopMaybe_1bd760.cpp sha256 be4188ab79599dc3a2389415134575050c3a7b5b4763e664f3e4775180ce2f56
 * why: native audio (docs/NATIVE-AUDIO.md, PLAN.md D9): with native PCM streams the
 *      block built in game memory (self->unk124) is mixed into the engine's port
 *      directly (rg_audio_game_pcm_mix) instead of SIF DMA to the IOP staging buffer +
 *      the 0x8090 mixer RPC, and the "IOP staging allocated" check no longer applies.
 *      hle: the original; compare: both (the HLE's result is used).
 *      P6 source volumes (docs/NATIVE-AUDIO.md "Source volumes"): before each block the
 *      engine is told which stream file the port plays (the stream manager channel whose
 *      slot is this port: name at +0, slot id at +0x80, StreamChanGetName /
 *      StreamChanGetSlotId), read only, so the presentation mix can apply the music or
 *      voice volume.  Nothing the game reads changes. */
/* rgp:protos */
#line 1
#pragma opt_dead_assignments off
#include "types.h"
#include "port/native_audio.h"
#pragma divbyzerocheck on

typedef struct Hw {
    u8 pad0[0x8];
    s32 unk8;
    u8 padC[0x4];
    s32 unk10;
    s32 unk14;
    u8 pad18[0xB4];
    f32 unkCC;
} Hw;

typedef struct Strm {
    s32 unk0;
    u8 pad4[0x4];
    Hw *unk8;
    u8 padC[0x68];
    f32 unk74;
    f32 unk78;
    u8 pad7C[0x50];
    f32 unkCC;
    u8 padD0[0x14];
    s32 unkE4;
    f32 unkE8;
    s32 unkEC;
    u8 unkF0;
    u8 padF1[0x3];
    u32 unkF4;
    s16 *unkF8;
    s16 *unkFC;
    s32 unk100;
    s32 unk104;
    u8 unk108;
    u8 pad109[0x13];
    u32 unk11C;
    s32 unk120;
    s16 *unk124;
} Strm;

extern "C" {
s32 SoundRpcCall_1bc5e0(int, int, ...);
void SifDmaSendSync_1c21e0(s16 *, s32, s32);
extern f32 D_0047D1D4;
extern s32 D_0047E20C;
extern s32 D_004814D8;
extern s32 D_004814DC;
}

extern "C" void *GetStreamMgr_207ea0(void);

/* the stream manager's 4 channels (224 bytes each): which one plays through `port` */
static void tag_source(s32 port)
{
    const u8 *mgr = (const u8 *)GetStreamMgr_207ea0();
    char name[0x80];
    s32 k;
    for (k = 0; k < 4; k++) {
        const u8 *ch = mgr + k * 224;
        if (*(const s16 *)(ch + 0x80) == port) {
            s32 i;
            for (i = 0; i < (s32)sizeof name - 1 && ch[i]; i++)
                name[i] = (char)ch[i];
            name[i] = 0;
            rg_audio_game_pcm_source(port, name);
            return;
        }
    }
}

extern "C" s32 SoundStreamSlotSendToIopMaybe_1bd760(Strm *self) {
    Hw *hw;
    unsigned int rate;
    s32 wr;
    u32 f4;
    s32 rd;
    s32 n;
    s32 fr;
    s32 pos;
    s32 len;
    s32 blocks;
    s16 *dst;
    s32 i;
    s16 *da;
    s16 *db;
    s16 *srcL;
    s16 *srcR;
    bool mix;
    s32 peak;
    s32 j;
    s32 l;
    s16 r;
    s32 a;
    s32 v;
    s32 acc;
    s32 step;
    s32 k;
    f32 g;
    f32 fm;
    f32 x0;
    f32 x1;
    f32 h;
    f32 c;
    s32 native;

    if (self->unkF0 == 0) {
        return 0;
    }
    hw = self->unk8;
    if (self->unkE4 != 0) {
        hw->unkCC = self->unkE8;
    }
    f4 = *(volatile u32 *)&self->unkF4;
    wr = self->unk104;
    rd = self->unk100;
    if (rd == wr) {
        if (self->unk108) {
            n = self->unkF4;
        } else {
            n = 0;
        }
    } else {
        n = 0;
        if (rd >= wr) {
            n += f4 - rd;
            n += wr;
        } else {
            n = n + (wr - rd);
        }
    }
    fr = self->unkF4 - n;
    if (fr == 0) {
        return 0;
    }
    rate = hw->unk10;
    if ((fr << 13) / (s32)rate < (s32)self->unk11C) {
        return 0;
    }
    native = rg_audio_mode() != RG_AUDIO_HLE && rg_audio_pcm_native();
    if (D_004814D8 == 0 && !(native && rg_audio_mode() == RG_AUDIO_NATIVE)) {
        return 0;
    }
    if (SoundRpcCall_1bc5e0(0x80A0, 1, self->unk0) <= 0) {
        return 0;
    }
    pos = (u32)self->unk104 >> 1;
    len = self->unkF4 >> 1;
    blocks = (s32)((u32)self->unk11C >> 1) / 256;
    dst = self->unk124;
    srcL = self->unkF8;
    srcR = self->unkFC;
    mix = false;
    if (hw->unk14 < 2) {
        srcR = srcL;
    } else if (D_0047E20C == 0) {
        mix = true;
    }
    peak = 0;
    if (hw->unk8 == 48000) {
        for (i = 0; i < blocks; i += 2) {
            da = dst;
            db = dst + 0x100;
            for (j = 0; j < 256; j++) {
                l = srcL[pos];
                r = srcR[pos];
                if (l > 0) {
                    a = l;
                } else {
                    a = -l;
                }
                if (peak < a) {
                    peak = a;
                }
                if (!mix) {
                    *da = l;
                    *db = r;
                    da++;
                    db++;
                } else {
                    v = l / 2 + r / 2;
                    *da = v;
                    *db = v;
                    da++;
                    db++;
                }
                pos = (pos + 1) % len;
            }
            dst += 0x200;
        }
    } else {
        for (i = 0; i < blocks; i += 2) {
            da = dst;
            db = dst + 0x100;
            for (j = 0; j < 256; j++) {
                l = srcL[pos];
                r = srcR[pos];
                if (l > 0) {
                    a = l;
                } else {
                    a = -l;
                }
                if (peak < a) {
                    peak = a;
                }
                if (!mix) {
                    *da = l;
                    *db = r;
                    da++;
                    db++;
                } else {
                    v = l / 2 + r / 2;
                    *da = v;
                    *db = v;
                    da++;
                    db++;
                }
                acc = self->unk120 + (s32)rate;
                self->unk120 = acc;
                if (acc >= 0x1000) {
                    step = acc / 4096;
                    self->unk120 %= 4096;
                    pos += step;
                    pos %= len;
                }
            }
            dst += 0x200;
        }
    }
    self->unkEC = peak;
    self->unk104 = pos * 2;
    if (self->unk104 == self->unk100) {
        self->unk108 = 1;
    }
    if (!(native && rg_audio_mode() == RG_AUDIO_NATIVE)) {
        SifDmaSendSync_1c21e0(self->unk124, D_004814DC, self->unk11C);
    }
    g = 1.0f;
    if (hw->unk14 == 1) {
        g = D_0047D1D4;
    }
    h = hw->unkCC;
    c = self->unkCC;
    x0 = g * self->unk74;
    x0 = c * (h * x0);
    x1 = g * self->unk78;
    x1 = c * (h * x1);
    fm = 0x7FFF;
    if (native && rg_audio_mode() == RG_AUDIO_NATIVE) {
        tag_source(self->unk0);
        return rg_audio_game_pcm_mix(self->unk0, self->unk124, (s32)(fm * x0), (s32)(fm * x1)) > 0 ? 1 : 0;
    }
    if (native) { /* compare: the engine first (the RPC may advance time), same block */
        rg_audio_game_pcm_mix(self->unk0, self->unk124, (s32)(fm * x0), (s32)(fm * x1));
    }
    if (SoundRpcCall_1bc5e0(0x8090, 4, self->unk0, (s32)(u32)D_004814DC, (s32)(fm * x0), (s32)(fm * x1)) == 0) {
        return 0;
    }
    return 1;
}
