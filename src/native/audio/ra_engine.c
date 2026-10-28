/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine: state, clock and output, banks, sequences, SE input, tracks,
 * bus settings (docs/NATIVE-AUDIO.md "Engine").  The track / entry rules (first free,
 * attach checks, error codes) are the Standard Kit's (docs/SOUND-PROTOCOL.md section 2)
 * because the game keeps and checks the ids; they were carried over from the bring-up
 * HLE servers (src/ps2/iop/sound/snd_srv.c sk_hsynth / sk_midi / sk_msin). */
#include <stdlib.h>
#include <string.h>

#include "ra_internal.h"

static ra_state g_state;
ra_state *g_ra = &g_state;

static int track_ok(int t) { return t >= 0 && t < RA_TRACKS; }

/* ---- lifecycle --------------------------------------------------------------------------- */
void ra_default_config(ra_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->interp = RA_INTERP_BSPLINE;
    cfg->fifo_frames = 96000;
}

static void free_all(void)
{
    ra_state *s = g_ra;
    for (int i = 0; i < RA_BANKS; i++) {
        ra_blob_unref(s->bank[i].hd);
        ra_blob_unref(s->bank[i].bd);
    }
    for (int i = 0; i < RA_SEQS; i++)
        ra_blob_unref(s->sq[i].data);
    for (int b = 0; b < RA_BUSES; b++) {
        for (int v = 0; v < RA_BUS_VOICES; v++) {
            ra_blob_unref(s->bus[b].v[v].bd);
            s->bus[b].v[v].bd = NULL;
        }
        free(s->bus[b].rev.buf);
        s->bus[b].rev.buf = NULL;
    }
    ra_pcm_shutdown();
    for (int i = 0; i < RA_STREAM_BUFS; i++)
        free(s->sbuf[i].mem);
    free(s->fifo);
}

void ra_init(const ra_config *cfg)
{
    ra_state *s = g_ra;
    ra_config c;
    if (!cfg) {
        ra_default_config(&c);
        cfg = &c;
    }
    uint64_t (*now)(void *) = s->now;
    void *now_user = s->now_user;
    if (s->inited)
        free_all();
    memset(s, 0, sizeof *s);
    s->cfg = *cfg;
    if (!s->cfg.fifo_frames)
        s->cfg.fifo_frames = 96000;
    s->now = now;
    s->now_user = now_user;
    s->frame = now ? now(now_user) : 0;
    s->tick_origin = s->frame;
    s->fifo_cap = s->cfg.fifo_frames;
    s->fifo = (int16_t *)calloc(s->fifo_cap, 4);
    ra_mix_reset();
    for (int t = 0; t < RA_TRACKS; t++) {
        ra_track *tr = &s->track[t];
        for (int i = 0; i < RA_SLOTS; i++)
            tr->slot_bank[i] = -1;
        tr->in_entry = -1;
        tr->port = -1;
        tr->seq_vol = 0x80;
        for (int ch = 0; ch < 16; ch++)
            ra_channel_reset(&tr->ch[ch]);
    }
    s->pcm.pending_vol = 0x7FFF7FFFu;
    ra_synth_reset();
    /* the game's sound init: bus 0 master 0x3FFF, bus 1 master 0 (raised later) */
    s->bus[0].master[0] = s->bus[0].master[1] = 0x3FFF;
    s->inited = 1;
    ra_present_reset(); /* the presentation mix follows (host side, ra_present.c) */
}

void ra_shutdown(void)
{
    if (g_ra->inited)
        free_all();
    uint64_t (*now)(void *) = g_ra->now;
    void *u = g_ra->now_user;
    memset(g_ra, 0, sizeof *g_ra);
    g_ra->now = now;
    g_ra->now_user = u;
    ra_present_reset();
}

int ra_initialized(void) { return g_ra->inited; }
const ra_stats *ra_get_stats(void) { return &g_ra->st; }

/* ---- clock / render / FIFO ------------------------------------------------------------------ */
void ra_set_clock(uint64_t (*now_frames)(void *user), void *user)
{
    g_ra->now = now_frames;
    g_ra->now_user = user;
    if (now_frames && !g_ra->inited)
        g_ra->frame = now_frames(user);
}

void ra_set_tick_origin(uint64_t frame) { g_ra->tick_origin = frame; }

static void tick(void)
{
    for (int i = 0; i < RA_SEQ_PORTS; i++)
        ra_seq_tick(&g_ra->port[i]);
}

/* render `n` frames (float, may be NULL; pout: the presentation mix, may be NULL),
 * running the 240 Hz tick at its frames */
static void render(float *out, float *pout, uint32_t n)
{
    ra_state *s = g_ra;
    while (n) {
        uint64_t rel = (s->frame - s->tick_origin) % RA_TICK_FRAMES;
        uint32_t chunk = (uint32_t)(RA_TICK_FRAMES - rel);
        if (chunk > n)
            chunk = n;
        ra_mix_render(out, pout, chunk);
        if (out)
            out += chunk * 2;
        if (pout)
            pout += chunk * 2;
        n -= chunk;
        s->frame += chunk;
        s->st.frames += chunk;
        if ((s->frame - s->tick_origin) % RA_TICK_FRAMES == 0)
            tick();
    }
}

static int16_t to16(float v, uint32_t *clips)
{
    if (v >= 32767.0f) {
        if (v > 32767.5f)
            (*clips)++;
        return 32767;
    }
    if (v <= -32768.0f) {
        if (v < -32768.5f)
            (*clips)++;
        return -32768;
    }
    return (int16_t)(v < 0 ? v - 0.5f : v + 0.5f);
}

void ra_render_f(float *lr, uint32_t frames)
{
    render(lr, NULL, frames);
    if (lr)
        for (uint32_t i = 0; i < frames * 2; i++)
            lr[i] /= 32768.0f;
}

void ra_render2(int16_t *lr, int16_t *plr, uint32_t frames)
{
    float buf[2 * 256], pbuf[2 * 256];
    while (frames) {
        uint32_t n = frames > 256 ? 256 : frames;
        render(buf, plr ? pbuf : NULL, n);
        if (lr) {
            for (uint32_t i = 0; i < n * 2; i++)
                lr[i] = to16(buf[i], &g_ra->st.clips);
            lr += n * 2;
        }
        if (plr) { /* presentation: its clips are not the model's statistic */
            uint32_t pclips = 0;
            for (uint32_t i = 0; i < n * 2; i++)
                plr[i] = to16(pbuf[i], &pclips);
            plr += n * 2;
        }
        frames -= n;
    }
}

void ra_render(int16_t *lr, uint32_t frames) { ra_render2(lr, NULL, frames); }

static void fifo_push(const int16_t *lr, uint32_t n)
{
    ra_state *s = g_ra;
    if (!s->fifo || !s->fifo_cap)
        return;
    for (uint32_t i = 0; i < n; i++) {
        if (s->fifo_n == s->fifo_cap) {
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

/* $RG_AUDIO_CMDLOG: once a second, the sounding voices ("V" lines: bus*24+voice, track,
 * channel, note, id, seq, released, envelope level) */
static void voice_log(void)
{
    static uint64_t last;
    if (!ra_host_cmdlog_on() || g_ra->frame / 48000 == last)
        return;
    last = g_ra->frame / 48000;
    for (int hv = 0; hv < RA_VOICES; hv++) {
        const ra_voice *v = ra_voice_at(hv);
        if (!ra_voice_active(v))
            continue;
        int w[8] = {hv, v->track, v->ch, v->note, v->id, v->seq, v->released, v->env.level};
        ra_host_cmdlog(g_ra->frame, 'V', hv, w, 8, v->pitch);
    }
}

uint32_t ra_sync(void)
{
    ra_state *s = g_ra;
    if (!s->now || !s->inited)
        return 0;
    voice_log();
    uint64_t target = s->now(s->now_user);
    if (target <= s->frame)
        return 0;
    uint64_t todo = target - s->frame;
    uint32_t done = 0;
    int16_t buf[2 * 512], pbuf[2 * 512];
    while (todo) {
        uint32_t n = todo > 512 ? 512 : (uint32_t)todo;
        ra_render2(buf, pbuf, n);
        ra_present_fifo_push(pbuf, n); /* first: it mirrors the model FIFO's state before the push */
        fifo_push(buf, n);
        todo -= n;
        done += n;
    }
    return done;
}

uint32_t ra_output_available(void) { return g_ra->fifo_n; }
uint64_t ra_output_dropped(void) { return g_ra->fifo_dropped; }
uint64_t ra_frames_rendered(void) { return g_ra->frame; }

uint32_t ra_output_read(int16_t *lr, uint32_t max_frames) { return ra_output_read2(lr, NULL, max_frames); }

uint32_t ra_output_read2(int16_t *lr, int16_t *plr, uint32_t max_frames)
{
    ra_state *s = g_ra;
    uint32_t n = s->fifo_n < max_frames ? s->fifo_n : max_frames;
    uint32_t pn = ra_present_fifo_read(plr, n); /* first: it checks against the model FIFO */
    for (uint32_t i = 0; i < n; i++) {
        lr[2 * i] = s->fifo[2 * s->fifo_rd];
        lr[2 * i + 1] = s->fifo[2 * s->fifo_rd + 1];
        s->fifo_rd = (s->fifo_rd + 1) % s->fifo_cap;
    }
    s->fifo_n -= n;
    if (plr && pn < n) /* no presentation frames (allocation failed): the model's */
        memcpy(plr + 2 * pn, lr + 2 * pn, (size_t)(n - pn) * 4);
    return n;
}

/* every state change first renders up to the clock (sample-exact command timing) */
#define SYNC() ra_sync()

/* ---- banks ------------------------------------------------------------------------------------ */
static void bank_clear(ra_bank *b)
{
    ra_blob_unref(b->hd);
    ra_blob_unref(b->bd);
    memset(b, 0, sizeof *b);
}

int ra_bank_load(int entry, const void *hd, uint32_t hd_size, const void *bd, uint32_t bd_size)
{
    SYNC();
    if (entry == -1)
        for (int i = 0; i < RA_BANKS && entry < 0; i++)
            if (!g_ra->bank[i].used)
                entry = i;
    if (entry < 0 || entry >= RA_BANKS)
        return RA_E_INDEX;
    ra_bank *b = &g_ra->bank[entry];
    bank_clear(b);
    b->hd = ra_blob_new(hd, hd ? hd_size : 0);
    b->bd = ra_blob_new(bd, bd ? bd_size : 0);
    if (!b->hd || !b->bd) {
        bank_clear(b);
        return RA_E_LIB;
    }
    b->used = 1;
    b->parsed_ok = hd_size && ra_hd_parse(&b->parsed, b->hd->data, hd_size) == 0;
    g_ra->st.banks_loaded++;
    g_ra->st.bank_bytes += hd_size + bd_size;
    return entry;
}

int ra_bank_release(int entry)
{
    SYNC();
    if (entry < 0 || entry >= RA_BANKS)
        return RA_E_INDEX;
    bank_clear(&g_ra->bank[entry]);
    return 0;
}

int ra_bank_attach(int track, int entry, int slot)
{
    SYNC();
    if (track == -1)
        for (int i = 0; i < RA_TRACKS && track < 0; i++)
            if ((g_ra->track[i].status & 3) == 0)
                track = i;
    if (!track_ok(track) || slot < 0 || slot >= RA_SLOTS)
        return RA_E_STATE;
    if (entry < 0 || entry >= RA_BANKS || !g_ra->bank[entry].used)
        return RA_E_NOENTRY;
    g_ra->track[track].slot_bank[slot] = entry;
    g_ra->track[track].status |= 2;
    return track;
}

int ra_bank_detach(int track)
{
    SYNC();
    if (!track_ok(track))
        return RA_E_STATE;
    ra_synth_all_off(track, 1, 0);
    for (int i = 0; i < RA_SLOTS; i++)
        g_ra->track[track].slot_bank[i] = -1;
    g_ra->track[track].status &= ~2;
    return 0;
}

/* ---- inputs ------------------------------------------------------------------------------------- */
static int first_input_track(void)
{
    for (int i = 0; i < RA_TRACKS; i++)
        if (g_ra->track[i].status == 0)
            return i;
    return -1;
}

static void track_detach_input(int t)
{
    ra_track *tr = &g_ra->track[t];
    if (tr->in_type == 0 && tr->port >= 0) {
        ra_player *p = &g_ra->port[tr->port];
        p->playing = 0;
        p->used = 0;
        ra_synth_all_off(t, 0, 1);
    }
    tr->port = -1;
    tr->status &= ~1;
    tr->in_entry = -1;
}

int ra_seq_load(int id, const void *sq, uint32_t size)
{
    SYNC();
    if (id == -1)
        for (int i = 0; i < RA_SEQS && id < 0; i++)
            if (!g_ra->sq[i].used)
                id = i;
    if (id < 0 || id >= RA_SEQS)
        return RA_E_INDEX;
    if (!sq || !size)
        return RA_E_LIB;
    ra_seqdata *q = &g_ra->sq[id];
    ra_blob_unref(q->data);
    q->data = ra_blob_new(sq, size);
    if (!q->data) {
        q->used = 0;
        return RA_E_LIB;
    }
    q->used = 1;
    g_ra->st.seqs_loaded++;
    return id;
}

int ra_seq_release(int id)
{
    SYNC();
    if (id < 0 || id >= RA_SEQS)
        return RA_E_INDEX;
    for (int t = 0; t < RA_TRACKS; t++)
        if ((g_ra->track[t].status & 1) && g_ra->track[t].in_type == 0 && g_ra->track[t].in_entry == id)
            track_detach_input(t);
    ra_blob_unref(g_ra->sq[id].data);
    memset(&g_ra->sq[id], 0, sizeof g_ra->sq[id]);
    return 0;
}

int ra_seq_attach(int t, int e)
{
    SYNC();
    if (t == -1)
        t = first_input_track();
    if (!track_ok(t))
        return RA_E_STATE;
    if (g_ra->track[t].status & 1)
        return RA_E_BUSY;
    if (e < 0 || e >= RA_SEQS || !g_ra->sq[e].used)
        return RA_E_NOENTRY;
    int port = -1;
    for (int i = 0; i < RA_SEQ_PORTS && port < 0; i++)
        if (!g_ra->port[i].used)
            port = i;
    if (port < 0)
        return RA_E_INDEX;
    ra_player *p = &g_ra->port[port];
    memset(p, 0, sizeof *p);
    p->used = 1;
    p->track = t;
    p->entry = e;
    p->speed = 0x100;
    if (ra_seq_select(p, g_ra->sq[e].data->data, g_ra->sq[e].data->size, 0) < 0)
        p->d = NULL;
    ra_track *tr = &g_ra->track[t];
    tr->in_entry = e;
    tr->in_type = 0;
    tr->port = port;
    tr->status |= 1;
    for (int c = 0; c < 16; c++)
        ra_channel_reset(&tr->ch[c]);
    return t;
}

int ra_seq_detach(int t)
{
    SYNC();
    if (!track_ok(t))
        return RA_E_STATE;
    if ((g_ra->track[t].status & 1) && g_ra->track[t].in_type == 0)
        track_detach_input(t);
    return 0;
}

static ra_player *seq_port(int t)
{
    if (!track_ok(t) || (g_ra->track[t].status & 3) != 3 || g_ra->track[t].in_type != 0 || g_ra->track[t].port < 0)
        return NULL;
    return &g_ra->port[g_ra->track[t].port];
}

int ra_seq_play(int t, int block)
{
    SYNC();
    ra_player *p = seq_port(t);
    if (!p)
        return RA_E_STATE;
    if (p->playing)
        return 0;
    ra_seqdata *q = &g_ra->sq[p->entry];
    if (!q->data || ra_seq_select(p, q->data->data, q->data->size, block) < 0) {
        if (!p->d)
            return RA_E_LIB;
        if (p->ended)
            ra_seq_rewind(p);
    }
    p->playing = p->d != NULL;
    return 0;
}

int ra_seq_stop(int t)
{
    SYNC();
    ra_player *p = seq_port(t);
    if (!p)
        return RA_E_STATE;
    p->playing = 0;
    ra_synth_all_off(t, 0, 1);
    if (p->d)
        ra_seq_rewind(p);
    return 0;
}

int ra_seq_pause(int t)
{
    SYNC();
    ra_player *p = seq_port(t);
    if (!p)
        return RA_E_STATE;
    p->playing = 0;
    ra_synth_all_off(t, 0, 1);
    return 0;
}

int ra_seq_volume(int t, int v)
{
    SYNC();
    if (!seq_port(t))
        return RA_E_STATE;
    g_ra->track[t].seq_vol = v & 0xFF;
    ra_synth_track_changed(t);
    return 0;
}

int ra_seq_tempo(int t, int bpm)
{
    SYNC();
    ra_player *p = seq_port(t);
    if (!p)
        return RA_E_STATE;
    if ((bpm & 0xFF) != 0)
        p->tempo = 60000000u / (uint32_t)(bpm & 0xFF);
    return 0;
}

int ra_seq_speed(int t, int rel)
{
    SYNC();
    ra_player *p = seq_port(t);
    if (!p)
        return RA_E_STATE;
    p->speed = (uint32_t)rel & 0xFFFF;
    return 0;
}

int ra_seq_query(int t, int q)
{
    SYNC();
    if (!track_ok(t) || g_ra->track[t].port < 0)
        return RA_E_STATE;
    const ra_player *p = &g_ra->port[g_ra->track[t].port];
    int st = (p->playing ? 2 : 0) | (p->ended ? 4 : 0);
    switch (q) {
    case 0: return st & 2;
    case 1: return st & 4;
    case 8: return st;
    default: return RA_E_CMD;
    }
}

int ra_seq_playing(int t)
{
    if (!track_ok(t) || g_ra->track[t].port < 0)
        return 0;
    return g_ra->port[g_ra->track[t].port].playing;
}

int ra_se_open(int id)
{
    SYNC();
    if (id == -1)
        for (int i = 0; i < RA_SE_INPUTS && id < 0; i++)
            if (!g_ra->se_used[i])
                id = i;
    if (id < 0 || id >= RA_SE_INPUTS)
        return RA_E_INDEX;
    g_ra->se_used[id] = 1;
    return id;
}

int ra_se_release(int id)
{
    SYNC();
    if (id < 0 || id >= RA_SE_INPUTS)
        return RA_E_INDEX;
    g_ra->se_used[id] = 0;
    return 0;
}

int ra_se_attach(int t, int e)
{
    SYNC();
    if (t == -1)
        t = first_input_track();
    if (!track_ok(t))
        return RA_E_STATE;
    if (g_ra->track[t].status & 1)
        return RA_E_BUSY;
    if (e < 0 || e >= RA_SE_INPUTS || !g_ra->se_used[e])
        return RA_E_NOENTRY;
    ra_track *tr = &g_ra->track[t];
    tr->in_entry = e;
    tr->in_type = 2;
    tr->port = -1;
    tr->status |= 1;
    for (int c = 0; c < 16; c++)
        ra_channel_reset(&tr->ch[c]);
    return t;
}

int ra_se_detach(int t)
{
    SYNC();
    if (!track_ok(t))
        return RA_E_STATE;
    if ((g_ra->track[t].status & 1) && g_ra->track[t].in_type == 2) {
        ra_synth_all_off(t, 0, 0);
        track_detach_input(t);
    }
    return 0;
}

static int se_track_ok(int t)
{
    return track_ok(t) && (g_ra->track[t].status & 3) == 3 && g_ra->track[t].in_type == 2;
}

int ra_key_on(int t, int id, int slot, int prog, int ch, int note, int vel, int pan)
{
    SYNC();
    if (!se_track_ok(t))
        return RA_E_STATE;
    if (id < 0) {
        id = g_ra->se_counter;
        g_ra->se_counter = (g_ra->se_counter + 1) % 127;
    } else
        id &= 0xFF;
    ch &= 0xF;
    note &= 0x7F;
    vel &= 0x7F;
    ra_synth_cc(t, ch, 0, slot & 0x7F);    /* bank slot */
    ra_synth_prog(t, ch, prog & 0x7F);
    ra_synth_next(t, ch, 1, pan & 0x7F);   /* the next key on's pan */
    ra_synth_note_on(t, ch, note, vel, id, 0);
    return id;
}

int ra_key_off(int t, int id, int ch, int note)
{
    SYNC();
    if (!se_track_ok(t))
        return RA_E_STATE;
    if (id < 0) { /* id-less key off: the input's counter, like key on */
        id = g_ra->se_counter;
        g_ra->se_counter = (g_ra->se_counter + 1) % 127;
    } else
        id &= 0xFF;
    ra_synth_note_off(t, ch & 0xF, note & 0x7F, id, 0);
    return id;
}

int ra_note_volume(int t, int id, int ch, int note, int v)
{
    SYNC();
    if (!se_track_ok(t))
        return RA_E_STATE;
    ra_synth_voice_ctl(t, ch & 0xF, note & 0x7F, id & 0xFF, 0, v & 0x7F);
    return 0;
}

int ra_note_pan(int t, int id, int ch, int note, int v)
{
    SYNC();
    if (!se_track_ok(t))
        return RA_E_STATE;
    ra_synth_voice_ctl(t, ch & 0xF, note & 0x7F, id & 0xFF, 1, v & 0x7F);
    return 0;
}

int ra_note_bend(int t, int id, int ch, int note, int v)
{
    SYNC();
    if (!se_track_ok(t))
        return RA_E_STATE;
    ra_synth_voice_ctl(t, ch & 0xF, note & 0x7F, id & 0xFF, 2, v & 0x3FFF);
    return 0;
}

int ra_all_notes_off(int t)
{
    SYNC();
    if (track_ok(t))
        ra_synth_all_off(t, 0, 0);
    return 0;
}

int ra_all_sound_off(int t)
{
    SYNC();
    if (track_ok(t))
        ra_synth_all_off(t, 1, 0);
    return 0;
}

void ra_set_mono(int on)
{
    SYNC();
    g_ra->mono = on != 0;
}

/* ---- buses -------------------------------------------------------------------------------------- */
void ra_master_volume(uint32_t l, uint32_t r)
{
    ra_bus_master(1, (uint16_t)((l * 129u) & 0x7FFF), (uint16_t)((r * 129u) & 0x7FFF));
}

void ra_bus_master(int bus, uint16_t l, uint16_t r)
{
    SYNC();
    g_ra->bus[bus & 1].master[0] = l & 0x7FFF;
    g_ra->bus[bus & 1].master[1] = r & 0x7FFF;
}

void ra_effect_enable(int on, int input_wet)
{
    SYNC();
    for (int b = 0; b < RA_BUSES; b++) {
        g_ra->bus[b].effect_on = on != 0;
        g_ra->bus[b].in_wet = on && input_wet;
    }
}

void ra_bus_effect(int bus, int on)
{
    SYNC();
    g_ra->bus[bus & 1].effect_on = on != 0;
}

void ra_reverb_mode(int bus, int mode, int clear)
{
    SYNC();
    ra_bus *b = &g_ra->bus[bus & 1];
    ra_reverb_set(b, mode, clear);
    b->rev.depth[0] = b->rev.depth[1] = 0;
}

void ra_reverb_depth(int bus, int16_t l, int16_t r)
{
    SYNC();
    g_ra->bus[bus & 1].rev.depth[0] = l;
    g_ra->bus[bus & 1].rev.depth[1] = r;
}

void ra_bus_input_volume(int bus, int16_t l, int16_t r)
{
    SYNC();
    g_ra->bus[bus & 1].in_vol[0] = l;
    g_ra->bus[bus & 1].in_vol[1] = r;
}

/* ---- introspection ------------------------------------------------------------------------------ */
int ra_voices_playing(void)
{
    int n = 0;
    for (int hv = 0; hv < RA_VOICES; hv++)
        if (ra_voice_active(ra_voice_at(hv)))
            n++;
    return n;
}

int ra_track_status(int t) { return track_ok(t) ? g_ra->track[t].status : -1; }
