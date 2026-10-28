/* SPDX-License-Identifier: CC0-1.0 */
/* Movie playback (PLAN.md P4, docs/MOVIE.md, docs/MVI.md).
 *
 * Three layers, all original CC0 code with no external dependencies:
 *
 *   rg_mvdec_*    MPEG-2 MP@ML video decoder for the converted movies
 *                 (data/converted/MOVIE/<dir>/<name>.mpg, an MPEG-2 program stream).
 *                 It implements exactly the subset the 89 retail movies use (docs/MOVIE.md
 *                 "Stream survey") and refuses anything else with an error.
 *   rg_mvaudio_*  The converted .wav (PCM s16 LRLR, 48048 or 48000 Hz) read back either as
 *                 host PCM or re-encoded as the original Sony SShd/SSbd byte stream that the
 *                 game's AudioDec layer parses (block-interleaved 512-byte halves).
 *   rg_movie_*    The movie service that replaces the game's movie layer (IPU, DMA ch3/4,
 *                 the three movie threads and their handlers): start / per-vblank update /
 *                 frame for the game's GS upload / skip / pause / completion / restart /
 *                 teardown, paced on the virtual clock.
 *
 * Single-threaded: a decoder or service instance must be used from one thread at a time.
 * Everything is deterministic (no wall clock, no threads, no floating point in the
 * bitstream path; the IDCT is double precision evaluated in a fixed order with SSE2 scalar
 * math, PLAN.md D2, so the same build always produces the same pixels). */
#ifndef RG_MOVIE_H
#define RG_MOVIE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ decoder */

typedef struct rg_mvdec rg_mvdec;

typedef struct rg_mvdec_info {
    int width, height;        /* horizontal_size / vertical_size */
    int fps_num, fps_den;     /* 30000/1001 or 30/1 */
    int pts_step;             /* 90 kHz ticks per frame: 3003 or 3000 */
    int aspect_code;          /* aspect_ratio_information */
    uint32_t bit_rate;        /* bit_rate_value * 400 (bit/s) */
} rg_mvdec_info;

typedef struct rg_mvframe {
    const uint8_t *y, *cb, *cr;   /* NULL when the frame was decoded with want_pixels = 0 */
    int ystride, cstride;         /* bytes per row */
    int width, height;            /* luma size; chroma is (width/2) x (height/2) */
    uint32_t index;               /* display index, 0-based */
    int64_t pts;                  /* 90 kHz presentation time stamp (from the PES headers) */
    int type;                     /* 1 = I, 2 = P, 3 = B */
} rg_mvframe;

enum {
    RG_MV_OK = 0,
    RG_MV_EOF = 1,
    RG_MV_ERR_IO = -1,
    RG_MV_ERR_FORMAT = -2,     /* not an MPEG-2 PS / malformed headers */
    RG_MV_ERR_UNSUPPORTED = -3, /* a syntax feature no retail movie uses */
    RG_MV_ERR_BITSTREAM = -4,   /* a VLC/marker error inside picture data */
    RG_MV_ERR_NOMEM = -5
};

/* Open a converted movie (.mpg). Reads up to the first sequence header. 0 on success. */
int rg_mvdec_open(rg_mvdec **out, const char *mpg_path, char *err, size_t errcap);
/* Same, from memory (the buffer must outlive the decoder). */
int rg_mvdec_open_memory(rg_mvdec **out, const void *data, size_t size, char *err, size_t errcap);
void rg_mvdec_close(rg_mvdec *d);
const rg_mvdec_info *rg_mvdec_get_info(const rg_mvdec *d);
/* Decode until the next frame in display order. RG_MV_OK with *f filled, RG_MV_EOF
 * after the last frame, or a negative RG_MV_ERR_*. The frame's planes stay valid until the
 * next call on this decoder. With want_pixels = 0 a B picture is parsed past without
 * being decoded (frame dropping); its planes are then NULL but index/pts/type are set. */
int rg_mvdec_next(rg_mvdec *d, rg_mvframe *f, int want_pixels);
/* Seek to the start (the first frame is returned again by the next rg_mvdec_next). */
int rg_mvdec_rewind(rg_mvdec *d);
const char *rg_mvdec_error(const rg_mvdec *d);
/* Statistics since open/rewind. */
uint32_t rg_mvdec_pictures_decoded(const rg_mvdec *d);
/* Process-wide count of predictions whose source block reached outside the reference
 * picture (edge samples repeated; see MOVIE.md "Out-of-picture motion vectors"). */
uint32_t rg_mvdec_oob_predictions(void);

/* --------------------------------------------------------------- conversion */

/* BT.601 studio-swing YCbCr -> RGB, chroma replicated over 2x2 (as the IPU CSC does: it
 * has no chroma filter). Output words are little-endian R,G,B,A bytes in memory. */
void rg_mv_to_rgba(const rg_mvframe *f, uint32_t *rgba, int stride_px, uint8_t alpha);
/* The layout the game's GS upload packets expect (GsUploadImage16Blocks_1d27a0): 16x16
 * RGBA32 blocks of 1024 bytes, block row-major inside, blocks in COLUMN-major order
 * (x outer, y inner), i.e. exactly what sceMpegGetPicture's CSC output looks like.
 * dst must hold (w/16)*(h/16)*1024 bytes. */
void rg_mv_to_ps2_blocks(const rg_mvframe *f, uint8_t *dst, uint8_t alpha);
/* Hash of a frame's Y,Cb,Cr planes (FNV-1a 64 over the visible area, Y then Cb then Cr). */
uint64_t rg_mv_frame_hash(const rg_mvframe *f);

/* -------------------------------------------------------------------- audio */

typedef struct rg_mvaudio rg_mvaudio;

/* Open the converted .wav (PCM 16-bit, stereo). 0 on success. */
int rg_mvaudio_open(rg_mvaudio **out, const char *wav_path, char *err, size_t errcap);
int rg_mvaudio_open_memory(rg_mvaudio **out, const void *wav, size_t size, char *err, size_t errcap);
void rg_mvaudio_close(rg_mvaudio *a);
uint32_t rg_mvaudio_rate(const rg_mvaudio *a);       /* header rate: 48048 or 48000 */
uint64_t rg_mvaudio_frames(const rg_mvaudio *a);     /* total sample frames */
/* Host PCM: up to n LRLR frames from the current position; returns frames read. */
uint32_t rg_mvaudio_read_pcm(rg_mvaudio *a, int16_t *lr, uint32_t n);
/* The original private-stream-1 payload (after the 4 framing bytes): "SShd" header, "SSbd"
 * header, then [256 L][256 R] s16 blocks, zero-padded to a whole block. This is what the
 * game's AudioDecPcmCallback_1d4ca0 copies into the AudioDec ring. Returns bytes. */
uint32_t rg_mvaudio_read_ss(rg_mvaudio *a, uint8_t *dst, uint32_t n);
uint64_t rg_mvaudio_ss_size(const rg_mvaudio *a);    /* total SS stream bytes */
void rg_mvaudio_rewind(rg_mvaudio *a);
/* Position (frames) of the host-PCM reader / the SS reader. */
uint64_t rg_mvaudio_pcm_pos(const rg_mvaudio *a);
int rg_mvaudio_seek_pcm(rg_mvaudio *a, uint64_t frame);

/* ------------------------------------------------------------------ service */

/* Virtual clock: PS2 bus cycles (147.456 MHz, ps2k_now()). The SPU2 consumes the movie
 * ring at exactly 48000 frames per second of virtual time, so audio position is derived
 * from this clock; nothing reads the wall clock. */
#define RG_MOVIE_BUSCLK 147456000u
#define RG_MOVIE_SPU_RATE 48000u
/* One NTSC field (VBlank period) in bus cycles, as the EE kernel HLE: 59.94 Hz. Retail
 * shows one movie frame per two fields (docs/VALIDATION.md section 6). */
#define RG_MOVIE_FIELD_CYCLES 2460060u

typedef enum rg_movie_state {
    RG_MOVIE_IDLE = 0,      /* nothing open */
    RG_MOVIE_PREROLL,       /* opened, filling the frame FIFO (game: MovieIsStarted() == 0) */
    RG_MOVIE_PLAYING,       /* display started (D_004817BC = 1) */
    RG_MOVIE_PAUSED,        /* MoviePause: clock frozen, audio stopped */
    RG_MOVIE_COMPLETE,      /* last frame shown for its duration (MovieIsFinished() = 1) */
    RG_MOVIE_STOPPED,       /* skipped / shut down early (MovieIsFinished() = 1) */
    RG_MOVIE_ERROR          /* open or decode failed; reads as finished so the game moves on */
} rg_movie_state;

typedef enum rg_movie_sync {
    /* Default. The frame shown is the one whose PTS matches the audio being heard: authored
     * time = SPU frames played / header rate. A/V error <= 1 frame for the whole movie. */
    RG_MOVIE_SYNC_AUDIO = 0,
    /* Retail pacing, as measured on PCSX2 (docs/VALIDATION.md section 6): video advances
     * exactly one decoded frame per two VBlanks (59.94 / 2 = 29.97 fps) from display start,
     * never dropped or resynced (rg_movie_take_frame gives at most one new frame per call,
     * and only when its 2-field slot has come); audio plays at the SPU2's fixed 48000 Hz
     * whatever the header rate (48048 Hz content runs 0.1% slow). On the 29.97 fps /
     * 48048 Hz movies the audio drifts late by 1 ms per second, as on retail. */
    RG_MOVIE_SYNC_RETAIL = 1
} rg_movie_sync;

/* A frame source. The service owns one per open movie; tests can supply a synthetic one. */
typedef struct rg_movie_source {
    void *user;
    /* frame: as rg_mvdec_next. */
    int (*next)(void *user, rg_mvframe *f, int want_pixels);
    int (*rewind)(void *user);
    const rg_mvdec_info *(*info)(void *user);
    void (*close)(void *user);
} rg_movie_source;

typedef struct rg_movie_config {
    const char *data_root;   /* the extracted data dir ("data"); converted files are under
                                <data_root>/converted/MOVIE/<dir>/<name>.{mpg,wav} */
    rg_movie_sync sync;
    int fifo_frames;         /* decoded frames kept ahead (game: VoBuf, 2 slots); 1..8 */
    int audio;               /* 0 = the game opened the movie without audio (D_004817B8 = 0) */
    int loop;                /* 1 = rewind at the end (game: D_004817C8) */
    uint32_t preroll_audio_frames; /* audio that must be queued before display starts
                                (game: AudioDecIsPreset, ring fill); 0 = none */
} rg_movie_config;

typedef struct rg_movie rg_movie;

typedef struct rg_movie_status {
    rg_movie_state state;
    int started;              /* game D_004817BC: first frame ready, display + audio started */
    int finished;             /* game MovieIsFinished_1d5680 */
    uint32_t frames_decoded;  /* game MovieGetFrameCount_1d52d0 (D_004B3218) */
    uint32_t frames_shown;    /* frames handed out by rg_movie_take_frame */
    uint32_t frames_dropped;  /* decoded-or-skipped but never shown (video behind clock) */
    uint32_t frames_repeated; /* take_frame calls that kept the previous frame */
    int64_t shown_pts;        /* PTS of the frame on screen (relative: 0 = first frame) */
    uint64_t audio_frames;    /* SPU frames played since display start (virtual clock) */
    int width, height;
    int loops;                /* completed loop passes */
} rg_movie_status;

void rg_movie_config_default(rg_movie_config *c);
rg_movie *rg_movie_create(const rg_movie_config *c);
void rg_movie_destroy(rg_movie *m);

/* Map a game path ("cdrom0:\\MOVIE\\00\\TITLE01.MVI;1", "MOVIE/00/TITLE01.MVI",
 * "00/TITLE01" ...) to the converted file base path (no extension). 0 on success. */
int rg_movie_resolve(const rg_movie_config *c, const char *game_path, char *out, size_t cap);

/* Start a movie by game path (MovieOpen + MoviePlayerStart). now = virtual clock.
 * Returns 0, or <0 (state ERROR, finished = 1, as a missing movie must not hang the game). */
int rg_movie_start(rg_movie *m, const char *game_path, uint64_t now);
/* Start from explicit files (wav may be NULL: no audio). */
int rg_movie_start_file(rg_movie *m, const char *mpg_path, const char *wav_path, uint64_t now);
/* A source over an open decoder (the service closes it). */
rg_movie_source rg_movie_source_decoder(rg_mvdec *d);
/* Start from an explicit source and optional audio (takes ownership of both). */
int rg_movie_start_source(rg_movie *m, rg_movie_source src, rg_mvaudio *audio, uint64_t now);

/* ---- save states (docs/TEST-FIXTURES.md): open FILEs are host state; after a
 * load the movie hook (rg_movie_g_ss_*) reopens them.  _tell: -1 = no file. */
rg_mvdec *rg_movie_ss_decoder(rg_movie *m);      /* NULL: no file decoder */
rg_mvaudio *rg_movie_ss_audio(rg_movie *m);
int64_t rg_mvdec_ss_tell(const rg_mvdec *d);
int rg_mvdec_ss_reopen(rg_mvdec *d, int64_t pos);
int rg_mvaudio_ss_file_backed(const rg_mvaudio *a);
int rg_mvaudio_ss_reopen(rg_mvaudio *a);
/* Per-vblank (or per game frame) pump: decodes ahead into the FIFO, runs preroll, advances
 * the clock, detects completion. Cheap when nothing is due. */
void rg_movie_update(rg_movie *m, uint64_t now);
/* Hold display start until the caller is ready too (the game also waits for its audio
 * ring to be preset: MovieAudioIsPreset_1d2490). Open by default. */
void rg_movie_set_start_gate(rg_movie *m, int open);
/* The game's MovieFrameQueueSendNext: returns 1 and the frame to upload if a NEW frame is
 * due at `now` (*f valid until the next call), 0 if the frame on screen stays. */
int rg_movie_take_frame(rg_movie *m, uint64_t now, rg_mvframe *f);
void rg_movie_pause(rg_movie *m, uint64_t now);
void rg_movie_resume(rg_movie *m, uint64_t now);
/* Skip (the game shuts the player down early): state STOPPED, finished = 1. */
void rg_movie_skip(rg_movie *m);
/* Rewind the current movie and preroll again (seek to start). */
int rg_movie_restart(rg_movie *m, uint64_t now);
/* Teardown (MoviePlayerShutdown): closes files, back to IDLE. Safe in any state. */
void rg_movie_stop(rg_movie *m);
void rg_movie_get_status(const rg_movie *m, rg_movie_status *s);
const char *rg_movie_error(const rg_movie *m);

/* Audio for the host directly (tools, or a port build that bypasses the game's AudioDec
 * layer): LRLR PCM at the header rate, from the position matching display start. */
uint32_t rg_movie_read_pcm(rg_movie *m, int16_t *lr, uint32_t n);
/* Audio for the game's AudioDec layer: the SShd/SSbd stream (see rg_mvaudio_read_ss). */
uint32_t rg_movie_read_ss(rg_movie *m, uint8_t *dst, uint32_t n);
rg_mvaudio *rg_movie_audio(rg_movie *m);

#ifdef __cplusplus
}
#endif
#endif
