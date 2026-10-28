/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine: notes -> bank layers -> voices, MIDI channel state, per-note
 * volume/pan/bend, voice allocation.  The semantics are MODHSYN's (the Standard Kit
 * hardware synth the game's banks were authored for), carried over from the bring-up
 * HLE (src/ps2/iop/sound/snd_synth.c, docs/SOUND.md "Synth"; sub_ names are MODHSYN
 * offsets):
 *   - pitch (sub_4a48): Note2Pitch(sample base note, 0, note + prog/split transpose,
 *            prog/sample/split detune + bend) x (VAG rate / 48000 in Q16) >> 16,
 *   - volume (sub_41dc, sub_4e80, sub_4ca4): integer chain prog x split x sample x
 *            velocity curve x crossfade, x CC7 x note volume, x pan gain,
 *   - pan (sub_5074, sub_5158), sample attribute routing (dry/wet, bus select),
 *   - allocation: a free voice on the preferred bus, else steal (quietest released,
 *            else lowest priority oldest).
 * Here a "voice" is a native generator (ra_mix.c), not an SPU2 register set. */
#include <string.h>

#include "ra_internal.h"

ra_voice *ra_voice_at(int hv) { return &g_ra->bus[hv / RA_BUS_VOICES].v[hv % RA_BUS_VOICES]; }
#define VT(hv) ra_voice_at(hv)

void ra_channel_reset(ra_channel *c)
{
    memset(c, 0, sizeof *c);
    c->vol = 127;
    c->expr = 127;
    c->pan = 64;
    c->bend = 0x2000;
    c->nrpn_msb = c->nrpn_lsb = 0x7F;
    /* MODHSYN sub_7c0 */
    c->vol43 = 128;
    c->expr44 = 128;
    c->pan49 = 0;
    c->bend38 = 0;
    c->next_bend = 0xFFFF;
    c->next_vol = 0xFF;
    c->next_pan = 0xFF;
}

void ra_synth_reset(void)
{
    g_ra->vage = 0;
    g_ra->mono = 0;
}

static ra_bank *bank_for(int track, int ch)
{
    ra_track *t = &g_ra->track[track];
    int slot = t->ch[ch].bank & (RA_SLOTS - 1);
    int b = t->slot_bank[slot];
    if (b < 0) { /* fall back to the first attached slot */
        for (int s = 0; s < RA_SLOTS && b < 0; s++)
            b = t->slot_bank[s];
    }
    if (b < 0 || b >= RA_BANKS || !g_ra->bank[b].parsed_ok)
        return NULL;
    return &g_ra->bank[b];
}

/* ---- parameter computation (MODHSYN) ---------------------------------------------------- */
/* CC7 / CC11 / FD 00 value -> MODHSYN's internal 0..128 scale: (v << 7) / 127 */
static uint8_t scale128(int v) { return (uint8_t)(((v & 0x7F) << 7) / 127); }

/* sub_4c50: bend (14-bit value - 0x2000) -> 1/128 semitone over the split's range */
static int16_t bend_fine(const ra_voice *t, int32_t b)
{
    int32_t range = b >= 0 ? t->layer.split.bend_hi : t->layer.split.bend_lo;
    return (int16_t)((b * range) / 8192); /* C division truncates toward 0, like the IRX */
}

/* sub_97dc: v * v / 127, at least 1 */
static int vel_sq(int v)
{
    int r = (v * v) / 127;
    return r ? r : 1;
}

/* sub_98a4: Sset velocity curve, low nibble = curve type (6..9 repeat 0..3). The high
 * nibble selects a user table from the bank; none are modelled (no game bank needs one
 * that we know of: docs/SOUND.md). */
static int vel_curve(int vel, int curve)
{
    if (vel == 0)
        vel = 1;
    int type = curve & 0x0F;
    if (type >= 11)
        type = 0;
    switch (type % 6) {
    default:
    case 0: return vel & 0xFF;
    case 1: return (128 - vel) & 0xFF;
    case 2: return vel_sq(vel) & 0xFF;
    case 3: return (128 - vel_sq(vel)) & 0xFF;
    case 4: return (128 - vel_sq((128 - vel) & 0xFF)) & 0xFF;
    case 5: return vel_sq((128 - vel) & 0xFF) & 0xFF;
    }
}

/* sub_52f4: velocity crossfade (sample vel lo/xfade/hi, bit 7 = fade) times key crossfade
 * (split key lo/xfade/hi), Q16. */
static uint32_t crossfade(const ra_voice *t)
{
    const ra_hd_sample *sm = &t->layer.sample;
    const ra_hd_split *sp = &t->layer.split;
    uint32_t xf = 0x10000;
    int vel = t->vel, note = t->note;
    if (vel < sm->vel_xfade) {
        if (sm->vel_lo & 0x80) {
            int lo = sm->vel_lo & 0x7F;
            if (lo != sm->vel_xfade) {
                lo -= 1;
                xf = ((uint32_t)(vel - lo) << 16) / (uint32_t)(sm->vel_xfade - lo);
            }
        }
    } else if (sm->vel_hi & 0x80) {
        int hi = sm->vel_hi & 0x7F;
        if (hi != sm->vel_xfade) {
            hi += 1;
            xf = ((uint32_t)(hi - vel) << 16) / (uint32_t)(hi - sm->vel_xfade);
        }
    }
    if (note < sp->key_xfade) {
        if (sp->key_lo & 0x80) {
            int lo = sp->key_lo & 0x7F;
            if (lo != sp->key_xfade) {
                lo -= 1;
                xf = (xf * (uint32_t)(note - lo)) / (uint32_t)(sp->key_xfade - lo);
            }
        }
    } else if (sp->key_hi & 0x80) {
        int hi = sp->key_hi & 0x7F;
        if (hi != sp->key_xfade) {
            hi += 1;
            xf = (xf * (uint32_t)(hi - note)) / (uint32_t)(hi - sp->key_xfade);
        }
    }
    return xf;
}

/* sub_5074 (standard pan mode): |prog pan| - 128 + |split pan| + |sample pan| + key follow,
 * clamped to 0..127 */
static int16_t pan_base(const ra_voice *t)
{
    const ra_hd_layer *l = &t->layer;
    int kf = ((t->note - l->split.kf_pan_center) * l->split.kf_pan +
              (t->note - l->prog.kf_pan_center) * l->prog.kf_pan) / 12;
    int pp = (int8_t)l->prog.pan, ps = (int8_t)l->split.pan, pm = (int8_t)l->sample.pan;
    int p = (pp < 0 ? -pp : pp) - 128 + (ps < 0 ? -ps : ps) + (pm < 0 ? -pm : pm) + kf;
    return (int16_t)(p < 0 ? 0 : p > 127 ? 127 : p);
}

/* sub_5158: pan offset (CC10 / F9 01 / FD 01 value - 64) -> left/right gains */
static void voice_pan(ra_voice *t, int arg)
{
    t->g76 = t->g77 = 128;
    if (g_ra->mono)
        return;
    if (arg > 63) arg = 63;
    if (arg < -191) arg = -191;
    int p = arg + t->pan30 - 64; /* + voice+88 (64) - 64 */
    if (p > 0)
        t->g76 = p >= 63 ? 0 : (uint8_t)(((63 - p) << 7) / 63);
    else if (p < 0)
        t->g77 = p < -62 ? 0 : (uint8_t)(((p + 63) << 7) / 63);
}

static uint16_t voice_pitch(const ra_voice *t)
{
    const ra_hd_layer *l = &t->layer;
    int note = t->note + l->prog.transpose + l->split.transpose;
    int fine = l->prog.detune + l->sample.detune + l->split.detune + t->bend52;
    if (g_ra->cfg.break_mode == 1) /* compare control: one semitone sharp */
        fine += 128;
    uint32_t p = ra_note2pitch(l->sample.base_note, 0, note, fine);
    p = (p * t->rate60) >> 16;
    return (uint16_t)(p > 0x3FFF ? 0x3FFF : p);
}

static void voice_volume(const ra_voice *t, uint16_t *vl, uint16_t *vr)
{
    const ra_track *tr = &g_ra->track[t->track];
    const ra_channel *c = &tr->ch[t->ch];
    /* sub_4e80: v24 = CC7 x note volume x v22 >> 14; sub_4ca4: x track volume (256) x 127/127
     * >> 8, then the pan gains >> 7, clamped to 0x3FFF */
    uint32_t v = ((uint32_t)c->vol43 * t->vol84 * t->v22) >> 14;
    v &= 0xFFFF; /* stored as a halfword */
    if (t->seq)  /* SKMIDI track volume, 0x80 = unity (port model, docs/SOUND.md) */
        v = v * (uint32_t)tr->seq_vol / 128;
    uint32_t l = (t->g76 * v) >> 7, r = (t->g77 * v) >> 7;
    *vl = (uint16_t)(l > 0x3FFF ? 0x3FFF : l);
    *vr = (uint16_t)(r > 0x3FFF ? 0x3FFF : r);
}

static void voice_apply(int hv)
{
    ra_voice *t = VT(hv);
    uint16_t vl, vr;
    voice_volume(t, &vl, &vr);
    ra_voice_set_volume(t, vl, vr);
    t->pitch = voice_pitch(t);
}

/* ---- allocation ----------------------------------------------------------------------- */
static int core_free_count(int core)
{
    int n = 0;
    for (int v = 0; v < RA_BUS_VOICES; v++)
        if (!ra_voice_active(&g_ra->bus[core].v[v]))
            n++;
    return n;
}

static int alloc_voice(int core_pref, uint8_t priority)
{
    int cores[2];
    int nc = 0;
    if (core_pref == 0 || core_pref == 1)
        cores[nc++] = core_pref;
    else {
        int f0 = core_free_count(0), f1 = core_free_count(1);
        cores[nc++] = f1 > f0 ? 1 : 0;
        cores[nc++] = f1 > f0 ? 0 : 1;
    }
    for (int i = 0; i < nc; i++)
        for (int v = 0; v < RA_BUS_VOICES; v++)
            if (!ra_voice_active(&g_ra->bus[cores[i]].v[v]))
                return cores[i] * RA_BUS_VOICES + v;
    /* steal: a released voice with the lowest envelope, else the lowest-priority oldest */
    int best = -1;
    int32_t best_level = 0x10000;
    for (int i = 0; i < nc; i++)
        for (int v = 0; v < RA_BUS_VOICES; v++) {
            int hv = cores[i] * RA_BUS_VOICES + v;
            const ra_voice *sv = &g_ra->bus[cores[i]].v[v];
            if (sv->phase == RA_ENV_RELEASE && sv->env.level < best_level) {
                best = hv;
                best_level = sv->env.level;
            }
        }
    if (best < 0) {
        uint32_t best_age = 0xFFFFFFFFu;
        int best_pri = 0x100;
        for (int i = 0; i < nc; i++)
            for (int v = 0; v < RA_BUS_VOICES; v++) {
                int hv = cores[i] * RA_BUS_VOICES + v;
                const ra_voice *t = VT(hv);
                int pri = t->used ? t->layer.sample.priority : 0;
                if (pri < best_pri || (pri == best_pri && t->age < best_age)) {
                    best = hv;
                    best_pri = pri;
                    best_age = t->age;
                }
            }
        (void)priority;
    }
    if (best >= 0)
        g_ra->st.voice_steals++;
    return best;
}

/* sub_6cac + sub_41dc: the voice fields a key on sets */
static void voice_init(ra_voice *t, const ra_channel *c, const ra_bank *b)
{
    const ra_hd_layer *l = &t->layer;
    (void)b;
    /* +60: (rate << 16) * 0x057619F1 >> 32 >> 10, i.e. rate * 65536 / 48000 */
    t->rate60 = (uint32_t)(((uint64_t)((uint32_t)l->vag.rate << 16) * 0x057619F1u) >> 32) >> 10;
    /* +22: prog x split x sample volume x velocity curve >> 14, x crossfade >> 16 */
    int32_t pv = (int32_t)((uint32_t)l->prog.volume * l->split.volume * l->sample.volume *
                           (uint32_t)vel_curve(t->vel, l->sset.vel_curve)) / 16384; /* 32-bit mult, / toward 0 */
    t->v22 = (uint16_t)(((uint32_t)pv * crossfade(t)) >> 16);
    t->vol84 = c->next_vol != 0xFF ? c->next_vol : c->expr44;
    t->pan30 = pan_base(t);
    int arg;
    if (c->next_pan & 0x80)
        arg = c->pan49;
    else {
        arg = (int)c->next_pan - 64;
        if (arg < -63)
            arg = -63;
    }
    voice_pan(t, arg);
    t->bend52 = bend_fine(t, (c->next_bend & 0x8000) ? c->bend38 : (int32_t)c->next_bend - 0x2000);
}

/* ---- public synth operations -------------------------------------------------------------- */
void ra_synth_note_on(int track, int ch, int note, int vel, int id, int seq)
{
    if (track < 0 || track >= RA_TRACKS || ch < 0 || ch > 15)
        return;
    if (vel <= 0) {
        ra_synth_note_off(track, ch, note, id, seq);
        return;
    }
    ra_bank *b = bank_for(track, ch);
    if (!b) {
        g_ra->st.no_layer++;
        return;
    }
    ra_hd_layer layers[8];
    int n = ra_hd_resolve(&b->parsed, g_ra->track[track].ch[ch].prog, note, vel, layers, 8);
    if (n == 0) {
        g_ra->st.no_layer++;
        return;
    }
    int created = 0;
    for (int i = 0; i < n; i++) {
        const ra_hd_layer *l = &layers[i];
        int pref = (l->sample.spu_attr & 0x30) == 0x10 ? 0 : (l->sample.spu_attr & 0x30) == 0x20 ? 1 : -1;
        int hv = alloc_voice(pref, l->sample.priority);
        if (hv < 0)
            continue;
        ra_voice *t = VT(hv);
        /* the tag part is rebuilt; the generator restarts in ra_voice_start */
        ra_blob *keep = t->bd;
        memset(t, 0, sizeof *t);
        t->bd = keep;
        t->used = 1;
        t->track = track;
        t->ch = ch;
        t->note = note;
        t->id = id;
        t->seq = seq;
        t->vel = vel;
        t->age = ++g_ra->vage;
        t->layer = *l;
        voice_init(t, &g_ra->track[track].ch[ch], b);
        uint16_t vl, vr;
        voice_volume(t, &vl, &vr);
        t->pitch = voice_pitch(t);
        t->adsr1 = l->sample.adsr1;
        t->adsr2 = l->sample.adsr2;
        ra_voice_set_volume(t, vl, vr);
        t->route = l->sample.spu_attr & 0x0F;
        ra_voice_start(t, b->bd, l->vag.offset);
        if (ra_host_cmdlog_on()) { /* "K": key on (track, ch, prog, note, vel, id, seq, bus*24+voice, vol L, vol R) */
            int w[10] = {track, ch, g_ra->track[track].ch[ch].prog, note, vel, id, seq, hv, vl, vr};
            ra_host_cmdlog(g_ra->frame, 'K', t->layer.sample.adsr1, w, 10, t->pitch);
        }
        created = 1;
    }
    if (created) { /* sub_6cac: the F9 "next note" values are used by one key on */
        ra_channel *c = &g_ra->track[track].ch[ch];
        c->next_bend = 0xFFFF;
        c->next_vol = 0xFF;
        c->next_pan = 0xFF;
    }
}

/* Voices a key off or an FD message addresses: SE voices by (track, ch, note, id);
 * id 127 matches any id (MODHSYN sub_ee0/sub_dc4/sub_ffc). Sequence notes by note. */
static int tag_match(const ra_voice *t, int track, int ch, int note, int id, int seq)
{
    if (!t->used || t->track != track || t->ch != ch || t->note != note)
        return 0;
    if (seq)
        return t->seq;
    if (id == 127)
        return 1;
    return !t->seq && t->id == id;
}

void ra_synth_note_off(int track, int ch, int note, int id, int seq)
{
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (!tag_match(t, track, ch, note, id, seq) || t->released)
            continue;
        if (g_ra->track[track].ch[ch].sustain) {
            t->sustained = 1;
            continue;
        }
        t->released = 1;
        ra_voice_release(VT(hv));
        g_ra->st.key_offs++;
    }
}

static int voice_on(int hv) { return ra_voice_active(VT(hv)); }

/* FD 00 volume (sub_ee0), FD 01 pan (sub_dc4), FD 02 bend (sub_ffc), per (ch, note, id) */
void ra_synth_voice_ctl(int track, int ch, int note, int id, int what, int value)
{
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (!tag_match(t, track, ch, note, id, 0))
            continue;
        if (what == 0)
            t->vol84 = scale128(value);
        else if (what == 1) {
            int arg = (value & 0x7F) - 64;
            voice_pan(t, arg < -63 ? -63 : arg);
        } else
            t->bend52 = bend_fine(t, (int32_t)(value & 0x3FFF) - 0x2000);
        if (voice_on(hv))
            voice_apply(hv);
    }
}

static void channel_changed(int track, int ch)
{
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (t->used && t->track == track && t->ch == ch && voice_on(hv))
            voice_apply(hv);
    }
}

void ra_synth_track_changed(int track)
{
    for (int ch = 0; ch < 16; ch++)
        channel_changed(track, ch);
}

/* CC7 (sub_a58): +43 changed -> recompute the channel's voices. CC11 (sub_ab4): +44
 * changed -> every voice's note volume = +44. CC10 (sub_cf8): +49 changed -> every
 * voice's pan offset = +49. */
static void cc_volume(int track, int ch, int value)
{
    ra_channel *c = &g_ra->track[track].ch[ch];
    c->vol = (uint8_t)value;
    uint8_t v = scale128(value);
    if (v == c->vol43)
        return;
    c->vol43 = v;
    channel_changed(track, ch);
}

static void cc_expression(int track, int ch, int value)
{
    ra_channel *c = &g_ra->track[track].ch[ch];
    c->expr = (uint8_t)value;
    uint8_t v = scale128(value);
    if (v == c->expr44)
        return;
    c->expr44 = v;
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (t->used && t->track == track && t->ch == ch) {
            t->vol84 = v;
            if (voice_on(hv))
                voice_apply(hv);
        }
    }
}

static void cc_pan(int track, int ch, int value)
{
    ra_channel *c = &g_ra->track[track].ch[ch];
    c->pan = (uint8_t)value;
    int p = value - 64;
    if (p < -63)
        p = -63;
    if (p == c->pan49)
        return;
    c->pan49 = (int8_t)p;
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (t->used && t->track == track && t->ch == ch) {
            voice_pan(t, p);
            if (voice_on(hv))
                voice_apply(hv);
        }
    }
}

void ra_synth_cc(int track, int ch, int cc, int value)
{
    if (track < 0 || track >= RA_TRACKS || ch < 0 || ch > 15)
        return;
    ra_channel *c = &g_ra->track[track].ch[ch];
    value &= 0x7F;
    switch (cc) {
    case 0: c->bank = (uint8_t)value; break;
    case 7: cc_volume(track, ch, value); break;
    case 10: cc_pan(track, ch, value); break;
    case 11: cc_expression(track, ch, value); break;
    case 64:
        c->sustain = value >= 64;
        if (!c->sustain)
            for (int hv = 0; hv < RA_VOICES; hv++) {
                ra_voice *t = VT(hv);
                if (t->used && t->sustained && t->track == track && t->ch == ch) {
                    t->sustained = 0;
                    t->released = 1;
                    ra_voice_release(VT(hv));
                }
            }
        break;
    case 0x62: c->nrpn_lsb = (uint8_t)value; break;
    case 0x63: c->nrpn_msb = (uint8_t)value; break;
    case 120: ra_synth_all_off(track, 1, 0); break; /* all sound off */
    case 121:                                    /* reset controllers (sub_1110) */
        ra_synth_cc(track, ch, 64, 0);
        ra_synth_bend(track, ch, 0x2000);
        cc_volume(track, ch, 127);
        cc_pan(track, ch, 64);
        cc_expression(track, ch, 127);
        break;
    case 123: /* all notes off */
        for (int hv = 0; hv < RA_VOICES; hv++) {
            ra_voice *t = VT(hv);
            if (t->used && t->track == track && t->ch == ch && !t->released) {
                t->released = 1;
                ra_voice_release(VT(hv));
            }
        }
        break;
    default: break;
    }
}

void ra_synth_prog(int track, int ch, int prog)
{
    if (track < 0 || track >= RA_TRACKS || ch < 0 || ch > 15)
        return;
    g_ra->track[track].ch[ch].prog = (uint8_t)(prog & 0x7F);
}

/* E0 (sub_8d8): +38 = bend - 0x2000; if it changed, every voice of the channel takes it */
void ra_synth_bend(int track, int ch, int value)
{
    if (track < 0 || track >= RA_TRACKS || ch < 0 || ch > 15)
        return;
    ra_channel *c = &g_ra->track[track].ch[ch];
    c->bend = (uint16_t)(value & 0x3FFF);
    int16_t b = (int16_t)((value & 0x3FFF) - 0x2000);
    if (b == c->bend38)
        return;
    c->bend38 = b;
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (t->used && t->track == track && t->ch == ch) {
            t->bend52 = bend_fine(t, b);
            if (voice_on(hv))
                voice_apply(hv);
        }
    }
}

/* F9 0/1/2 (sub_148c): values for the channel's next key on: 0 raw volume, 1 pan,
 * 2 14-bit bend */
void ra_synth_next(int track, int ch, int what, int value)
{
    if (track < 0 || track >= RA_TRACKS || ch < 0 || ch > 15)
        return;
    ra_channel *c = &g_ra->track[track].ch[ch];
    if (what == 0)
        c->next_vol = (uint8_t)value;
    else if (what == 1)
        c->next_pan = (uint8_t)value;
    else if (what == 2)
        c->next_bend = (uint16_t)value;
}

/* immediate = all sound off (envelopes cut), else all notes off (release). */
void ra_synth_all_off(int track, int immediate, int seq_only)
{
    for (int hv = 0; hv < RA_VOICES; hv++) {
        ra_voice *t = VT(hv);
        if (!t->used || (track >= 0 && t->track != track) || (seq_only && !t->seq))
            continue;
        if (immediate) {
            ra_voice_cut(t);
            t->used = 0;
        } else if (!t->released) {
            t->released = 1;
            ra_voice_release(t);
        }
    }
}

/* SE voices of (track, id) still sounding (SKMSIN G3/3 0x11 semantics) */
int ra_note_state(int track, int id)
{
    for (int hv = 0; hv < RA_VOICES; hv++) {
        const ra_voice *t = VT(hv);
        if (t->used && t->track == track && !t->seq && t->id == (id & 0xFF) && ra_voice_active(t))
            return 0x10;
    }
    return 0;
}
