/* SPDX-License-Identifier: CC0-1.0 */
/* Sound HLE servers: sdr_driver (SID 0x80000701) incl. the 0x90F0 Standard Kit
 * command blocks, and pcm_mixer (SID 0x123456). Protocol: docs/SOUND-PROTOCOL.md
 * (section numbers below refer to it). Model and caveats: docs/SOUND.md. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iop.h"
#include "sif.h"
#include "snd_internal.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */

#define SDR_SID 0x80000701u
#define PCM_SID 0x00123456u

static snd_state g_state;
snd_state *g_snd = &g_state;

static uint32_t g_reply[0x100]; /* reply buffer (0x400 bytes) shared by both servers */

/* ---- logging ------------------------------------------------------------------------- */
static void note_unknown(const char *what, uint32_t a, uint32_t b)
{
    g_snd->stats.unknown_calls++;
    if (g_snd->cfg.quiet || getenv("RG_IOP_QUIET"))
        return;
    static int count;
    if (count++ < 64)
        fprintf(stderr, "[snd] unhandled %s 0x%X 0x%X\n", what, a, b);
}

/* ---- clock / render / FIFO ------------------------------------------------------------- */
static uint64_t clock_sif(void *user)
{
    (void)user;
    return sif_now();
}

static void sk_tick(void)
{
    g_snd->sk_ticks++;
    for (int i = 0; i < SND_MIDI_PORTS; i++)
        seq_tick(&g_snd->port[i]);
}

static void render_frames(int16_t *out, uint32_t n)
{
    while (n) {
        uint32_t chunk = SND_TICK_FRAMES - g_snd->tick_phase;
        if (chunk > n)
            chunk = n;
        spu2_render(&g_snd->spu, out, chunk);
        if (out)
            out += chunk * 2;
        n -= chunk;
        g_snd->tick_phase += chunk;
        g_snd->rendered += chunk;
        if (g_snd->tick_phase == SND_TICK_FRAMES) {
            g_snd->tick_phase = 0;
            sk_tick();
        }
    }
}

void snd_render(int16_t *lr, uint32_t frames) { render_frames(lr, frames); }

static void fifo_push(const int16_t *lr, uint32_t n)
{
    snd_state *s = g_snd;
    if (!s->fifo || !s->fifo_cap)
        return;
    for (uint32_t i = 0; i < n; i++) {
        if (s->fifo_n == s->fifo_cap) { /* drop the oldest frame */
            s->fifo_rd = (s->fifo_rd + 1) % s->fifo_cap;
            s->fifo_n--;
            s->fifo_dropped++;
        }
        uint32_t w = (s->fifo_rd + s->fifo_n) % s->fifo_cap;
        s->fifo[2 * w] = lr[2 * i];
        s->fifo[2 * w + 1] = lr[2 * i + 1];
        s->fifo_n++;
    }
}

uint32_t snd_sync(void)
{
    RG_IOP_HLE("snd_sync");
    snd_state *s = g_snd;
    if (!s->now)
        return 0;
    uint64_t target = s->now(s->now_user) / SND_CYCLES_PER_FRAME;
    if (target <= s->base_frame + s->rendered)
        return 0;
    uint64_t todo = target - s->base_frame - s->rendered;
    uint32_t done = 0;
    int16_t buf[2 * 512];
    while (todo) {
        uint32_t n = todo > 512 ? 512 : (uint32_t)todo;
        render_frames(buf, n);
        fifo_push(buf, n);
        todo -= n;
        done += n;
    }
    return done;
}

uint32_t snd_output_available(void) { return g_snd->fifo_n; }
uint64_t snd_output_dropped(void) { return g_snd->fifo_dropped; }

uint32_t snd_output_read(int16_t *lr, uint32_t max_frames)
{
    RG_IOP_HLE("snd_output_read");
    snd_state *s = g_snd;
    uint32_t n = s->fifo_n < max_frames ? s->fifo_n : max_frames;
    for (uint32_t i = 0; i < n; i++) {
        lr[2 * i] = s->fifo[2 * s->fifo_rd];
        lr[2 * i + 1] = s->fifo[2 * s->fifo_rd + 1];
        s->fifo_rd = (s->fifo_rd + 1) % s->fifo_cap;
    }
    s->fifo_n -= n;
    return n;
}

uint64_t snd_frames_rendered(void) { return g_snd->rendered; }
uint64_t snd_clock_frame(void) { return g_snd->base_frame + g_snd->rendered; }

uint32_t snd_frames_for_field(uint64_t k)
{
    return (uint32_t)((48000ull * 1001 * (k + 1)) / 60000 - (48000ull * 1001 * k) / 60000);
}

void snd_set_clock(uint64_t (*now)(void *user), void *user)
{
    g_snd->now = now;
    g_snd->now_user = user;
    g_snd->base_frame = now ? now(user) / SND_CYCLES_PER_FRAME - g_snd->rendered : 0;
}

struct spu2 *snd_spu(void) { return &g_snd->spu; }
const snd_stats *snd_get_stats(void) { return &g_snd->stats; }

/* ---- AutoDMA sources ---------------------------------------------------------------------- */
/* sceSdBlockTrans ring in IOP RAM: 1 KiB units of [256 x L s16][256 x R s16].
 * AutoDMA copies one unit into a half of the core's input buffer, which the core
 * plays at 48 kHz; when a half has been played it is refilled with the next unit.
 * Without that buffer the EE's first refill after the start (AudioDecSendToIop, free
 * space = DMA position - write position - 1 KiB) would overwrite the units the core
 * has not played yet: the first 24 KiB of every movie's audio were lost. */
static void movie_xfer(snd_movie *m, int h)
{
    if (m->xfer_done) {
        memset(m->half[h], 0, 1024);
        return;
    }
    const uint8_t *p = (const uint8_t *)iop_ptr(m->base + m->xfer, 1024);
    if (p)
        memcpy(m->half[h], p, 1024);
    else
        memset(m->half[h], 0, 1024);
    m->xfer += 1024;
    if (m->xfer >= m->size) {
        m->xfer = 0;
        if (!m->loop)
            m->xfer_done = 1;
    }
}

static int adma_movie(void *user, int core, int16_t lr[2])
{
    (void)user;
    snd_movie *m = &g_snd->movie[core & 1];
    if (!m->running)
        return 0;
    const uint8_t *p = m->half[m->play];
    lr[0] = (int16_t)(p[m->k * 2] | p[m->k * 2 + 1] << 8);
    lr[1] = (int16_t)(p[512 + m->k * 2] | p[512 + m->k * 2 + 1] << 8);
    m->frames++;
    if (++m->k == 256) {
        m->k = 0;
        movie_xfer(m, m->play); /* the half just played takes the next unit */
        m->play ^= 1;
        m->unit += 1024;
        if (m->unit >= m->size) {
            m->unit = 0;
            if (!m->loop)
                m->running = 0;
        }
    }
    return 1;
}

static void pcm_half_irq(void);

/* pcm_mixer output: the 2-half AutoDMA buffer on its core. */
static int adma_pcm(void *user, int core, int16_t lr[2])
{
    (void)user;
    snd_pcm *p = &g_snd->pcm;
    if (!p->running || core != p->core)
        return 0;
    uint32_t fpb = p->block_bytes / 4; /* frames per half (block) */
    const int16_t *h = p->dma + (size_t)p->play_half * (p->block_bytes / 2);
    uint32_t f = p->play_pos, pair = f >> 8, k = f & 0xFF;
    lr[0] = h[pair * 512 + k];
    lr[1] = h[pair * 512 + 256 + k];
    if (++p->play_pos >= fpb) {
        p->play_pos = 0;
        pcm_half_irq();
        p->play_half ^= 1;
    }
    return 1;
}

static void adma_bind(int core)
{
    spu2 *s = &g_snd->spu;
    if (g_snd->movie[core].running)
        spu2_set_adma(s, core, adma_movie, NULL);
    else if (g_snd->pcm.running && g_snd->pcm.core == core)
        spu2_set_adma(s, core, adma_pcm, NULL);
    else
        spu2_set_adma(s, core, NULL, NULL);
}

/* ---- pcm_mixer (section 3) -------------------------------------------------------------------- */
static void pcm_set_avol(uint32_t vol)
{
    snd_pcm *p = &g_snd->pcm;
    p->cur_vol = vol;
    uint32_t e = (uint32_t)p->core & 1;
    spu2_set_param(&g_snd->spu, (SPU2_P_BVOLL << 8) | 0x80 | e, (uint16_t)(vol >> 16));
    spu2_set_param(&g_snd->spu, (SPU2_P_BVOLR << 8) | 0x80 | e, (uint16_t)vol);
}

/* Half-buffer interrupt (output thread 0x638): the half that just finished playing is
 * refilled from ring block rpos (silence if nobody wrote it), the ring block is
 * cleared, rpos advances, and ports that fell behind are pushed one block ahead. */
static void pcm_half_irq(void)
{
    snd_pcm *p = &g_snd->pcm;
    uint32_t hw = p->block_bytes / 2;
    int16_t *dst = p->dma + (size_t)p->play_half * hw;
    int16_t *src = p->ring + (size_t)p->rpos * hw;
    memcpy(dst, src, p->block_bytes);
    memset(src, 0, p->block_bytes);
    p->rpos = (p->rpos + 1) % p->nblocks;
    for (int i = 0; i < 4; i++)
        if (p->wpos[i] == p->rpos) {
            p->wpos[i] = (p->rpos + 1) % p->nblocks;
            p->underruns++;
        }
    if (p->pending_vol != p->cur_vol)
        pcm_set_avol(p->pending_vol);
    p->irqs++;
}

static void pcm_free(void)
{
    snd_pcm *p = &g_snd->pcm;
    free(p->ring);
    free(p->dma);
    uint32_t pv = p->pending_vol;
    memset(p, 0, sizeof *p);
    p->pending_vol = pv;
}

static int32_t pcm_call(uint32_t fno, const uint32_t *d, uint32_t n)
{
    snd_pcm *p = &g_snd->pcm;
    uint32_t a0 = n > 0 ? d[0] : 0, a1 = n > 1 ? d[1] : 0, a2 = n > 2 ? d[2] : 0, a3 = n > 3 ? d[3] : 0;
    switch (fno & 0xFFF0) {
    case 0x8000: { /* init (core, blockBytes, nBlocks) */
        if (a0 > 1 || a1 < 2048 || a2 < 2)
            return -1;
        if (p->running) {
            p->running = 0;
            adma_bind(p->core);
        }
        pcm_free();
        p->core = (int)a0;
        p->block_bytes = a1 & ~1023u;
        p->nblocks = a2;
        p->ring = (int16_t *)calloc(p->nblocks, p->block_bytes);
        p->dma = (int16_t *)calloc(2, p->block_bytes);
        if (!p->ring || !p->dma) {
            pcm_free();
            return -1;
        }
        for (int i = 0; i < 4; i++)
            p->wpos[i] = 1 % p->nblocks;
        p->rpos = 0;
        p->inited = 1;
        return 0;
    }
    case 0x8090: { /* mix (port, srcIop, volL, volR) */
        if (!p->inited || a0 > 3)
            return -1;
        if ((p->wpos[a0] + p->nblocks - p->rpos) % p->nblocks == 0)
            return 0;
        const uint8_t *src = (const uint8_t *)iop_ptr(a1, p->block_bytes);
        if (!src)
            return -1;
        int16_t *dst = p->ring + (size_t)p->wpos[a0] * (p->block_bytes / 2);
        int32_t vl = (int32_t)a2, vr = (int32_t)a3;
        for (uint32_t i = 0; i < p->block_bytes / 2; i++) {
            int32_t sv = (int16_t)(src[2 * i] | src[2 * i + 1] << 8);
            int32_t vol = ((i >> 8) & 1) ? vr : vl; /* [256 L][256 R] pairs */
            int32_t m = dst[i] + ((sv * vol) >> 15);
            dst[i] = (int16_t)(m < -32768 ? -32768 : m > 32767 ? 32767 : m);
        }
        p->wpos[a0] = (p->wpos[a0] + 1) % p->nblocks;
        p->mixed_blocks++;
        return 1;
    }
    case 0x80A0: /* free distance */
        if (!p->inited || a0 > 3)
            return -1;
        return (int32_t)((p->wpos[a0] + p->nblocks - p->rpos) % p->nblocks);
    case 0x8100: /* output start */
        if (!p->inited)
            return -1;
        if (!p->running) {
            memset(p->dma, 0, (size_t)p->block_bytes * 2);
            p->play_half = 0;
            p->play_pos = 0;
            p->running = 1;
            pcm_set_avol(p->pending_vol);
            adma_bind(p->core);
        }
        return 0;
    case 0x8400: /* output stop */
        if (!p->running)
            return 1;
        p->running = 0;
        pcm_set_avol(0);
        adma_bind(p->core);
        return 0;
    case 0x0010: /* shutdown */
        if (p->running) {
            p->running = 0;
            adma_bind(p->core);
        }
        pcm_free();
        return 0;
    case 0x0200: p->pending_vol = a0; return 0;
    case 0x0300:
        p->pending_vol = a0;
        if (p->inited)
            pcm_set_avol(a0);
        return 0;
    case 0x8080: return 0;
    default: note_unknown("pcm_mixer fno", fno, a0); return -1;
    }
}

static void *srv_pcm(sif_rpc_ctx *c, void *user)
{
    (void)user;
    snd_sync();
    g_snd->stats.pcm_calls++;
    uint32_t d[16] = {0};
    uint32_t n = c->size / 4 > 16 ? 16 : c->size / 4;
    memcpy(d, c->data, n * 4);
    memset(g_reply, 0, 0x40);
    g_reply[0] = (uint32_t)pcm_call(c->fno, d, n);
    return c->rsize <= sizeof g_reply ? g_reply : NULL;
}

/* ---- sdr_driver: libsd calls (section 1) ------------------------------------------------------- */
/* BlockTransStatus: the DMA's IOP address (the next unit to transfer, two units
 * ahead of the one being played) and whether it is in the second half of the ring. */
static uint32_t movie_status(int core)
{
    const snd_movie *m = &g_snd->movie[core & 1];
    uint32_t half = (m->size && m->xfer >= m->size / 2) ? 1u : 0u;
    return (half << 24) | ((m->base + m->xfer) & 0xFFFFFFu);
}

static int32_t block_trans(int ch, uint32_t mode, uint32_t iop, uint32_t size, uint32_t start)
{
    int core = ch & 1;
    snd_movie *m = &g_snd->movie[core];
    uint32_t op = mode & 3;
    if (op == 2) { /* STOP: reply in the BlockTransStatus form */
        uint32_t r = movie_status(core);
        m->running = 0;
        adma_bind(core);
        return (int32_t)r;
    }
    if (op == 1) /* READ (SPU output -> IOP) is not modelled */
        return 0;
    m->base = iop;
    m->size = size & ~1023u;
    if (!m->size)
        return -1;
    m->unit = 0;
    if (op == 3 && start >= iop && start < iop + m->size)
        m->unit = (start - iop) & ~1023u;
    m->k = 0;
    m->loop = (mode & 0x10) != 0;
    m->running = 1;
    m->frames = 0;
    m->xfer = m->unit;
    m->xfer_done = 0;
    m->play = 0;
    movie_xfer(m, 0); /* the start fills both halves of the input buffer */
    movie_xfer(m, 1);
    adma_bind(core);
    return 0;
}

static int32_t voice_trans(int ch, uint32_t mode, uint32_t iop, uint32_t spu, uint32_t size)
{
    (void)ch;
    if ((mode & 3) == 1) { /* READ: SPU -> IOP */
        uint8_t *dst = (uint8_t *)iop_ptr(iop, size);
        if (!dst)
            return -1;
        spu2_ram_read(&g_snd->spu, spu, dst, size);
        return (int32_t)size;
    }
    const uint8_t *src = (const uint8_t *)iop_ptr(iop, size);
    if (!src)
        return -1;
    spu2_ram_write(&g_snd->spu, spu, src, size);
    g_snd->stats.bank_uploads++;
    g_snd->stats.bank_bytes += size;
    return (int32_t)size;
}

static int32_t sk_dispatch(const uint32_t *w, uint32_t nwords);

/* $RG_SND_LOG=path: a validation log (docs/SOUND.md "Validation"): one line per
 * sdr_driver call (output frame, fno, words 1..6, result) and one KON line per
 * synth voice key on (snd_synth.c). The movie position poll 0x8100 is left out
 * unless $RG_SND_LOG_ALL is set. */
FILE *snd_log_file(void)
{
    static FILE *f;
    static int state; /* 0 unknown, 1 on, -1 off */
    if (state == 0) {
        const char *p = getenv("RG_SND_LOG");
        f = p && *p ? fopen(p, "w") : NULL;
        state = f ? 1 : -1;
        if (f)
            fprintf(f, "# frame\tfno\tw1..w6 (w1..w11 for 0x90F0)\tresult\n");
    }
    return f;
}

static void sdr_log(uint32_t fno, const uint32_t *d, uint32_t nw, int32_t r)
{
    FILE *f = snd_log_file();
    if (!f || ((fno & 0xFFF0) == 0x8100 && !getenv("RG_SND_LOG_ALL")))
        return;
    fprintf(f, "%llu\t%04X", (unsigned long long)g_snd->rendered, fno);
    uint32_t last = (fno & 0xFFF0) == 0x90F0 ? 11 : 6; /* SK blocks: w1..w11 */
    for (uint32_t i = 1; i <= last; i++)
        fprintf(f, "\t%X", i < nw ? d[i] : 0u);
    fprintf(f, "\t%d\n", r);
    fflush(f);
}

static void *srv_sdr(sif_rpc_ctx *c, void *user)
{
    (void)user;
    snd_sync();
    g_snd->stats.sdr_calls++;
    spu2 *s = &g_snd->spu;
    uint32_t d[16] = {0};
    uint32_t nw = c->size / 4 > 16 ? 16 : c->size / 4;
    memcpy(d, c->data, nw * 4);
    const uint8_t *db = (const uint8_t *)c->data;
    uint32_t fno = c->fno;
    int32_t r = 0;
    memset(g_reply, 0, 0x40);
    /* d+4 = a1, d+8 = a2, ... (word 0 is the EE buffer's own address) */
    uint16_t h1 = (uint16_t)d[1], h2 = (uint16_t)d[2];
    switch (fno & 0xFFF0) {
    case 0x8000: { /* sceSdInit: registers and voices; sound RAM is kept */
        int interp = s->interp;
        uint8_t *save = (uint8_t *)malloc(SPU2_RAM_SIZE);
        if (save)
            memcpy(save, s->ram, SPU2_RAM_SIZE);
        spu2_reset(s);
        spu2_set_interp(s, interp);
        if (save) {
            memcpy(s->ram, save, SPU2_RAM_SIZE);
            free(save);
        }
        synth_reset();
        adma_bind(0);
        adma_bind(1);
        break;
    }
    case 0x8010: spu2_set_param(s, h1, h2); break;
    case 0x8020: r = spu2_get_param(s, h1); break;
    case 0x8030: spu2_set_switch(s, h1, d[2]); break;
    case 0x8040: r = (int32_t)spu2_get_switch(s, h1); break;
    case 0x8050: spu2_set_addr(s, h1, d[2]); break;
    case 0x8060: r = (int32_t)spu2_get_addr(s, h1); break;
    case 0x8070: spu2_set_core_attr(s, h1, h2); break;
    case 0x8080: r = (int32_t)spu2_get_core_attr(s, h1); break;
    case 0x8090: r = spu2_note2pitch(h1, h2, (uint16_t)d[3], (int16_t)d[4]); break;
    case 0x80A0: r = spu2_pitch2note(h1, h2, (uint16_t)d[3]); break;
    case 0x80D0: r = voice_trans((int16_t)d[1], h2, d[3], d[4], d[5]); break;
    case 0x80E0: r = block_trans((int16_t)d[1], h2, d[3], d[4], d[5]); break;
    case 0x80F0: r = 1; break; /* VoiceTransStatus: transfers complete at once */
    case 0x8100: r = (int32_t)movie_status((int16_t)d[1]); break;
    case 0x8130: { /* SetEffectAttr: core = fno & 0xF, d = sceSdEffectAttr
                    * {int core, int mode, s16 depth L, s16 depth R, int delay, int feedback}:
                    * the layout the game builds (SoundThreadCmdSetReverbMode_1b66b0 stores mode
                    * as a word at +4, the depths as halfwords at +8/+10; docs/NATIVE-AUDIO.md) */
        int core = (int)(fno & 1);
        int mode = (int)d[1];
        int16_t dl = (int16_t)(db[8] | db[9] << 8), dr = (int16_t)(db[10] | db[11] << 8);
        spu2_set_effect_attr(s, core, mode, dl, dr, (int32_t)d[3], (int32_t)d[4]);
        break;
    }
    case 0x8140: { /* GetEffectAttr -> 0x40-byte attr struct */
        int core = (int)(fno & 1);
        const spu2_reverb *rv = &s->core[core].rev;
        uint16_t *h = (uint16_t *)g_reply;
        g_reply[0] = (uint32_t)core;
        g_reply[1] = (uint32_t)rv->mode;
        h[4] = (uint16_t)rv->depth_l;
        h[5] = (uint16_t)rv->depth_r;
        g_reply[3] = (uint32_t)rv->delay;
        g_reply[4] = (uint32_t)rv->feedback;
        return c->rsize <= sizeof g_reply ? g_reply : NULL;
    }
    case 0x8150: case 0x8190: spu2_clear_effect_area(s, (int)(d[1] & 1)); break;
    case 0x8160: if (d[1] < 2) g_snd->sdr_trans_handler[d[1]] = d[2]; break;
    case 0x8170: g_snd->sdr_spu2_handler = d[1]; break;
    case 0x8180: /* StopTrans */
        g_snd->movie[d[1] & 1].running = 0;
        adma_bind((int)(d[1] & 1));
        break;
    case 0x8F10: case 0xE620: case 0xE630: break;
    case 0x9000: case 0x9010: case 0x9020: case 0x9030: case 0x9040: case 0x9050: case 0x9060:
    case 0x9070: case 0x9080: case 0x9090: case 0x90A0: case 0x90B0: case 0x90C0: case 0x90D0:
    case 0x90E0:
        r = 0; /* no user command registered */
        break;
    case 0x90F0: r = sk_dispatch(d, nw); break;
    default: note_unknown("sdr_driver fno", fno, d[1]); r = 0; break;
    }
    sdr_log(fno, d, nw, r);
    g_reply[0] = (uint32_t)r;
    return c->rsize <= sizeof g_reply ? g_reply : NULL;
}

/* ---- Standard Kit blocks (section 2) --------------------------------------------------------------- */
static int track_ok(int32_t t) { return t >= 0 && t < SND_TRACKS; }

static int32_t sk_sound(const uint32_t *w)
{
    spu2 *s = &g_snd->spu;
    switch (w[1]) {
    case 0: case 1: return 0;
    case 2: { /* ctl(w2, w3, w4, w5, w6) */
        uint32_t a = w[4], b = w[5], f = w[6];
        switch (w[3]) {
        case 0x80: /* core 1 master volume: SKSOUND's (x * 129) & 0x7FFF, wrap included */
            spu2_set_param(s, (SPU2_P_MVOLL << 8) | 0x81, (uint16_t)((a * 129u) & 0x7FFF));
            spu2_set_param(s, (SPU2_P_MVOLR << 8) | 0x81, (uint16_t)((b * 129u) & 0x7FFF));
            return 0;
        case 0x81:
            spu2_set_core_attr(s, SPU2_C_MUTE_ENABLE | 0, a);
            spu2_set_core_attr(s, SPU2_C_MUTE_ENABLE | 1, a);
            return 0;
        case 0x82:
            spu2_set_core_attr(s, SPU2_C_EFFECT_ENABLE | 0, a);
            spu2_set_core_attr(s, SPU2_C_EFFECT_ENABLE | 1, a);
            return 0;
        case 0x83:
            spu2_set_effect_attr(s, 0, (int)a, 0, 0, (int32_t)b, (int32_t)f);
            spu2_set_effect_attr(s, 1, (int)a, 0, 0, (int32_t)b, (int32_t)f);
            return 0;
        case 0x84:
            for (int c = 0; c < 2; c++) {
                spu2_set_param(s, (SPU2_P_EVOLL << 8) | 0x80 | (uint32_t)c, (uint16_t)(a * 0x7FFFu / 127u));
                spu2_set_param(s, (SPU2_P_EVOLR << 8) | 0x80 | (uint32_t)c, (uint16_t)(b * 0x7FFFu / 127u));
            }
            return 0;
        case 0x8F:
            spu2_set_core_attr(s, SPU2_C_SPDIF_MODE, a);
            return 0;
        case 1: g_snd->sk_timer_on = 1; return 0;
        case 2: g_snd->sk_timer_on = 0; return 0;
        default: note_unknown("SKSOUND ctl", w[3], a); return 0;
        }
    }
    case 3: return w[2] == 0 ? (int32_t)g_snd->sk_ticks : SK_E_CMD;
    case 0xA: /* VoiceTrans(ch w2, WRITE, iop w3, spu w4, size w5) + wait */
        return voice_trans((int)w[2], 0, w[3], w[4], w[5]);
    default: note_unknown("SKSOUND sub", w[1], w[2]); return SK_E_CMD;
    }
}

static void bank_clear(snd_bank *b, int what)
{
    if (what & 1) {
        free(b->hd);
        b->hd = NULL;
        b->hd_iop = b->hd_size = 0;
        b->parsed_ok = 0;
        b->flags &= ~1;
    }
    if (what & 2) {
        b->bd_spu = b->bd_size = 0;
        b->flags &= ~2;
    }
}

static int bank_take_hd(snd_bank *b, uint32_t iop, uint32_t size)
{
    bank_clear(b, 1);
    b->hd_iop = iop;
    b->flags |= 1;
    if (!size) /* empty HD: the entry exists but plays nothing */
        return 0;
    const uint8_t *p = (const uint8_t *)iop_ptr(iop, size);
    if (!p)
        return -1;
    b->hd = (uint8_t *)malloc(size);
    if (!b->hd)
        return -1;
    memcpy(b->hd, p, size);
    b->hd_size = size;
    b->parsed_ok = snd_hd_parse(&b->parsed, b->hd, size) == 0;
    return 0;
}

static int32_t sk_hsynth(const uint32_t *w)
{
    int32_t a2 = (int32_t)w[2];
    switch (w[1]) {
    case 0:
        if (a2 >= 1 && a2 <= 3) { /* fill HD / BD / both */
            int32_t id = (int32_t)w[3];
            if (id == -1) {
                for (int i = 0; i < SND_BANKS && id < 0; i++)
                    if (g_snd->bank[i].flags == 0)
                        id = i;
            }
            if (id < 0 || id >= SND_BANKS)
                return SK_E_INDEX;
            snd_bank *b = &g_snd->bank[id];
            if (a2 == 1) {
                if (bank_take_hd(b, w[4], w[5]) < 0)
                    return SK_E_LIB;
            } else if (a2 == 2) {
                b->bd_spu = w[4];
                b->bd_size = w[5];
                b->flags |= 2;
            } else {
                if (bank_take_hd(b, w[4], w[5]) < 0)
                    return SK_E_LIB;
                b->bd_spu = w[6];
                b->bd_size = w[7];
                b->flags |= 2;
            }
            return id;
        }
        if (a2 == 5) { /* attach (track, entry, slot) */
            int32_t t = (int32_t)w[3], e = (int32_t)w[4], slot = (int32_t)w[5];
            if (t == -1) {
                for (int i = 0; i < SND_TRACKS && t < 0; i++)
                    if ((g_snd->track[i].status & 3) == 0)
                        t = i;
            }
            if (!track_ok(t) || slot < 0 || slot >= SND_SLOTS)
                return SK_E_STATE;
            if (e < 0 || e >= SND_BANKS || g_snd->bank[e].flags != 3)
                return SK_E_NOENTRY;
            if (!g_snd->bank[e].parsed_ok) /* attached but silent (logged) */
                note_unknown("SKHSYNTH attach of an unparsable HD, entry", (uint32_t)e, g_snd->bank[e].hd_size);
            g_snd->track[t].slot_bank[slot] = e;
            g_snd->track[t].status |= 2;
            return t;
        }
        return SK_E_CMD;
    case 1:
        if (a2 >= 1 && a2 <= 3) {
            int32_t e = (int32_t)w[3];
            if (e < 0 || e >= SND_BANKS)
                return SK_E_INDEX;
            bank_clear(&g_snd->bank[e], a2);
            return 0;
        }
        if (a2 == 5) {
            int32_t t = (int32_t)w[3];
            if (!track_ok(t))
                return SK_E_STATE;
            synth_all_off(t, 1, 0);
            for (int i = 0; i < SND_SLOTS; i++)
                g_snd->track[t].slot_bank[i] = -1;
            g_snd->track[t].status &= ~2;
            return 0;
        }
        return SK_E_CMD;
    case 2: { /* (track, cmd, v, v2) */
        int32_t t = a2;
        switch (w[3]) {
        case 0x1E: if (track_ok(t)) synth_all_off(t, 0, 0); return 0;
        case 0x1F: if (track_ok(t)) synth_all_off(t, 1, 0); return 0;
        case 0x71: g_snd->mono = w[4] != 0; return 0;
        case 0x70: g_snd->modhsyn_8[0] = w[4]; g_snd->modhsyn_8[1] = w[5]; return 0;
        case 0: case 1: case 2:
            if (track_ok(t)) {
                g_snd->track[t].flag2 = (uint8_t)w[4];
                g_snd->track[t].flag3 = (uint8_t)w[5];
            }
            return 0;
        default: note_unknown("SKHSYNTH ctl", w[3], w[4]); return SK_E_CMD;
        }
    }
    case 3:
        switch (w[3]) {
        case 0x72: return synth_count_bank_voices((int32_t)w[4]);
        case 0x70: case 0x71: return 0;
        default: return SK_E_CMD;
        }
    default: note_unknown("SKHSYNTH sub", w[1], w[2]); return SK_E_CMD;
    }
}

static int first_input_track(void)
{
    for (int i = 0; i < SND_TRACKS; i++)
        if (g_snd->track[i].status == 0)
            return i;
    return -1;
}

static void track_detach_input(int t)
{
    snd_track *tr = &g_snd->track[t];
    if (tr->in_type == 0 && tr->port >= 0) {
        snd_player *p = &g_snd->port[tr->port];
        p->playing = 0;
        p->used = 0;
        synth_all_off(t, 0, 1);
    }
    tr->port = -1;
    tr->status &= ~1;
    tr->in_entry = -1;
}

static int32_t sk_midi(const uint32_t *w)
{
    int32_t a2 = (int32_t)w[2];
    switch (w[1]) {
    case 0:
        if (a2 == 0) { /* register (id, sqIop, size) */
            int32_t id = (int32_t)w[3];
            if (id == -1)
                for (int i = 0; i < SND_SQ_ENTRIES && id < 0; i++)
                    if (!g_snd->sq[i].used)
                        id = i;
            if (id < 0 || id >= SND_SQ_ENTRIES)
                return SK_E_INDEX;
            snd_sqdata *q = &g_snd->sq[id];
            const uint8_t *p = (const uint8_t *)iop_ptr(w[4], w[5]);
            if (!p || !w[5])
                return SK_E_LIB;
            free(q->data);
            q->data = (uint8_t *)malloc(w[5]);
            if (!q->data)
                return SK_E_LIB;
            memcpy(q->data, p, w[5]);
            q->iop = w[4];
            q->size = w[5];
            q->used = 1;
            return id;
        }
        if (a2 == 5) { /* attach (track, entry) */
            int32_t t = (int32_t)w[3], e = (int32_t)w[4];
            if (t == -1)
                t = first_input_track();
            if (!track_ok(t))
                return SK_E_STATE;
            if (g_snd->track[t].status & 1)
                return SK_E_BUSY;
            if (e < 0 || e >= SND_SQ_ENTRIES || !g_snd->sq[e].used)
                return SK_E_NOENTRY;
            int port = -1;
            for (int i = 0; i < SND_MIDI_PORTS && port < 0; i++)
                if (!g_snd->port[i].used)
                    port = i;
            if (port < 0)
                return SK_E_INDEX;
            snd_player *p = &g_snd->port[port];
            memset(p, 0, sizeof *p);
            p->used = 1;
            p->track = t;
            p->entry = e;
            p->speed = 0x100;
            if (seq_select(p, g_snd->sq[e].data, g_snd->sq[e].size, 0) < 0)
                p->d = NULL;
            snd_track *tr = &g_snd->track[t];
            tr->in_entry = e;
            tr->in_type = 0;
            tr->port = port;
            tr->status |= 1;
            tr->flag2 = tr->flag3 = 0;
            for (int c = 0; c < 16; c++)
                synth_channel_reset(&tr->ch[c]);
            return t;
        }
        return SK_E_CMD;
    case 1:
        if (a2 == 0) {
            int32_t id = (int32_t)w[3];
            if (id < 0 || id >= SND_SQ_ENTRIES)
                return SK_E_INDEX;
            for (int t = 0; t < SND_TRACKS; t++)
                if ((g_snd->track[t].status & 1) && g_snd->track[t].in_type == 0 && g_snd->track[t].in_entry == id)
                    track_detach_input(t);
            free(g_snd->sq[id].data);
            memset(&g_snd->sq[id], 0, sizeof g_snd->sq[id]);
            return 0;
        }
        if (a2 == 5) {
            int32_t t = (int32_t)w[3];
            if (!track_ok(t))
                return SK_E_STATE;
            if ((g_snd->track[t].status & 1) && g_snd->track[t].in_type == 0)
                track_detach_input(t);
            return 0;
        }
        return SK_E_CMD;
    case 2: { /* (track, cmd, mode, v) */
        int32_t t = a2;
        if (!track_ok(t) || (g_snd->track[t].status & 3) != 3 || g_snd->track[t].in_type != 0 ||
            g_snd->track[t].port < 0)
            return SK_E_STATE;
        snd_player *p = &g_snd->port[g_snd->track[t].port];
        uint32_t v = w[5];
        switch (w[3]) {
        case 0: /* play: rewind if it ended, SelectMidi(v), PlaySwitch(1) */
            if (p->playing)
                return 0;
            if (seq_select(p, g_snd->sq[p->entry].data, g_snd->sq[p->entry].size, (int)v) < 0) {
                if (!p->d)
                    return SK_E_LIB;
                if (p->ended)
                    seq_rewind(p);
            }
            p->playing = p->d != NULL;
            return 0;
        case 2: /* stop: PlaySwitch off + rewind */
            p->playing = 0;
            synth_all_off(t, 0, 1);
            if (p->d)
                seq_rewind(p);
            return 0;
        case 3: /* pause */
            p->playing = 0;
            synth_all_off(t, 0, 1);
            return 0;
        case 0x30:
            g_snd->track[t].seq_vol = (int)(v & 0xFF);
            synth_track_changed(t);
            return 0;
        case 0x31: /* absolute tempo (BPM) */
            if ((v & 0xFF) != 0)
                p->tempo = 60000000u / (v & 0xFF);
            return 0;
        case 0x32: /* relative tempo, 0x100 = 1.0 (L) */
            p->speed = v & 0xFFFF;
            return 0;
        default: note_unknown("SKMIDI cmd", w[3], v); return SK_E_CMD;
        }
    }
    case 3: {
        int32_t t = a2;
        if (!track_ok(t) || g_snd->track[t].port < 0)
            return SK_E_STATE;
        const snd_player *p = &g_snd->port[g_snd->track[t].port];
        uint32_t st = (p->playing ? 2u : 0u) | (p->ended ? 4u : 0u);
        switch (w[3]) {
        case 0: return (int32_t)(st & 2);
        case 1: return (int32_t)(st & 4);
        case 8: return (int32_t)st;
        default: return SK_E_CMD;
        }
    }
    default: note_unknown("SKMIDI sub", w[1], w[2]); return SK_E_CMD;
    }
}

static int32_t sk_msin(const uint32_t *w)
{
    int32_t a2 = (int32_t)w[2];
    switch (w[1]) {
    case 0:
        if (a2 == 0 || a2 == 2) {
            int32_t id = (int32_t)w[3];
            if (id == -1)
                for (int i = 0; i < SND_MSIN_ENTRIES && id < 0; i++)
                    if (!g_snd->msin_used[i])
                        id = i;
            if (id < 0 || id >= SND_MSIN_ENTRIES)
                return SK_E_INDEX;
            g_snd->msin_used[id] = 1;
            return id;
        }
        if (a2 == 5) {
            int32_t t = (int32_t)w[3], e = (int32_t)w[4];
            if (t == -1)
                t = first_input_track();
            if (!track_ok(t))
                return SK_E_STATE;
            if (g_snd->track[t].status & 1)
                return SK_E_BUSY;
            if (e < 0 || e >= SND_MSIN_ENTRIES || !g_snd->msin_used[e])
                return SK_E_NOENTRY;
            snd_track *tr = &g_snd->track[t];
            tr->in_entry = e;
            tr->in_type = 2;
            tr->port = -1;
            tr->status |= 1;
            tr->flag2 = tr->flag3 = 0;
            for (int c = 0; c < 16; c++)
                synth_channel_reset(&tr->ch[c]);
            return t;
        }
        return SK_E_CMD;
    case 1:
        if (a2 == 0 || a2 == 2) {
            int32_t id = (int32_t)w[3];
            if (id < 0 || id >= SND_MSIN_ENTRIES)
                return SK_E_INDEX;
            g_snd->msin_used[id] = 0;
            return 0;
        }
        if (a2 == 5) {
            int32_t t = (int32_t)w[3];
            if (!track_ok(t))
                return SK_E_STATE;
            if ((g_snd->track[t].status & 1) && g_snd->track[t].in_type == 2) {
                synth_all_off(t, 0, 0);
                track_detach_input(t);
            }
            return 0;
        }
        return SK_E_CMD;
    case 2: {
        int32_t t = a2;
        if (!track_ok(t) || (g_snd->track[t].status & 3) != 3 || g_snd->track[t].in_type != 2)
            return SK_E_STATE;
        uint32_t cmd = w[3];
        switch (cmd) {
        case 0x10: case 0x11: case 0x12: case 0x13: {
            /* 0x11/0x13: (id, bank, prog, ch, note, vel, x); 0x10/0x12 carry no id */
            int has_id = cmd & 1;
            const uint32_t *a = w + 4;
            int id;
            if (has_id) {
                id = (int)(a[0] & 0xFF);
                a++;
            } else {
                id = g_snd->msin_counter;
                g_snd->msin_counter = (g_snd->msin_counter + 1) % 127;
            }
            int bank = (int)(a[0] & 0x7F), prog = (int)(a[1] & 0x7F), ch = (int)(a[2] & 0xF);
            int note = (int)(a[3] & 0x7F), vel = (int)(a[4] & 0x7F);
            if (cmd >= 0x12) { /* key off: only the FD 10 message, velocity 0 */
                synth_note_off(t, ch, note, id, 0);
                return id;
            }
            synth_cc(t, ch, 0, bank);   /* B0|ch 00 bank */
            synth_prog(t, ch, prog);    /* C0|ch prog */
            /* F9 01 ch x: the next key on's pan (MODHSYN channel +48 -> voice +86, x - 64) */
            synth_next(t, ch, 1, (int)(a[5] & 0x7F));
            synth_note_on(t, ch, note, vel, id, 0); /* FD 10 ch note id vel */
            if (vel)
                g_snd->track[t].msin_status |= 0x40010u;
            return id;
        }
        case 0x40: case 0x41: case 0x42: { /* (id, ch, note, v) */
            int id = (int)(w[4] & 0xFF), ch = (int)(w[5] & 0xF), note = (int)(w[6] & 0x7F);
            uint32_t v = w[7];
            if (cmd == 0x40)
                synth_voice_ctl(t, ch, note, id, 1, (int)(v & 0x7F));
            else if (cmd == 0x41)
                synth_voice_ctl(t, ch, note, id, 2, (int)(v & 0x3FFF));
            else
                synth_voice_ctl(t, ch, note, id, 0, (int)(v & 0x7F));
            return 0;
        }
        default: note_unknown("SKMSIN cmd", cmd, w[4]); return SK_E_CMD;
        }
    }
    case 3:
        if (w[3] == 0x11) { /* voice state of an SE id: 0x10 while one of its voices sounds */
            for (int hv = 0; hv < SND_HWVOICES; hv++) {
                const snd_vtag *vt = &g_snd->vt[hv];
                if (vt->used && vt->track == a2 && !vt->seq && vt->id == (int)(w[4] & 0xFF) &&
                    spu2_voice_active(&g_snd->spu, hv / SPU2_NVOICES, hv % SPU2_NVOICES))
                    return 0x10;
            }
            return 0;
        }
        return SK_E_CMD;
    default: note_unknown("SKMSIN sub", w[1], w[2]); return SK_E_CMD;
    }
}

static int32_t sk_dispatch(const uint32_t *w, uint32_t nwords)
{
    (void)nwords;
    g_snd->stats.sk_calls++;
    switch ((w[0] >> 24) & 0x7F) {
    case 0: return sk_sound(w);
    case 1: return sk_hsynth(w);
    case 2: return sk_midi(w);
    case 3: return sk_msin(w);
    default: return SK_E_CMD; /* no module registered at that index */
    }
}

/* ---- lifecycle --------------------------------------------------------------------------------------- */
void snd_default_config(snd_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->interp = SPU2_INTERP_BSPLINE;
    cfg->fifo_frames = 96000;
}

void snd_reset(void)
{
    snd_state *s = g_snd;
    for (int i = 0; i < SND_BANKS; i++)
        free(s->bank[i].hd);
    for (int i = 0; i < SND_SQ_ENTRIES; i++)
        free(s->sq[i].data);
    free(s->pcm.ring);
    free(s->pcm.dma);
    free(s->fifo);
    snd_config cfg = s->cfg;
    memset(s, 0, sizeof *s);
    s->cfg = cfg;
    if (!s->cfg.fifo_frames)
        s->cfg.fifo_frames = 96000;
    s->spu.interp = cfg.interp;
    spu2_reset(&s->spu);
    s->fifo_cap = s->cfg.fifo_frames;
    s->fifo = (int16_t *)calloc(s->fifo_cap, 4);
    for (int t = 0; t < SND_TRACKS; t++) {
        snd_track *tr = &s->track[t];
        for (int i = 0; i < SND_SLOTS; i++)
            tr->slot_bank[i] = -1;
        tr->in_entry = -1;
        tr->port = -1;
        tr->seq_vol = 0x80;
        for (int c = 0; c < 16; c++)
            synth_channel_reset(&tr->ch[c]);
    }
    s->pcm.pending_vol = 0x7FFF7FFFu;
    synth_reset();
    seq_reset();
}

int snd_install(const snd_config *cfg)
{
    RG_IOP_HLE("snd_install");
    snd_config c;
    if (!cfg) {
        snd_default_config(&c);
        cfg = &c;
    }
    g_snd->cfg = *cfg;
    snd_reset();
    snd_set_clock(clock_sif, NULL);
    int r = sif_server_register(SDR_SID, "sdr_driver", 0x400, srv_sdr, NULL);
    r |= sif_server_register(PCM_SID, "pcm_mixer", 0x40, srv_pcm, NULL);
    return r;
}

/* ---- RPC front ends (tools/tests) ------------------------------------------------------------------- */
static int32_t call(uint32_t sid, uint32_t fno, const void *send, uint32_t ssize)
{
    uint32_t recv[16] = {0};
    sif_call c;
    memset(&c, 0, sizeof c);
    c.sid = sid;
    c.fno = fno;
    c.send = send;
    c.ssize = ssize;
    c.recv = recv;
    c.rsize = 0x10;
    uint32_t tk = sif_rpc_call(&c);
    while (tk && sif_rpc_busy(tk)) {
        if (sif_deliver_all() == 0)
            break;
    }
    return (int32_t)recv[0];
}

int32_t snd_sdremote(uint32_t cmd, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6)
{
    uint32_t buf[16] = {0};
    buf[0] = 0x48D900u; /* the EE buffer's own address (ignored) */
    buf[1] = a1; buf[2] = a2; buf[3] = a3; buf[4] = a4; buf[5] = a5; buf[6] = a6;
    if (cmd == 0x8130u || cmd == 0x81A0u || cmd == 0x81B0u)
        return call(SDR_SID, cmd | a1, (const void *)(uintptr_t)a2, 0x40);
    return call(SDR_SID, cmd, buf, 0x40);
}

int32_t snd_sk(const uint32_t blk[16]) { return call(SDR_SID, 0x90F0, blk, 0x40); }

int32_t snd_pcm_rpc(uint32_t fno, int n, const uint32_t *args)
{
    uint32_t buf[16] = {0};
    for (int i = 0; i < n && i < 15; i++)
        buf[i] = args[i];
    return call(PCM_SID, fno, buf, 0x40);
}

/* ---- introspection ------------------------------------------------------------------------------------- */
int snd_voices_playing(void)
{
    int n = 0;
    for (int c = 0; c < SPU2_NCORES; c++)
        for (int v = 0; v < SPU2_NVOICES; v++)
            n += spu2_voice_active(&g_snd->spu, c, v);
    return n;
}

int snd_track_status(int track) { return track_ok(track) ? g_snd->track[track].status : -1; }

int snd_midi_playing(int track)
{
    if (!track_ok(track) || g_snd->track[track].port < 0)
        return 0;
    return g_snd->port[g_snd->track[track].port].playing;
}

uint32_t snd_midi_ticks(int track)
{
    if (!track_ok(track) || g_snd->track[track].port < 0)
        return 0;
    return g_snd->port[g_snd->track[track].port].ticks;
}

uint32_t snd_movie_position(int core) { return g_snd->movie[core & 1].unit; }
