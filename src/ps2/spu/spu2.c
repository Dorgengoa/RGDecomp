/* SPDX-License-Identifier: CC0-1.0 */
/* SPU2 voice engine, see spu2.h and docs/SOUND.md. Written from scratch from public
 * documentation; the reverb presets and work-area sizes are read out of the retail
 * LIBSD.IRX data (offsets 0x4B48 sizes, 0x4B70 presets, 0x44 bytes per mode). */
#include "spu2.h"

#include <string.h>

/* ---- small helpers ---------------------------------------------------------------- */
static inline int16_t clamp16(int32_t v)
{
    return (int16_t)(v < -32768 ? -32768 : v > 32767 ? 32767 : v);
}

static inline int16_t ram_r16(const spu2 *s, uint32_t hw)
{
    uint32_t a = (hw << 1) & (SPU2_RAM_SIZE - 1);
    return (int16_t)(s->ram[a] | (s->ram[a + 1] << 8));
}

static inline void ram_w16(spu2 *s, uint32_t hw, int16_t v)
{
    uint32_t a = (hw << 1) & (SPU2_RAM_SIZE - 1);
    s->ram[a] = (uint8_t)v;
    s->ram[a + 1] = (uint8_t)((uint16_t)v >> 8);
}

void spu2_ram_write(spu2 *s, uint32_t addr, const void *src, uint32_t len)
{
    const uint8_t *p = (const uint8_t *)src;
    for (uint32_t i = 0; i < len; i++)
        s->ram[(addr + i) & (SPU2_RAM_SIZE - 1)] = p[i];
}

void spu2_ram_read(const spu2 *s, uint32_t addr, void *dst, uint32_t len)
{
    uint8_t *p = (uint8_t *)dst;
    for (uint32_t i = 0; i < len; i++)
        p[i] = s->ram[(addr + i) & (SPU2_RAM_SIZE - 1)];
}

void spu2_ram_fill(spu2 *s, uint32_t addr, uint8_t value, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
        s->ram[(addr + i) & (SPU2_RAM_SIZE - 1)] = value;
}

/* ---- PS-ADPCM ---------------------------------------------------------------------- */
/* Prediction filters (positive, negative coefficient) in 1/64 units. Filters above 4
 * are not defined by the documentation; they are clamped to filter 4 (docs/SOUND.md). */
static const int8_t k_filter[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};

uint8_t spu2_adpcm_decode_block(const uint8_t blk[16], int16_t out[28], int16_t hist[2])
{
    int shift = blk[0] & 0x0F;
    int filter = (blk[0] >> 4) & 0x0F;
    if (shift > 12)
        shift = 9; /* shift values 13..15 behave like 9 (psx-spx) */
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

/* ---- envelope ----------------------------------------------------------------------- */
/* psx-spx "Envelope Operation": rate = shift << 2 | step.
 *   cycles = 1 << max(0, shift - 11); step = s << max(0, 11 - shift),
 *   s = 7 - step (increase) / -8 + step (decrease);
 *   exponential increase above 0x6000: cycles * 4; exponential decrease: step * level / 0x8000.
 * The generator waits `cycles` samples, then adds the step (saturating 0..0x7FFF).
 * `wait` counts samples since the last step. */
int32_t spu2_env_step(spu2_env *e, int rate, int decreasing, int exponential)
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

static void env_enter(spu2_voice *v, int phase)
{
    v->phase = phase;
    v->env.wait = 0;
}

static void voice_env_tick(spu2_voice *v)
{
    switch (v->phase) {
    case SPU2_ENV_ATTACK:
        spu2_env_step(&v->env, (v->adsr1 >> 8) & 0x7F, 0, (v->adsr1 >> 15) & 1);
        if (v->env.level >= 0x7FFF)
            env_enter(v, SPU2_ENV_DECAY);
        break;
    case SPU2_ENV_DECAY:
        /* Decay runs while (level >> 11) is above the sustain level; the comparison comes
         * first, so SL = 15 goes straight to sustain at full level. */
        if ((v->env.level >> 11) <= (v->adsr1 & 0xF)) {
            env_enter(v, SPU2_ENV_SUSTAIN);
            break;
        }
        spu2_env_step(&v->env, ((v->adsr1 >> 4) & 0xF) << 2, 1, 1);
        break;
    case SPU2_ENV_SUSTAIN:
        spu2_env_step(&v->env, (v->adsr2 >> 6) & 0x7F, (v->adsr2 >> 14) & 1, (v->adsr2 >> 15) & 1);
        break;
    case SPU2_ENV_RELEASE:
        spu2_env_step(&v->env, (v->adsr2 & 0x1F) << 2, 1, (v->adsr2 >> 5) & 1);
        if (v->env.level <= 0) {
            v->env.level = 0;
            v->phase = SPU2_ENV_OFF;
            v->keyed = 0;
        }
        break;
    default: break;
    }
}

/* ---- volumes (fixed or swept) -------------------------------------------------------- */
static void vol_write(spu2_vol *vo, uint16_t reg)
{
    vo->reg = reg;
    if (!(reg & 0x8000))
        vo->cur = (int16_t)(uint16_t)(reg << 1); /* 15-bit signed value, x2 */
    else {
        int32_t mag = vo->cur < 0 ? -(int32_t)vo->cur : vo->cur;
        vo->sweep.level = mag > 0x7FFF ? 0x7FFF : mag;
        vo->sweep.wait = 0;
    }
}

static void vol_tick(spu2_vol *vo)
{
    uint16_t r = vo->reg;
    if (!(r & 0x8000))
        return;
    spu2_env_step(&vo->sweep, r & 0x7F, (r >> 13) & 1, (r >> 14) & 1);
    vo->cur = (int16_t)((r & 0x1000) ? -vo->sweep.level : vo->sweep.level);
}

/* ---- pitch (sceSdNote2Pitch semantics) ---------------------------------------------- */
/* 2^(k/12) and 2^(k/1536) in Q16, computed offline (round half up). */
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

uint16_t spu2_note2pitch(int center_note, int center_fine, int note, int fine)
{
    int32_t total = (note - center_note) * 128 + (fine - center_fine);
    int32_t oct = total >= 0 ? total / 1536 : -((-total + 1535) / 1536);
    int32_t rem = total - oct * 1536;
    uint64_t p = (uint64_t)k_semi[rem >> 7] * k_fine[rem & 127]; /* Q32 ratio within the octave */
    p *= SPU2_PITCH_1X;                                            /* Q32 pitch */
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

uint16_t spu2_pitch2note(int center_note, int center_fine, uint16_t pitch)
{
    int32_t lo = -128 * 128, hi = 128 * 128;
    while (lo < hi) { /* smallest total with note2pitch(total) >= pitch */
        int32_t mid = lo + ((hi - lo) >> 1);
        if (spu2_note2pitch(0, 0, 0, mid) >= pitch)
            hi = mid;
        else
            lo = mid + 1;
    }
    int32_t total = lo + center_note * 128 + center_fine;
    if (total < 0)
        total = 0;
    return (uint16_t)(((total >> 7) << 8) | ((total & 127) << 1));
}

/* ---- interpolation -------------------------------------------------------------------- */
/* Uniform cubic B-spline weights at t = phase/256, Q15, exact integer arithmetic:
 *   (1-t)^3/6, (3t^3 - 6t^2 + 4)/6, (-3t^3 + 3t^2 + 3t + 1)/6, t^3/6.
 * The weight that would be lost to rounding goes to w[1] so the sum is 0x8000. */
void spu2_interp_weights(int phase, int32_t w[4])
{
    int64_t t = phase & 0xFF, u = 256 - t;
    const int64_t den = 6LL * 256 * 256 * 256;
    w[0] = (int32_t)((u * u * u * 32768) / den);
    w[3] = (int32_t)((t * t * t * 32768) / den);
    w[2] = (int32_t)(((-3 * t * t * t + 3 * 256 * t * t + 3 * 256 * 256 * t + 256LL * 256 * 256) * 32768) / den);
    w[1] = 32768 - w[0] - w[2] - w[3];
}

static int32_t g_bspline[256][4];
static int g_bspline_ready;

static void interp_init(void)
{
    if (g_bspline_ready)
        return;
    for (int i = 0; i < 256; i++)
        spu2_interp_weights(i, g_bspline[i]);
    g_bspline_ready = 1;
}

/* ---- reverb presets (LIBSD.IRX) -------------------------------------------------------- */
/* Work area sizes in 8-byte units, LIBSD.IRX 0x4B48. */
static const uint16_t k_rev_size[SPU2_REV_MODES] = {0x0002, 0x04D8, 0x03E8, 0x0908, 0x0DFC,
                                                    0x15BC, 0x1ED8, 0x3008, 0x3008, 0x0780};
/* Registers per mode, psx-spx order:
 *  0 dAPF1  1 dAPF2  2 vIIR  3 vCOMB1  4 vCOMB2  5 vCOMB3  6 vCOMB4  7 vWALL  8 vAPF1  9 vAPF2
 * 10 mLSAME 11 mRSAME 12 mLCOMB1 13 mRCOMB1 14 mLCOMB2 15 mRCOMB2 16 dLSAME 17 dRSAME
 * 18 mLDIFF 19 mRDIFF 20 mLCOMB3 21 mRCOMB3 22 mLCOMB4 23 mRCOMB4 24 dLDIFF 25 dRDIFF
 * 26 mLAPF1 27 mRAPF1 28 mLAPF2 29 mRAPF2 30 vLIN 31 vRIN
 * Address registers are in 8-byte units relative to the work-area start (ESA). */
static const uint16_t k_rev_preset[SPU2_REV_MODES][32] = {
    /* OFF */
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000,
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    /* ROOM */
    {0x007D, 0x005B, 0x6D80, 0x54B8, 0xBED0, 0x0000, 0x0000, 0xBA80, 0x5800, 0x5300, 0x04D6, 0x0333,
     0x03F0, 0x0227, 0x0374, 0x01EF, 0x0336, 0x01B7, 0x0335, 0x01B6, 0x0334, 0x01B5, 0x0334, 0x01B5,
     0x0334, 0x01B5, 0x01B4, 0x0136, 0x00B8, 0x005C, 0x8000, 0x8000},
    /* STUDIO_A */
    {0x0033, 0x0025, 0x70F0, 0x4FA8, 0xBCE0, 0x4410, 0xC0F0, 0x9C00, 0x5280, 0x4EC0, 0x03E4, 0x031B,
     0x03A4, 0x02AF, 0x0372, 0x0266, 0x031C, 0x025D, 0x025C, 0x018E, 0x022F, 0x0135, 0x01D2, 0x00B7,
     0x018F, 0x00B5, 0x00B4, 0x0080, 0x004C, 0x0026, 0x8000, 0x8000},
    /* STUDIO_B */
    {0x00B1, 0x007F, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xB4C0, 0x5280, 0x4EC0, 0x0904, 0x076B,
     0x0824, 0x065F, 0x07A2, 0x0616, 0x076C, 0x05ED, 0x05EC, 0x042E, 0x050F, 0x0305, 0x0462, 0x02B7,
     0x042F, 0x0265, 0x0264, 0x01B2, 0x0100, 0x0080, 0x8000, 0x8000},
    /* STUDIO_C */
    {0x00E3, 0x00A9, 0x6F60, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0xA680, 0x5680, 0x52C0, 0x0DFB, 0x0B58,
     0x0D09, 0x0A3C, 0x0BD9, 0x0973, 0x0B59, 0x08DA, 0x08D9, 0x05E9, 0x07EC, 0x04B0, 0x06EF, 0x03D2,
     0x05EA, 0x031D, 0x031C, 0x0238, 0x0154, 0x00AA, 0x8000, 0x8000},
    /* HALL */
    {0x01A5, 0x0139, 0x6000, 0x5000, 0x4C00, 0xB800, 0xBC00, 0xC000, 0x6000, 0x5C00, 0x15BA, 0x11BB,
     0x14C2, 0x10BD, 0x11BC, 0x0DC1, 0x11C0, 0x0DC3, 0x0DC0, 0x09C1, 0x0BC4, 0x07C1, 0x0A00, 0x06CD,
     0x09C2, 0x05C1, 0x05C0, 0x041A, 0x0274, 0x013A, 0x8000, 0x8000},
    /* SPACE */
    {0x033D, 0x0231, 0x7E00, 0x5000, 0xB400, 0xB000, 0x4C00, 0xB000, 0x6000, 0x5400, 0x1ED6, 0x1A31,
     0x1D14, 0x183B, 0x1BC2, 0x16B2, 0x1A32, 0x15EF, 0x15EE, 0x1055, 0x1334, 0x0F2D, 0x11F6, 0x0C5D,
     0x1056, 0x0AE1, 0x0AE0, 0x07A2, 0x0464, 0x0232, 0x8000, 0x8000},
    /* ECHO */
    {0x0003, 0x0003, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x8100, 0x0000, 0x0000, 0x1FFD, 0x0FFD,
     0x1009, 0x0009, 0x0000, 0x0000, 0x1009, 0x0009, 0x1FFF, 0x1FFF, 0x1FFE, 0x1FFE, 0x1FFE, 0x1FFE,
     0x1FFE, 0x1FFE, 0x1008, 0x1004, 0x0008, 0x0004, 0x8000, 0x8000},
    /* DELAY */
    {0x0003, 0x0003, 0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FFD, 0x0FFD,
     0x1009, 0x0009, 0x0000, 0x0000, 0x1009, 0x0009, 0x1FFF, 0x1FFF, 0x1FFE, 0x1FFE, 0x1FFE, 0x1FFE,
     0x1FFE, 0x1FFE, 0x1008, 0x1004, 0x0008, 0x0004, 0x8000, 0x8000},
    /* PIPE */
    {0x0017, 0x0013, 0x70F0, 0x4FA8, 0xBCE0, 0x4510, 0xBEF0, 0x8500, 0x5F80, 0x54C0, 0x0371, 0x02AF,
     0x02E5, 0x01DF, 0x02B0, 0x01D7, 0x0358, 0x026A, 0x01D6, 0x011E, 0x012D, 0x00B1, 0x011F, 0x0059,
     0x01A0, 0x00E3, 0x0058, 0x0040, 0x0028, 0x0014, 0x8000, 0x8000},
};

uint32_t spu2_effect_size(int mode)
{
    mode &= 0xFF;
    if (mode < 0 || mode >= SPU2_REV_MODES)
        mode = 0;
    return (uint32_t)k_rev_size[mode] * 8u;
}

/* Work area in halfwords [*start, *start + *size). 0 if not usable. */
static int rev_area(const spu2_core *c, uint32_t *start, uint32_t *size)
{
    uint32_t bytes = spu2_effect_size(c->rev.mode);
    uint32_t end = c->eea & (SPU2_RAM_SIZE - 1);
    if (end + 1 < bytes)
        return 0;
    *start = (end + 1 - bytes) >> 1;
    *size = bytes >> 1;
    return *size > 0;
}

void spu2_clear_effect_area(spu2 *s, int core)
{
    spu2_core *c = &s->core[core & 1];
    uint32_t start, size;
    if (rev_area(c, &start, &size))
        spu2_ram_fill(s, start << 1, 0, size << 1);
}

void spu2_set_effect_attr(spu2 *s, int core, int mode, int16_t depth_l, int16_t depth_r,
                          int32_t delay, int32_t feedback)
{
    spu2_core *c = &s->core[core & 1];
    int m = mode & 0xFF;
    if (m >= SPU2_REV_MODES)
        m = 0;
    c->rev.mode = m;
    memcpy(c->rev.r, k_rev_preset[m], sizeof c->rev.r);
    c->rev.depth_l = depth_l;
    c->rev.depth_r = depth_r;
    c->rev.delay = (int16_t)delay;
    c->rev.feedback = (int16_t)feedback;
    c->rev.pos = 0;
    c->rev.acc_l = c->rev.acc_r = 0;
    c->rev.out_l = c->rev.out_r = 0;
    c->evol[0] = depth_l;
    c->evol[1] = depth_r;
    uint32_t start, size;
    if (rev_area(c, &start, &size))
        c->esa = start << 1;
    if (mode & SPU2_REV_CLEAR_WA)
        spu2_clear_effect_area(s, core);
}

/* One 24 kHz reverb step (psx-spx "Reverb Formula"); volumes are s16 / 0x8000,
 * buffer addresses are halfwords relative to the current position. */
static void rev_step(spu2 *s, spu2_core *c, int32_t in_l, int32_t in_r)
{
    spu2_reverb *rv = &c->rev;
    uint32_t start, size;
    if (!rev_area(c, &start, &size))
        return;
    const uint16_t *r = rv->r;
#define RV(i) ((int32_t)(int16_t)r[i])
#define OFS(i) ((uint32_t)r[i] * 4u)
#define AT(o) (start + ((rv->pos + (o)) % size))
#define RD(o) ((int32_t)ram_r16(s, AT(o)))
#define WR(o, v) ram_w16(s, AT(o), clamp16(v))
    uint32_t m1 = size - 1; /* "-1 halfword" without going negative */
    int32_t lin = (in_l * RV(30)) >> 15, rin = (in_r * RV(31)) >> 15;
    int32_t vwall = RV(7), viir = RV(2);
    /* same side reflection */
    {
        int32_t prev = RD(OFS(10) + m1);
        WR(OFS(10), (((lin + ((RD(OFS(16)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
        prev = RD(OFS(11) + m1);
        WR(OFS(11), (((rin + ((RD(OFS(17)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
    }
    /* different side reflection */
    {
        int32_t prev = RD(OFS(18) + m1);
        WR(OFS(18), (((lin + ((RD(OFS(25)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
        prev = RD(OFS(19) + m1);
        WR(OFS(19), (((rin + ((RD(OFS(24)) * vwall) >> 15) - prev) * viir) >> 15) + prev);
    }
    /* early echo (comb) */
    int32_t lo = (RV(3) * RD(OFS(12)) + RV(4) * RD(OFS(14)) + RV(5) * RD(OFS(20)) + RV(6) * RD(OFS(22))) >> 15;
    int32_t ro = (RV(3) * RD(OFS(13)) + RV(4) * RD(OFS(15)) + RV(5) * RD(OFS(21)) + RV(6) * RD(OFS(23))) >> 15;
    /* late reverb all-pass filters */
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
    rv->out_l = clamp16(lo);
    rv->out_r = clamp16(ro);
    rv->pos = (rv->pos + 1) % size;
#undef RV
#undef OFS
#undef AT
#undef RD
#undef WR
}

/* ---- reset / registers ------------------------------------------------------------------ */
void spu2_reset(spu2 *s)
{
    int interp = s->interp;
    memset(s, 0, sizeof *s);
    s->interp = (interp >= 0 && interp <= SPU2_INTERP_NONE) ? interp : SPU2_INTERP_BSPLINE;
    interp_init();
    for (int c = 0; c < SPU2_NCORES; c++) {
        spu2_core *co = &s->core[c];
        for (int v = 0; v < SPU2_NVOICES; v++)
            co->v[v].block_pos = 28;
        co->eea = SPU2_RAM_SIZE - 1;
        co->rev.mode = SPU2_REV_OFF;
        memcpy(co->rev.r, k_rev_preset[0], sizeof co->rev.r);
        co->noise_level = 1;
        /* Assumed post-sceSdInit state (docs/SOUND.md): the core 0 -> core 1 external
         * input volume is open, so core 0 voices reach the DAC once MVOL is raised. */
        co->avol[0] = co->avol[1] = 0x7FFF;
    }
}

void spu2_set_interp(spu2 *s, int mode)
{
    s->interp = (mode >= 0 && mode <= SPU2_INTERP_NONE) ? mode : SPU2_INTERP_BSPLINE;
    interp_init();
}

static void voice_key_on(spu2 *s, spu2_core *c, int vi)
{
    spu2_voice *v = &c->v[vi];
    v->nax = v->ssa;
    v->block_pos = 28;
    v->block_flags = 0;
    v->hist1 = v->hist2 = 0;
    v->counter = 0;
    memset(v->ih, 0, sizeof v->ih);
    v->lsax_written = 0;
    v->env.level = 0;
    env_enter(v, SPU2_ENV_ATTACK);
    v->out = 0;
    v->keyed = 1;
    v->kon_count++;
    c->endx &= ~(1u << vi);
    s->stats.key_ons++;
}

static void voice_key_off(spu2 *s, spu2_core *c, int vi)
{
    spu2_voice *v = &c->v[vi];
    if (v->phase != SPU2_ENV_OFF && v->phase != SPU2_ENV_RELEASE) {
        env_enter(v, SPU2_ENV_RELEASE);
        s->stats.key_offs++;
    }
}

void spu2_key_on(spu2 *s, int core, uint32_t mask)
{
    spu2_core *c = &s->core[core & 1];
    for (int v = 0; v < SPU2_NVOICES; v++)
        if (mask & (1u << v))
            voice_key_on(s, c, v);
}

void spu2_key_off(spu2 *s, int core, uint32_t mask)
{
    spu2_core *c = &s->core[core & 1];
    for (int v = 0; v < SPU2_NVOICES; v++)
        if (mask & (1u << v))
            voice_key_off(s, c, v);
}

void spu2_voice_setup(spu2 *s, int core, int voice, uint32_t ssa, uint16_t pitch,
                      uint16_t adsr1, uint16_t adsr2, uint16_t voll, uint16_t volr)
{
    spu2_voice *v = &s->core[core & 1].v[voice % SPU2_NVOICES];
    v->ssa = ssa & (SPU2_RAM_SIZE - 1) & ~15u;
    v->pitch = pitch;
    v->adsr1 = adsr1;
    v->adsr2 = adsr2;
    vol_write(&v->vol[0], voll);
    vol_write(&v->vol[1], volr);
}

const spu2_voice *spu2_voice_get(const spu2 *s, int core, int voice)
{
    return &s->core[core & 1].v[voice % SPU2_NVOICES];
}

int spu2_voice_active(const spu2 *s, int core, int voice)
{
    return s->core[core & 1].v[voice % SPU2_NVOICES].phase != SPU2_ENV_OFF;
}

void spu2_set_adma(spu2 *s, int core, spu2_adma_fn fn, void *user)
{
    s->core[core & 1].adma = fn;
    s->core[core & 1].adma_user = user;
}

void spu2_set_param(spu2 *s, uint32_t entry, uint16_t value)
{
    spu2_core *c = &s->core[entry & 1];
    uint32_t p = (entry >> 8) & 0xFF;
    if (p <= SPU2_VP_VOLXR) {
        spu2_voice *v = &c->v[((entry >> 1) & 0x1F) % SPU2_NVOICES];
        switch (p) {
        case SPU2_VP_VOLL: vol_write(&v->vol[0], value); break;
        case SPU2_VP_VOLR: vol_write(&v->vol[1], value); break;
        case SPU2_VP_PITCH: v->pitch = value; break;
        case SPU2_VP_ADSR1: v->adsr1 = value; break;
        case SPU2_VP_ADSR2: v->adsr2 = value; break;
        case SPU2_VP_ENVX: v->env.level = value & 0x7FFF; break;
        case SPU2_VP_VOLXL: v->vol[0].cur = (int16_t)value; break;
        case SPU2_VP_VOLXR: v->vol[1].cur = (int16_t)value; break;
        }
        return;
    }
    switch (p) {
    case SPU2_P_MMIX: c->mmix = value; break;
    case SPU2_P_MVOLL: vol_write(&c->mvol[0], value); break;
    case SPU2_P_MVOLR: vol_write(&c->mvol[1], value); break;
    case SPU2_P_EVOLL: c->evol[0] = (int16_t)value; break;
    case SPU2_P_EVOLR: c->evol[1] = (int16_t)value; break;
    case SPU2_P_AVOLL: c->avol[0] = (int16_t)value; break;
    case SPU2_P_AVOLR: c->avol[1] = (int16_t)value; break;
    case SPU2_P_BVOLL: c->bvol[0] = (int16_t)value; break;
    case SPU2_P_BVOLR: c->bvol[1] = (int16_t)value; break;
    case SPU2_P_MVOLXL: c->mvol[0].cur = (int16_t)value; break;
    case SPU2_P_MVOLXR: c->mvol[1].cur = (int16_t)value; break;
    default: break;
    }
}

uint16_t spu2_get_param(const spu2 *s, uint32_t entry)
{
    const spu2_core *c = &s->core[entry & 1];
    uint32_t p = (entry >> 8) & 0xFF;
    if (p <= SPU2_VP_VOLXR) {
        const spu2_voice *v = &c->v[((entry >> 1) & 0x1F) % SPU2_NVOICES];
        switch (p) {
        case SPU2_VP_VOLL: return v->vol[0].reg;
        case SPU2_VP_VOLR: return v->vol[1].reg;
        case SPU2_VP_PITCH: return v->pitch;
        case SPU2_VP_ADSR1: return v->adsr1;
        case SPU2_VP_ADSR2: return v->adsr2;
        case SPU2_VP_ENVX: return (uint16_t)v->env.level;
        case SPU2_VP_VOLXL: return (uint16_t)v->vol[0].cur;
        case SPU2_VP_VOLXR: return (uint16_t)v->vol[1].cur;
        }
    }
    switch (p) {
    case SPU2_P_MMIX: return c->mmix;
    case SPU2_P_MVOLL: return c->mvol[0].reg;
    case SPU2_P_MVOLR: return c->mvol[1].reg;
    case SPU2_P_EVOLL: return (uint16_t)c->evol[0];
    case SPU2_P_EVOLR: return (uint16_t)c->evol[1];
    case SPU2_P_AVOLL: return (uint16_t)c->avol[0];
    case SPU2_P_AVOLR: return (uint16_t)c->avol[1];
    case SPU2_P_BVOLL: return (uint16_t)c->bvol[0];
    case SPU2_P_BVOLR: return (uint16_t)c->bvol[1];
    case SPU2_P_MVOLXL: return (uint16_t)c->mvol[0].cur;
    case SPU2_P_MVOLXR: return (uint16_t)c->mvol[1].cur;
    default: return 0;
    }
}

void spu2_set_switch(spu2 *s, uint32_t entry, uint32_t value)
{
    spu2_core *c = &s->core[entry & 1];
    value &= 0xFFFFFFu;
    switch ((entry >> 8) & 0xFF) {
    case SPU2_S_PMON: c->pmon = value & ~1u; break;
    case SPU2_S_NON: c->non = value; break;
    case SPU2_S_KON: spu2_key_on(s, (int)(entry & 1), value); break;
    case SPU2_S_KOFF: spu2_key_off(s, (int)(entry & 1), value); break;
    case SPU2_S_ENDX: c->endx = value; break;
    case SPU2_S_VMIXL: c->vmixl = value; break;
    case SPU2_S_VMIXEL: c->vmixel = value; break;
    case SPU2_S_VMIXR: c->vmixr = value; break;
    case SPU2_S_VMIXER: c->vmixer = value; break;
    default: break;
    }
}

uint32_t spu2_get_switch(const spu2 *s, uint32_t entry)
{
    const spu2_core *c = &s->core[entry & 1];
    switch ((entry >> 8) & 0xFF) {
    case SPU2_S_PMON: return c->pmon;
    case SPU2_S_NON: return c->non;
    case SPU2_S_ENDX: return c->endx;
    case SPU2_S_VMIXL: return c->vmixl;
    case SPU2_S_VMIXEL: return c->vmixel;
    case SPU2_S_VMIXR: return c->vmixr;
    case SPU2_S_VMIXER: return c->vmixer;
    default: return 0;
    }
}

void spu2_set_addr(spu2 *s, uint32_t entry, uint32_t a)
{
    spu2_core *c = &s->core[entry & 1];
    a &= SPU2_RAM_SIZE - 1;
    if ((entry & 0xFF00) == 0x2000) {
        spu2_voice *v = &c->v[((entry >> 1) & 0x1F) % SPU2_NVOICES];
        switch (entry & 0xC0) {
        case 0x40: v->ssa = a & ~15u; break;
        case 0x80: v->lsax = a & ~15u; v->lsax_written = 1; break;
        case 0xC0: v->nax = a & ~15u; break;
        }
        return;
    }
    switch (entry & 0xFF00) {
    case SPU2_A_ESA: c->esa = a; break;
    case SPU2_A_EEA: c->eea = a | 0x1FFFFu; break; /* EEA holds address bits 17..20 only */
    case SPU2_A_TSA: c->tsa = a; break;
    case SPU2_A_IRQA: c->irqa = a; break;
    default: break;
    }
}

uint32_t spu2_get_addr(const spu2 *s, uint32_t entry)
{
    const spu2_core *c = &s->core[entry & 1];
    if ((entry & 0xFF00) == 0x2000) {
        const spu2_voice *v = &c->v[((entry >> 1) & 0x1F) % SPU2_NVOICES];
        switch (entry & 0xC0) {
        case 0x40: return v->ssa;
        case 0x80: return v->lsax;
        case 0xC0: return v->nax;
        }
        return 0;
    }
    switch (entry & 0xFF00) {
    case SPU2_A_ESA: return c->esa;
    case SPU2_A_EEA: return c->eea;
    case SPU2_A_TSA: return c->tsa;
    case SPU2_A_IRQA: return c->irqa;
    default: return 0;
    }
}

void spu2_set_core_attr(spu2 *s, uint32_t entry, uint32_t value)
{
    spu2_core *c = &s->core[entry & 1];
    switch (entry & ~1u) {
    case SPU2_C_EFFECT_ENABLE:
        if (value) c->attr |= 2u; else c->attr &= ~2u;
        break;
    case SPU2_C_IRQ_ENABLE: c->irq_enable = value != 0; break;
    case SPU2_C_MUTE_ENABLE:
        if (value) c->attr |= 8u; else c->attr &= ~8u;
        break;
    case SPU2_C_NOISE_CLK: c->noise_clk = (uint16_t)(value & 0x3F); break;
    case SPU2_C_SPDIF_MODE: c->spdif = (uint16_t)value; break;
    default: break;
    }
}

uint32_t spu2_get_core_attr(const spu2 *s, uint32_t entry)
{
    const spu2_core *c = &s->core[entry & 1];
    switch (entry & ~1u) {
    case SPU2_C_EFFECT_ENABLE: return (c->attr >> 1) & 1;
    case SPU2_C_IRQ_ENABLE: return (uint32_t)c->irq_enable;
    case SPU2_C_MUTE_ENABLE: return (c->attr >> 3) & 1;
    case SPU2_C_NOISE_CLK: return c->noise_clk;
    case SPU2_C_SPDIF_MODE: return c->spdif;
    default: return 0;
    }
}

/* ---- render --------------------------------------------------------------------------------- */
static int16_t voice_next_sample(spu2 *s, spu2_core *c, int vi)
{
    spu2_voice *v = &c->v[vi];
    if (v->block_pos >= 28) {
        if (v->block_flags & 1) { /* the block just played had LOOP END */
            c->endx |= 1u << vi;
            v->nax = v->lsax;
            if (!(v->block_flags & 2)) { /* no REPEAT: the voice is muted */
                v->phase = SPU2_ENV_OFF;
                v->env.level = 0;
                v->keyed = 0;
            }
        }
        uint8_t blk[16];
        spu2_ram_read(s, v->nax, blk, 16);
        int16_t h[2] = {v->hist1, v->hist2};
        v->block_flags = spu2_adpcm_decode_block(blk, v->block, h);
        v->hist1 = h[0];
        v->hist2 = h[1];
        if ((v->block_flags & 4) && !v->lsax_written)
            v->lsax = v->nax;
        v->nax = (v->nax + 16) & (SPU2_RAM_SIZE - 1);
        v->block_pos = 0;
        s->stats.blocks_decoded++;
    }
    return v->block[v->block_pos++];
}

static int16_t voice_tick(spu2 *s, spu2_core *c, int vi, int16_t prev_out)
{
    spu2_voice *v = &c->v[vi];
    if (v->phase == SPU2_ENV_OFF) {
        v->out = 0;
        return 0;
    }
    int32_t smp;
    if (c->non & (1u << vi))
        smp = (int16_t)c->noise_level;
    else {
        switch (s->interp) {
        case SPU2_INTERP_NONE: smp = v->ih[3]; break;
        case SPU2_INTERP_LINEAR: {
            int32_t t = (int32_t)(v->counter & 0xFFF);
            smp = v->ih[2] + (((v->ih[3] - v->ih[2]) * t) >> 12);
            break;
        }
        default: {
            const int32_t *w = g_bspline[(v->counter >> 4) & 0xFF];
            smp = (w[0] * v->ih[0] + w[1] * v->ih[1] + w[2] * v->ih[2] + w[3] * v->ih[3]) >> 15;
            break;
        }
        }
    }
    uint32_t step = v->pitch > 0x3FFF ? 0x3FFF : v->pitch;
    if (vi > 0 && (c->pmon & (1u << vi))) {
        int32_t f = (int32_t)prev_out + 0x8000;
        step = (uint32_t)(((int64_t)step * f) >> 15);
        if (step > 0x3FFF)
            step = 0x3FFF;
    }
    v->counter += step;
    while (v->counter >= 0x1000 && v->phase != SPU2_ENV_OFF) {
        v->counter -= 0x1000;
        int16_t n = voice_next_sample(s, c, vi);
        v->ih[0] = v->ih[1];
        v->ih[1] = v->ih[2];
        v->ih[2] = v->ih[3];
        v->ih[3] = n;
    }
    voice_env_tick(v);
    int16_t out = clamp16((smp * v->env.level) >> 15);
    if (v->phase == SPU2_ENV_OFF)
        out = 0;
    v->out = out;
    return out;
}

static void noise_tick(spu2_core *c)
{
    int shift = (c->noise_clk >> 2) & 0xF;
    int step = (c->noise_clk & 3) + 4;
    c->noise_timer -= step;
    uint16_t n = c->noise_level;
    int parity = ((n >> 15) ^ (n >> 12) ^ (n >> 11) ^ (n >> 10) ^ 1) & 1;
    if (c->noise_timer < 0) {
        c->noise_level = (uint16_t)((n << 1) | parity);
        c->noise_timer += 0x20000 >> shift;
        if (c->noise_timer < 0)
            c->noise_timer += 0x20000 >> shift;
    }
}

static void core_tick(spu2 *s, int ci)
{
    spu2_core *c = &s->core[ci];
    int32_t dl = 0, dr = 0, wl = 0, wr = 0;
    if (c->non)
        noise_tick(c);
    int16_t prev = 0;
    for (int vi = 0; vi < SPU2_NVOICES; vi++) {
        spu2_voice *v = &c->v[vi];
        int16_t o = voice_tick(s, c, vi, prev);
        prev = o;
        if (v->phase == SPU2_ENV_OFF && o == 0)
            continue;
        vol_tick(&v->vol[0]);
        vol_tick(&v->vol[1]);
        int32_t l = (o * v->vol[0].cur) >> 15, r = (o * v->vol[1].cur) >> 15;
        uint32_t bit = 1u << vi;
        if (c->vmixl & bit) dl += l;
        if (c->vmixr & bit) dr += r;
        if (c->vmixel & bit) wl += l;
        if (c->vmixer & bit) wr += r;
    }
    /* sound data input (AutoDMA) */
    int16_t in[2] = {0, 0};
    if (c->adma && !c->adma(c->adma_user, ci, in))
        in[0] = in[1] = 0;
    int32_t il = (in[0] * c->bvol[0]) >> 15, ir = (in[1] * c->bvol[1]) >> 15;
    /* external input: core 0's output into core 1 */
    int32_t el = 0, er = 0;
    if (ci == 1) {
        el = (s->core[0].out_l * c->avol[0]) >> 15;
        er = (s->core[0].out_r * c->avol[1]) >> 15;
    }
    uint16_t m = c->mmix;
    int32_t sdl = ((m & SPU2_MMIX_MSNDL) ? dl : 0) + ((m & SPU2_MMIX_SINL) ? il : 0) + ((m & SPU2_MMIX_MINL) ? el : 0);
    int32_t sdr = ((m & SPU2_MMIX_MSNDR) ? dr : 0) + ((m & SPU2_MMIX_SINR) ? ir : 0) + ((m & SPU2_MMIX_MINR) ? er : 0);
    int32_t swl = ((m & SPU2_MMIX_MSNDEL) ? wl : 0) + ((m & SPU2_MMIX_SINEL) ? il : 0) + ((m & SPU2_MMIX_MINEL) ? el : 0);
    int32_t swr = ((m & SPU2_MMIX_MSNDER) ? wr : 0) + ((m & SPU2_MMIX_SINER) ? ir : 0) + ((m & SPU2_MMIX_MINER) ? er : 0);
    /* effect */
    if (c->attr & 2u) {
        c->rev.acc_l += clamp16(swl);
        c->rev.acc_r += clamp16(swr);
        if (c->rev.half) {
            rev_step(s, c, c->rev.acc_l >> 1, c->rev.acc_r >> 1);
            c->rev.acc_l = c->rev.acc_r = 0;
        }
        c->rev.half ^= 1;
        sdl += (c->rev.out_l * c->evol[0]) >> 15;
        sdr += (c->rev.out_r * c->evol[1]) >> 15;
    }
    vol_tick(&c->mvol[0]);
    vol_tick(&c->mvol[1]);
    int32_t ol = (clamp16(sdl) * c->mvol[0].cur) >> 15;
    int32_t orr = (clamp16(sdr) * c->mvol[1].cur) >> 15;
    if (c->attr & 8u)
        ol = orr = 0;
    if (sdl > 32767 || sdl < -32768 || sdr > 32767 || sdr < -32768)
        s->stats.clips++;
    c->out_l = clamp16(ol);
    c->out_r = clamp16(orr);
}

void spu2_render(spu2 *s, int16_t *lr, uint32_t frames)
{
    for (uint32_t i = 0; i < frames; i++) {
        core_tick(s, 0);
        core_tick(s, 1);
        if (lr) {
            lr[2 * i] = s->core[1].out_l;
            lr[2 * i + 1] = s->core[1].out_r;
        }
        s->stats.samples++;
    }
}
