/* SPDX-License-Identifier: CC0-1.0 */
/* The game's sound-driver command set on the native engine (docs/NATIVE-AUDIO.md
 * "Game side").
 *
 * The game talks to its sound driver through one queue, SoundQueueCmd_1b6d60(cmd,
 * args, size): 38 commands (the worker table D_0044AE10, ids 0x01..0x26), each with
 * up to 10 s32 arguments, synchronous, returning one s32.  On the PS2 each command
 * became one to three SK blocks or libsd calls sent to the IOP.  Here each becomes
 * one or two engine calls.  The game-side overrides (overrides/src/main/sound/) call
 * rg_audio_game_*; nothing below knows about SIF, IOP memory or SPU2 registers.
 *
 * RG_AUDIO=native (default) | hle | compare (rg_audio_mode):
 *   hle      the bring-up path only (worker thread -> SK blocks -> SIF RPC -> HLE),
 *   native   note/bank/sequence commands go to this engine only; mixer commands
 *            (master volume, effects, reverb, input volume) and the movie's raw libsd
 *            commands also still go to the HLE, which keeps serving the paths not
 *            yet native (movie audio, PCM streams unless RG_AUDIO_PCM=hle); the
 *            runtime adds both outputs,
 *   compare  everything goes to both; the HLE is what is heard, the engine's output
 *            goes to $RG_AUDIO_NATIVE_WAV for tools/native/audio_compare.py. */
#include <stdio.h>
#include <string.h>

#include "ra_internal.h"
#include "rg_audio_game.h"
#include "../threads/kapi/ps2k_fpu.h"

static int g_mode = -1;     /* model state: restored with a save state (the banks are) */
static int g_pcm_native = -1;
static int g_movie_native = -1;
static uint32_t g_mismatch;
static uint32_t to_native(uint32_t addr);

int rg_audio_mode(void)
{
    if (g_mode < 0)
        g_mode = ra_host_env_mode();
    return g_mode;
}

int rg_audio_pcm_native(void)
{
    if (g_pcm_native < 0)
        g_pcm_native = rg_audio_mode() == RG_AUDIO_HLE ? 0 : ra_host_env_pcm_native();
    return g_pcm_native;
}

int rg_audio_movie_native(void)
{
    if (g_movie_native < 0)
        g_movie_native = rg_audio_mode() == RG_AUDIO_HLE ? 0 : ra_host_env_movie_native();
    return g_movie_native;
}

/* native mode: does the HLE still serve something (movie or PCM left on it)? */
int rg_audio_hle_needed(void)
{
    return rg_audio_mode() != RG_AUDIO_NATIVE || !rg_audio_movie_native() || !rg_audio_pcm_native();
}

int rg_audio_game_route(int cmd)
{
    switch (cmd) {
    case 0x03: case 0x05: case 0x09: /* carry IOP addresses: replaced at the upload sites */
        return RG_AUDIO_ROUTE_HLE;
    case 0x26:                       /* the movie layer's libsd calls */
        return rg_audio_movie_native() ? RG_AUDIO_ROUTE_NATIVE : RG_AUDIO_ROUTE_HLE;
    case 0x0C: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
        return rg_audio_hle_needed() ? RG_AUDIO_ROUTE_BOTH : RG_AUDIO_ROUTE_NATIVE;
    default:
        return RG_AUDIO_ROUTE_NATIVE;
    }
}

void rg_audio_game_init(void)
{
    ra_config c;
    ra_default_config(&c);
    c.break_mode = ra_host_env_break();
    ra_init(&c);
    ra_host_runtime_attach();
    /* what SoundIopInit_1b7160 makes the driver do after its master volume init:
     * SPDIF (no meaning here), both buses: hall reverb with a cleared work area and
     * depth 0, effects off, bus 1 master (0x7F * 129) & 0x7FFF */
    ra_reverb_mode(0, 5, 1);
    ra_reverb_mode(1, 5, 1);
    ra_effect_enable(0, 0);
    ra_master_volume(0x7F, 0x7F);
}

int rg_audio_game_bank(const void *hd, unsigned hd_size, const void *bd, unsigned bd_size)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    if (!ra_initialized())
        rg_audio_game_init();
    int r = ra_bank_load(-1, hd, hd_size, bd, bd_size);
    ra_host_cmdlog(ra_frames_rendered(), 'B', 0x05, NULL, 0, r);
    return r;
}

int rg_audio_game_seq(const void *sq, unsigned size)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    if (!ra_initialized())
        rg_audio_game_init();
    int r = ra_seq_load(-1, sq, size);
    ra_host_cmdlog(ra_frames_rendered(), 'B', 0x03, NULL, 0, r);
    return r;
}

int rg_audio_game_cmd(int cmd, const int *a)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    int r = 0;
    if (!ra_initialized())
        rg_audio_game_init();
    switch (cmd) {
    case 0x01: ra_all_notes_off(a[0]); break;
    case 0x02: ra_all_sound_off(a[0]); break;
    case 0x04: r = ra_se_open(a[0]); break;
    case 0x06: r = ra_seq_attach(a[0], a[1]); break;
    case 0x07: r = ra_se_attach(a[0], a[1]); break;
    case 0x08: r = ra_bank_attach(a[0], a[1], a[2]); break;
    case 0x0A: ra_set_mono(a[0]); break;
    case 0x0B: r = 0; break;
    case 0x0C: ra_master_volume((uint32_t)a[0], (uint32_t)a[1]); break;
    case 0x0D: r = ra_seq_pause(a[0]); break;
    case 0x0E: ra_seq_play(a[0], a[1]); break;
    case 0x0F: r = ra_seq_stop(a[0]); break;
    case 0x10: ra_seq_tempo(a[0], a[1]); break;
    case 0x11: ra_seq_speed(a[0], a[1]); break;
    case 0x12: ra_seq_volume(a[0], a[1]); break;
    case 0x13: r = ra_seq_query(a[0], a[1]); break;
    case 0x14: r = a[1] == 0x11 ? ra_note_state(a[0], a[2]) : RA_E_CMD; break;
    case 0x15: ra_seq_release(a[0]); break;
    case 0x16: ra_se_release(a[0]); break;
    case 0x17: ra_bank_release(a[0]); break;
    case 0x18: ra_seq_detach(a[0]); break;
    case 0x19: ra_se_detach(a[0]); break;
    case 0x1A: ra_bank_detach(a[0]); break;
    /* key off (track, id, slot, prog, ch, note) */
    case 0x1B: ra_key_off(a[0], a[1], a[4], a[5]); break;
    /* key on, muted: (track, id, slot, prog, ch, note, vel, pan), then volume 0 */
    case 0x1C:
        ra_key_on(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
        ra_note_volume(a[0], a[1], a[4], a[5], 0);
        r = 0;
        break;
    /* (track, id, ch, note, value) */
    case 0x1D: ra_note_volume(a[0], a[1], a[2], a[3], a[4]); break;
    case 0x1E: ra_note_pan(a[0], a[1], a[2], a[3], a[4]); break;
    case 0x1F: ra_note_bend(a[0], a[1], a[2], a[3], a[4]); break;
    /* key on (track, id, slot, prog, ch, note, vel, pan, volume, bend) */
    case 0x20:
        r = ra_key_on(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
        ra_note_volume(a[0], a[1], a[4], a[5], a[8]);
        ra_note_bend(a[0], a[1], a[4], a[5], a[9]);
        break;
    /* (on, input): effects on both buses; input = stream inputs into the reverb too */
    case 0x21: ra_effect_enable(a[0], a[1]); r = 0; break;
    case 0x22: ra_reverb_mode(a[0] != 0, a[1], 1); r = 0; break;          /* (bus, mode) */
    case 0x23: {                                                           /* (bus, depth) */
        int16_t d = (int16_t)((a[1] << 8) & 0xFFFF);
        ra_bus_effect(a[0] != 0, 1);
        ra_reverb_depth(a[0] != 0, d, d);
        r = 0;
        break;
    }
    case 0x24: ra_bus_effect(a[0] != 0, 0); r = 0; break;                 /* work area: no meaning */
    case 0x25: ra_bus_input_volume(a[0] != 0, (int16_t)a[1], (int16_t)a[1]); r = 0; break;
    /* the movie layer's libsd calls (fno, ch, mode, ...): AudioDecStart / AudioDecPause /
     * AudioDecSendToIop.  BlockTrans start/stop, BlockTransStatus, and the VoiceTrans
     * that cleared the hardware input buffer (nothing to clear here) */
    case 0x26:
        switch (a[0] & 0xFFF0) {
        case 0x80E0:
            if ((a[2] & 3) == 2)
                r = (int)ra_movie_stop(a[1] & 1);
            else if ((a[2] & 3) == 1)
                r = 0;
            else
                r = ra_movie_start(a[1] & 1, to_native((uint32_t)a[3]), (uint32_t)a[4],
                                   to_native((a[2] & 3) == 3 ? (uint32_t)a[5] : (uint32_t)a[3]), (a[2] & 0x10) != 0);
            break;
        case 0x8100: r = (int)ra_movie_position(a[1] & 1); break;
        case 0x80D0: r = a[5]; break;
        default: r = 0; break;
        }
        break;
    default:
        g_ra->st.unknown++;
        r = 0;
        break;
    }
    ra_host_cmdlog(ra_frames_rendered(), 'T', cmd, a, 10, r);
    return r;
}

void rg_audio_game_compare(int cmd, int hle, int native)
{
    /* ids the game keeps (entries, tracks, SE ids) must agree between the engines */
    /* (the key on's reply is not used by the game: SoundSendKeyOn_1b80c0 drops it) */
    int kept = cmd == 0x03 || cmd == 0x04 || cmd == 0x05 || cmd == 0x06 || cmd == 0x07 || cmd == 0x08;
    if (kept && hle != native && g_mismatch++ < 32)
        fprintf(stderr, "rg_audio compare: cmd 0x%02X hle %d native %d\n", cmd, hle, native);
}

unsigned rg_audio_game_mismatches(void) { return g_mismatch; }

/* ---- PCM streams (the game's pcm_mixer calls) ---------------------------------------------- */
int rg_audio_game_pcm(int fno, const int *a)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    int r;
    if (!ra_initialized())
        rg_audio_game_init();
    switch (fno) {
    case 0x8000: r = ra_pcm_init(a[0], (uint32_t)a[1], (uint32_t)a[2]); break;
    case 0x80A0: r = ra_pcm_free_blocks(a[0]); break;
    case 0x8100: r = ra_pcm_start(); break;
    case 0x8400: r = ra_pcm_stop(); break;
    case 0x0010: r = ra_pcm_shutdown(); break;
    case 0x0200: ra_pcm_volume((uint32_t)a[0], 0); r = 0; break;
    case 0x0300: ra_pcm_volume((uint32_t)a[0], 1); r = 0; break;
    default: r = -1; break;
    }
    if (fno != 0x80A0)
        ra_host_cmdlog(ra_frames_rendered(), 'P', fno, a, 3, r);
    return r;
}

int rg_audio_game_pcm_mix(int port, const void *block, int vol_l, int vol_r)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    int r = ra_pcm_mix(port, block, vol_l, vol_r);
    return r;
}

/* ---- movie audio stream buffers (the AudioDec ring, AudioDecCreate_1d3210) ------------------------ */
/* compare mode: the game holds the HLE's IOP addresses; the engine's buffers are mapped to them */
static struct { uint32_t hle, nat, size; } g_map[RA_STREAM_BUFS];

static uint32_t to_native(uint32_t addr)
{
    for (int i = 0; i < RA_STREAM_BUFS; i++)
        if (g_map[i].size && addr >= g_map[i].hle && addr - g_map[i].hle < g_map[i].size)
            return g_map[i].nat + (addr - g_map[i].hle);
    return addr;
}

unsigned rg_audio_game_stream_alloc(unsigned size)
{
    if (!ra_initialized())
        rg_audio_game_init();
    return ra_stream_alloc(size);
}

void rg_audio_game_stream_map(unsigned hle_addr, unsigned size)
{
    if (!hle_addr)
        return;
    uint32_t nat = rg_audio_game_stream_alloc(size);
    for (int i = 0; nat && i < RA_STREAM_BUFS; i++)
        if (!g_map[i].size) {
            g_map[i].hle = hle_addr;
            g_map[i].nat = nat;
            g_map[i].size = size;
            return;
        }
}

void rg_audio_game_stream_free(unsigned addr)
{
    for (int i = 0; i < RA_STREAM_BUFS; i++)
        if (g_map[i].size && g_map[i].hle == addr) {
            ra_stream_free(g_map[i].nat);
            memset(&g_map[i], 0, sizeof g_map[i]);
            return;
        }
    ra_stream_free(addr);
}

int rg_audio_game_stream_write(unsigned addr, const void *src, int n)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    return n <= 0 ? 0 : ra_stream_write(to_native(addr), src, (uint32_t)n) < 0 ? 0 : n;
}
