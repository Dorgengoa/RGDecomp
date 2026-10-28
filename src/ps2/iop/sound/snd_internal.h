/* SPDX-License-Identifier: CC0-1.0 */
/* Sound HLE internals shared by snd_srv.c (servers, clock, pcm_mixer, movie audio),
 * snd_synth.c (SKHSYNTH/MODHSYN voice allocation) and snd_seq.c (SKMIDI/MODMIDI). */
#ifndef RG_SND_INTERNAL_H
#define RG_SND_INTERNAL_H

#include <stdint.h>

#include "snd.h"
#include "snd_hd.h"
#include "spu2.h"

#define SND_TRACKS     16 /* SKSOUND maxtrack=16 */
#define SND_BANKS      16 /* SKHSYNTH maxentry=16 */
#define SND_SLOTS      16
#define SND_SQ_ENTRIES 16 /* SKMIDI maxentry=16 */
#define SND_MIDI_PORTS 5  /* SKMIDI maxtrack=5 */
#define SND_MSIN_ENTRIES 16
#define SND_MSIN_PORTS 9  /* SKMSIN maxtrack=9 */
#define SND_HWVOICES   (SPU2_NCORES * SPU2_NVOICES)
#define SND_TICK_FRAMES 200 /* SKSOUND default tickresolution=240 -> 48000 / 240 */

/* SK error codes (SOUND-PROTOCOL.md section 2) */
#define SK_E_INDEX   (-101)
#define SK_E_STATE   (-102)
#define SK_E_NOENTRY (-201)
#define SK_E_BUSY    (-202)
#define SK_E_PLAYING (-299)
#define SK_E_CMD     (-310)
#define SK_E_LIB     (-402)

typedef struct snd_channel {  /* MODHSYN channel (sub_7c0 init; offsets in the 56-byte record) */
    uint8_t prog, bank, vol, expr, pan, sustain; /* raw MIDI values (log/state) */
    uint16_t bend;     /* 14-bit, 0x2000 = centre */
    uint8_t nrpn_msb, nrpn_lsb;
    uint8_t vol43;     /* +43 CC7 as (v << 7) / 127, 128 = unity */
    uint8_t expr44;    /* +44 CC11 as (v << 7) / 127: the key-on volume of a note */
    int8_t pan49;      /* +49 CC10 - 64, >= -63 */
    int16_t bend38;    /* +38 pitch bend - 0x2000 */
    uint16_t next_bend; /* +40 F9 02: 14-bit bend for the next key on, 0xFFFF = none */
    uint8_t next_vol;  /* +47 F9 00: raw volume for the next key on, 0xFF = none */
    uint8_t next_pan;  /* +48 F9 01: pan for the next key on, 0xFF = none */
} snd_channel;

typedef struct snd_track {
    int status;        /* bit 0 input attached, bit 1 banks attached */
    int in_entry, in_type; /* input entry id, 0 = MIDI, 2 = MSIN */
    int slot_bank[SND_SLOTS]; /* bank entry per hsynth slot, -1 = none */
    snd_channel ch[16];
    int seq_vol;       /* SKMIDI 0x30 volume, 0x80 = unity */
    int port;          /* MIDI port when in_type == 0, else -1 */
    uint8_t flag2, flag3; /* SKHSYNTH per-track flags (S2 0/1/2) */
    uint32_t msin_status; /* bits SKMSIN sets on key on (0x40010) */
} snd_track;

typedef struct snd_bank {
    int flags;         /* bit 0 HD set, bit 1 BD set */
    uint32_t hd_iop, hd_size, bd_spu, bd_size;
    uint8_t *hd;       /* host copy of the HD bytes, taken when the entry is filled */
    snd_hd parsed;
    int parsed_ok;
} snd_bank;

typedef struct snd_sqdata {
    int used;
    uint32_t iop, size;
    uint8_t *data;     /* host copy */
} snd_sqdata;

typedef struct snd_player {
    int used, track, entry;
    int block;         /* selected Midi block */
    const uint8_t *d;
    uint32_t size, start, pos;
    uint8_t status;    /* running status */
    uint32_t wait;     /* MIDI ticks until the next event */
    uint32_t tempo;    /* us per quarter note */
    uint16_t ppq;
    uint64_t acc;      /* tick accumulator */
    int playing, ended;
    uint32_t speed;    /* relative tempo, 0x100 = 1.0 */
    uint32_t loop_pos;
    int loop_set, loop_nodelta, loops_done;
    uint32_t ticks;    /* MIDI ticks played (stats) */
    uint32_t events;
} snd_player;

typedef struct snd_vtag {  /* what a hardware voice is playing */
    int used;
    int track, ch, note, id; /* id -1 = sequence note */
    int seq;
    int vel;
    uint32_t age;
    int released, sustained;
    /* MODHSYN voice fields (offsets in its voice record) */
    int16_t bend52;    /* +52 pitch bend in 1/128 semitone (sub_4c50) */
    uint8_t vol84;     /* +84 note volume, 128 = unity (FD 00, CC11, F9 00) */
    uint16_t v22;      /* +22 prog x split x sample volume x velocity curve x crossfade */
    int16_t pan30;     /* +30 prog/split/sample/key-follow pan, 64 = centre */
    uint8_t g76, g77;  /* +76/+77 left/right pan gains, 128 = full (sub_5158) */
    uint32_t rate60;   /* +60 VAG rate / 48000 in Q16 */
    uint32_t bd_spu, bd_size;
    snd_hd_layer layer;
} snd_vtag;

typedef struct snd_movie {   /* core AutoDMA from an IOP ring (sceSdBlockTrans) */
    int running;
    uint32_t base, size;     /* IOP ring */
    uint32_t unit;           /* byte offset of the 1 KiB unit being played */
    uint32_t k;              /* frame inside the unit (0..255) */
    int loop;
    uint32_t frames;         /* frames played since start (stats) */
    /* The SPU2's core input buffer: two 1 KiB halves ([256 L][256 R] each). AutoDMA
     * copies a ring unit into a half when it starts (both halves) and each time a
     * half has been played, so the DMA position (0x8100) runs two units ahead of
     * the unit being played, and the EE may refill everything behind it. */
    uint8_t half[2][1024];
    int play;                /* half being played */
    uint32_t xfer;           /* byte offset of the next unit to transfer */
    int xfer_done;           /* one-shot ring: the last unit has been transferred */
} snd_movie;

typedef struct snd_pcm {
    int inited, core, running;
    uint32_t block_bytes, nblocks;
    int16_t *ring;           /* nblocks * block_bytes */
    int16_t *dma;            /* 2 halves of block_bytes */
    uint32_t wpos[4], rpos;
    int play_half;
    uint32_t play_pos;       /* frame inside the playing half */
    uint32_t pending_vol, cur_vol; /* (L << 16) | R */
    uint32_t mixed_blocks, irqs, underruns;
} snd_pcm;

typedef struct snd_state {
    spu2 spu;
    snd_config cfg;
    /* clock */
    uint64_t (*now)(void *user);
    void *now_user;
    uint64_t base_frame;     /* clock frame at install */
    uint64_t rendered;       /* frames rendered since install */
    uint32_t tick_phase;
    uint32_t sk_ticks;
    int sk_timer_on;
    /* output FIFO */
    int16_t *fifo;
    uint32_t fifo_cap, fifo_rd, fifo_n;
    uint64_t fifo_dropped;
    /* SK */
    snd_track track[SND_TRACKS];
    snd_bank bank[SND_BANKS];
    snd_sqdata sq[SND_SQ_ENTRIES];
    snd_player port[SND_MIDI_PORTS];
    int msin_used[SND_MSIN_ENTRIES];
    int msin_counter;
    snd_vtag vt[SND_HWVOICES];
    uint32_t vage;
    int mono;
    uint32_t modhsyn_8[2];
    /* sdr_driver / pcm_mixer / movie */
    snd_movie movie[2];
    snd_pcm pcm;
    uint32_t sdr_trans_handler[2], sdr_spu2_handler;
    snd_stats stats;
} snd_state;

extern snd_state *g_snd;

/* snd_synth.c */
#include <stdio.h>
FILE *snd_log_file(void); /* $RG_SND_LOG validation log, or NULL */
void synth_reset(void);
void synth_note_on(int track, int ch, int note, int vel, int id, int seq);
void synth_note_off(int track, int ch, int note, int id, int seq);
void synth_voice_ctl(int track, int ch, int note, int id, int what, int value); /* 0 vol 1 pan 2 bend */
void synth_cc(int track, int ch, int cc, int value);
void synth_prog(int track, int ch, int prog);
void synth_bend(int track, int ch, int value);
void synth_next(int track, int ch, int what, int value); /* F9 0/1/2: next key on's vol/pan/bend */
void synth_all_off(int track, int immediate, int seq_only);
void synth_track_changed(int track);
int synth_count_bank_voices(int entry);
void synth_channel_reset(snd_channel *c);

/* snd_seq.c */
void seq_reset(void);
int seq_select(snd_player *p, const uint8_t *d, uint32_t size, int block);
void seq_rewind(snd_player *p);
void seq_tick(snd_player *p);

#endif
