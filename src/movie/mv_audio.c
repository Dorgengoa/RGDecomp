/* SPDX-License-Identifier: CC0-1.0 */
/* Movie audio (docs/MOVIE.md "Audio", docs/MVI.md "Audio stream").
 *
 * The converted .wav is canonical RIFF PCM s16le stereo at the header rate (48048 or 48000
 * Hz), de-interleaved to LRLR by rg-extract. This file reads it back two ways:
 *  - host PCM (LRLR), for tools or a host-side mixer;
 *  - the original private-stream-1 byte stream after its 4 framing bytes: a 24-byte
 *    "SShd" chunk, the "SSbd" chunk header, then 1024-byte blocks [256 L s16][256 R s16].
 *    That is what MpegDemuxPssRing_115340 handed to AudioDecPcmCallback_1d4ca0 on the PS2,
 *    so the game's AudioDec layer (header parse, IOP ring, sdr_driver AutoDMA) runs
 *    unchanged when the movie service feeds it. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"

#ifndef _WIN32
#define _fseeki64 fseeko
#define _ftelli64 ftello
#endif

#define SS_HDR 40u   /* "SShd" + 4 + 24 + "SSbd" + 4 */

struct rg_mvaudio {
    FILE *fp;
    char path[520];        /* fp's file (save states reopen it: rg_mvaudio_ss_reopen) */
    const uint8_t *mem;
    uint64_t data_off;     /* byte offset of the PCM data */
    uint64_t frames;       /* total frames */
    uint32_t rate;
    uint64_t pcm_pos;      /* host reader, frames */
    uint64_t ss_pos;       /* SS reader, bytes */
    uint64_t ss_block;     /* index of the cached SS block, or ~0 */
    uint8_t ss_cache[1024];
    uint8_t hdr[SS_HDR];
};

static uint32_t rd32(const uint8_t *p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24); }
static uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | (p[1] << 8)); }
static void wr32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

/* read `n` bytes at absolute offset `off`; returns bytes read */
static size_t rd_at(rg_mvaudio *a, uint64_t off, void *dst, size_t n, uint64_t total)
{
    if (off >= total) return 0;
    if (n > total - off) n = (size_t)(total - off);
    if (a->mem) {
        memcpy(dst, a->mem + off, n);
        return n;
    }
    if (_fseeki64(a->fp, (long long)off, SEEK_SET) != 0) return 0;
    return fread(dst, 1, n, a->fp);
}

static int parse_wav(rg_mvaudio *a, uint64_t size, char *err, size_t cap)
{
    uint8_t h[12];
    if (rd_at(a, 0, h, 12, size) != 12 || memcmp(h, "RIFF", 4) || memcmp(h + 8, "WAVE", 4)) {
        snprintf(err, cap, "not a RIFF/WAVE file");
        return -1;
    }
    uint64_t off = 12;
    int have_fmt = 0;
    while (off + 8 <= size) {
        uint8_t c[8];
        if (rd_at(a, off, c, 8, size) != 8) break;
        uint32_t len = rd32(c + 4);
        if (!memcmp(c, "fmt ", 4)) {
            uint8_t f[16];
            if (len < 16 || rd_at(a, off + 8, f, 16, size) != 16) break;
            if (rd16(f) != 1 || rd16(f + 2) != 2 || rd16(f + 14) != 16) {
                snprintf(err, cap, "WAV is not PCM s16 stereo (fmt %u, %u ch, %u bit)", rd16(f),
                         rd16(f + 2), rd16(f + 14));
                return -1;
            }
            a->rate = rd32(f + 4);
            have_fmt = 1;
        } else if (!memcmp(c, "data", 4)) {
            if (!have_fmt) break;
            a->data_off = off + 8;
            uint64_t avail = size - a->data_off;
            if (len > avail) len = (uint32_t)avail;
            a->frames = len / 4;
            return 0;
        }
        off += 8 + len + (len & 1);
    }
    snprintf(err, cap, "WAV has no fmt/data chunk");
    return -1;
}

static void build_header(rg_mvaudio *a)
{
    uint64_t body = (a->frames + 255) / 256 * 1024;
    memcpy(a->hdr, "SShd", 4);
    wr32(a->hdr + 4, 24);
    wr32(a->hdr + 8, 1);          /* format: 16-bit PCM */
    wr32(a->hdr + 12, a->rate);
    wr32(a->hdr + 16, 2);         /* channels */
    wr32(a->hdr + 20, 512);       /* interleave: bytes per channel per block */
    wr32(a->hdr + 24, 0xFFFFFFFFu);
    wr32(a->hdr + 28, 0xFFFFFFFFu);
    memcpy(a->hdr + 32, "SSbd", 4);
    wr32(a->hdr + 36, (uint32_t)body);
}

static int finish_open(rg_mvaudio *a, uint64_t size, rg_mvaudio **out, char *err, size_t cap)
{
    char tmp[160];
    if (parse_wav(a, size, tmp, sizeof tmp)) {
        if (err) snprintf(err, cap, "%s", tmp);
        rg_mvaudio_close(a);
        return RG_MV_ERR_FORMAT;
    }
    a->ss_block = ~(uint64_t)0;
    build_header(a);
    *out = a;
    return 0;
}

int rg_mvaudio_open(rg_mvaudio **out, const char *path, char *err, size_t cap)
{
    *out = NULL;
    rg_mvaudio *a = (rg_mvaudio *)calloc(1, sizeof *a);
    if (!a) return RG_MV_ERR_NOMEM;
    a->fp = fopen(path, "rb");
    snprintf(a->path, sizeof a->path, "%s", path);
    if (!a->fp) {
        if (err) snprintf(err, cap, "cannot open %s", path);
        free(a);
        return RG_MV_ERR_IO;
    }
    _fseeki64(a->fp, 0, SEEK_END);
    uint64_t size = (uint64_t)_ftelli64(a->fp);
    return finish_open(a, size, out, err, cap);
}

int rg_mvaudio_open_memory(rg_mvaudio **out, const void *wav, size_t size, char *err, size_t cap)
{
    *out = NULL;
    rg_mvaudio *a = (rg_mvaudio *)calloc(1, sizeof *a);
    if (!a) return RG_MV_ERR_NOMEM;
    a->mem = (const uint8_t *)wav;
    return finish_open(a, size, out, err, cap);
}

void rg_mvaudio_close(rg_mvaudio *a)
{
    if (!a) return;
    if (a->fp) fclose(a->fp);
    free(a);
}

uint32_t rg_mvaudio_rate(const rg_mvaudio *a) { return a->rate; }
uint64_t rg_mvaudio_frames(const rg_mvaudio *a) { return a->frames; }
uint64_t rg_mvaudio_ss_size(const rg_mvaudio *a) { return SS_HDR + (a->frames + 255) / 256 * 1024; }
uint64_t rg_mvaudio_pcm_pos(const rg_mvaudio *a) { return a->pcm_pos; }

void rg_mvaudio_rewind(rg_mvaudio *a)
{
    a->pcm_pos = 0;
    a->ss_pos = 0;
}

int rg_mvaudio_seek_pcm(rg_mvaudio *a, uint64_t frame)
{
    if (frame > a->frames) frame = a->frames;
    a->pcm_pos = frame;
    return 0;
}

uint32_t rg_mvaudio_read_pcm(rg_mvaudio *a, int16_t *lr, uint32_t n)
{
    uint64_t left = a->frames - a->pcm_pos;
    if (n > left) n = (uint32_t)left;
    if (!n) return 0;
    uint64_t total = a->data_off + a->frames * 4;
    size_t got = rd_at(a, a->data_off + a->pcm_pos * 4, lr, (size_t)n * 4, total);
    n = (uint32_t)(got / 4);
    /* WAV is little-endian; so is every host this port targets (i686/x86-64) */
    a->pcm_pos += n;
    return n;
}

static void fill_block(rg_mvaudio *a, uint64_t blk)
{
    int16_t lr[512];
    memset(lr, 0, sizeof lr);
    uint64_t f0 = blk * 256;
    uint64_t total = a->data_off + a->frames * 4;
    if (f0 < a->frames) rd_at(a, a->data_off + f0 * 4, lr, 256 * 4, total);
    uint8_t *o = a->ss_cache;
    for (int ch = 0; ch < 2; ch++)
        for (int i = 0; i < 256; i++) {
            uint16_t s = (uint16_t)lr[i * 2 + ch];
            *o++ = (uint8_t)s;
            *o++ = (uint8_t)(s >> 8);
        }
    a->ss_block = blk;
}

uint32_t rg_mvaudio_read_ss(rg_mvaudio *a, uint8_t *dst, uint32_t n)
{
    uint64_t size = rg_mvaudio_ss_size(a);
    uint32_t done = 0;
    while (done < n && a->ss_pos < size) {
        if (a->ss_pos < SS_HDR) {
            uint32_t k = (uint32_t)(SS_HDR - a->ss_pos);
            if (k > n - done) k = n - done;
            memcpy(dst + done, a->hdr + a->ss_pos, k);
            a->ss_pos += k;
            done += k;
            continue;
        }
        uint64_t body = a->ss_pos - SS_HDR;
        uint64_t blk = body / 1024;
        uint32_t in = (uint32_t)(body % 1024);
        if (a->ss_block != blk) fill_block(a, blk);
        uint32_t k = 1024 - in;
        if (k > n - done) k = n - done;
        memcpy(dst + done, a->ss_cache + in, k);
        a->ss_pos += k;
        done += k;
    }
    return done;
}

/* ---- save states (docs/TEST-FIXTURES.md): every read seeks first, so the
 * reopened FILE needs no position. */
int rg_mvaudio_ss_file_backed(const rg_mvaudio *a) { return a && a->fp && a->path[0]; }

int rg_mvaudio_ss_reopen(rg_mvaudio *a)
{
    if (!a || !a->path[0]) return -1;
    a->fp = fopen(a->path, "rb");
    return a->fp ? 0 : -1;
}
