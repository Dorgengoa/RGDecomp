/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine internals (docs/NATIVE-AUDIO.md "Engine").  ra_mix.c: voices
 * (PS-ADPCM, pitch, interpolation, ADSR), buses, reverb, render loop, PCM ports;
 * ra_synth.c: note -> layers -> voices (MODHSYN semantics); ra_seq.c: SQ player;
 * ra_engine.c: state, banks, tracks, inputs, clock, FIFO. */
#ifndef RG_NATIVE_RA_INTERNAL_H
#define RG_NATIVE_RA_INTERNAL_H

#include <stdint.h>

#include "ra_hd.h"
#include "rg_audio.h"

/* reference-counted host copy of bank data (voices keep the BD alive) */
typedef struct ra_blob {
    int refs;
    uint32_t size;
    uint8_t data[1];
} ra_blob;

ra_blob *ra_blob_new(const void *src, uint32_t size);
void ra_blob_ref(ra_blob *b);
void ra_blob_unref(ra_blob *b);

enum { RA_ENV_OFF = 0, RA_ENV_ATTACK, RA_ENV_DECAY, RA_ENV_SUSTAIN, RA_ENV_RELEASE };

typedef struct ra_env {
    int32_t level;   /* 0..0x7FFF */
    int32_t wait;
} ra_env;

typedef struct ra_channel {  /* MIDI channel state (MODHSYN channel record fields) */
    uint8_t prog, bank, vol, expr, pan, sustain;
    uint16_t bend;
    uint8_t nrpn_msb, nrpn_lsb;
    uint8_t vol43, expr44;
    int8_t pan49;
    int16_t bend38;
    uint16_t next_bend;
    uint8_t next_vol, next_pan;
} ra_channel;

typedef struct ra_voice {
    /* --- sound generator --- */
    ra_blob *bd;              /* sample data owner (NULL = idle) */
    uint32_t ssa, lsa, nax;   /* byte offsets into bd (16-byte blocks) */
    int16_t hist[2];
    int16_t block[28];
    int block_pos;
    uint8_t block_flags;
    uint32_t counter;         /* pitch phase, 12-bit fraction */
    int16_t ih[4];
    uint16_t pitch, adsr1, adsr2;
    uint16_t vol_reg[2];      /* 15-bit levels as MODHSYN computes them */
    float gain[2];            /* vol_reg * 2 / 32768 */
    uint8_t route;            /* bit0 dry L, bit1 dry R, bit2 wet L, bit3 wet R */
    int phase;
    ra_env env;
    /* --- what it plays (synth tag) --- */
    int used;
    int track, ch, note, id, seq, vel;
    uint32_t age;
    int released, sustained;
    int16_t bend52;
    uint8_t vol84;
    uint16_t v22;
    int16_t pan30;
    uint8_t g76, g77;
    uint32_t rate60;
    ra_hd_layer layer;
} ra_voice;

typedef struct ra_reverb {
    int mode;
    int16_t depth[2];
    uint32_t pos, size;       /* halfwords */
    int16_t *buf;
    int32_t acc[2];
    int16_t out[2];
    int half;
} ra_reverb;

typedef struct ra_bus {
    ra_voice v[RA_BUS_VOICES];
    uint16_t master[2];       /* 15-bit levels, applied x2 / 32768 */
    int16_t chain[2];         /* bus 1: gain of bus 0's output (0x7FFF) */
    int16_t in_vol[2];        /* stream input volume */
    int effect_on;
    int in_wet;               /* stream / chained input also feeds the reverb */
    ra_reverb rev;
    float out[2];
} ra_bus;

typedef struct ra_bank {
    int used;                 /* entry filled */
    ra_blob *hd, *bd;
    ra_hd parsed;
    int parsed_ok;
} ra_bank;

typedef struct ra_seqdata {
    int used;
    ra_blob *data;
} ra_seqdata;

typedef struct ra_player {
    int used, track, entry, block;
    const uint8_t *d;
    uint32_t size, start, pos;
    uint8_t status;
    uint32_t wait, tempo;
    uint16_t ppq;
    uint64_t acc;
    int playing, ended;
    uint32_t speed;
    uint32_t loop_pos;
    int loop_set, loop_nodelta, loops_done;
    uint32_t ticks, events;
} ra_player;

typedef struct ra_track {
    int status;               /* bit 0 input attached, bit 1 banks attached */
    int in_entry, in_type;    /* 0 = sequence, 2 = SE input */
    int slot_bank[RA_SLOTS];
    ra_channel ch[16];
    int seq_vol;
    int port;
} ra_track;

typedef struct ra_pcm {
    int inited, bus, running;
    uint32_t block_bytes, nblocks;
    int16_t *ring;
    int16_t *play;            /* block being played (copied out of the ring) */
    int have_play;
    uint32_t wpos[4], rpos;
    uint32_t play_pos;
    uint32_t pending_vol, cur_vol;
} ra_pcm;

#define RA_STREAM_BUFS 4
typedef struct ra_sbuf {      /* an engine-owned stream buffer the game addresses by handle */
    uint32_t base, size;      /* handle "address" (non-zero, < 16 MB) and size */
    uint8_t *mem;
} ra_sbuf;

typedef struct ra_movie {     /* movie audio: a ring of 1 KiB [256 L][256 R] units */
    int running, loop;
    uint32_t ring, size;      /* ring handle address, bytes */
    uint32_t unit, k;         /* unit being played (offset), frame in it */
    uint32_t xfer;            /* next unit to take into the double buffer */
    int xfer_done, play;
    uint8_t half[2][1024];
    uint32_t frames;
} ra_movie;

typedef struct ra_state {
    ra_config cfg;
    int inited;
    ra_bus bus[RA_BUSES];
    ra_track track[RA_TRACKS];
    ra_bank bank[RA_BANKS];
    ra_seqdata sq[RA_SEQS];
    ra_player port[RA_SEQ_PORTS];
    int se_used[RA_SE_INPUTS];
    int se_counter;
    uint32_t vage;
    int mono;
    /* clock */
    uint64_t (*now)(void *user);
    void *now_user;
    uint64_t frame;           /* absolute frame of the next sample */
    uint64_t tick_origin;
    /* FIFO */
    int16_t *fifo;
    uint32_t fifo_cap, fifo_rd, fifo_n;
    uint64_t fifo_dropped;
    ra_pcm pcm;
    ra_sbuf sbuf[RA_STREAM_BUFS];
    ra_movie movie[RA_BUSES];
    ra_stats st;
} ra_state;

extern ra_state *g_ra;

/* ra_present.c: the presentation mix (docs/NATIVE-AUDIO.md "Source volumes", PLAN.md P6).
 * The model mix above is what the runtime hashes and what the game's state depends on; this
 * is a second mix of the same voices with a gain per source (music, effects, voice, movie),
 * rendered only while some gain is not 1.  It never writes model state, and the model never
 * reads it.  HOST for save states (src/savestate/ss_map.c); a load is detected (frame / FIFO
 * mismatch) and resynchronised from the model. */
#define RA_PCM_SRCS 3            /* PCM ports carry music, effects or voice (RA_SRC_*) */
typedef struct ra_present {
    int on;                      /* rendering the second mix */
    volatile int32_t target_q[RA_SRC_COUNT]; /* gain x 65536 (ra_present_set_gain, any thread) */
    float g[RA_SRC_COUNT];       /* current gains (ramped towards the targets) */
    float gm1[RA_SRC_COUNT];     /* g - 1 for the frame being mixed */
    ra_reverb rev[RA_BUSES];     /* shadow reverb per bus (own work buffer) */
    int rev_ok[RA_BUSES];        /* rev[] is a copy of the model's state (else re-cloned) */
    float out[RA_BUSES][2];      /* presentation bus outputs (bus 0 chains into bus 1) */
    /* PCM: each port's contribution per source, parallel to the model ring */
    int32_t *ring[RA_PCM_SRCS], *play[RA_PCM_SRCS];
    uint32_t nblocks, block_bytes;
    int port_src[4];
    char port_path[4][128];
    /* FIFO parallel to the model's (same capacity, same drops) */
    int16_t *fifo;
    uint32_t cap, rd, n;
    uint64_t frame_seen;         /* g_ra->frame after the last render (load detection) */
    uint32_t unity_frames;       /* frames since every gain came back to 1 */
    uint64_t frames_on;          /* statistics */
} ra_present;
extern ra_present g_rp;

void ra_present_reset(void);                       /* ra_init / ra_mix_reset */
void ra_present_begin(uint32_t frames);            /* ra_mix_render: activation, resync */
void ra_present_frame(void);                       /* per frame: gain ramp */
void ra_present_end(uint32_t frames);              /* ra_mix_render: deactivation */
void ra_present_reverb_changed(int bus);           /* ra_reverb_set */
void ra_present_pcm_init(uint32_t nblocks, uint32_t block_bytes);
void ra_present_pcm_free(void);
void ra_present_pcm_start(void);
void ra_present_pcm_mix(int port, uint32_t block, const uint8_t *src, int vol_l, int vol_r);
void ra_present_pcm_block(uint32_t rpos, int have_play);
void ra_present_pcm_frame(int have_play, uint32_t il, uint32_t ir, float cls[RA_PCM_SRCS][2]);
void ra_present_fifo_push(const int16_t *lr, uint32_t n);
uint32_t ra_present_fifo_read(int16_t *lr, uint32_t n);  /* lr NULL = discard */

/* ra_mix.c */
void ra_mix_reset(void);
void ra_mix_render(float *lr, float *plr, uint32_t frames); /* advances voices/buses, no tick;
                                                     plr (may be NULL): the presentation mix */
void ra_voice_start(ra_voice *v, ra_blob *bd, uint32_t ssa);
void ra_voice_release(ra_voice *v);
void ra_voice_cut(ra_voice *v);
void ra_voice_set_volume(ra_voice *v, uint16_t l, uint16_t r);
static inline int ra_voice_active(const ra_voice *v) { return v->phase != RA_ENV_OFF; }
void ra_reverb_set(ra_bus *b, int mode, int clear);
int ra_hd_rev_size_halfwords(int mode);

/* ra_synth.c */
void ra_synth_reset(void);
void ra_channel_reset(ra_channel *c);
void ra_synth_note_on(int track, int ch, int note, int vel, int id, int seq);
void ra_synth_note_off(int track, int ch, int note, int id, int seq);
void ra_synth_voice_ctl(int track, int ch, int note, int id, int what, int value);
void ra_synth_cc(int track, int ch, int cc, int value);
void ra_synth_prog(int track, int ch, int prog);
void ra_synth_bend(int track, int ch, int value);
void ra_synth_next(int track, int ch, int what, int value);
void ra_synth_all_off(int track, int immediate, int seq_only);
void ra_synth_track_changed(int track);
ra_voice *ra_voice_at(int hv);

/* ra_host.c (HOST: environment, logs, WAV, runtime glue) */
int ra_host_env_mode(void);
int ra_host_env_pcm_native(void);
int ra_host_env_movie_native(void);
int ra_host_env_break(void);
void ra_host_cmdlog(uint64_t frame, char kind, int id, const int *w, int n, int result);
int ra_host_cmdlog_on(void);
void ra_host_runtime_attach(void);

/* ra_seq.c */
int ra_seq_select(ra_player *p, const uint8_t *d, uint32_t size, int block);
void ra_seq_rewind(ra_player *p);
void ra_seq_tick(ra_player *p);

#endif
