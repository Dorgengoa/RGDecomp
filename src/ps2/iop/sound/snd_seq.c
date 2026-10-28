/* SPDX-License-Identifier: CC0-1.0 */
/* SKMIDI / MODMIDI sequence player for SCEI "SQ" data (the .sq parts of the game's
 * snd2\bgm\*.snd packs). Format (checked against all 92 .sq files on the disc, each
 * parses start to FF 2F; docs/SOUND.md "SQ format"):
 *
 *   IECS Vers, IECS Sequ, IECS Midi { u32 size, u32 max, u32 block_off[max+1] }
 *   Midi block: { u32 stream_off (from the block), u16 ppq, ... }
 *   stream: delta (VLQ), then { event, [delta] }*:
 *     channel events take MIDI's data counts, but 8n (note off) has ONE data byte;
 *     running status as in MIDI; if the LAST data byte of an event has bit 7 set, the
 *     delta that follows is omitted (= 0) and the data value is byte & 0x7F;
 *     FF type len data = meta (51 tempo, 2F end), always followed by a delta.
 *   loop markers: NRPN MSB (CC 0x63) 0 + data entry (CC 6) = loop start,
 *                 NRPN MSB 1 + data entry v = loop end (v = 0: forever, else v times).
 *
 * Timing: SKSOUND ticks at 240 Hz (tickresolution default); each tick advances
 * ppq * 1e6 / (240 * tempo) MIDI ticks (exact rational accumulator), scaled by the
 * relative tempo (0x100 = 1.0). */
#include <string.h>

#include "snd_internal.h"

static uint32_t rd32(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }

void seq_reset(void)
{
    memset(g_snd->port, 0, sizeof g_snd->port);
}

/* Find block `block` of the Midi chunk; 0 ok. */
int seq_select(snd_player *p, const uint8_t *d, uint32_t size, int block)
{
    uint32_t off = 0;
    while (off + 16 <= size && memcmp(d + off, "IECS", 4) == 0) {
        uint32_t csz = rd32(d + off + 8);
        if (memcmp(d + off + 4, "idiM", 4) == 0) {
            uint32_t maxi = rd32(d + off + 12);
            if (block < 0 || (uint32_t)block > maxi || off + 16 + (maxi + 1) * 4 > size)
                return -1;
            uint32_t bo = rd32(d + off + 16 + (uint32_t)block * 4);
            if (bo == 0xFFFFFFFFu || off + bo + 6 > size)
                return -1;
            uint32_t blk = off + bo;
            uint32_t so = rd32(d + blk);
            if (blk + so >= size)
                return -1;
            p->d = d;
            p->size = size;
            p->block = block;
            p->ppq = (uint16_t)(d[blk + 4] | d[blk + 5] << 8);
            if (p->ppq == 0)
                p->ppq = 480;
            p->start = blk + so;
            seq_rewind(p);
            return 0;
        }
        if (csz < 16)
            break;
        off += csz;
    }
    return -1;
}

static int rd_byte(snd_player *p)
{
    if (p->pos >= p->size) {
        p->ended = 1;
        p->playing = 0;
        return 0;
    }
    return p->d[p->pos++];
}

static uint32_t rd_vlq(snd_player *p)
{
    uint32_t v = 0;
    for (int i = 0; i < 4; i++) {
        int b = rd_byte(p);
        v = (v << 7) | (uint32_t)(b & 0x7F);
        if (!(b & 0x80))
            break;
    }
    return v;
}

void seq_rewind(snd_player *p)
{
    p->pos = p->start;
    p->status = 0;
    p->tempo = 500000;
    p->acc = 0;
    p->ended = 0;
    p->loop_set = 0;
    p->loops_done = 0;
    p->ticks = 0;
    if (p->d)
        p->wait = rd_vlq(p);
}

/* Execute one event at pos; returns 1 if a delta follows. */
static int seq_event(snd_player *p)
{
    int b = rd_byte(p);
    if (p->ended)
        return 0;
    if (b & 0x80) {
        p->status = (uint8_t)b;
    } else {
        p->pos--; /* running status: b is the first data byte */
        b = p->status;
    }
    p->events++;
    g_snd->stats.seq_events++;
    if (b == 0xFF) {
        int type = rd_byte(p);
        uint32_t len = rd_vlq(p);
        uint32_t at = p->pos;
        if (p->pos + len > p->size) {
            p->ended = 1;
            p->playing = 0;
            return 0;
        }
        p->pos += len;
        if (type == 0x51 && len >= 3)
            p->tempo = (uint32_t)p->d[at] << 16 | (uint32_t)p->d[at + 1] << 8 | p->d[at + 2];
        if (type == 0x2F) {
            p->ended = 1;
            p->playing = 0;
            synth_all_off(p->track, 0, 1);
            return 0;
        }
        return 1;
    }
    if (b == 0xF0 || b == 0xF7) {
        uint32_t len = rd_vlq(p);
        p->pos += len;
        return 1;
    }
    int hi = b & 0xF0, ch = b & 0x0F;
    int n = (hi == 0x80 || hi == 0xC0 || hi == 0xD0) ? 1 : 2;
    int d0 = rd_byte(p), d1 = n > 1 ? rd_byte(p) : 0;
    int last = n > 1 ? d1 : d0;
    d0 &= 0x7F;
    d1 &= 0x7F;
    int t = p->track;
    switch (hi) {
    case 0x80: synth_note_off(t, ch, d0, -1, 1); break;
    case 0x90:
        if (d1) {
            synth_note_on(t, ch, d0, d1, -1, 1);
            g_snd->stats.seq_notes++;
        } else
            synth_note_off(t, ch, d0, -1, 1);
        break;
    case 0xB0: {
        snd_channel *c = &g_snd->track[t].ch[ch];
        if (d0 == 6) { /* data entry: SCEI loop markers on NRPN MSB 0/1 */
            if (c->nrpn_msb == 0) {
                p->loop_pos = p->pos;
                p->loop_nodelta = (last & 0x80) != 0;
                p->loop_set = 1;
                p->loops_done = 0;
            } else if (c->nrpn_msb == 1 && p->loop_set) {
                if (d1 == 0 || p->loops_done < d1) {
                    p->loops_done++;
                    p->pos = p->loop_pos;
                    return !p->loop_nodelta;
                }
            }
        } else
            synth_cc(t, ch, d0, d1);
        break;
    }
    case 0xC0: synth_prog(t, ch, d0); break;
    case 0xE0: synth_bend(t, ch, d0 | d1 << 7); break;
    default: break; /* An, Dn: no synth effect modelled */
    }
    return !(last & 0x80);
}

void seq_tick(snd_player *p)
{
    if (!p->used || !p->playing || !p->d)
        return;
    /* MIDI ticks this SK tick: ppq * 1e6 * speed / (240 * tempo * 256) */
    uint64_t den = 240ull * (p->tempo ? p->tempo : 500000) * 256ull;
    p->acc += (uint64_t)p->ppq * 1000000ull * (p->speed ? p->speed : 0x100);
    uint32_t budget = (uint32_t)(p->acc / den);
    p->acc %= den;
    p->ticks += budget;
    int guard = 0;
    while (p->playing) {
        if (p->wait > budget) {
            p->wait -= budget;
            break;
        }
        budget -= p->wait;
        p->wait = 0;
        int delta = seq_event(p);
        if (!p->playing)
            break;
        if (delta)
            p->wait = rd_vlq(p);
        if (++guard > 100000) { /* malformed data: stop instead of spinning */
            p->playing = 0;
            p->ended = 1;
        }
    }
}
