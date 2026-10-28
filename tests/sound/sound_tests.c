/* SPDX-License-Identifier: CC0-1.0 */
/* Sound tests (docs/SOUND.md): rg-sound-tests <name>; ctest -L sound.
 * Exit 0 = pass, 1 = fail, 77 = skipped (RG_DATA not available). */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iop.h"
#include "sif.h"
#include "snd.h"
#include "snd_eesim.h"
#include "snd_hd.h"
#include "snd_pack.h"
#include "spu2.h"

static int g_fail;
#define CHECK(c, ...)                                                    \
    do {                                                                 \
        if (!(c)) {                                                      \
            g_fail++;                                                    \
            fprintf(stderr, "FAIL %s:%d: %s: ", __FILE__, __LINE__, #c); \
            fprintf(stderr, __VA_ARGS__);                                \
            fprintf(stderr, "\n");                                       \
        }                                                                \
    } while (0)

static spu2 g_spu; /* 2 MiB: static */

static uint64_t fnv(const int16_t *s, size_t n)
{
    uint64_t h = 1469598103934665603ull;
    for (size_t i = 0; i < n; i++) {
        uint16_t v = (uint16_t)s[i];
        h = (h ^ (v & 0xFF)) * 1099511628211ull;
        h = (h ^ (v >> 8)) * 1099511628211ull;
    }
    return h;
}

/* ---- ADPCM -------------------------------------------------------------------------------- */
static void put_nibbles(uint8_t blk[16], const int8_t nib[28])
{
    for (int i = 0; i < 28; i++)
        blk[2 + i / 2] |= (uint8_t)((nib[i] & 0xF) << ((i & 1) * 4));
}

static int t_adpcm(int control)
{
    int16_t out[28], hist[2];
    /* shift 12, filter 0: samples equal the signed nibbles */
    uint8_t b[16] = {0x0C, 0x00};
    int8_t nib[28];
    for (int i = 0; i < 28; i++)
        nib[i] = (int8_t)((i % 16) - 8);
    put_nibbles(b, nib);
    hist[0] = hist[1] = 0;
    spu2_adpcm_decode_block(b, out, hist);
    for (int i = 0; i < 28; i++)
        CHECK(out[i] == (i % 16) - 8, "f0 s12 sample %d = %d", i, out[i]);
    /* shift 0: nibble 7 -> 0x7000, nibble 8 -> -0x8000 */
    uint8_t b2[16] = {0x00, 0x00, 0x87};
    hist[0] = hist[1] = 0;
    spu2_adpcm_decode_block(b2, out, hist);
    CHECK(out[0] == 0x7000 && out[1] == -0x8000, "shift 0: %d %d", out[0], out[1]);
    /* filter 1 with history: hand-computed (s1*60 + 32) >> 6 chain from 64 */
    uint8_t b3[16] = {0x1C, 0x00};
    hist[0] = 64;
    hist[1] = 0;
    spu2_adpcm_decode_block(b3, out, hist);
    int exp1[3] = {60, 56, 53}; /* 3872>>6, 3632>>6, 3392>>6 */
    if (control)
        exp1[1] = 57; /* deliberately wrong */
    for (int i = 0; i < 3; i++)
        CHECK(out[i] == exp1[i], "filter 1 sample %d = %d want %d", i, out[i], exp1[i]);
    CHECK(hist[0] == out[27] && hist[1] == out[26], "history carried");
    /* filter 2 saturates: (32767*115 - 32768*-52 + 32) >> 6 = 85502 -> 32767 */
    uint8_t b4[16] = {0x2C, 0x00};
    hist[0] = 32767;
    hist[1] = -32768;
    spu2_adpcm_decode_block(b4, out, hist);
    CHECK(out[0] == 32767, "filter 2 clamp %d", out[0]);
    /* shift 13 behaves like 9: nibble 1 -> 0x1000 >> 9 = 8 */
    uint8_t b5[16] = {0x0D, 0x00, 0x01};
    hist[0] = hist[1] = 0;
    spu2_adpcm_decode_block(b5, out, hist);
    CHECK(out[0] == 8, "shift 13 -> 9: %d", out[0]);
    /* flags byte returned */
    uint8_t b6[16] = {0x0C, 0x07};
    CHECK(spu2_adpcm_decode_block(b6, out, hist) == 7, "flags");
    return g_fail;
}

/* ---- voice helpers ------------------------------------------------------------------------------ */
/* n blocks of a square wave (+/-0x2000) at addr; flags per block from `flags`. */
static void write_wave(spu2 *s, uint32_t addr, int n, const uint8_t *flags)
{
    for (int k = 0; k < n; k++) {
        uint8_t b[16] = {0x00, flags ? flags[k] : 0};
        int8_t nib[28];
        for (int i = 0; i < 28; i++)
            nib[i] = i < 14 ? 2 : -2;
        put_nibbles(b, nib);
        spu2_ram_write(s, addr + 16u * (uint32_t)k, b, 16);
    }
}

static void spu_basic(spu2 *s)
{
    spu2_reset(s);
    spu2_set_param(s, (SPU2_P_MMIX << 8) | 1, SPU2_MMIX_MSNDL | SPU2_MMIX_MSNDR | SPU2_MMIX_MINL | SPU2_MMIX_MINR);
    spu2_set_param(s, (SPU2_P_MMIX << 8) | 0, SPU2_MMIX_MSNDL | SPU2_MMIX_MSNDR);
    spu2_set_param(s, (SPU2_P_MVOLL << 8) | 0x80, 0x3FFF);
    spu2_set_param(s, (SPU2_P_MVOLR << 8) | 0x80, 0x3FFF);
    spu2_set_param(s, (SPU2_P_MVOLL << 8) | 0x81, 0x3FFF);
    spu2_set_param(s, (SPU2_P_MVOLR << 8) | 0x81, 0x3FFF);
    spu2_set_switch(s, (SPU2_S_VMIXL << 8) | 0, 0xFFFFFF);
    spu2_set_switch(s, (SPU2_S_VMIXR << 8) | 0, 0xFFFFFF);
}

/* ---- ADSR ----------------------------------------------------------------------------------------- */
static int t_adsr(void)
{
    spu2 *s = &g_spu;
    uint8_t loopf[2] = {4, 3};
    /* 1. linear attack, shift 13 step 1: +6 every 4 samples (closed form) */
    spu_basic(s);
    write_wave(s, 0x1000, 2, loopf);
    spu2_voice_setup(s, 0, 0, 0x1000, 0x1000, (uint16_t)(0x35 << 8 | 0xF), 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1);
    for (uint32_t n = 1; n < 21848; n++) {
        spu2_render(s, NULL, 1);
        int32_t want = (int32_t)(n / 4) * 6;
        if (spu2_voice_get(s, 0, 0)->env.level != want) {
            CHECK(0, "linear attack n=%u level %d want %d", n, spu2_voice_get(s, 0, 0)->env.level, want);
            break;
        }
    }
    spu2_render(s, NULL, 1); /* step 5462 saturates -> decay */
    CHECK(spu2_voice_get(s, 0, 0)->phase == SPU2_ENV_DECAY, "attack -> decay at 0x7FFF (phase %d)",
          spu2_voice_get(s, 0, 0)->phase);

    /* 2. exponential attack, shift 10 step 0: +14 per sample, then every 4 samples above 0x6000 */
    spu_basic(s);
    write_wave(s, 0x1000, 2, loopf);
    spu2_voice_setup(s, 0, 0, 0x1000, 0x1000, (uint16_t)(0x8000 | 0x28 << 8 | 0xF), 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1);
    for (uint32_t n = 1; n < 4000; n++) {
        spu2_render(s, NULL, 1);
        int32_t want = n <= 1756 ? (int32_t)n * 14 : 24584 + 14 * (int32_t)((n - 1756) / 4);
        if (want > 0x7FFF)
            break;
        if (spu2_voice_get(s, 0, 0)->env.level != want) {
            CHECK(0, "exp attack n=%u level %d want %d", n, spu2_voice_get(s, 0, 0)->env.level, want);
            break;
        }
    }

    /* 3. exponential decay to sustain level: psx-spx step -8 << (11 - shift) scaled by level */
    spu_basic(s);
    write_wave(s, 0x1000, 2, loopf);
    int dshift = 6, sl = 7; /* rate 0x18: step -8<<5 = -256 * level / 0x8000 */
    spu2_voice_setup(s, 0, 0, 0x1000, 0x1000, (uint16_t)(0x00 << 8 | dshift << 4 | sl), 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1);
    spu2_render(s, NULL, 3); /* attack rate 0: +0x3800 per sample -> 0x7FFF after 3 */
    CHECK(spu2_voice_get(s, 0, 0)->phase == SPU2_ENV_DECAY, "fast attack done");
    int32_t ref = 0x7FFF;
    int sustain_at = -1;
    for (int n = 1; n < 20000; n++) {
        spu2_render(s, NULL, 1);
        if ((ref >> 11) <= sl) { /* at or below SL: sustain, no step */
            sustain_at = n;
            CHECK(spu2_voice_get(s, 0, 0)->env.level == ref, "level kept entering sustain");
            break;
        }
        int32_t stp = (-8 * (1 << (11 - dshift)) * ref) >> 15;
        ref += stp;
        if (ref < 0) ref = 0;
        if (spu2_voice_get(s, 0, 0)->env.level != ref) {
            CHECK(0, "exp decay n=%d level %d want %d", n, spu2_voice_get(s, 0, 0)->env.level, ref);
            break;
        }
    }
    CHECK(sustain_at > 0 && spu2_voice_get(s, 0, 0)->phase == SPU2_ENV_SUSTAIN, "decay -> sustain at SL (%d)", sustain_at);
    /* sustain rate 0x7F holds the level */
    int32_t held = spu2_voice_get(s, 0, 0)->env.level;
    spu2_render(s, NULL, 4800);
    CHECK(spu2_voice_get(s, 0, 0)->env.level == held, "sustain rate 0x7F holds (%d vs %d)",
          spu2_voice_get(s, 0, 0)->env.level, held);

    /* 4. linear release, shift 5: -512 per sample; voice off exactly when it reaches 0 */
    spu_basic(s);
    write_wave(s, 0x1000, 2, loopf);
    spu2_voice_setup(s, 0, 0, 0x1000, 0x1000, 0x000F, 0x1FC0 | 5, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1);
    spu2_render(s, NULL, 10);
    int32_t L = spu2_voice_get(s, 0, 0)->env.level;
    spu2_key_off(s, 0, 1);
    int need = (L + 511) / 512;
    spu2_render(s, NULL, (uint32_t)need - 1);
    CHECK(spu2_voice_active(s, 0, 0) && spu2_voice_get(s, 0, 0)->env.level == L - 512 * (need - 1),
          "release ramp level %d want %d", spu2_voice_get(s, 0, 0)->env.level, L - 512 * (need - 1));
    spu2_render(s, NULL, 1);
    CHECK(!spu2_voice_active(s, 0, 0), "voice off after %d release samples", need);
    return g_fail;
}

/* ---- pitch ------------------------------------------------------------------------------------------ */
static int t_pitch(void)
{
    CHECK(spu2_note2pitch(60, 0, 60, 0) == 0x1000, "center");
    CHECK(spu2_note2pitch(60, 0, 72, 0) == 0x2000, "+12");
    CHECK(spu2_note2pitch(60, 0, 48, 0) == 0x0800, "-12");
    CHECK(spu2_note2pitch(60, 0, 67, 0) == 6137, "+7 = %u", spu2_note2pitch(60, 0, 67, 0));
    CHECK(spu2_note2pitch(60, 0, 59, 0) == 3866, "-1 = %u", spu2_note2pitch(60, 0, 59, 0)); /* 4096/2^(1/12) */
    CHECK(spu2_note2pitch(60, 0, 60, 64) == 4216, "+half semitone = %u", spu2_note2pitch(60, 0, 60, 64));
    CHECK(spu2_note2pitch(60, 0, 120, 0) == 0x3FFF, "clamp");
    /* fetch rate: floor(N * pitch / 4096) samples after N frames */
    spu2 *s = &g_spu;
    uint16_t pitches[3] = {0x800, 0x1000, 0x2000};
    for (int k = 0; k < 3; k++) {
        spu_basic(s);
        write_wave(s, 0x2000, 64, NULL);
        spu2_voice_setup(s, 0, 3, 0x2000, pitches[k], 0x000F, 0x1FC0, 0x3FFF, 0x3FFF);
        spu2_key_on(s, 0, 1u << 3);
        uint32_t N = 1000;
        spu2_render(s, NULL, N);
        uint32_t fetched = N * pitches[k] / 4096;
        uint32_t blocks = fetched ? (fetched - 1) / 28 + 1 : 0;
        CHECK(spu2_voice_get(s, 0, 3)->nax == 0x2000 + 16 * blocks, "pitch %04X: nax %X want %X", pitches[k],
              spu2_voice_get(s, 0, 3)->nax, 0x2000 + 16 * blocks);
        CHECK(spu2_voice_get(s, 0, 3)->block_pos == (int)(fetched - (blocks - 1) * 28), "pitch %04X: block pos",
              pitches[k]);
    }
    return g_fail;
}

/* ---- loop flags ----------------------------------------------------------------------------------------- */
static int t_loop(void)
{
    spu2 *s = &g_spu;
    /* looping sample: block1 = loop start, block3 = end+repeat */
    spu_basic(s);
    uint8_t f[4] = {0, 4, 0, 3};
    write_wave(s, 0x3000, 4, f);
    spu2_voice_setup(s, 0, 5, 0x3000, 0x1000, 0x000F, 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1u << 5);
    spu2_render(s, NULL, 28 * 4); /* fetched 112 samples: blocks 0..3 decoded */
    CHECK(spu2_voice_get(s, 0, 5)->lsax == 0x3010, "loop start from flag: %X", spu2_voice_get(s, 0, 5)->lsax);
    CHECK((spu2_get_switch(s, SPU2_S_ENDX << 8) & (1u << 5)) == 0, "ENDX clear before the end block finishes");
    spu2_render(s, NULL, 1); /* next fetch: end block done -> jump to 0x3010 */
    CHECK(spu2_get_switch(s, SPU2_S_ENDX << 8) & (1u << 5), "ENDX set at loop end");
    CHECK(spu2_voice_get(s, 0, 5)->nax == 0x3020, "jumped to loop start (nax %X)", spu2_voice_get(s, 0, 5)->nax);
    CHECK(spu2_voice_active(s, 0, 5), "repeat keeps the voice");
    spu2_render(s, NULL, 28 * 30);
    CHECK(spu2_voice_active(s, 0, 5), "still looping");
    /* key on clears ENDX */
    spu2_key_on(s, 0, 1u << 5);
    CHECK((spu2_get_switch(s, SPU2_S_ENDX << 8) & (1u << 5)) == 0, "KON clears ENDX");

    /* one-shot: end without repeat mutes the voice */
    spu_basic(s);
    uint8_t g[3] = {0, 0, 1};
    write_wave(s, 0x4000, 3, g);
    spu2_voice_setup(s, 1, 2, 0x4000, 0x1000, 0x000F, 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 1, 1u << 2);
    spu2_render(s, NULL, 84);
    CHECK(spu2_voice_active(s, 1, 2), "one-shot playing its last block");
    spu2_render(s, NULL, 1);
    CHECK(!spu2_voice_active(s, 1, 2), "one-shot off after the end block");
    CHECK(spu2_get_switch(s, (SPU2_S_ENDX << 8) | 1) & (1u << 2), "one-shot ENDX");

    /* LSAX written by software wins over the loop-start flag */
    spu_basic(s);
    write_wave(s, 0x3000, 4, f);
    spu2_voice_setup(s, 0, 5, 0x3000, 0x1000, 0x000F, 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1u << 5);
    spu2_set_addr(s, SPU2_VA_LSAX | (5 << 1), 0x3020);
    spu2_render(s, NULL, 28 * 4 + 1);
    CHECK(spu2_voice_get(s, 0, 5)->nax == 0x3030, "software LSAX kept (nax %X)", spu2_voice_get(s, 0, 5)->nax);
    return g_fail;
}

/* ---- synthetic bank / sequence --------------------------------------------------------------------------- */
static void w32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24); }
static void w16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }
static void chunk(uint8_t *p, const char *rev, uint32_t size, uint32_t maxi)
{
    memcpy(p, "IECS", 4);
    memcpy(p + 4, rev, 4);
    w32(p + 8, size);
    w32(p + 12, maxi);
}

#define HD_SIZE 0x120
static void make_hd(uint8_t hd[HD_SIZE], uint32_t bd_size, uint16_t adsr1, uint16_t adsr2)
{
    memset(hd, 0, HD_SIZE);
    chunk(hd, "sreV", 0x10, 0x00020000);
    memset(hd + 0x10, 0xFF, 0x40);
    chunk(hd + 0x10, "daeH", 0x40, HD_SIZE);
    w32(hd + 0x20, bd_size);
    w32(hd + 0x24, 0xD0); /* Prog */
    w32(hd + 0x28, 0xB0); /* Sset */
    w32(hd + 0x2C, 0x70); /* Smpl */
    w32(hd + 0x30, 0x50); /* Vagi */
    /* Vagi */
    chunk(hd + 0x50, "igaV", 0x20, 0);
    w32(hd + 0x60, 0x14);
    w32(hd + 0x64, 0);       /* bd offset */
    w16(hd + 0x68, 48000);   /* rate */
    hd[0x6A] = 1;
    hd[0x6B] = 0xFF;
    /* Smpl */
    chunk(hd + 0x70, "lpmS", 0x40, 0);
    w32(hd + 0x80, 0x14);
    uint8_t *sm = hd + 0x84;
    w16(sm, 0);
    sm[2] = 1; sm[3] = 0; sm[4] = 127;
    sm[11] = 60;   /* base note */
    sm[13] = 0x40; /* pan */
    sm[15] = 10;   /* priority */
    sm[16] = 0x80; /* volume */
    sm[17] = 0xFF;
    w16(sm + 0x12, adsr1);
    w16(sm + 0x14, adsr2);
    sm[0x29] = 0x13; /* dry L/R, core 0 */
    /* Sset */
    chunk(hd + 0xB0, "tesS", 0x20, 0);
    w32(hd + 0xC0, 0x14);
    uint8_t *ss = hd + 0xC4;
    ss[0] = 0; ss[1] = 1; ss[2] = 127; ss[3] = 1;
    w16(ss + 4, 0);
    /* Prog */
    chunk(hd + 0xD0, "gorP", 0x50, 0);
    w32(hd + 0xE0, 0x14);
    uint8_t *pg = hd + 0xE4;
    w32(pg, 0x24);
    pg[4] = 1; pg[5] = 0x14; pg[6] = 0x80; pg[7] = 0x40;
    uint8_t *sp = pg + 0x24;
    w16(sp, 0);
    sp[2] = 0; sp[4] = 127;
    w16(sp + 6, 0x400);
    w16(sp + 8, 0x400);
    sp[16] = 0x80; sp[17] = 0x40;
}

#define BD_BLOCKS 8
static void make_bd(uint8_t *bd)
{
    memset(bd, 0, BD_BLOCKS * 16);
    for (int k = 0; k < BD_BLOCKS; k++) {
        uint8_t *b = bd + 16 * k;
        b[0] = 0x00;
        b[1] = k == 1 ? 4 : k == BD_BLOCKS - 1 ? 3 : 0;
        if (k == 0)
            continue; /* leading silent block, as Sony VAGs have */
        int8_t nib[28];
        for (int i = 0; i < 28; i++)
            nib[i] = i < 14 ? 2 : -2;
        put_nibbles(b, nib);
    }
}

/* SQ: tempo 500000, ppq 480, prog 0, vol 127, note 60 on at 0, off at 480, end. */
static uint32_t make_sq(uint8_t *sq)
{
    static const uint8_t stream[] = {0x00, 0xFF, 0x51, 0x03, 0x07, 0xA1, 0x20, 0x00, 0xC0, 0x80, 0xB0, 0x07,
                                     0xFF, 0x90, 0x3C, 0x64, 0x83, 0x60, 0x80, 0xBC, 0xFF, 0x2F, 0x00};
    memset(sq, 0, 0x100);
    chunk(sq, "sreV", 0x10, 0x00010000);
    chunk(sq + 0x10, "uqeS", 0x20, 0);
    memset(sq + 0x1C, 0xFF, 0x14);
    uint32_t msize = 0x14 + 6 + (uint32_t)sizeof stream;
    chunk(sq + 0x30, "idiM", msize, 0);
    w32(sq + 0x40, 0x14);
    w32(sq + 0x44, 6);
    w16(sq + 0x48, 480);
    memcpy(sq + 0x4A, stream, sizeof stream);
    return 0x30 + msize;
}

static int boot_synthetic(snd_ee_bank *b, int with_sq)
{
    static uint8_t hd[HD_SIZE], bd[BD_BLOCKS * 16], sq[0x100];
    make_hd(hd, sizeof bd, 0x000F, 0x1FC0 | 0x0A);
    make_bd(bd);
    uint32_t sqn = make_sq(sq);
    if (snd_ee_boot() < 0)
        return -1;
    return snd_ee_load_bank(hd, HD_SIZE, bd, sizeof bd, 0x5040, 0, with_sq ? sq : NULL, with_sq ? sqn : 0, b);
}

static int t_hd_synthetic(void)
{
    uint8_t hd[HD_SIZE];
    make_hd(hd, 128, 0x80FF, 0x5FE7);
    snd_hd h;
    CHECK(snd_hd_parse(&h, hd, HD_SIZE) == 0, "parse");
    snd_hd_layer l[4];
    int n = snd_hd_resolve(&h, 0, 72, 100, l, 4);
    CHECK(n == 1, "one layer (%d)", n);
    CHECK(n == 1 && l[0].sample.base_note == 60 && l[0].sample.adsr1 == 0x80FF && l[0].vag.rate == 48000,
          "fields");
    CHECK(snd_hd_resolve(&h, 1, 60, 100, l, 4) == 0, "absent program");
    CHECK(snd_hd_resolve(&h, 0, 60, 0, l, 4) == 0, "velocity 0 outside the window");
    hd[0x10] = 'X';
    CHECK(snd_hd_parse(&h, hd, HD_SIZE) < 0, "bad Head magic rejected");
    return g_fail;
}

/* ---- real bank from data/ ----------------------------------------------------------------------------------- */
static const char *data_dir(void)
{
    const char *d = getenv("RG_DATA");
    return d && *d ? d : NULL;
}

static int t_hd_real(void)
{
    const char *dd = data_dir();
    if (!dd)
        return 77;
    uint32_t size = 0;
    uint8_t *pack = snd_data_load(dd, "snd2\\sy_000.snd", &size);
    if (!pack) {
        fprintf(stderr, "skip: snd2\\sy_000.snd not found under %s\n", dd);
        return 77;
    }
    snd_pack_entry e[64];
    int n = snd_pack_list(pack, size, e, 64);
    const snd_pack_entry *hd = snd_pack_find(e, n, ".hd"), *bd = snd_pack_find(e, n, ".bd");
    CHECK(hd && bd, "pack has .hd and .bd (%d entries)", n);
    if (!hd || !bd)
        return g_fail;
    CHECK(bd->size == 0x14E10 && hd->size == 0x2430, "sizes bd %X hd %X", bd->size, hd->size);
    snd_hd h;
    CHECK(snd_hd_parse(&h, pack + hd->offset, hd->size) == 0, "parse sy_000.hd");
    CHECK(h.bd_size == bd->size, "Head bd size %X", h.bd_size);
    CHECK(h.nprog == 128 && h.nsmpl == 86 && h.nsset == 86 && h.nvagi == 20, "counts %u %u %u %u", h.nprog,
          h.nsmpl, h.nsset, h.nvagi);
    snd_hd_sample sm;
    CHECK(snd_hd_get_sample(&h, 0, &sm) == 0 && sm.vag == 0x0C && sm.base_note == 0x24 && sm.adsr1 == 0x80FF &&
              sm.adsr2 == 0x5FE7 && sm.spu_attr == 0x13 && sm.volume == 0x80,
          "sample 0 fields");
    snd_hd_vag vg;
    CHECK(snd_hd_get_vag(&h, 1, &vg) == 0 && vg.offset == 0xD20 && vg.rate == 36000, "vag 1");
    /* every program resolves to samples inside the BD */
    int layers = 0, progs = 0;
    for (uint32_t p = 0; p < h.nprog; p++) {
        snd_hd_prog pg;
        if (snd_hd_get_prog(&h, (int)p, &pg) < 0)
            continue;
        progs++;
        for (int i = 0; i < pg.nsplit; i++) {
            snd_hd_split sp;
            CHECK(snd_hd_get_split(&h, &pg, i, &sp) == 0, "prog %u split %d", p, i);
            snd_hd_layer l[8];
            int nl = snd_hd_resolve(&h, (int)p, sp.key_lo, 100, l, 8);
            for (int k = 0; k < nl; k++)
                CHECK(l[k].vag.offset < h.bd_size, "prog %u vag offset %X", p, l[k].vag.offset);
            layers += nl;
        }
    }
    CHECK(progs > 0 && layers >= progs, "progs %d layers %d", progs, layers);
    free(pack);
    /* every bank in the archive parses */
    char h6[600], dat[600];
    snprintf(h6, sizeof h6, "%s/DATA0_0.HD6", dd);
    snprintf(dat, sizeof dat, "%s/DATA0_0.DAT", dd);
    snd_archive a;
    if (snd_archive_open(&a, h6, dat) == 0) {
        int banks = 0, bad = 0;
        for (int i = 0; i < a.nfiles; i++) {
            size_t l = strlen(a.files[i].path);
            if (l < 4 || strcmp(a.files[i].path + l - 4, ".snd") != 0)
                continue;
            uint8_t *d = snd_archive_read(&a, &a.files[i]);
            if (!d)
                continue;
            snd_pack_entry pe[64];
            int pn = snd_pack_list(d, a.files[i].size, pe, 64);
            const snd_pack_entry *x = snd_pack_find(pe, pn, ".hd");
            if (x && x->size) {
                banks++;
                if (snd_hd_parse(&h, d + x->offset, x->size) != 0) {
                    bad++;
                    fprintf(stderr, "bad bank %s\n", a.files[i].path);
                }
            }
            free(d);
        }
        CHECK(banks > 700 && bad == 0, "archive banks %d bad %d", banks, bad);
        printf("hd_real: %d banks parsed\n", banks);
        snd_archive_close(&a);
    }
    return g_fail;
}

static int t_se_keyon_real(void)
{
    const char *dd = data_dir();
    if (!dd)
        return 77;
    uint32_t size = 0;
    uint8_t *pack = snd_data_load(dd, "snd2\\sy_000.snd", &size);
    if (!pack)
        return 77;
    snd_pack_entry e[64];
    int n = snd_pack_list(pack, size, e, 64);
    const snd_pack_entry *hd = snd_pack_find(e, n, ".hd"), *bd = snd_pack_find(e, n, ".bd");
    snd_hd h;
    snd_hd_parse(&h, pack + hd->offset, hd->size);
    /* first program with a sounding layer */
    int prog = -1, note = 60;
    for (uint32_t p = 0; p < h.nprog && prog < 0; p++) {
        snd_hd_prog pg;
        snd_hd_split sp;
        snd_hd_layer l[4];
        if (snd_hd_get_prog(&h, (int)p, &pg) == 0 && snd_hd_get_split(&h, &pg, 0, &sp) == 0 &&
            snd_hd_resolve(&h, (int)p, sp.key_lo, 127, l, 4) > 0) {
            prog = (int)p;
            note = sp.key_lo;
        }
    }
    CHECK(prog >= 0, "a playable program");
    uint64_t hashes[2];
    for (int run = 0; run < 2; run++) {
        snd_ee_bank b;
        CHECK(snd_ee_boot() == 0, "boot");
        CHECK(snd_ee_load_bank(pack + hd->offset, hd->size, pack + bd->offset, bd->size, 0x5040, 0, NULL, 0, &b) == 0,
              "load bank");
        int id = snd_ee_key_on(b.msin_track, 0x66, 0, prog, note, 127);
        CHECK(id == 0x66, "key on returns the id (%d)", id);
        CHECK(snd_voices_playing() >= 1, "voice keyed");
        static int16_t buf[48000 * 2];
        snd_render(buf, 24000);
        snd_ee_key_off(b.msin_track, 0x66, 0, prog, note);
        snd_render(buf + 48000, 24000);
        uint64_t sq = 0;
        int peak = 0;
        for (int i = 0; i < 48000 * 2; i++) {
            int a = buf[i] < 0 ? -buf[i] : buf[i];
            if (a > peak) peak = a;
            sq += (uint64_t)((int64_t)buf[i] * buf[i]);
        }
        hashes[run] = fnv(buf, 48000 * 2);
        printf("se_keyon_real: prog %d note %d peak %d meansq %llu hash %016llx\n", prog, note, peak,
               (unsigned long long)(sq / 96000), (unsigned long long)hashes[run]);
        CHECK(peak > 500, "non-silent (peak %d)", peak);
    }
    CHECK(hashes[0] == hashes[1], "deterministic");
    free(pack);
    return g_fail;
}

/* ---- HLE path on the synthetic bank -------------------------------------------------------------------------- */
static int t_se_keyon(void)
{
    snd_ee_bank b;
    CHECK(boot_synthetic(&b, 0) == 0, "boot + load");
    CHECK(b.entry == 0 && b.msin_track == 0, "entry %d track %d", b.entry, b.msin_track);
    CHECK(snd_track_status(b.msin_track) == 3, "track status %d", snd_track_status(b.msin_track));
    /* SKSOUND master volume wrap: (0x3FFF * 129) & 0x7FFF = 0x3F7F */
    uint32_t blk[16] = {0, 2, 3, 0x80, 0x3FFF, 0x7F};
    snd_sk(blk);
    CHECK(spu2_get_param(snd_spu(), (SPU2_P_MVOLL << 8) | 0x81) == 0x3F7F, "MVOLL wrap %X",
          spu2_get_param(snd_spu(), (SPU2_P_MVOLL << 8) | 0x81));
    CHECK(spu2_get_param(snd_spu(), (SPU2_P_MVOLR << 8) | 0x81) == 0x3FFF, "MVOLR 0x7F*129");
    int id = snd_ee_key_on(b.msin_track, 0x70, 0, 0, 72, 127);
    CHECK(id == 0x70, "id");
    const spu2_voice *v = spu2_voice_get(snd_spu(), 0, 0);
    CHECK(spu2_voice_active(snd_spu(), 0, 0) && v->ssa == 0x5040, "voice 0 core 0 at the BD (ssa %X)", v->ssa);
    CHECK(v->pitch == 0x2000, "note 72 on base 60 at 48 kHz = 0x2000 (%X)", v->pitch);
    static int16_t buf[9600 * 2];
    snd_render(buf, 9600);
    int peak = 0;
    for (int i = 0; i < 9600 * 2; i++)
        if (buf[i] > peak) peak = buf[i];
    CHECK(peak > 1000, "audible (%d)", peak);
    /* per-id volume 0 silences that voice only */
    uint32_t vol[16] = {3u << 24, 2, (uint32_t)b.msin_track, 0x42, 0x70, 0, 72, 0};
    snd_sk(vol);
    CHECK(spu2_voice_get(snd_spu(), 0, 0)->vol[0].reg == 0, "id volume 0 -> VOLL 0");
    /* key off releases */
    snd_ee_key_off(b.msin_track, 0x70, 0, 0, 72);
    CHECK(spu2_voice_get(snd_spu(), 0, 0)->phase == SPU2_ENV_RELEASE, "released");
    snd_render(buf, 9600);
    CHECK(snd_voices_playing() == 0, "release finished");
    /* errors: key on to a track without input -> -102 */
    uint32_t bad[16] = {3u << 24, 2, 5, 0x11, 1, 0, 0, 0, 60, 100, 0};
    CHECK(snd_sk(bad) == -102, "bad track state");
    uint32_t unk[16] = {6u << 24, 0};
    CHECK(snd_sk(unk) == -310, "unregistered module");
    return g_fail;
}

static int t_midi(void)
{
    snd_ee_bank b;
    CHECK(boot_synthetic(&b, 1) == 0, "boot + load with sq");
    CHECK(b.midi_track == 1, "midi track %d", b.midi_track);
    CHECK(snd_track_status(b.midi_track) == 3, "status");
    CHECK(snd_ee_seq_play(b.midi_track, 0, 0x80) == 0, "play");
    CHECK(snd_midi_playing(b.midi_track), "playing");
    snd_render(NULL, 200); /* first SK tick: note on */
    CHECK(snd_voices_playing() == 1, "note on at the first tick (%d)", snd_voices_playing());
    snd_render(NULL, 23800 - 200);
    CHECK(spu2_voice_get(snd_spu(), 0, 0)->phase != SPU2_ENV_RELEASE, "held until tick 120");
    snd_render(NULL, 200); /* frame 24000: 480 ticks at 120 BPM = 0.5 s */
    CHECK(spu2_voice_get(snd_spu(), 0, 0)->phase == SPU2_ENV_RELEASE, "note off at frame 24000");
    CHECK(!snd_midi_playing(b.midi_track), "ended at FF 2F");
    CHECK(snd_get_stats()->seq_notes == 1, "one note");
    /* replay after the end rewinds */
    CHECK(snd_ee_seq_play(b.midi_track, 0, 0x40) == 0 && snd_midi_playing(b.midi_track), "replay");
    snd_render(NULL, 400);
    CHECK(snd_get_stats()->seq_notes == 2, "second note");
    snd_ee_seq_stop(b.midi_track);
    CHECK(!snd_midi_playing(b.midi_track), "stopped");
    return g_fail;
}

/* ---- pcm_mixer ring ---------------------------------------------------------------------------------------------- */
static int t_pcm_ring(int control)
{
    CHECK(snd_ee_boot() == 0, "boot");
    snd_sdremote(0x8010, (SPU2_P_MMIX << 8) | 1, SPU2_MMIX_SINL | SPU2_MMIX_SINR, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLL << 8) | 0x81, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLR << 8) | 0x81, 0x3FFF, 0, 0, 0, 0);
    uint32_t init[3] = {1, 0x1000, 3};
    CHECK(snd_pcm_rpc(0x8000, 3, init) == 0, "init");
    uint32_t bad[3] = {2, 0x1000, 3};
    CHECK(snd_pcm_rpc(0x8000, 3, bad) == -1, "bad core rejected");
    CHECK(snd_pcm_rpc(0x8000, 3, init) == 0, "re-init");
    uint32_t port0 = 0;
    CHECK(snd_pcm_rpc(0x80A0, 1, &port0) == 1, "free distance 1 at start");
    uint32_t staging = iop_heap_alloc(0x1004);
    int16_t blkA[2048], blkB[2048];
    for (int i = 0; i < 2048; i++) {
        blkA[i] = (int16_t)((i * 37) % 20000 - 10000);
        blkB[i] = (int16_t)((i * 91) % 30000 - 15000);
    }
    iop_write(staging, blkA, sizeof blkA);
    uint32_t mix[4] = {0, staging, 0x7FFF, 0x7FFF};
    CHECK(snd_pcm_rpc(0x8090, 4, mix) == 1, "mix A");
    CHECK(snd_pcm_rpc(0x80A0, 1, &port0) == 2, "distance 2");
    iop_write(staging, blkB, sizeof blkB);
    CHECK(snd_pcm_rpc(0x8090, 4, mix) == 1, "mix B");
    CHECK(snd_pcm_rpc(0x80A0, 1, &port0) == 0, "full");
    CHECK(snd_pcm_rpc(0x8090, 4, mix) == 0, "mix refused when full");
    uint32_t badport[4] = {4, staging, 0x7FFF, 0x7FFF};
    CHECK(snd_pcm_rpc(0x8090, 4, badport) == -1, "bad port");
    CHECK(snd_pcm_rpc(0x8100, 0, NULL) == 0, "start");
    static int16_t out[6144 * 2];
    snd_render(out, 6144);
    /* A plays at frames 3072..4095, B at 4096..5119 (one-block ring latency + DMA half) */
    int first = control ? 2048 : 3072;
    int bad_samples = 0;
    for (int f = 0; f < 2048 && bad_samples < 5; f++) {
        const int16_t *src = f < 1024 ? blkA : blkB;
        int g = f % 1024, pair = g / 256, k = g % 256;
        int32_t sl = src[pair * 512 + k], sr = src[pair * 512 + 256 + k];
        int32_t el = ((((sl * 0x7FFF) >> 15) * 0x7FFF) >> 15) * 0x7FFE >> 15;
        int32_t er = ((((sr * 0x7FFF) >> 15) * 0x7FFF) >> 15) * 0x7FFE >> 15;
        if (out[2 * (first + f)] != el || out[2 * (first + f) + 1] != er) {
            CHECK(0, "frame %d: %d/%d want %d/%d", first + f, out[2 * (first + f)], out[2 * (first + f) + 1], el, er);
            bad_samples++;
        }
    }
    for (int f = 0; f < 3072; f++)
        if (out[2 * f] || out[2 * f + 1]) {
            CHECK(control, "silence before A at frame %d", f);
            break;
        }
    /* after consuming, the port can write again; an idle port is pushed ahead (underrun) */
    int d = snd_pcm_rpc(0x80A0, 1, &port0);
    CHECK(d > 0, "distance after drain %d", d);
    CHECK(snd_pcm_rpc(0x8400, 0, NULL) == 0, "stop");
    CHECK(snd_pcm_rpc(0x8400, 0, NULL) == 1, "stop when stopped");
    CHECK(snd_pcm_rpc(0x0010, 0, NULL) == 0, "shutdown");
    return g_fail;
}

/* ---- movie audio: 0x80E0 / 0x8100 on the virtual clock ---------------------------------------------------------- */
static uint64_t sifclock(void *u)
{
    (void)u;
    return sif_now();
}

static int t_movie(int control)
{
    CHECK(snd_ee_boot() == 0, "boot");
    snd_set_clock(sifclock, NULL);
    uint32_t ring = iop_heap_alloc(0x6000);
    uint32_t zero = iop_heap_alloc(0x800);
    CHECK(snd_sdremote(0x80E0, 0, 0x13, ring, 0x6000, ring + 0x400, 0) == 0, "BlockTrans start");
    /* the DMA position runs two units ahead of playback: the start copies the
     * start unit and the next into the core's input buffer */
    uint32_t st = (uint32_t)snd_sdremote(0x8100, 0, 0, 0, 0, 0, 0);
    CHECK(st == ring + 0xC00, "start position %X", st);
    sif_advance(256ull * SND_CYCLES_PER_FRAME);
    st = (uint32_t)snd_sdremote(0x8100, 0, 0, 0, 0, 0, 0);
    CHECK(st == ring + 0x1000, "after 256 frames %X", st);
    uint32_t rate = control ? 44100 : 48000; /* control: the wrong rate must fail */
    sif_advance((uint64_t)(48000 - 256) * SND_CYCLES_PER_FRAME);
    st = (uint32_t)snd_sdremote(0x8100, 0, 0, 0, 0, 0, 0);
    uint32_t units = rate / 256 + 3; /* 1 s of units + the start offset unit + 2 buffered */
    uint32_t off = (units * 0x400) % 0x6000;
    uint32_t want = ((off >= 0x3000 ? 1u : 0u) << 24) | (ring + off);
    CHECK(st == want, "after 1 s: %X want %X", st, want);
    /* pause: STOP returns the same form and freezes the position */
    uint32_t stop = (uint32_t)snd_sdremote(0x80E0, 0, 2, 0, 0, 0, 0);
    CHECK(stop == st, "STOP reply %X", stop);
    sif_advance(48000ull * SND_CYCLES_PER_FRAME);
    CHECK((uint32_t)snd_sdremote(0x8100, 0, 0, 0, 0, 0, 0) == st, "frozen while stopped");
    /* the input-buffer clear: VoiceTrans PIO of the zero buffer to SPU 0x4000 */
    spu2_ram_fill(snd_spu(), 0x4000, 0xAA, 0x800);
    CHECK(snd_sdremote(0x80D0, 0, 8, zero, 0x4000, 0x800, 0) == 0x800, "VoiceTrans");
    uint8_t chk[16];
    spu2_ram_read(snd_spu(), 0x4000, chk, 16);
    CHECK(chk[0] == 0 && chk[15] == 0, "SPU RAM cleared");
    /* host side: the FIFO received exactly the rendered frames */
    CHECK(snd_output_available() == 96000 || snd_output_dropped() > 0, "FIFO %u", snd_output_available());
    CHECK(snd_frames_rendered() == 96000, "rendered %llu", (unsigned long long)snd_frames_rendered());
    uint64_t sum = 0;
    for (uint64_t k = 0; k < 60; k++)
        sum += snd_frames_for_field(k);
    CHECK(sum == 48048, "60 fields = 48048 frames (%llu)", (unsigned long long)sum);
    return g_fail;
}

/* ---- movie audio: the EE's first refill after the start must not reach unplayed units ------------------------------ */
/* AudioDecSendToIop_1d2e90 / AudioDecIopGetArea_1d2df0: after the preset (one full
 * ring, write position back at 0) and the start, free = ((pos - ring) + size - write
 * - 0x400) % size, rounded down to 1 KiB, where pos is the 0x8100 position. The EE
 * then writes `free` bytes at the write position. Every unit of the preset must
 * still be heard, in order. control: expects the old behaviour (the refill wins). */
static int t_movie_refill(int control)
{
    CHECK(snd_ee_boot() == 0, "boot");
    snd_set_clock(sifclock, NULL);
    const uint32_t size = 0x6000, nunits = size / 0x400;
    uint32_t ring = iop_heap_alloc(size);
    int16_t *r = (int16_t *)iop_ptr(ring, size);
    CHECK(r != NULL, "ring");
    if (!r)
        return g_fail;
    for (uint32_t u = 0; u < nunits; u++) /* preset: unit u holds L = 100 (u+1), R = -100 (u+1) */
        for (int k = 0; k < 256; k++) {
            r[u * 512 + k] = (int16_t)(100 * (u + 1));
            r[u * 512 + 256 + k] = (int16_t)(-100 * (int)(u + 1));
        }
    /* the game's core 0 input path: BVOL 0x7FFF, MMIX dry SIN (as AudioDecStart / SoundSpuInit) */
    snd_sdremote(0x8010, (SPU2_P_BVOLL << 8) | 0x80, 0x7FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_BVOLR << 8) | 0x80, 0x7FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MMIX << 8) | 0, 0xFFCC, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLL << 8) | 0x80, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLR << 8) | 0x80, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLL << 8) | 0x81, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, (SPU2_P_MVOLR << 8) | 0x81, 0x3FFF, 0, 0, 0, 0);
    snd_sync();
    uint32_t before = (uint32_t)snd_frames_rendered();
    int16_t junk[2];
    while (snd_output_read(junk, 1)) {
    }
    CHECK(snd_sdremote(0x80E0, 0, 0x13, ring, size, ring, 0) == 0, "start");
    uint32_t pos = ((uint32_t)snd_sdremote(0x8100, 0, 0, 0, 0, 0, 0) & 0xFFFFFFu) - ring;
    uint32_t wr = 0;
    uint32_t free_b = ((pos + size - wr - 0x400) % size) / 0x400 * 0x400;
    if (control)
        free_b = ((0 + size - wr - 0x400) % size) / 0x400 * 0x400; /* position = unit being played */
    for (uint32_t b = 0; b < free_b; b += 2) /* the refill: next movie data, here 0x7777 */
        r[(wr + b) % size / 2] = 0x7777;
    /* render the whole preset and check every unit, in order */
    static int16_t out[24 * 256 * 2];
    sif_advance((uint64_t)nunits * 256 * SND_CYCLES_PER_FRAME + SND_CYCLES_PER_FRAME);
    snd_sync();
    uint32_t got = snd_output_read(out, nunits * 256);
    CHECK(got == nunits * 256, "frames %u (rendered from %u)", got, before);
    int bad = 0;
    for (uint32_t u = 0; u < nunits && u * 256 < got; u++) {
        int32_t l = out[(u * 256 + 128) * 2], rr = out[(u * 256 + 128) * 2 + 1];
        int32_t want = 100 * (int32_t)(u + 1);
        /* gains: BVOL 0x7FFF, MVOL 0x3FFF x2, AVOL 0x7FFF, MVOL x2: within 1% */
        if (l < want * 95 / 100 || l > want || rr > -want * 95 / 100 || rr < -want) {
            if (bad++ < 4)
                fprintf(stderr, "  unit %u: L %d R %d, want ~%d/%d\n", u, l, rr, want, -want);
        }
    }
    CHECK(bad == 0, "%d of %u preset units not heard (DMA position %X, EE refill %X bytes)", bad, nunits, pos,
          free_b);
    printf("movie_refill: DMA position at start +0x%X, EE refill 0x%X bytes, %u units checked\n", pos, free_b,
           nunits);
    return g_fail;
}

/* ---- MODHSYN pitch bend and volume chain (docs/SOUND.md "Synth") ---------------------------------------------------- */
/* Synthetic bank: prog/split/sample volume 0x80, sample base note 60 at 48 kHz, split bend
 * range 0x400 both ways, Sset velocity curve 0 (linear). */
static uint32_t sk_voice(int track, uint32_t cmd, int id, int note, uint32_t v)
{
    uint32_t blk[16] = {3u << 24, 2, (uint32_t)track, cmd, (uint32_t)id, 0, (uint32_t)note, v};
    return (uint32_t)snd_sk(blk);
}

static int t_modhsyn_bend(int control)
{
    snd_ee_bank b;
    CHECK(boot_synthetic(&b, 0) == 0, "boot + load");
    const spu2_voice *v = spu2_voice_get(snd_spu(), 0, 0);
    /* key on with the bend the game sends (0x2000): unbent */
    snd_ee_key_on_ex(b.msin_track, 0x70, 0, 0, 60, 127, 0x40, 0x7F, 0x2000);
    CHECK(spu2_voice_active(snd_spu(), 0, 0) && v->pitch == 0x1000, "bend 0x2000: pitch %X", v->pitch);
    /* FD 02 value 0: sub_4c50 (0 - 0x2000) * 0x400 / 8192 = -1024 = -8 semitones (the port's
     * old >> 14 gave -4) */
    uint16_t want = control ? spu2_note2pitch(60, 0, 56, 0) : spu2_note2pitch(60, 0, 52, 0);
    sk_voice(b.msin_track, 0x41, 0x70, 60, 0);
    CHECK(want == (control ? 3251 : 2580), "Note2Pitch reference %u", want);
    CHECK(v->pitch == want, "bend 0: pitch %u want %u", v->pitch, want);
    /* full up: 0x1FFF * 0x400 / 8192 = 1023 (truncated): 8 semitones minus 1/128 */
    sk_voice(b.msin_track, 0x41, 0x70, 60, 0x3FFF);
    CHECK(v->pitch == spu2_note2pitch(60, 0, 60, 1023), "bend 0x3FFF: pitch %u want %u", v->pitch,
          spu2_note2pitch(60, 0, 60, 1023));
    /* -1 step: (-1 * 0x400) / 8192 truncates to 0, not -1 */
    sk_voice(b.msin_track, 0x41, 0x70, 60, 0x1FFF);
    CHECK(v->pitch == 0x1000, "bend 0x1FFF truncates to 0: pitch %X", v->pitch);
    /* another id or note is not touched; id 127 addresses every id */
    sk_voice(b.msin_track, 0x41, 0x71, 60, 0);
    sk_voice(b.msin_track, 0x41, 0x70, 61, 0);
    CHECK(v->pitch == 0x1000, "other id / note untouched: pitch %X", v->pitch);
    sk_voice(b.msin_track, 0x41, 127, 60, 0);
    CHECK(v->pitch == spu2_note2pitch(60, 0, 52, 0), "id 127 = any id: pitch %u", v->pitch);
    return g_fail;
}

static int t_modhsyn_volume(int control)
{
    snd_ee_bank b;
    CHECK(boot_synthetic(&b, 0) == 0, "boot + load");
    const spu2_voice *v = spu2_voice_get(snd_spu(), 0, 0);
    /* the title cursor's words: vel 127, pan 0x40, volume 0x28.  v22 = 128^3 * 127 >> 14 =
     * 16256; note volume (0x28 << 7) / 127 = 40; v24 = 128 * 40 * 16256 >> 14 = 5080.  The
     * port's old product, 0x3FFF * 40 / 127 = 0x1428, is the control. */
    snd_ee_key_on_ex(b.msin_track, 0x70, 0, 0, 60, 127, 0x40, 0x28, 0x2000);
    uint16_t want = control ? 0x1428 : 5080;
    CHECK(v->vol[0].reg == want && v->vol[1].reg == want, "volume 0x28: VOLL/R %X/%X want %X", v->vol[0].reg,
          v->vol[1].reg, want);
    /* volume 0x7F -> 128: v24 = 16256 = 0x3F80 */
    sk_voice(b.msin_track, 0x42, 0x70, 60, 0x7F);
    CHECK(v->vol[0].reg == 0x3F80 && v->vol[1].reg == 0x3F80, "volume 0x7F: %X/%X", v->vol[0].reg, v->vol[1].reg);
    /* FD 01 pan 0x60: offset 32, left gain (63 - 32) * 128 / 63 = 62: 16256 * 62 >> 7 = 7874 */
    sk_voice(b.msin_track, 0x40, 0x70, 60, 0x60);
    CHECK(v->vol[0].reg == 7874 && v->vol[1].reg == 0x3F80, "pan 0x60: %u/%X", v->vol[0].reg, v->vol[1].reg);
    /* pan 0: offset clamped to -63, right gain 0 */
    sk_voice(b.msin_track, 0x40, 0x70, 60, 0);
    CHECK(v->vol[0].reg == 0x3F80 && v->vol[1].reg == 0, "pan 0: %X/%X", v->vol[0].reg, v->vol[1].reg);
    snd_ee_key_off(b.msin_track, 0x70, 0, 0, 60);
    snd_render(NULL, 48000);
    /* the key on's F9 01 pan: x = 0 -> hard left from the start */
    snd_ee_key_on_ex(b.msin_track, 0x71, 0, 0, 60, 127, 0, 0x7F, 0x2000);
    int hv = spu2_voice_active(snd_spu(), 0, 0) ? 0 : 1;
    v = spu2_voice_get(snd_spu(), 0, hv);
    CHECK(v->vol[0].reg == 0x3F80 && v->vol[1].reg == 0, "F9 01 x 0: %X/%X", v->vol[0].reg, v->vol[1].reg);
    snd_ee_key_off(b.msin_track, 0x71, 0, 0, 60);
    snd_render(NULL, 48000);
    /* velocity 64, linear curve: v22 = 128^3 * 64 >> 14 = 8192, at volume 0x7F: 0x2000 */
    snd_ee_key_on_ex(b.msin_track, 0x72, 0, 0, 60, 64, 0x40, 0x7F, 0x2000);
    v = spu2_voice_get(snd_spu(), 0, 0);
    CHECK(v->vol[0].reg == 0x2000, "velocity 64: %X", v->vol[0].reg);
    snd_ee_key_off(b.msin_track, 0x72, 0, 0, 60);
    /* Sset velocity curve 2 (v * v / 127): velocity 64 -> 32, v22 = 4096 */
    static uint8_t hd[HD_SIZE], bd[BD_BLOCKS * 16];
    make_hd(hd, sizeof bd, 0x000F, 0x1FC0 | 0x0A);
    hd[0xC4] = 2;
    make_bd(bd);
    CHECK(snd_ee_boot() == 0 && snd_ee_load_bank(hd, HD_SIZE, bd, sizeof bd, 0x5040, 0, NULL, 0, &b) == 0, "curve bank");
    snd_ee_key_on_ex(b.msin_track, 0x70, 0, 0, 60, 64, 0x40, 0x7F, 0x2000);
    v = spu2_voice_get(snd_spu(), 0, 0);
    CHECK(v->vol[0].reg == 0x1000, "curve 2, velocity 64: %X", v->vol[0].reg);
    return g_fail;
}

/* ---- deterministic render hash ------------------------------------------------------------------------------------- */
/* pinned 2026-10-12 (MODHSYN volume chain, bend / 8192, F9 01 pan); changes when the engine output changes */
#define GOLDEN_HASH 0xe9f27e51846e7ed7ull
static uint64_t render_scene(void)
{
    snd_ee_bank b;
    if (boot_synthetic(&b, 1) != 0)
        return 0;
    static int16_t buf[48000 * 2];
    snd_ee_seq_play(b.midi_track, 0, 0x60);
    snd_ee_key_on(b.msin_track, 0x66, 0, 0, 67, 100);
    snd_render(buf, 12000);
    uint32_t bend[16] = {3u << 24, 2, (uint32_t)b.msin_track, 0x41, 0x66, 0, 67, 0x3000};
    snd_sk(bend);
    snd_render(buf + 24000, 12000);
    snd_ee_key_off(b.msin_track, 0x66, 0, 0, 67);
    snd_render(buf + 48000, 24000);
    return fnv(buf, 48000 * 2);
}

static int t_render_hash(void)
{
    uint64_t a = render_scene(), b = render_scene();
    printf("render_hash: %016llx\n", (unsigned long long)a);
    CHECK(a != 0 && a == b, "run-to-run %016llx vs %016llx", (unsigned long long)a, (unsigned long long)b);
    if (GOLDEN_HASH)
        CHECK(a == GOLDEN_HASH, "golden %016llx", (unsigned long long)GOLDEN_HASH);
    return g_fail;
}

/* ---- reverb: a wet voice produces a tail after it stops ------------------------------------------------------------- */
static int t_reverb(void)
{
    spu2 *s = &g_spu;
    spu_basic(s);
    spu2_set_addr(s, SPU2_A_EEA | 0, 0x1FFFFF);
    spu2_set_effect_attr(s, 0, SPU2_REV_HALL | SPU2_REV_CLEAR_WA, 0x7FFF, 0x7FFF, 0, 0);
    CHECK(spu2_get_addr(s, SPU2_A_ESA) == 0x200000 - 0xADE0, "hall ESA %X", spu2_get_addr(s, SPU2_A_ESA));
    spu2_set_core_attr(s, SPU2_C_EFFECT_ENABLE | 0, 1);
    spu2_set_param(s, (SPU2_P_MMIX << 8) | 0, 0xFFFF);
    spu2_set_switch(s, (SPU2_S_VMIXEL << 8) | 0, 1);
    spu2_set_switch(s, (SPU2_S_VMIXER << 8) | 0, 1);
    uint8_t g[3] = {0, 0, 1};
    write_wave(s, 0x4000, 3, g);
    spu2_voice_setup(s, 0, 0, 0x4000, 0x1000, 0x000F, 0x1FC0, 0x3FFF, 0x3FFF);
    spu2_key_on(s, 0, 1);
    static int16_t out[24000 * 2];
    spu2_render(s, out, 24000);
    int tail = 0;
    for (int f = 2000; f < 24000; f++)
        if (out[2 * f] || out[2 * f + 1])
            tail = f;
    CHECK(!spu2_voice_active(s, 0, 0), "dry voice ended");
    CHECK(tail > 4000, "reverb tail until frame %d", tail);
    return g_fail;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-sound-tests <test>\n");
        return 2;
    }
    setvbuf(stdout, NULL, _IONBF, 0);
    const char *t = argv[1];
    int r;
    if (!strcmp(t, "adpcm")) r = t_adpcm(0);
    else if (!strcmp(t, "adpcm_control")) r = t_adpcm(1);
    else if (!strcmp(t, "adsr")) r = t_adsr();
    else if (!strcmp(t, "pitch")) r = t_pitch();
    else if (!strcmp(t, "loop")) r = t_loop();
    else if (!strcmp(t, "hd_synthetic")) r = t_hd_synthetic();
    else if (!strcmp(t, "hd_real")) r = t_hd_real();
    else if (!strcmp(t, "se_keyon")) r = t_se_keyon();
    else if (!strcmp(t, "se_keyon_real")) r = t_se_keyon_real();
    else if (!strcmp(t, "midi")) r = t_midi();
    else if (!strcmp(t, "pcm_ring")) r = t_pcm_ring(0);
    else if (!strcmp(t, "pcm_ring_control")) r = t_pcm_ring(1);
    else if (!strcmp(t, "movie")) r = t_movie(0);
    else if (!strcmp(t, "movie_control")) r = t_movie(1);
    else if (!strcmp(t, "movie_refill")) r = t_movie_refill(0);
    else if (!strcmp(t, "movie_refill_control")) r = t_movie_refill(1);
    else if (!strcmp(t, "render_hash")) r = t_render_hash();
    else if (!strcmp(t, "modhsyn_bend")) r = t_modhsyn_bend(0);
    else if (!strcmp(t, "modhsyn_bend_control")) r = t_modhsyn_bend(1);
    else if (!strcmp(t, "modhsyn_volume")) r = t_modhsyn_volume(0);
    else if (!strcmp(t, "modhsyn_volume_control")) r = t_modhsyn_volume(1);
    else if (!strcmp(t, "reverb")) r = t_reverb();
    else {
        fprintf(stderr, "unknown test %s\n", t);
        return 2;
    }
    if (r == 77) {
        printf("SKIP %s (set RG_DATA to the extracted data folder)\n", t);
        return 77;
    }
    printf("%s %s\n", r ? "FAIL" : "PASS", t);
    return r ? 1 : 0;
}
