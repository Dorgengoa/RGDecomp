/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine (PLAN.md D9, docs/NATIVE-AUDIO.md).
 *
 * What the game's sound driver layer asks for, as host calls: banks (SCEI HD + raw
 * PS-ADPCM BD, copied from the caller's memory), sequences (SCEI SQ), SE note input,
 * per-note volume/pan/bend, a 240 Hz sequencer tick, two mix buses with reverb and a
 * master volume, float mixing.  No SIF/RPC, no IOP memory, no SPU2 register model:
 * the sound semantics (MODHSYN layer resolution, volume/pan/pitch formulas, ADSR,
 * PS-ADPCM, psx-style reverb) are carried over from the bring-up HLE
 * (src/ps2/iop/sound, src/ps2/spu), which stays as the test oracle (RG_AUDIO=hle /
 * compare).
 *
 * Ids and error codes follow the Standard Kit rules the game was written against
 * (first free entry, -101/-102/-201/-202/-310), because the game stores and checks
 * them.  "track" = an SK track (0..15): one note input (a sequence or SE input)
 * plus up to 16 bank slots.
 *
 * Time: the engine renders 48 kHz stereo frames up to a clock (frames) given by the
 * host (ra_set_clock); every call first renders up to the clock, so commands land at
 * exact sample times and the output is a pure function of the timed call sequence.
 * Without a clock, ra_render() pulls frames (tools, tests).  Single threaded. */
#ifndef RG_NATIVE_AUDIO_H
#define RG_NATIVE_AUDIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RA_RATE        48000
#define RA_TRACKS      16
#define RA_BANKS       16
#define RA_SLOTS       16
#define RA_SEQS        16
#define RA_SEQ_PORTS   5
#define RA_SE_INPUTS   16
#define RA_BUSES       2
#define RA_BUS_VOICES  24
#define RA_VOICES      (RA_BUSES * RA_BUS_VOICES)
#define RA_TICK_FRAMES 200   /* 240 Hz sequencer / input tick */

/* SK error codes (docs/SOUND-PROTOCOL.md section 2) */
#define RA_E_INDEX   (-101)
#define RA_E_STATE   (-102)
#define RA_E_NOENTRY (-201)
#define RA_E_BUSY    (-202)
#define RA_E_CMD     (-310)
#define RA_E_LIB     (-402)

enum { RA_INTERP_BSPLINE = 0, RA_INTERP_LINEAR = 1, RA_INTERP_NONE = 2 };

typedef struct ra_config {
    int interp;            /* RA_INTERP_* */
    uint32_t fifo_frames;  /* output FIFO capacity (default 96000 = 2 s) */
    int break_mode;        /* deliberately wrong engine for the compare control:
                              0 off, 1 pitch +1 semitone, 2 output x0.5, 3 no reverb */
} ra_config;

typedef struct ra_stats {
    uint64_t frames;
    uint32_t key_ons, key_offs, voice_steals, no_layer, seq_notes, seq_events;
    uint32_t banks_loaded, bank_bytes, seqs_loaded, clips, unknown;
    uint32_t pcm_blocks, pcm_underruns, movie_frames;
} ra_stats;

void ra_default_config(ra_config *cfg);
/* Reset everything (banks freed, voices off, buses to the post-init state below).
 * Bus 0 master = 0x3FFF, bus 1 master = 0 (what the game's sound init writes first),
 * bus 0 -> bus 1 gain = 0x7FFF, reverb off, effects off. */
void ra_init(const ra_config *cfg);
void ra_shutdown(void);
int ra_initialized(void);

/* ---- clock / output ------------------------------------------------------------- */
void ra_set_clock(uint64_t (*now_frames)(void *user), void *user);
/* The 240 Hz tick runs on frames where (frame - origin) % 200 == 0. Default origin:
 * the clock frame at ra_init. */
void ra_set_tick_origin(uint64_t frame);
uint32_t ra_sync(void);                      /* render up to the clock into the FIFO */
uint32_t ra_output_read(int16_t *lr, uint32_t max_frames);   /* the model mix */
uint32_t ra_output_available(void);
uint64_t ra_output_dropped(void);
void ra_render(int16_t *lr, uint32_t frames); /* pull (no clock): s16 */
void ra_render_f(float *lr, uint32_t frames); /* pull (no clock): float, +-1.0 */
uint64_t ra_frames_rendered(void);           /* absolute frame of the next sample */
const ra_stats *ra_get_stats(void);

/* ---- banks ------------------------------------------------------------------------- */
/* Copy an HD header and its BD (PS-ADPCM) into a bank entry; entry -1 = first free.
 * Returns the entry id (0..15) or < 0. An empty or unparsable HD is accepted (the bank
 * plays nothing). */
int ra_bank_load(int entry, const void *hd, uint32_t hd_size, const void *bd, uint32_t bd_size);
int ra_bank_release(int entry);              /* voices still playing it keep their data */
int ra_bank_attach(int track, int entry, int slot); /* track -1 = first track with no
                                                       input and no banks; returns track */
int ra_bank_detach(int track);               /* cuts the track's voices */

/* ---- sequences (SQ) -------------------------------------------------------------------- */
int ra_seq_load(int id, const void *sq, uint32_t size); /* id -1 = first free */
int ra_seq_release(int id);
int ra_seq_attach(int track, int id);        /* track -1 = first free; returns track */
int ra_seq_detach(int track);
int ra_seq_play(int track, int block);
int ra_seq_stop(int track);                  /* stop + rewind, release notes */
int ra_seq_pause(int track);
int ra_seq_volume(int track, int v);         /* 0x80 = unity */
int ra_seq_tempo(int track, int bpm);
int ra_seq_speed(int track, int rel);        /* 0x100 = 1.0 */
int ra_seq_query(int track, int q);

/* ---- SE note input ------------------------------------------------------------------- */
int ra_se_open(int id);                      /* id -1 = first free */
int ra_se_release(int id);
int ra_se_attach(int track, int id);
int ra_se_detach(int track);
/* key on: bank slot, program, MIDI channel, note, velocity, pan (0x40 = centre).
 * id < 0: the engine picks one (0..126). Returns the id. */
int ra_key_on(int track, int id, int slot, int prog, int ch, int note, int vel, int pan);
int ra_key_off(int track, int id, int ch, int note);
int ra_note_volume(int track, int id, int ch, int note, int v);  /* 0..127 */
int ra_note_pan(int track, int id, int ch, int note, int v);     /* 0..127 */
int ra_note_bend(int track, int id, int ch, int note, int v);    /* 14-bit, 0x2000 = 0 */
int ra_note_state(int track, int id);        /* 0x10 while one of its voices sounds */

/* ---- tracks / output --------------------------------------------------------------------- */
int ra_all_notes_off(int track);             /* release */
int ra_all_sound_off(int track);             /* cut */
void ra_set_mono(int on);

/* ---- mix buses ------------------------------------------------------------------------- */
/* master volume as the game's sound driver computes it: x = 0x3FFF * v sent per side,
 * stored (x * 129) & 0x7FFF (the SK formula, wrap included), applied to bus 1. */
void ra_master_volume(uint32_t l, uint32_t r);
void ra_bus_master(int bus, uint16_t l, uint16_t r);  /* raw 15-bit level (x2 like the HLE) */
/* effects on/off on both buses; input = the buses' stream inputs also feed reverb */
void ra_effect_enable(int on, int input_wet);
void ra_bus_effect(int bus, int on);
void ra_reverb_mode(int bus, int mode, int clear); /* libsd modes 0..9; depth -> 0 */
void ra_reverb_depth(int bus, int16_t l, int16_t r); /* raw s16 return level */
void ra_bus_input_volume(int bus, int16_t l, int16_t r);

/* ---- PCM stream ports (the game's 4-port streamed audio: voices, ambience) ----------- */
/* A ring of nblocks blocks of block_bytes ([256 L][256 R] s16 pairs) played on bus 1,
 * same latency and refill rules as the game's pcm mixer (docs/NATIVE-AUDIO.md). */
int ra_pcm_init(int bus, uint32_t block_bytes, uint32_t nblocks);
int ra_pcm_free_blocks(int port);
int ra_pcm_mix(int port, const void *block, int vol_l, int vol_r); /* 1 mixed, 0 full */
int ra_pcm_start(void);
int ra_pcm_stop(void);
int ra_pcm_shutdown(void);
void ra_pcm_volume(uint32_t lr, int now);    /* (L << 16) | R, applied at the next block
                                                boundary unless now */

/* ---- movie audio ------------------------------------------------------------------------ */
/* Engine-owned stream buffers.  The game's movie layer keeps "addresses" into them and does
 * its ring arithmetic on those (base + offset): a handle is a non-zero number below 16 MB,
 * not a memory model.  ra_stream_write copies into the buffer that holds `addr`. */
uint32_t ra_stream_alloc(uint32_t size);
void ra_stream_free(uint32_t addr);
int ra_stream_write(uint32_t addr, const void *src, uint32_t n);
/* Play the ring [ring, ring + size) of 1 KiB units ([256 L][256 R] s16) on the bus's stream
 * input from `start`, looping or once.  Like the hardware's input double buffer, the start
 * takes two units and each played unit takes the next, so the position runs two units ahead
 * of what is heard and the game may refill everything behind it. */
int ra_movie_start(int bus, uint32_t ring, uint32_t size, uint32_t start, int loop);
uint32_t ra_movie_position(int bus);         /* (second half << 24) | (ring + next unit) */
uint32_t ra_movie_stop(int bus);             /* returns the position, freezes */

/* ---- presentation mix: per-source volumes (docs/NATIVE-AUDIO.md "Source volumes") ------
 * The FIFO above (ra_output_read) is the model mix: the run hash folds it and it never
 * changes with these gains.  Beside it the engine keeps a presentation FIFO of the same
 * frames with a gain per source applied inside the mix (before reverb, so a muted source
 * leaves no reverb tail):
 *   MUSIC    sequenced notes (SQ tracks) and PCM streams of BGM / jingles
 *   EFFECTS  SE notes (the game's key ons) and PCM streams of anything else
 *   VOICE    PCM streams of event voice and LiveTalk lines
 *   MOVIE    the movie audio stream
 * While every gain is 1 the presentation frames are the model frames (bit for bit).
 * A gain change ramps over 10 ms. */
enum { RA_SRC_MUSIC = 0, RA_SRC_EFFECTS, RA_SRC_VOICE, RA_SRC_MOVIE, RA_SRC_COUNT };
void ra_present_set_gain(int src, float gain);   /* 0..1; any thread */
float ra_present_get_gain(int src);
int ra_present_active(void);                     /* the second mix is being rendered */
/* ra_output_read plus the matching presentation frames (plr may be NULL) */
uint32_t ra_output_read2(int16_t *lr, int16_t *plr, uint32_t max_frames);
void ra_render2(int16_t *lr, int16_t *plr, uint32_t frames); /* pull: both mixes */
/* The source of what a PCM port plays (the stream's file path, RA_SRC_* by name):
 * "BGM" -> music, "SND2/MWV" (jingles) -> music, "LIVETALK" or an "/EVnn-" folder ->
 * voice, anything else -> effects.  ra_pcm_source_of is the classifier alone. */
void ra_pcm_source(int port, const char *path);
int ra_pcm_source_of(const char *path);
int ra_pcm_port_source(int port);

/* introspection (tests) */
int ra_voices_playing(void);
int ra_track_status(int track);
int ra_seq_playing(int track);

/* sceSdNote2Pitch semantics (0x1000 = 48 kHz at center_note), exposed for tests */
uint16_t ra_note2pitch(int center_note, int center_fine, int note, int fine);
uint8_t ra_adpcm_decode_block(const uint8_t blk[16], int16_t out[28], int16_t hist[2]);

#ifdef __cplusplus
}
#endif
#endif
