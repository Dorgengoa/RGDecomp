/* SPDX-License-Identifier: CC0-1.0 */
/* Minimal PNG writer: RGBA8, filter 0, zlib stream of STORED deflate blocks.
 * Written from the PNG (RFC 2083 / ISO 15948) and zlib/deflate (RFC 1950 /
 * 1951) specifications.  Big but trivially correct; screenshots only. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "host_internal.h"

static uint32_t g_crc_table[256];
static int g_crc_ready;

uint32_t rg_crc32(uint32_t crc, const void *data, size_t n)
{
    if (!g_crc_ready) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            g_crc_table[i] = c;
        }
        g_crc_ready = 1;
    }
    const uint8_t *p = (const uint8_t *)data;
    crc = ~crc;
    while (n--) crc = g_crc_table[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return ~crc;
}

uint32_t rg_adler32(uint32_t adler, const void *data, size_t n)
{
    const uint8_t *p = (const uint8_t *)data;
    uint32_t a = adler & 0xFFFF, b = adler >> 16;
    while (n) {
        size_t k = n < 5552 ? n : 5552;   /* largest run without overflow */
        n -= k;
        while (k--) { a += *p++; b += a; }
        a %= 65521u;
        b %= 65521u;
    }
    return (b << 16) | a;
}

static uint8_t *put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24); p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >> 8); p[3] = (uint8_t)v;
    return p + 4;
}

/* chunk at p: length, type, data (already in place at p+8), crc */
static uint8_t *chunk_finish(uint8_t *p, const char *type, uint32_t len)
{
    put32(p, len);
    memcpy(p + 4, type, 4);
    uint32_t crc = rg_crc32(0, p + 4, 4 + (size_t)len);
    return put32(p + 8 + len, crc);
}

uint8_t *rg_png_encode(const uint32_t *rgba, uint32_t w, uint32_t h, size_t *len)
{
    if (!w || !h || w > 0x7FFFu || h > 0x7FFFu) return NULL;
    size_t row = 1 + (size_t)w * 4;
    size_t raw = row * h;
    size_t nblk = (raw + 65534) / 65535;
    size_t zlen = 2 + raw + 5 * nblk + 4;
    size_t total = 8 + (12 + 13) + (12 + zlen) + 12;
    uint8_t *out = (uint8_t *)malloc(total);
    if (!out) return NULL;
    static const uint8_t sig[8] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
    uint8_t *p = out;
    memcpy(p, sig, 8);
    p += 8;
    /* IHDR */
    uint8_t *d = p + 8;
    d = put32(d, w);
    d = put32(d, h);
    d[0] = 8; d[1] = 6; d[2] = 0; d[3] = 0; d[4] = 0;  /* 8-bit RGBA, deflate, filter 0, no interlace */
    p = chunk_finish(p, "IHDR", 13);
    /* IDAT: one zlib stream of stored blocks over the filtered scanlines */
    uint8_t *z = p + 8, *zp = z;
    *zp++ = 0x78; *zp++ = 0x01;          /* CM 8, 32K window, FCHECK: 0x7801 % 31 == 0 */
    uint32_t adler = 1;
    size_t left = raw, y = 0, x = 0;     /* x: byte offset within the current row */
    while (left) {
        size_t k = left < 65535 ? left : 65535;
        left -= k;
        *zp++ = left ? 0 : 1;            /* BFINAL, BTYPE 00 */
        zp[0] = (uint8_t)k; zp[1] = (uint8_t)(k >> 8);
        zp[2] = (uint8_t)~k; zp[3] = (uint8_t)(~k >> 8);
        zp += 4;
        uint8_t *blk = zp;
        while (k) {
            if (x == 0) { *zp++ = 0; x = 1; k--; continue; }   /* filter type 0 */
            size_t px = (x - 1) / 4, c = (x - 1) % 4;
            size_t n = row - x;
            if (n > k) n = k;
            const uint8_t *src = (const uint8_t *)(rgba + y * w + px) + c;
            memcpy(zp, src, n);
            zp += n; x += n; k -= n;
            if (x == row) { x = 0; y++; }
        }
        adler = rg_adler32(adler, blk, (size_t)(zp - blk));
    }
    zp = put32(zp, adler);
    p = chunk_finish(p, "IDAT", (uint32_t)(zp - z));
    p = chunk_finish(p, "IEND", 0);
    *len = (size_t)(p - out);
    return out;
}

int rg_png_write(const char *path, const uint32_t *rgba, uint32_t w, uint32_t h)
{
    size_t n;
    uint8_t *png = rg_png_encode(rgba, w, h, &n);
    if (!png) return -1;
    FILE *f = fopen(path, "wb");
    int ok = f && fwrite(png, 1, n, f) == n;
    if (f && fclose(f)) ok = 0;
    free(png);
    return ok ? 0 : -1;
}
