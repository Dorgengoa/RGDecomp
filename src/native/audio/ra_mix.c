/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine: sound generation and mixing (docs/NATIVE-AUDIO.md "Engine").
 *
 * Carried over from the bring-up SPU2 model (src/ps2/spu/spu2.c, docs/SOUND.md), whose
 * formulas came from public documentation (psx-spx ADPCM / envelope / reverb) and the
 * retail LIBSD.IRX reverb tables:
 *   - PS-ADPCM decoded block by block from the bank's BD bytes in host memory (loop
 *     start / loop end / repeat flags, decoder history carried across the loop jump),
 *   - pitch as a 12-bit phase step (0x1000 = 48 kHz), 4-tap cubic B-spline interpolation,
 *   - ADSR envelope generator (integer state machine, as the bank data expects),
 *   - two mix buses: voice dry/wet sums, a stream input, bus 0 chained into bus 1,
 *     psx-style reverb at 24 kHz on a per-bus work buffer, master gain.
 * What is gone: sound RAM, voice/core registers, KON/KOFF switch words, MMIX/VMIX
 * masks, AutoDMA, address registers.  Mixing is float; the reverb network keeps its
 * integer arithmetic on its own s16 buffer (its taps and saturation are part of the
 * sound).  The bus outputs are not clipped to s16 between stages (the hardware did);
 * only the final output is. */
#include <stdlib.h>
#include <string.h>

#include "ra_internal.h"

static inline int16_t clamp16(int32_t v) { return (int16_t)(v < -32768 ? -32768 : v > 32767 ? 32767 : v); }
static inline int16_t clamp16f(float v)
{
    if (v >= 32767.0f) return 32767;
    if (v <= -32768.0f) return -32768;
    return (int16_t)(v < 0 ? v - 0.5f : v + 0.5f);
}

/* ---- blobs -------------------------------------------------------------------------- */
ra_blob *ra_blob_new(const void *src, uint32_t size)
{
    ra_blob *b = (ra_blob *)malloc(sizeof(ra_blob) + (size ? size : 1));
    if (!b)
        return NULL;
    b->refs = 1;
    b->size = size;
    if (size && src)
        memcpy(b->data, src, size);
    else if (size)
        memset(b->data, 0, size);
    return b;
}

void ra_blob_ref(ra_blob *b)
{
    if (b)
        b->refs++;
}

void ra_blob_unref(ra_blob *b)
{
    if (b && --b->refs <= 0)
        free(b);
}

/* ---- PS-ADPCM -------------------------------------------------------------------------- */
static const int8_t k_filter[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};

uint8_t ra_adpcm_decode_block(const uint8_t blk[16], int16_t out[28], int16_t hist[2])
{
    int shift = blk[0] & 0x0F;
    int filter = (blk[0] >> 4) & 0x0F;
    if (shift > 12)
        shift = 9;
    if (filter > 4)
        filter = 4;
    int32_t f0 = k_filter[filter][0], f1 = k_filter[filter][1];
    int32_t s1 = hist[0], s2 = hist[1];
    for (int i = 0; i < 28; i++) {
        int nib = (blk[2 + (i >> 1)] >> ((i & 1) * 4)) & 0x0F;
        int32_t smp = (int32_t)(int16_t)(uint16_t)(nib << 12) >> shift;
        smp += (s1 * f0 + s2 * f1 + 32) >> 6;
        int16_t o = clamp16(smp);
        out[i] = o;
        s2 = s1;
        s1 = o;
    }
    hist[0] = (int16_t)s1;
    hist[1] = (int16_t)s2;
    return blk[1];
}

/* ---- envelope (psx-spx "Envelope Operation") ---------------------------------------------- */
static int32_t env_step(ra_env *e, int rate, int decreasing, int exponential)
{
    int shift = (rate >> 2) & 0x1F, st = rate & 3;
    int32_t sv = decreasing ? (-8 + st) : (7 - st);
    int32_t cycles = 1;
    if (shift > 11)
        cycles = 1 << (shift - 11);
    else
        sv <<= (11 - shift);
    if (exponential && !decreasing && e->level > 0x6000)
        cycles <<= 2;
    if (exponential && decreasing)
        sv = (sv * e->level) >> 15;
    if (++e->wait < cycles)
        return e->level;
    e->wait = 0;
    int32_t l = e->level + sv;
    e->level = l < 0 ? 0 : l > 0x7FFF ? 0x7FFF : l;
    return e->level;
}

static void env_enter(ra_voice *v, int phase)
{
    v->phase = phase;
    v->env.wait = 0;
}

static void voice_env_tick(ra_voice *v)
{
    switch (v->phase) {
    case RA_ENV_ATTACK:
        env_step(&v->env, (v->adsr1 >> 8) & 0x7F, 0, (v->adsr1 >> 15) & 1);
        if (v->env.level >= 0x7FFF)
            env_enter(v, RA_ENV_DECAY);
        break;
    case RA_ENV_DECAY:
        if ((v->env.level >> 11) <= (v->adsr1 & 0xF)) {
            env_enter(v, RA_ENV_SUSTAIN);
            break;
        }
        env_step(&v->env, ((v->adsr1 >> 4) & 0xF) << 2, 1, 1);
        break;
    case RA_ENV_SUSTAIN:
        env_step(&v->env, (v->adsr2 >> 6) & 0x7F, (v->adsr2 >> 14) & 1, (v->adsr2 >> 15) & 1);
        break;
    case RA_ENV_RELEASE:
        env_step(&v->env, (v->adsr2 & 0x1F) << 2, 1, (v->adsr2 >> 5) & 1);
        if (v->env.level <= 0) {
            v->env.level = 0;
            v->phase = RA_ENV_OFF;
        }
        break;
    default: break;
    }
}

/* ---- pitch (sceSdNote2Pitch semantics) ------------------------------------------------------- */
static const uint32_t k_semi[12] = {65536, 69433, 73562, 77936, 82570, 87480,
                                     92682, 98193, 104032, 110218, 116772, 123715};
static const uint32_t k_fine[128] = {
    65536, 65566, 65595, 65625, 65654, 65684, 65714, 65743, 65773, 65803, 65832, 65862, 65892, 65922, 65951, 65981,
    66011, 66041, 66071, 66100, 66130, 66160, 66190, 66220, 66250, 66280, 66309, 66339, 66369, 66399, 66429, 66459,
    66489, 66519, 66549, 66579, 66609, 66639, 66670, 66700, 66730, 66760, 66790, 66820, 66850, 66880, 66911, 66941,
    66971, 67001, 67032, 67062, 67092, 67122, 67153, 67183, 67213, 67244, 67274, 67304, 67335, 67365, 67395, 67426,
    67456, 67487, 67517, 67548, 67578, 67609, 67639, 67670, 67700, 67731, 67761, 67792, 67823, 67853, 67884, 67915,
    67945, 67976, 68007, 68037, 68068, 68099, 68129, 68160, 68191, 68222, 68252, 68283, 68314, 68345, 68376, 68407,
    68438, 68468, 68499, 68530, 68561, 68592, 68623, 68654, 68685, 68716, 68747, 68778, 68809, 68840, 68871, 68902,
    68933, 68965, 68996, 69027, 69058, 69089, 69120, 69152, 69183, 69214, 69245, 69276, 69308, 69339, 69370, 69402};

uint16_t ra_note2pitch(int center_note, int center_fine, int note, int fine)
{
    int32_t total = (note - center_note) * 128 + (fine - center_fine);
    int32_t oct = total >= 0 ? total / 1536 : -((-total + 1535) / 1536);
    int32_t rem = total - oct * 1536;
    uint64_t p = (uint64_t)k_semi[rem >> 7] * k_fine[rem & 127];
    p *= 0x1000u;
    if (oct >= 0) {
        if (oct > 4)
            return 0x3FFF;
        p <<= oct;
    } else {
        if (oct < -20)
            return 0;
        p >>= -oct;
    }
    uint64_t r = (p + 0x80000000u) >> 32;
    return (uint16_t)(r > 0x3FFF ? 0x3FFF : r);
}

/* ---- interpolation: uniform cubic B-spline, 256 phases ------------------------------------- */
static float g_w[256][4];
static int g_w_ready;

static void interp_init(void)
{
    if (g_w_ready)
        return;
    for (int i = 0; i < 256; i++) {
        /* the same exact-integer Q15 weights as the HLE, then as floats */
        int64_t t = i, u = 256 - t;
        const int64_t den = 6LL * 256 * 256 * 256;
        int32_t w0 = (int32_t)((u * u * u * 32768) / den);
        int32_t w3 = (int32_t)((t * t * t * 32768) / den);
        int32_t w2 = (int32_t)(((-3 * t * t * t + 3 * 256 * t * t + 3 * 256 * 256 * t + 256LL * 256 * 256) * 32768) / den);
        int32_t w1 = 32768 - w0 - w2 - w3;
        g_w[i][0] = (float)w0 / 32768.0f;
        g_w[i][1] = (float)w1 / 32768.0f;
        g_w[i][2] = (float)w2 / 32768.0f;
        g_w[i][3] = (float)w3 / 32768.0f;
    }
    g_w_ready = 1;
}

/* ---- reverb (psx-spx "Reverb Formula"; presets and sizes from LIBSD.IRX) ----------------------- */
static const uint16_t k_rev_size[10] = {0x0002, 0x04D8, 0x03E8, 0x0908, 0x0DFC,
                                        0x15BC, 0x1ED8, 0x3008, 0x3008, 0x0780};
static const uint16_t k_rev_preset[10][32] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x007D, 0x005B, 0x6D80, 0x54B8, 0xBED0, 0x0000, 0x0000, 0xBA80, 0x5800, 0x5300, 0x04D6, 0x0333,
     0x03F0, 0x0227, 0x0374, 0x01EF, 0x0336, 0x01B7, 0x0335, 0x01B6, 0x0334, 0x01B5, 0x0334, 0x01B5,
     0x0334, 0x01B5, 0x01B4, 0x0136, 0x00B8, 0x005C, 0x8000, 0x8000},
    {0x0033, 0x0025, 0x70F0, 0x4FA8, 0xBCE0, 0x4410, 0xC0F0, 0x9C00, 0x5280, 0x4EC0, 0x03E4, 0x031B,
     0x03A4, 0x02AF, 0x0372, 0x0266, 0x031C, 0x025D, 0x025C, 0x018E, 0x022F, 0x0135, 0x01D2, 0x00B7,
     0x018F, 0x00B5, 0x00B4, 0x0080, 0x004C, 0x0026, 0x8000, 0x8000},
    {0x00B1, 0x007F, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xB4C0, 0x5280, 0x4EC0, 0x0904, 0x076B,
     0x0824, 0x065F, 0x07A2, 0x0616, 0x076C, 0x05ED, 0x05EC, 0x042E, 0x050F, 0x0305, 0x0462, 0x02B7,
     0x042F, 0x0265, 0x0264, 0x01B2, 0x0100, 0x0080, 0x8000, 0x8000},
    {0x00E3, 0x00A9, 0x6F60, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xA680, 0x5680, 0x52C0, 0x0DFB, 0x0B58,
     0x0D09, 0x0A3C, 0x0BD9, 0x0973, 0x0B59, 0x08DA, 0x08D9, 0x05E9, 0x07EC, 0x04B0, 0x06EF, 0x03D2,
     0x05EA, 0x031D, 0x031C, 0x0238, 0x0154, 0x00AA, 0x8000, 0x8000},
    {0x01A5, 0x0139, 0x6000, 0x5000, 0x4C00, 0xB800, 0xBC00, 0xC000, 0x6000, 0x5C00, 0x15BA, 0x11BB,
     0x14C2, 0x10BD, 0x11BC, 0x0DC1, 0x11C0, 0x0DC3, 0x0DC0, 0x09C1, 0x0BC4, 0x07C1, 0x0A00, 0x06CD,
     0x09C2, 0x05C1, 0x05C0, 0x041A, 0x0274, 0x013A, 0x8000, 0x8000},
    {0x033D, 0x0231, 0x7E00, 0x5000, 0xB400, 0xB000, 0x4C00, 0xB000, 0x6000, 0x5400, 0x1ED6, 0x1A31,
     0x1D14, 0x183B, 0x1BC2, 0x16B2, 0x1A32, 0x15EF, 0x15EE, 0x1055, 0x1334, 0x0F2D, 0x11F6, 0x0C5D,
     0x1056, 0x0AE1, 0x0AE0, 0x07A2, 0x0464, 0x0232, 0x8000, 0x8000},
    {0x0003, 0x0003, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x8100, 0x0000, 0x0000, 0x1FFD, 0x0FFD,
     0x1009, 0x0009, 0x0000, 0x0000, 0x1009, 0x0009, 0x1FFF, 0x1FFF, 0x1FFE, 0x1FFE, 0x1FFE, 0x1FFE,
     0x1FFE, 0x1FFE, 0x1008, 0x1004, 0x0008, 0x0004, 0x8000, 0x8000},
    {0x0003, 0x0003, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FFD, 0x0FFD,
     0x1009, 0x0009, 0x0000, 0x0000, 0x1009, 0x0009, 0x1FFF, 0x1FFF, 0x1FFE, 0x1FFE, 0x1FFE, 0x1FFE,
     0x1FFE, 0x1FFE, 0x1008, 0x1004, 0x0008, 0x0004, 0x8000, 0x8000},
    {0x0017, 0x0013, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0x8500, 0x5F80, 0x54C0, 0x0371, 0x02AF,
     0x02E5, 0x01DF, 0x02B0, 0x01D7, 0x0358, 0x026A, 0x01D6, 0x011E, 0x012D, 0x00B1, 0x011F, 0x0059,
     0x01A0, 0x00E3, 0x0058, 0x0040, 0x0028, 0x0014, 0x8000, 0x8000},
};

int ra_hd_rev_size_halfwords(int mode)
{
    mode &= 0xFF;
    if (mode < 0 || mode >= 10)
        mode = 0;
    return (int)k_rev_size[mode] * 4;
}

void ra_reverb_set(ra_bus *b, int mode, int clear)
{
    ra_reverb *rv = &b->rev;
    int m = mode & 0xFF;
    if (m >= 10)
        m = 0;
    uint32_t size = (uint32_t)ra_hd_rev_size_halfwords(m);
    if (rv->size != size || !rv->buf) {
        free(rv->buf);
        rv->buf = (int16_t *)calloc(size, sizeof(int16_t));
        rv->size = rv->buf ? size : 0;
    } else if (clear) {
        memset(rv->buf, 0, size * sizeof(int16_t));
    }
    rv->mode = m;
    rv->pos = 0;
    rv->acc[0] = rv->acc[1] = 0;
    rv->out[0] = rv->out[1] = 0;
    if (g_ra && b >= g_ra->bus && b < g_ra->bus + RA_BUSES)
        ra_present_reverb_changed((int)(b - g_ra->bus));
}

/* one 24 kHz step; same integer network as the HLE (spu2.c rev_step) on our buffer */
static void rev_step(ra_reverb *rv, int32_t in_l, int32_t in_r)
{
    if (!rv->buf || !rv->size)
        return;
    const uint16_t *r = k_rev_preset[rv->mode];
    uint32_t size = rv->size;
    int16_t *m = rv->buf;
#define RV(i) ((int32_t)(int16_t)r[i])
#define OFS(i) ((uint32_t)r[i] * 4u)
#define AT(o) ((rv->pos + (o)) % size)
#define RD(o) ((int32_t)m[AT(o)])
#define WR(o, v) (m[AT(o)] = clamp16(v))
    uint32_t m1 = size - 1;
    int32_t lin = (in_l * RV(30)) >> 15, rin = (in_r * RV(31)) >> 15;
    int32_t vwall = RV(7), viir = RV(2);
    {
        int32_t prev = RD(OFS(10) + m1);
        WR(OFS(10), (((lin + ((RD(OFS(16)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
        prev = RD(OFS(11) + m1);
        WR(OFS(11), (((rin + ((RD(OFS(17)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
    }
    {
        int32_t prev = RD(OFS(18) + m1);
        WR(OFS(18), (((lin + ((RD(OFS(25)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
        prev = RD(OFS(19) + m1);
        WR(OFS(19), (((rin + ((RD(OFS(24)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
    }
    int32_t lo = (RV(3) * RD(OFS(12)) + RV(4) * RD(OFS(14)) + RV(5) * RD(OFS(20)) + RV(6) * RD(OFS(22))) >> 15;
    int32_t ro = (RV(3) * RD(OFS(13)) + RV(4) * RD(OFS(15)) + RV(5) * RD(OFS(21)) + RV(6) * RD(OFS(23))) >> 15;
    uint32_t d1 = OFS(0), d2 = OFS(1);
    {
        int32_t t = RD(OFS(26) + size - (d1 % size));
        lo = clamp16(lo - ((RV(8) * t) >> 15));
        WR(OFS(26), lo);
        lo = ((lo * RV(8)) >> 15) + t;
        t = RD(OFS(27) + size - (d1 % size));
        ro = clamp16(ro - ((RV(8) * t) >> 15));
        WR(OFS(27), ro);
        ro = ((ro * RV(8)) >> 15) + t;
    }
    {
        int32_t t = RD(OFS(28) + size - (d2 % size));
        lo = clamp16(lo - ((RV(9) * t) >> 15));
        WR(OFS(28), lo);
        lo = ((lo * RV(9)) >> 15) + t;
        t = RD(OFS(29) + size - (d2 % size));
        ro = clamp16(ro - ((RV(9) * t) >> 15));
        WR(OFS(29), ro);
        ro = ((ro * RV(9)) >> 15) + t;
    }
    rv->out[0] = clamp16(lo);
    rv->out[1] = clamp16(ro);
    rv->pos = (rv->pos + 1) % size;
#undef RV
#undef OFS
#undef AT
#undef RD
#undef WR
}

/* ---- voices ------------------------------------------------------------------------------ */
void ra_voice_start(ra_voice *v, ra_blob *bd, uint32_t ssa)
{
    if (v->bd != bd) {
        ra_blob_unref(v->bd);
        ra_blob_ref(bd);
        v->bd = bd;
    }
    v->ssa = ssa & ~15u;
    v->nax = v->ssa;
    v->lsa = v->ssa;
    v->block_pos = 28;
    v->block_flags = 0;
    v->hist[0] = v->hist[1] = 0;
    v->counter = 0;
    memset(v->ih, 0, sizeof v->ih);
    v->env.level = 0;
    env_enter(v, RA_ENV_ATTACK);
    g_ra->st.key_ons++;
}

void ra_voice_release(ra_voice *v)
{
    if (v->phase != RA_ENV_OFF && v->phase != RA_ENV_RELEASE) {
        env_enter(v, RA_ENV_RELEASE);
        g_ra->st.key_offs++;
    }
}

void ra_voice_cut(ra_voice *v)
{
    v->phase = RA_ENV_OFF;
    v->env.level = 0;
}

void ra_voice_set_volume(ra_voice *v, uint16_t l, uint16_t r)
{
    v->vol_reg[0] = l;
    v->vol_reg[1] = r;
    v->gain[0] = (float)(int16_t)(uint16_t)(l << 1) / 32768.0f;
    v->gain[1] = (float)(int16_t)(uint16_t)(r << 1) / 32768.0f;
}

static int16_t voice_next_sample(ra_voice *v)
{
    if (v->block_pos >= 28) {
        if (v->block_flags & 1) { /* loop end */
            v->nax = v->lsa;
            if (!(v->block_flags & 2)) { /* one-shot: the voice ends */
                v->phase = RA_ENV_OFF;
                v->env.level = 0;
            }
        }
        if (!v->bd || v->nax + 16 > v->bd->size) { /* ran off the sample data */
            v->phase = RA_ENV_OFF;
            v->env.level = 0;
            memset(v->block, 0, sizeof v->block);
            v->block_flags = 0;
        } else {
            v->block_flags = ra_adpcm_decode_block(v->bd->data + v->nax, v->block, v->hist);
            if (v->block_flags & 4)
                v->lsa = v->nax;
            v->nax += 16;
        }
        v->block_pos = 0;
    }
    return v->block[v->block_pos++];
}

/* one output sample of a voice (pre volume), +-32768 scale */
static float voice_tick(ra_voice *v, int interp)
{
    if (v->phase == RA_ENV_OFF)
        return 0.0f;
    float smp;
    switch (interp) {
    case RA_INTERP_NONE: smp = v->ih[3]; break;
    case RA_INTERP_LINEAR: {
        float t = (float)(v->counter & 0xFFF) / 4096.0f;
        smp = v->ih[2] + (v->ih[3] - v->ih[2]) * t;
        break;
    }
    default: {
        const float *w = g_w[(v->counter >> 4) & 0xFF];
        smp = w[0] * v->ih[0] + w[1] * v->ih[1] + w[2] * v->ih[2] + w[3] * v->ih[3];
        break;
    }
    }
    uint32_t step = v->pitch > 0x3FFF ? 0x3FFF : v->pitch;
    v->counter += step;
    while (v->counter >= 0x1000 && v->phase != RA_ENV_OFF) {
        v->counter -= 0x1000;
        int16_t n = voice_next_sample(v);
        v->ih[0] = v->ih[1];
        v->ih[1] = v->ih[2];
        v->ih[2] = v->ih[3];
        v->ih[3] = n;
    }
    voice_env_tick(v);
    if (v->phase == RA_ENV_OFF)
        return 0.0f;
    return smp * (float)v->env.level / 32768.0f;
}

/* ---- PCM stream ports: a ring of blocks played on a bus's stream input ----------------------- */
/* Same scheme as the game's pcm mixer so the game's refill pacing holds: the output
 * plays a double buffer; each time a buffer half has been played it takes ring block
 * rpos (silence if no port wrote it), that ring block is cleared, rpos advances, and
 * ports that fell behind are pushed one block ahead.  Blocks are [256 L][256 R] s16
 * pairs as the game builds them. */
/* the stream volume is the bus's input volume (one setting, as on the hardware) */
static void pcm_set_vol(ra_pcm *p, uint32_t vol)
{
    p->cur_vol = vol;
    g_ra->bus[p->bus & 1].in_vol[0] = (int16_t)(vol >> 16);
    g_ra->bus[p->bus & 1].in_vol[1] = (int16_t)(vol & 0xFFFF);
}

static void pcm_block_done(ra_pcm *p)
{
    uint32_t hw = p->block_bytes / 2;
    int16_t *dst = p->play + (size_t)p->have_play * hw; /* the half just played */
    int16_t *src = p->ring + (size_t)p->rpos * hw;
    memcpy(dst, src, p->block_bytes);
    memset(src, 0, p->block_bytes);
    ra_present_pcm_block(p->rpos, p->have_play); /* the same block per source */
    p->rpos = (p->rpos + 1) % p->nblocks;
    for (int i = 0; i < 4; i++)
        if (p->wpos[i] == p->rpos) {
            p->wpos[i] = (p->rpos + 1) % p->nblocks;
            g_ra->st.pcm_underruns++;
        }
    if (p->pending_vol != p->cur_vol)
        pcm_set_vol(p, p->pending_vol);
}

static int pcm_frame(ra_pcm *p, int bus, float in[2], float cls[RA_PCM_SRCS][2])
{
    if (!p->running || bus != p->bus)
        return 0;
    uint32_t fpb = p->block_bytes / 4;
    const int16_t *h = p->play + (size_t)p->have_play * (p->block_bytes / 2);
    uint32_t f = p->play_pos, pair = f >> 8, k = f & 0xFF;
    in[0] = h[pair * 512 + k];
    in[1] = h[pair * 512 + 256 + k];
    if (cls) /* presentation mix: what each source put into this frame */
        ra_present_pcm_frame(p->have_play, pair * 512 + k, pair * 512 + 256 + k, cls);
    if (++p->play_pos >= fpb) {
        p->play_pos = 0;
        pcm_block_done(p);
        p->have_play ^= 1;
    }
    return 1;
}

/* ---- stream buffers + movie audio ------------------------------------------------------------ */
uint32_t ra_stream_alloc(uint32_t size)
{
    for (int i = 0; i < RA_STREAM_BUFS; i++) {
        ra_sbuf *b = &g_ra->sbuf[i];
        if (b->mem)
            continue;
        b->mem = (uint8_t *)calloc(1, size ? size : 1);
        if (!b->mem)
            return 0;
        b->base = 0x100000u * (uint32_t)(i + 1);
        b->size = size;
        return b->base;
    }
    return 0;
}

static ra_sbuf *sbuf_at(uint32_t addr, uint32_t n)
{
    for (int i = 0; i < RA_STREAM_BUFS; i++) {
        ra_sbuf *b = &g_ra->sbuf[i];
        if (b->mem && addr >= b->base && addr - b->base + (uint64_t)n <= b->size)
            return b;
    }
    return NULL;
}

void ra_stream_free(uint32_t addr)
{
    ra_sync();
    ra_sbuf *b = sbuf_at(addr, 0);
    if (!b)
        return;
    for (int c = 0; c < RA_BUSES; c++) /* a movie playing from it stops */
        if (g_ra->movie[c].running && g_ra->movie[c].ring >= b->base && g_ra->movie[c].ring < b->base + b->size)
            g_ra->movie[c].running = 0;
    free(b->mem);
    memset(b, 0, sizeof *b);
}

int ra_stream_write(uint32_t addr, const void *src, uint32_t n)
{
    ra_sync();
    ra_sbuf *b = sbuf_at(addr, n);
    if (!b || !src)
        return -1;
    memcpy(b->mem + (addr - b->base), src, n);
    return (int)n;
}

static void movie_xfer(ra_movie *m, int h)
{
    const ra_sbuf *b = m->xfer_done ? NULL : sbuf_at(m->ring + m->xfer, 1024);
    if (b)
        memcpy(m->half[h], b->mem + (m->ring + m->xfer - b->base), 1024);
    else
        memset(m->half[h], 0, 1024);
    if (m->xfer_done)
        return;
    m->xfer += 1024;
    if (m->xfer >= m->size) {
        m->xfer = 0;
        if (!m->loop)
            m->xfer_done = 1;
    }
}

static int movie_frame(ra_movie *m, float in[2])
{
    if (!m->running)
        return 0;
    const uint8_t *p = m->half[m->play];
    in[0] = (float)(int16_t)(p[m->k * 2] | p[m->k * 2 + 1] << 8);
    in[1] = (float)(int16_t)(p[512 + m->k * 2] | p[512 + m->k * 2 + 1] << 8);
    m->frames++;
    g_ra->st.movie_frames++;
    if (++m->k == 256) {
        m->k = 0;
        movie_xfer(m, m->play);
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

int ra_movie_start(int bus, uint32_t ring, uint32_t size, uint32_t start, int loop)
{
    ra_sync();
    ra_movie *m = &g_ra->movie[bus & 1];
    m->ring = ring;
    m->size = size & ~1023u;
    if (!m->size)
        return -1;
    m->unit = 0;
    if (start >= ring && start < ring + m->size)
        m->unit = (start - ring) & ~1023u;
    m->k = 0;
    m->loop = loop != 0;
    m->running = 1;
    m->frames = 0;
    m->xfer = m->unit;
    m->xfer_done = 0;
    m->play = 0;
    movie_xfer(m, 0);
    movie_xfer(m, 1);
    return 0;
}

uint32_t ra_movie_position(int bus)
{
    ra_sync();
    const ra_movie *m = &g_ra->movie[bus & 1];
    uint32_t half = (m->size && m->xfer >= m->size / 2) ? 1u : 0u;
    return (half << 24) | ((m->ring + m->xfer) & 0xFFFFFFu);
}

uint32_t ra_movie_stop(int bus)
{
    uint32_t r = ra_movie_position(bus);
    g_ra->movie[bus & 1].running = 0;
    return r;
}

/* ---- buses / render ----------------------------------------------------------------------- */
void ra_mix_reset(void)
{
    interp_init();
    for (int b = 0; b < RA_BUSES; b++) {
        ra_bus *bu = &g_ra->bus[b];
        for (int i = 0; i < RA_BUS_VOICES; i++) {
            ra_blob_unref(bu->v[i].bd);
            bu->v[i].bd = NULL;
        }
        free(bu->rev.buf);
        memset(bu, 0, sizeof *bu);
        for (int i = 0; i < RA_BUS_VOICES; i++)
            bu->v[i].block_pos = 28;
        ra_reverb_set(bu, 0, 1);
    }
    g_ra->bus[1].chain[0] = g_ra->bus[1].chain[1] = 0x7FFF;
}

/* One frame of bus bi.  The model mix (out, b->out) is computed exactly as before the
 * presentation mix existed: the same operations in the same order (SSE floats, no
 * contraction: PLAN.md D2).  With g_rp.on the presentation mix (g_rp.out) runs beside it
 * on the same voice samples: each source's part is scaled by its gain as a DELTA,
 * sum + (g - 1) * part, so with every gain at 1 it is the model's value bit for bit
 * (x + 0 * y == x), and it feeds its own copy of the reverb (g_rp.rev) so a quieter source
 * also leaves a quieter tail. */
static void bus_tick(ra_state *s, int bi, float out[2])
{
    ra_bus *b = &s->bus[bi];
    float dl = 0, dr = 0, wl = 0, wr = 0;
    const int pon = g_rp.on;
    float part[2][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}}; /* [music, effects][dl dr wl wr] */
    int interp = s->cfg.interp;
    for (int i = 0; i < RA_BUS_VOICES; i++) {
        ra_voice *v = &b->v[i];
        if (v->phase == RA_ENV_OFF)
            continue;
        float o = voice_tick(v, interp);
        float l = o * v->gain[0], r = o * v->gain[1];
        if (v->route & 1) dl += l;
        if (v->route & 2) dr += r;
        if (v->route & 4) wl += l;
        if (v->route & 8) wr += r;
        if (pon) { /* sequenced notes are music, the game's key ons are effects */
            float *q = part[v->seq ? 0 : 1];
            if (v->route & 1) q[0] += l;
            if (v->route & 2) q[1] += r;
            if (v->route & 4) q[2] += l;
            if (v->route & 8) q[3] += r;
        }
    }
    float pdl = 0, pdr = 0, pwl = 0, pwr = 0;
    if (pon) {
        const float gm = g_rp.gm1[RA_SRC_MUSIC], ge = g_rp.gm1[RA_SRC_EFFECTS];
        pdl = dl + (gm * part[0][0] + ge * part[1][0]);
        pdr = dr + (gm * part[0][1] + ge * part[1][1]);
        pwl = wl + (gm * part[0][2] + ge * part[1][2]);
        pwr = wr + (gm * part[0][3] + ge * part[1][3]);
    }
    float in[2] = {0, 0};
    float cls[RA_PCM_SRCS][2] = {{0, 0}, {0, 0}, {0, 0}};
    int movie = movie_frame(&s->movie[bi], in);
    if (movie || pcm_frame(&s->pcm, bi, in, pon ? cls : NULL)) {
        float pin[2] = {0, 0};
        if (pon) { /* the stream's source parts, before the input volume */
            for (int c = 0; c < 2; c++) {
                if (movie)
                    pin[c] = g_rp.gm1[RA_SRC_MOVIE] * in[c];
                else
                    pin[c] = g_rp.gm1[RA_SRC_MUSIC] * cls[0][c] + g_rp.gm1[RA_SRC_EFFECTS] * cls[1][c] +
                             g_rp.gm1[RA_SRC_VOICE] * cls[2][c];
            }
        }
        in[0] *= (float)b->in_vol[0] / 32768.0f;
        in[1] *= (float)b->in_vol[1] / 32768.0f;
        dl += in[0];
        dr += in[1];
        if (b->in_wet) {
            wl += in[0];
            wr += in[1];
        }
        if (pon) {
            float p0 = in[0] + pin[0] * ((float)b->in_vol[0] / 32768.0f);
            float p1 = in[1] + pin[1] * ((float)b->in_vol[1] / 32768.0f);
            pdl += p0;
            pdr += p1;
            if (b->in_wet) {
                pwl += p0;
                pwr += p1;
            }
        }
    }
    if (bi == 1) {
        float el = s->bus[0].out[0] * (float)b->chain[0] / 32768.0f;
        float er = s->bus[0].out[1] * (float)b->chain[1] / 32768.0f;
        dl += el;
        dr += er;
        if (b->in_wet) {
            wl += el;
            wr += er;
        }
        if (pon) {
            float pel = g_rp.out[0][0] * (float)b->chain[0] / 32768.0f;
            float per = g_rp.out[0][1] * (float)b->chain[1] / 32768.0f;
            pdl += pel;
            pdr += per;
            if (b->in_wet) {
                pwl += pel;
                pwr += per;
            }
        }
    }
    if (b->effect_on && s->cfg.break_mode != 3) {
        ra_reverb *rv = &b->rev;
        rv->acc[0] += clamp16f(wl);
        rv->acc[1] += clamp16f(wr);
        if (rv->half) {
            rev_step(rv, rv->acc[0] >> 1, rv->acc[1] >> 1);
            rv->acc[0] = rv->acc[1] = 0;
        }
        rv->half ^= 1;
        dl += rv->out[0] * (float)rv->depth[0] / 32768.0f;
        dr += rv->out[1] * (float)rv->depth[1] / 32768.0f;
        if (pon && g_rp.rev_ok[bi]) {
            ra_reverb *pv = &g_rp.rev[bi];
            pv->acc[0] += clamp16f(pwl);
            pv->acc[1] += clamp16f(pwr);
            if (pv->half) {
                rev_step(pv, pv->acc[0] >> 1, pv->acc[1] >> 1);
                pv->acc[0] = pv->acc[1] = 0;
            }
            pv->half ^= 1;
            pdl += pv->out[0] * (float)rv->depth[0] / 32768.0f;
            pdr += pv->out[1] * (float)rv->depth[1] / 32768.0f;
        } else if (pon) { /* no copy (allocation failed): the model's return */
            pdl += rv->out[0] * (float)rv->depth[0] / 32768.0f;
            pdr += rv->out[1] * (float)rv->depth[1] / 32768.0f;
        }
    }
    b->out[0] = dl * (float)(int16_t)(uint16_t)(b->master[0] << 1) / 32768.0f;
    b->out[1] = dr * (float)(int16_t)(uint16_t)(b->master[1] << 1) / 32768.0f;
    if (s->cfg.break_mode == 2 && bi == 1) { /* compare control: 6 dB quiet */
        b->out[0] *= 0.5f;
        b->out[1] *= 0.5f;
    }
    out[0] = b->out[0];
    out[1] = b->out[1];
    if (pon) {
        g_rp.out[bi][0] = pdl * (float)(int16_t)(uint16_t)(b->master[0] << 1) / 32768.0f;
        g_rp.out[bi][1] = pdr * (float)(int16_t)(uint16_t)(b->master[1] << 1) / 32768.0f;
        if (s->cfg.break_mode == 2 && bi == 1) {
            g_rp.out[bi][0] *= 0.5f;
            g_rp.out[bi][1] *= 0.5f;
        }
    }
}

void ra_mix_render(float *lr, float *plr, uint32_t frames)
{
    ra_state *s = g_ra;
    ra_present_begin(frames);
    for (uint32_t i = 0; i < frames; i++) {
        float o0[2], o1[2];
        if (g_rp.on)
            ra_present_frame();
        bus_tick(s, 0, o0);
        bus_tick(s, 1, o1);
        if (lr) {
            lr[2 * i] = o1[0];
            lr[2 * i + 1] = o1[1];
        }
        if (plr) {
            plr[2 * i] = g_rp.on ? g_rp.out[1][0] : o1[0];
            plr[2 * i + 1] = g_rp.on ? g_rp.out[1][1] : o1[1];
        }
    }
    ra_present_end(frames);
}

/* ---- PCM API ------------------------------------------------------------------------------- */
static void pcm_free(void)
{
    ra_pcm *p = &g_ra->pcm;
    free(p->ring);
    free(p->play);
    ra_present_pcm_free();
    uint32_t pv = p->pending_vol;
    memset(p, 0, sizeof *p);
    p->pending_vol = pv;
}

int ra_pcm_init(int bus, uint32_t block_bytes, uint32_t nblocks)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    if (bus < 0 || bus > 1 || block_bytes < 2048 || nblocks < 2)
        return -1;
    pcm_free();
    p->bus = bus;
    p->block_bytes = block_bytes & ~1023u;
    p->nblocks = nblocks;
    p->ring = (int16_t *)calloc(nblocks, p->block_bytes);
    p->play = (int16_t *)calloc(2, p->block_bytes);
    if (!p->ring || !p->play) {
        pcm_free();
        return -1;
    }
    for (int i = 0; i < 4; i++)
        p->wpos[i] = 1 % nblocks;
    p->rpos = 0;
    p->inited = 1;
    ra_present_pcm_init(nblocks, p->block_bytes);
    return 0;
}

int ra_pcm_free_blocks(int port)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    if (!p->inited || port < 0 || port > 3)
        return -1;
    return (int)((p->wpos[port] + p->nblocks - p->rpos) % p->nblocks);
}

int ra_pcm_mix(int port, const void *block, int vol_l, int vol_r)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    if (!p->inited || port < 0 || port > 3 || !block)
        return -1;
    if ((p->wpos[port] + p->nblocks - p->rpos) % p->nblocks == 0)
        return 0;
    const uint8_t *src = (const uint8_t *)block;
    int16_t *dst = p->ring + (size_t)p->wpos[port] * (p->block_bytes / 2);
    for (uint32_t i = 0; i < p->block_bytes / 2; i++) {
        int32_t sv = (int16_t)(src[2 * i] | src[2 * i + 1] << 8);
        int32_t vol = ((i >> 8) & 1) ? vol_r : vol_l;
        int32_t m = dst[i] + ((sv * vol) >> 15);
        dst[i] = clamp16(m);
    }
    ra_present_pcm_mix(port, p->wpos[port], src, vol_l, vol_r);
    p->wpos[port] = (p->wpos[port] + 1) % p->nblocks;
    g_ra->st.pcm_blocks++;
    return 1;
}

int ra_pcm_start(void)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    if (!p->inited)
        return -1;
    if (!p->running) {
        memset(p->play, 0, (size_t)p->block_bytes * 2);
        ra_present_pcm_start();
        p->have_play = 0;
        p->play_pos = 0;
        p->running = 1;
        pcm_set_vol(p, p->pending_vol);
    }
    return 0;
}

int ra_pcm_stop(void)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    if (!p->running)
        return 1;
    p->running = 0;
    pcm_set_vol(p, 0);
    return 0;
}

int ra_pcm_shutdown(void)
{
    if (g_ra->inited)
        ra_sync();
    g_ra->pcm.running = 0;
    pcm_free();
    return 0;
}

void ra_pcm_volume(uint32_t lr, int now)
{
    ra_sync();
    ra_pcm *p = &g_ra->pcm;
    p->pending_vol = lr;
    if (now && p->inited)
        pcm_set_vol(p, lr);
}
