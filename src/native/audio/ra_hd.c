/* SPDX-License-Identifier: CC0-1.0 */
/* SCEI HD bank parser, see ra_hd.h. */
#include "ra_hd.h"

#include <string.h>

static uint32_t rd32(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | p[1] << 8); }

static int chunk_is(const ra_hd *hd, uint32_t off, const char name[4])
{
    if (off + 16 > hd->size)
        return 0;
    const uint8_t *p = hd->d + off;
    return memcmp(p, "IECS", 4) == 0 && p[4] == (uint8_t)name[3] && p[5] == (uint8_t)name[2] &&
           p[6] == (uint8_t)name[1] && p[7] == (uint8_t)name[0];
}

/* Validate a table chunk; returns max index + 1 or 0. */
static uint32_t table_count(const ra_hd *hd, uint32_t off)
{
    uint32_t csize = rd32(hd->d + off + 8), maxi = rd32(hd->d + off + 12);
    if (maxi == 0xFFFFFFFFu) /* empty table (banks with no samples exist on the disc) */
        return 0;
    if (maxi >= 0x10000 || off + csize > hd->size || 16 + (maxi + 1) * 4 > csize)
        return 0xFFFFFFFFu;
    return maxi + 1;
}

int ra_hd_parse(ra_hd *hd, const uint8_t *data, uint32_t size)
{
    memset(hd, 0, sizeof *hd);
    hd->d = data;
    hd->size = size;
    if (!data || size < 0x50)
        return -1;
    if (!chunk_is(hd, 0, "Vers"))
        return -2;
    uint32_t head = rd32(data + 8); /* the Vers chunk size = offset of Head */
    if (!chunk_is(hd, head, "Head"))
        return -3;
    const uint8_t *h = data + head;
    hd->hd_size = rd32(h + 0x0C);
    hd->bd_size = rd32(h + 0x10);
    uint32_t offs[4] = {rd32(h + 0x14), rd32(h + 0x18), rd32(h + 0x1C), rd32(h + 0x20)};
    static const char *names[4] = {"Prog", "Sset", "Smpl", "Vagi"};
    uint32_t *dst[4] = {&hd->prog, &hd->sset, &hd->smpl, &hd->vagi};
    uint32_t *cnt[4] = {&hd->nprog, &hd->nsset, &hd->nsmpl, &hd->nvagi};
    for (int i = 0; i < 4; i++) {
        if (offs[i] == 0xFFFFFFFFu)
            continue;
        if (!chunk_is(hd, offs[i], names[i]))
            return -4 - i;
        *dst[i] = offs[i];
        *cnt[i] = table_count(hd, offs[i]);
        if (*cnt[i] == 0xFFFFFFFFu)
            return -8 - i;
    }
    return 0; /* absent or empty tables are allowed: such a bank resolves to nothing */
}

/* Byte offset of record `i` of the chunk at `chunk`, or 0 if absent/out of range. */
static uint32_t rec(const ra_hd *hd, uint32_t chunk, uint32_t count, int i, uint32_t len)
{
    if (!chunk || i < 0 || (uint32_t)i >= count)
        return 0;
    uint32_t o = rd32(hd->d + chunk + 16 + (uint32_t)i * 4);
    if (o == 0xFFFFFFFFu)
        return 0;
    o += chunk;
    if (o + len > hd->size)
        return 0;
    return o;
}

int ra_hd_get_prog(const ra_hd *hd, int prog, ra_hd_prog *out)
{
    uint32_t o = rec(hd, hd->prog, hd->nprog, prog, 0x24);
    if (!o)
        return -1;
    const uint8_t *p = hd->d + o;
    out->split_off = rd32(p);
    out->nsplit = p[4];
    out->split_size = p[5];
    out->volume = p[6];
    out->pan = p[7];
    out->transpose = (int8_t)p[8];
    out->detune = (int8_t)p[9];
    out->kf_pan = (int8_t)p[10];
    out->kf_pan_center = p[11];
    out->rec_off = o;
    if (out->split_size < 0x14)
        return -1;
    return 0;
}

int ra_hd_get_split(const ra_hd *hd, const ra_hd_prog *pr, int i, ra_hd_split *out)
{
    if (i < 0 || i >= pr->nsplit)
        return -1;
    uint32_t o = pr->rec_off + pr->split_off + (uint32_t)i * pr->split_size;
    if (o + 0x14 > hd->size)
        return -1;
    const uint8_t *p = hd->d + o;
    out->sset = rd16(p);
    out->key_lo = p[2];
    out->key_xfade = p[3];
    out->key_hi = p[4];
    out->number = p[5];
    out->bend_lo = rd16(p + 6);
    out->bend_hi = rd16(p + 8);
    out->kf_pitch = (int8_t)p[10];
    out->kf_pitch_center = p[11];
    out->kf_amp = (int8_t)p[12];
    out->kf_amp_center = p[13];
    out->kf_pan = (int8_t)p[14];
    out->kf_pan_center = p[15];
    out->volume = p[16];
    out->pan = p[17];
    out->transpose = (int8_t)p[18];
    out->detune = (int8_t)p[19];
    return 0;
}

int ra_hd_get_sset(const ra_hd *hd, int index, ra_hd_sset *out)
{
    uint32_t o = rec(hd, hd->sset, hd->nsset, index, 4);
    if (!o)
        return -1;
    const uint8_t *p = hd->d + o;
    out->vel_curve = p[0];
    out->vel_lo = p[1];
    out->vel_hi = p[2];
    out->nsample = p[3];
    out->samples_off = o + 4;
    if (out->samples_off + out->nsample * 2u > hd->size)
        return -1;
    return 0;
}

int ra_hd_sset_sample(const ra_hd *hd, const ra_hd_sset *s, int i)
{
    if (i < 0 || i >= s->nsample)
        return -1;
    return rd16(hd->d + s->samples_off + (uint32_t)i * 2);
}

int ra_hd_get_sample(const ra_hd *hd, int index, ra_hd_sample *out)
{
    uint32_t o = rec(hd, hd->smpl, hd->nsmpl, index, 0x2A);
    if (!o)
        return -1;
    const uint8_t *p = hd->d + o;
    out->vag = rd16(p);
    out->vel_lo = p[2];
    out->vel_xfade = p[3];
    out->vel_hi = p[4];
    out->vel_follow_pitch = (int8_t)p[5];
    out->vel_follow_pitch_center = p[6];
    out->vel_follow_pitch_curve = p[7];
    out->vel_follow_amp = (int8_t)p[8];
    out->vel_follow_amp_center = p[9];
    out->vel_follow_amp_curve = p[10];
    out->base_note = p[11];
    out->detune = (int8_t)p[12];
    out->pan = p[13];
    out->group = p[14];
    out->priority = p[15];
    out->volume = p[16];
    out->adsr1 = rd16(p + 0x12);
    out->adsr2 = rd16(p + 0x14);
    out->lfo_attr = p[0x28];
    out->spu_attr = p[0x29];
    return 0;
}

int ra_hd_get_vag(const ra_hd *hd, int index, ra_hd_vag *out)
{
    uint32_t o = rec(hd, hd->vagi, hd->nvagi, index, 8);
    if (!o)
        return -1;
    const uint8_t *p = hd->d + o;
    out->offset = rd32(p);
    out->rate = rd16(p + 4);
    out->loop = p[6];
    return 0;
}

int ra_hd_resolve(const ra_hd *hd, int prog, int note, int vel, ra_hd_layer *out, int max)
{
    ra_hd_prog pr;
    if (ra_hd_get_prog(hd, prog, &pr) < 0)
        return 0;
    int n = 0;
    for (int i = 0; i < pr.nsplit && n < max; i++) {
        ra_hd_split sp;
        if (ra_hd_get_split(hd, &pr, i, &sp) < 0)
            break;
        if (note < (sp.key_lo & 0x7F) || note > (sp.key_hi & 0x7F))
            continue;
        ra_hd_sset ss;
        if (ra_hd_get_sset(hd, sp.sset, &ss) < 0)
            continue;
        if (vel < ss.vel_lo || vel > ss.vel_hi || ss.nsample == 0)
            continue;
        for (int k = 0; k < ss.nsample && n < max; k++) {
            int si = ra_hd_sset_sample(hd, &ss, k);
            ra_hd_sample sm;
            if (si < 0 || ra_hd_get_sample(hd, si, &sm) < 0)
                continue;
            if (vel < (sm.vel_lo & 0x7F) || vel > (sm.vel_hi & 0x7F))
                continue;
            ra_hd_vag vg;
            if (ra_hd_get_vag(hd, sm.vag, &vg) < 0)
                continue;
            out[n].prog = pr;
            out[n].split = sp;
            out[n].sset = ss;
            out[n].sample = sm;
            out[n].vag = vg;
            n++;
        }
    }
    return n;
}
