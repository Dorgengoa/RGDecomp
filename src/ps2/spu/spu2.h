/* SPDX-License-Identifier: CC0-1.0 */
/* SPU2 voice engine (PLAN.md D4/P4, docs/SOUND.md). Written from scratch from public
 * SPU/SPU2 documentation (psx-spx ADPCM/ADSR/reverb descriptions, the ps2sdk libsd
 * entry encodings) and the retail LIBSD.IRX reverb preset table. No emulator code.
 *
 * Model:
 *   - 2 MiB sound RAM (byte addressed here; the hardware registers are halfword based),
 *   - 2 cores x 24 voices: PS-ADPCM decode with loop start / loop end / repeat flags,
 *     14-bit pitch (0x1000 = 48 kHz), 4-tap interpolation, ADSR envelope, fixed or
 *     swept volumes, key on/off, ENDX, pitch modulation, noise,
 *   - per core: dry/wet voice mix (VMIX*), MMIX routing, AutoDMA input (sound data
 *     input, "SIN"), external input (core 0's output into core 1, "MIN"), reverb on the
 *     effect work area, effect return volume, master volume (with sweep),
 *   - output: core 1 = the DAC, 48 kHz stereo s16.
 *
 * No host dependency: spu2_render() is a pull API. Single threaded; nothing locks.
 * Deterministic: integer arithmetic only, no libm. */
#ifndef RG_PS2_SPU2_H
#define RG_PS2_SPU2_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SPU2_RAM_SIZE   0x200000u /* 2 MiB */
#define SPU2_NVOICES    24
#define SPU2_NCORES     2
#define SPU2_RATE       48000u
#define SPU2_PITCH_1X   0x1000u   /* pitch register value that plays at 48 kHz */

/* ---- libsd entry encodings (ps2sdk libsd-common.h numbering) ------------------- */
/* voice parameters: (param << 8) | (voice << 1) | core */
#define SPU2_VP_VOLL   0x00
#define SPU2_VP_VOLR   0x01
#define SPU2_VP_PITCH  0x02
#define SPU2_VP_ADSR1  0x03
#define SPU2_VP_ADSR2  0x04
#define SPU2_VP_ENVX   0x05
#define SPU2_VP_VOLXL  0x06
#define SPU2_VP_VOLXR  0x07
/* core parameters: (param << 8) | 0x80 | core (MMIX is sent without 0x80) */
#define SPU2_P_MMIX    0x08
#define SPU2_P_MVOLL   0x09
#define SPU2_P_MVOLR   0x0A
#define SPU2_P_EVOLL   0x0B
#define SPU2_P_EVOLR   0x0C
#define SPU2_P_AVOLL   0x0D /* external input volume (core 0 output -> core 1) */
#define SPU2_P_AVOLR   0x0E
#define SPU2_P_BVOLL   0x0F /* sound data input volume (AutoDMA) */
#define SPU2_P_BVOLR   0x10
#define SPU2_P_MVOLXL  0x11
#define SPU2_P_MVOLXR  0x12
/* switches: (sw << 8) | core, value = 24-bit voice mask */
#define SPU2_S_PMON    0x13
#define SPU2_S_NON     0x14
#define SPU2_S_KON     0x15
#define SPU2_S_KOFF    0x16
#define SPU2_S_ENDX    0x17
#define SPU2_S_VMIXL   0x18
#define SPU2_S_VMIXEL  0x19
#define SPU2_S_VMIXR   0x1A
#define SPU2_S_VMIXER  0x1B
/* addresses (bytes): core = (a << 8) | core; voice = 0x2000 | (k << 6) | (voice << 1) | core */
#define SPU2_A_ESA     0x1C00
#define SPU2_A_EEA     0x1D00
#define SPU2_A_TSA     0x1E00
#define SPU2_A_IRQA    0x1F00
#define SPU2_VA_SSA    0x2040
#define SPU2_VA_LSAX   0x2080
#define SPU2_VA_NAX    0x20C0
/* core attributes (sceSdSetCoreAttr entry, low bit = core) */
#define SPU2_C_EFFECT_ENABLE 0x2
#define SPU2_C_IRQ_ENABLE    0x4
#define SPU2_C_MUTE_ENABLE   0x6
#define SPU2_C_NOISE_CLK     0x8
#define SPU2_C_SPDIF_MODE    0xA

/* MMIX bits (ps2sdk SD_MMIX_*): S = sound data input (AutoDMA), M = external input,
 * MSND = voices; E = to the effect (wet) bus. */
#define SPU2_MMIX_SINER  0x001
#define SPU2_MMIX_SINEL  0x002
#define SPU2_MMIX_SINR   0x004
#define SPU2_MMIX_SINL   0x008
#define SPU2_MMIX_MINER  0x010
#define SPU2_MMIX_MINEL  0x020
#define SPU2_MMIX_MINR   0x040
#define SPU2_MMIX_MINL   0x080
#define SPU2_MMIX_MSNDER 0x100
#define SPU2_MMIX_MSNDEL 0x200
#define SPU2_MMIX_MSNDR  0x400
#define SPU2_MMIX_MSNDL  0x800

/* libsd effect modes (sceSdEffectAttr.mode low byte); 0x100 = clear the work area */
enum {
    SPU2_REV_OFF = 0, SPU2_REV_ROOM, SPU2_REV_STUDIO_A, SPU2_REV_STUDIO_B, SPU2_REV_STUDIO_C,
    SPU2_REV_HALL, SPU2_REV_SPACE, SPU2_REV_ECHO, SPU2_REV_DELAY, SPU2_REV_PIPE, SPU2_REV_MODES
};
#define SPU2_REV_CLEAR_WA 0x100

/* Interpolation between decoded samples (docs/SOUND.md "Interpolation"). */
enum {
    SPU2_INTERP_BSPLINE = 0, /* default: 4-tap cubic B-spline, a closed-form stand-in for
                                the hardware's 4-tap Gaussian table */
    SPU2_INTERP_LINEAR = 1,
    SPU2_INTERP_NONE = 2     /* sample and hold */
};

/* Envelope phases (ENVX state). */
enum { SPU2_ENV_OFF = 0, SPU2_ENV_ATTACK, SPU2_ENV_DECAY, SPU2_ENV_SUSTAIN, SPU2_ENV_RELEASE };

/* One envelope / volume-sweep generator (psx-spx "Envelope Operation"). */
typedef struct spu2_env {
    int32_t level;   /* 0..0x7FFF */
    int32_t wait;    /* samples until the next step */
} spu2_env;

typedef struct spu2_vol {     /* a VOLL/VOLR/MVOLL/MVOLR register and its current value */
    uint16_t reg;
    int16_t cur;              /* VOLX: the value applied (s16) */
    spu2_env sweep;           /* sweep magnitude, used when reg bit 15 is set */
} spu2_vol;

typedef struct spu2_voice {
    spu2_vol vol[2];
    uint16_t pitch, adsr1, adsr2;
    uint32_t ssa, lsax, nax;  /* byte addresses (16-byte aligned) */
    int lsax_written;         /* software wrote LSAX since the last key on */
    /* decoder */
    int16_t hist1, hist2;     /* ADPCM predictor history */
    int16_t block[28];
    int block_pos;            /* 28 = need a new block */
    uint8_t block_flags;      /* flags byte of the block being played */
    uint32_t counter;         /* pitch phase, 12-bit fraction */
    int16_t ih[4];            /* interpolation history, ih[3] newest */
    /* envelope */
    int phase;
    spu2_env env;
    int16_t out;              /* last voice output (pre volume), for PMON and ENVX */
    int keyed;                /* 1 between key on and envelope end */
    uint32_t kon_count;       /* key ons since reset (stats) */
} spu2_voice;

/* AutoDMA input: produce one stereo frame for `core`; return 0 when no data
 * (the input then reads as silence). */
typedef int (*spu2_adma_fn)(void *user, int core, int16_t lr[2]);

typedef struct spu2_reverb {
    uint16_t r[32];           /* preset registers in psx-spx order (see spu2.c) */
    int mode;                 /* SPU2_REV_* */
    int16_t depth_l, depth_r, delay, feedback; /* last sceSdSetEffectAttr values */
    uint32_t pos;             /* halfword offset inside the work area */
    int32_t acc_l, acc_r;     /* wet input accumulated over the 2-sample step */
    int16_t out_l, out_r;     /* last reverb output (held for 2 samples) */
    int half;                 /* 0/1: reverb runs every second sample (24 kHz) */
} spu2_reverb;

typedef struct spu2_core {
    spu2_voice v[SPU2_NVOICES];
    uint32_t pmon, non, vmixl, vmixr, vmixel, vmixer, endx; /* 24-bit masks */
    uint16_t mmix;
    uint16_t attr;            /* bit 1 effect enable, bit 3 mute (sceSdSetCoreAttr state) */
    uint16_t noise_clk;
    int irq_enable;
    uint16_t spdif;
    spu2_vol mvol[2];
    int16_t evol[2], avol[2], bvol[2];
    uint32_t esa, eea, tsa, irqa; /* bytes */
    spu2_reverb rev;
    /* noise generator */
    int32_t noise_timer;
    uint16_t noise_level;
    /* AutoDMA input */
    spu2_adma_fn adma;
    void *adma_user;
    int16_t out_l, out_r;     /* last core output (core 0 -> core 1 external input) */
} spu2_core;

typedef struct spu2_stats {
    uint64_t samples;         /* frames rendered since reset */
    uint32_t key_ons, key_offs, blocks_decoded, clips;
} spu2_stats;

typedef struct spu2 {
    uint8_t ram[SPU2_RAM_SIZE];
    spu2_core core[SPU2_NCORES];
    int interp;
    spu2_stats stats;
} spu2;

/* ---- lifecycle ------------------------------------------------------------- */
void spu2_reset(spu2 *s);        /* power-on state (RAM cleared, voices off, volumes 0) */
void spu2_set_interp(spu2 *s, int mode);

/* ---- sound RAM (byte addresses, wrap at 2 MiB) -------------------------------- */
void spu2_ram_write(spu2 *s, uint32_t addr, const void *src, uint32_t len);
void spu2_ram_read(const spu2 *s, uint32_t addr, void *dst, uint32_t len);
void spu2_ram_fill(spu2 *s, uint32_t addr, uint8_t value, uint32_t len);

/* ---- libsd-level register access (entry encodings above) --------------------- */
void spu2_set_param(spu2 *s, uint32_t entry, uint16_t value);
uint16_t spu2_get_param(const spu2 *s, uint32_t entry);
void spu2_set_switch(spu2 *s, uint32_t entry, uint32_t value);
uint32_t spu2_get_switch(const spu2 *s, uint32_t entry);
void spu2_set_addr(spu2 *s, uint32_t entry, uint32_t byte_addr);
uint32_t spu2_get_addr(const spu2 *s, uint32_t entry);
void spu2_set_core_attr(spu2 *s, uint32_t entry, uint32_t value);
uint32_t spu2_get_core_attr(const spu2 *s, uint32_t entry);
/* sceSdSetEffectAttr: mode (| SPU2_REV_CLEAR_WA), depth -> EVOL, delay/feedback stored.
 * The work area is [EEA - size(mode) + 1, EEA]. */
void spu2_set_effect_attr(spu2 *s, int core, int mode, int16_t depth_l, int16_t depth_r,
                          int32_t delay, int32_t feedback);
uint32_t spu2_effect_size(int mode); /* work area bytes for a libsd mode (LIBSD.IRX table) */
void spu2_clear_effect_area(spu2 *s, int core);

/* ---- direct voice control (what libsd's KON/KOFF switches do) ---------------- */
void spu2_key_on(spu2 *s, int core, uint32_t mask);
void spu2_key_off(spu2 *s, int core, uint32_t mask);
/* voice field helpers (byte addresses, raw register values) */
void spu2_voice_setup(spu2 *s, int core, int voice, uint32_t ssa, uint16_t pitch,
                      uint16_t adsr1, uint16_t adsr2, uint16_t voll, uint16_t volr);
const spu2_voice *spu2_voice_get(const spu2 *s, int core, int voice);
int spu2_voice_active(const spu2 *s, int core, int voice); /* envelope not OFF */

void spu2_set_adma(spu2 *s, int core, spu2_adma_fn fn, void *user);

/* ---- render: produce `frames` 48 kHz stereo s16 frames (core 1 output) ------- */
void spu2_render(spu2 *s, int16_t *lr, uint32_t frames);

/* ---- building blocks, exposed for tests ---------------------------------------- */
/* Decode one 16-byte PS-ADPCM block into 28 samples; hist[0] = s[-1], hist[1] = s[-2]
 * are updated. Returns the flags byte. */
uint8_t spu2_adpcm_decode_block(const uint8_t blk[16], int16_t out[28], int16_t hist[2]);
/* One envelope step for a 7-bit rate (shift << 2 | step). Returns the new level. */
int32_t spu2_env_step(spu2_env *e, int rate, int decreasing, int exponential);
/* libsd sceSdNote2Pitch semantics: center_note plays at 0x1000; fine in 1/128 semitone.
 * Result clamped to 0x3FFF. */
uint16_t spu2_note2pitch(int center_note, int center_fine, int note, int fine);
/* sceSdPitch2Note inverse: returns (note << 8) | fine*2 like libsd (approximate). */
uint16_t spu2_pitch2note(int center_note, int center_fine, uint16_t pitch);
/* B-spline interpolation weights (Q15) for phase 0..255; w[0] applies to the oldest. */
void spu2_interp_weights(int phase, int32_t w[4]);

#ifdef __cplusplus
}
#endif
#endif
