/* SPDX-License-Identifier: CC0-1.0 */
/* The VU1 work of walked frame chains without the VIF1 / VU1 models
 * (docs/NATIVE-RENDER.md "VU1 programs at the walker").
 *
 * The frame chain walker (nr_fx.c) hands every VIF command that is not DIRECT
 * (UNPACK, MPG, the VIF registers, program starts) to a forward sink.  In an
 * oracle build that is the VIF1 model; here it is a native consumer:
 *
 *  - the VU1 data memory as plain memory (1,024 qwords) written by the UNPACKs
 *    (formats S / V2 / V3 / V4 x 32 / 16 / 8, V4-5, sign / zero extension,
 *    STCYCL skipping and filling writes, STMOD offset / difference, STMASK
 *    write masks with STROW / STCOL), the double buffer (BASE, OFFSET, TOPS,
 *    DBF, XTOP) and ITOP;
 *  - the microcode memory as a list of resident uploads (MPG: load address,
 *    size, FNV-1a of the code), which names the program a start runs;
 *  - the programs themselves, translated to C (no interpreter): a start whose
 *    resident code is a translated program runs it on the memory above and
 *    hands its XGKICK packets to the GS input in order; any other start is
 *    counted (a missing draw: "untranslated" in the stats line).
 *
 * Translated programs (listings: out/nrender/dis, out/nrender/insect_mpg):
 *  - the object-constant program at 0 (retail data 0x436980, 88 pairs): kicks
 *    the register packet at qw19 and derives qw64-75 / 100-102 / 111.z
 *    (nr_const_prog0);
 *  - the particle quads of VuMicrocodeTableInit row 5 (head 0x43F820 at 0x320,
 *    main piece 0x43F9C0 at 0x1900 / 0x2100; EffQuadDrawNodes_1a7890 builds its
 *    batches): nr_vux_particles below.
 *
 * Every other command is consumed for its side effects only (FLUSH*, MARK,
 * MSKPATH3 have none here). */
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "nr_const.h"
#include "nr_im.h"
#include "nr_vu1.h"

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static uint64_t fnv64(const uint8_t *p, uint32_t n)
{
    uint64_t h = 1469598103934665603ull;
    while (n--) { h ^= *p++; h *= 1099511628211ull; }
    return h;
}

/* FNV-1a of the translated programs' uploads (the same bytes in every build: retail data) */
#define CODE_PROG0   0xad445cb29dd70baeull   /* 0x436980 -> 0x0000, 88 pairs */
#define CODE_PT_HEAD 0x32acfa1f972949a2ull   /* 0x43F820 -> 0x0320, 49 pairs */
#define CODE_PT_1900 0x1e3aadf3239d4a31ull   /* 0x43F9C0 -> 0x1900, 256 pairs */
#define CODE_PT_2100 0x3acf8e5fd05185d0ull   /* 0x43F9C0 -> 0x2100, 242 pairs */

enum { P_NONE = 0, P_PROG0, P_PARTICLES };

static struct {
    nr_qw mem[1024];
    uint32_t cl, wl, mode, mask, row[4], col[4];
    uint32_t base, ofst, tops, dbf, itop, xtop;
    uint32_t tpc;                     /* the next MSCNT's pc (instruction index) */
    /* resident uploads: instruction -> upload index + 1 */
    uint16_t owner[2048];
    struct { uint32_t dest, n; uint64_t hash; } up[64];
    int nup;
    nr_fx_sink sink;
    void *user;
    uint8_t *kick;
    uint32_t kcap;
    /* stats */
    uint64_t cmds, unpack_qw, mpg, starts, run[3], untranslated, kicks, kick_qw, particles, particles_adc;
    struct { uint32_t pc; uint64_t hash, n; } un[16];
    /* RG_NR_VU=check (oracle builds): the VIF / VU models run as well; our kicks are queued
     * and compared with the VU1's PATH1 packets (nr_vux_p1_tap) */
    int check;
    uint8_t *q;
    uint32_t qlen, qcap, qhead;
    nr_vux_p1_fn p1_fn;
    void *p1_user;
    uint64_t c_pk, c_exact, c_close, c_bad, c_len, c_unqueued;
    uint64_t c_role[6];     /* differing words: head, PRIM, STQ, RGBA, XYZF, other packets */
    int c_printed, c_rp[6];
} V;

static void chk_push(const uint8_t *d, uint32_t n)
{
    if (V.qhead == V.qlen) V.qhead = V.qlen = 0;
    if (V.qlen + n + 4 > V.qcap) {
        V.qcap = (V.qlen + n + 4) * 2;
        V.q = (uint8_t *)realloc(V.q, V.qcap);
        if (!V.q) { V.qcap = V.qlen = V.qhead = 0; return; }
    }
    memcpy(V.q + V.qlen, &n, 4);
    memcpy(V.q + V.qlen + 4, d, n);
    V.qlen += n + 4;
}

void nr_vux_bind(nr_fx_sink gs_sink, void *user)
{
    V.sink = gs_sink;
    V.user = user;
}

/* ---- XGKICK: the GIF packet at qword a (PACKED / REGLIST / IMAGE tags up to EOP) */
static void kick(uint32_t a)
{
    uint32_t n = 0, q = a, guard = 0;
    for (;;) {
        const nr_qw *t = &V.mem[q & 1023];
        uint32_t nloop = t->u[0] & 0x7FFF, eop = (t->u[0] >> 15) & 1, flg = (t->u[1] >> 26) & 3;
        uint32_t nreg = (t->u[1] >> 28) & 15, len;
        if (!nreg) nreg = 16;
        len = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1) / 2 : nloop;
        n += 1 + len;
        q += 1 + len;
        if (eop || ++guard > 1024 || n > 1024) break;
    }
    if (n > 1024) n = 1024;
    if (V.kcap < n * 16) {
        V.kcap = n * 16;
        V.kick = (uint8_t *)realloc(V.kick, V.kcap);
        if (!V.kick) { V.kcap = 0; return; }
    }
    for (q = 0; q < n; q++) memcpy(V.kick + q * 16, V.mem[(a + q) & 1023].u, 16);
    V.kicks++;
    V.kick_qw += n;
    if (V.check) { chk_push(V.kick, n * 16); return; }
#if !(defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY)   /* (native-only: the sink is the native GIF input) */
    {
        /* the packet as an immediate record: drawn by the native pipeline at its marker
         * (nr_im.h nr_im_gif), the GS input sees only the marker */
        uint8_t mk[32];
        if (nr_im_gif(V.kick, n, mk)) {
            if (V.sink) V.sink(V.user, mk, 32);
            return;
        }
    }
#endif
    if (V.sink) V.sink(V.user, V.kick, n * 16);
}

/* ---- the object-constant program at 0 ------------------------------------- */
static void prog0(void)
{
    static nr_cblock b;
    kick(0x13);                                  /* iaddiu vi01, vi00, 0x13; xgkick vi01 */
    memcpy(b.c, V.mem, sizeof b.c);
    nr_const_prog0(&b);
    memcpy(&V.mem[64], &b.c[64], 12 * 16);       /* 64-75 */
    memcpy(&V.mem[100], &b.c[100], 3 * 16);      /* 100-102 */
    V.mem[111].f[2] = b.c[111].f[2];
}

/* ---- the particle quads (row 5) --------------------------------------------
 * Head (0x330, MSCNT): the batch header at XTOP (.y count, .z count | 0x8000 =
 * the vertex tag's NLOOP + EOP, .w / next .x / .y offsets of the corner, UV and
 * colour arrays from XTOP + 2), output at XTOP + qw76.x: qw0 (A+D tag), PRIM 4,
 * PRMODE qw87.x, the vertex tag (qw86.yzw: 13 registers PRIM, then STQ / RGBAQ /
 * XYZF2 x 4), then 13 qwords per particle.  Main piece (0x1900): per particle
 * (position + scale/angle, two corners, two UV pairs, colour):
 *   world W = qw60..63 x pos, D = qw28 - W, R = (D.z, 0, -D.x), U = D x R, both
 *   normalised and scaled by scale.x / scale.y, rotated by the angle
 *   (A = R cos + U sin, B = U cos - R sin: the program's sine polynomial),
 *   corners W + A c.x + B c.y for (c0.x, c0.y) (c1.x, c0.y) (c0.x, c1.y) (c1.x, c1.y)
 *   -> screen (qw12..15 x qw8..11 x view qw24..27), STQ = (u, v, 1) / w with UVs
 *   (uA.x, uA.y) (uB.x, uA.y) (uA.x, uB.y) (uB.x, uB.y), RGBA = clamp(colour x
 *   128, 0, 128); every corner clip-tested against qw8..11 x view with x, y
 *   scaled by qw16.xy: any outside -> ADC on all four (XYZF2 word 3 = 0x8000,
 *   else 0x7FFF: F = 0xFF).  Then the register packet at 0x3FE (qw19.yzw tag,
 *   NLOOP 1 EOP, qw41 with .x cleared when qw87.y & 0x10) and the output. */
static float vu_ftoi4f(float v) { return v * 16.0f; }
static int32_t ftoi(float v)
{
    if (!(v == v)) return 0;
    if (v >= 2147483647.0f) return 2147483647;
    if (v <= -2147483648.0f) return (int32_t)0x80000000u;
    return (int32_t)v;
}
static void mat_mul(float o[4], const float m[4][4], const float v[4])
{
    int k;
    for (k = 0; k < 4; k++) o[k] = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2] + m[3][k] * v[3];
}
static void particles(uint32_t xtop)
{
    nr_qw *M = V.mem;
    uint32_t cnt = M[xtop & 1023].u[1] & 0xFFFF, nl = M[xtop & 1023].u[2] & 0xFFFF;
    uint32_t base = (xtop + 2) & 0xFFFF;
    uint32_t a_cor = (M[xtop & 1023].u[3] + base) & 0xFFFF, a_uv = (M[(xtop + 1) & 1023].u[0] + base) & 0xFFFF;
    uint32_t a_col = (M[(xtop + 1) & 1023].u[1] + base) & 0xFFFF;
    uint32_t out = (xtop + M[76].u[0]) & 0xFFFF, o, k, i;
    float scr[4][4], clp[4][4];
    int j;
    /* the inputs, read before any output is stored (the program reads particle k + 1 before it
     * stores particle k; the output area can overlap the input arrays) */
    static nr_qw in[512][8];
    if (cnt > 512) cnt = 512;
    for (k = 0; k < cnt; k++) {
        in[k][0] = M[(base + 2 * k) & 1023]; in[k][1] = M[(base + 2 * k + 1) & 1023];
        in[k][2] = M[(a_cor + 2 * k) & 1023]; in[k][3] = M[(a_cor + 2 * k + 1) & 1023];
        in[k][4] = M[(a_uv + 2 * k) & 1023]; in[k][5] = M[(a_uv + 2 * k + 1) & 1023];
        in[k][6] = M[(a_col + k) & 1023];
    }
    /* head */
    M[out & 1023] = M[0];
    memset(&M[(out + 1) & 1023], 0, 32);
    M[(out + 1) & 1023].u[0] = 4;
    M[(out + 2) & 1023].u[0] = M[87].u[0] & 0xFFFF;
    M[(out + 2) & 1023].u[2] = 0x1B;
    M[(out + 3) & 1023].u[0] = nl;
    M[(out + 3) & 1023].u[1] = M[86].u[1];
    M[(out + 3) & 1023].u[2] = M[86].u[2];
    M[(out + 3) & 1023].u[3] = M[86].u[3];
    M[103].u[0] = base; M[103].u[1] = a_cor; M[103].u[2] = a_uv; M[103].u[3] = a_col;
    M[104].u[0] = cnt; M[104].u[1] = out; M[104].u[2] = (out + 4) & 0xFFFF;
    M[105] = M[16];
    M[110] = M[18];
    M[109] = M[17];
    M[109].f[0] *= M[16].f[0];
    M[109].f[1] *= M[16].f[1];
    /* matrices: V' = qw8..11 x view (columns), screen = qw12..15 x V', clip = V' with x, y x qw105.xy */
    for (j = 0; j < 4; j++) {
        float t[4];
        mat_mul(t, (const float (*)[4])M[8].f, M[24 + j].f);
        memcpy(clp[j], t, 16);
        mat_mul(scr[j], (const float (*)[4])M[12].f, t);
        clp[j][0] *= M[105].f[0];
        clp[j][1] *= M[105].f[1];
    }
    for (k = 0, o = (out + 4) & 0xFFFF; k < cnt && k < 512; k++, o = (o + 13) & 0xFFFF) {
        const float *pos = in[k][0].f, *sc = in[k][1].f, *c0 = in[k][2].f, *c1 = in[k][3].f;
        const float *uA = in[k][4].f, *uB = in[k][5].f, *cl = in[k][6].f;
        float W[3], D[3], R[3], U[3], A[3], B[3], l, cs, sn, ang = sc[2];
        float cx[4], cy[4], us[4], vs[4];
        int32_t rgba[4];
        uint32_t adc = 0;
        for (i = 0; i < 3; i++) W[i] = M[60].f[i] * pos[0] + M[61].f[i] * pos[1] + M[62].f[i] * pos[2] + M[63].f[i];
        for (i = 0; i < 3; i++) D[i] = M[28].f[i] - W[i];
        R[0] = D[2]; R[1] = 0.0f; R[2] = -D[0];
        U[0] = D[1] * R[2] - R[1] * D[2];
        U[1] = D[2] * R[0] - R[2] * D[0];
        U[2] = D[0] * R[1] - R[0] * D[1];
        l = sqrtf(R[0] * R[0] + R[1] * R[1] + R[2] * R[2]);
        l = l > 0.0f ? sc[0] / l : 0.0f;
        for (i = 0; i < 3; i++) R[i] *= l;
        l = sqrtf(U[0] * U[0] + U[1] * U[1] + U[2] * U[2]);
        l = l > 0.0f ? sc[1] / l : 0.0f;
        for (i = 0; i < 3; i++) U[i] *= l;
        cs = cosf(ang);
        sn = sinf(ang);
        for (i = 0; i < 3; i++) { A[i] = R[i] * cs + U[i] * sn; B[i] = U[i] * cs - R[i] * sn; }
        cx[0] = c0[0]; cy[0] = c0[1]; us[0] = uA[0]; vs[0] = uA[1];
        cx[1] = c1[0]; cy[1] = c0[1]; us[1] = uB[0]; vs[1] = uA[1];
        cx[2] = c0[0]; cy[2] = c1[1]; us[2] = uA[0]; vs[2] = uB[1];
        cx[3] = c1[0]; cy[3] = c1[1]; us[3] = uB[0]; vs[3] = uB[1];
        for (i = 0; i < 4; i++) {
            float c = cl[i] * 128.0f;
            if (c > 128.0f) c = 128.0f;
            if (!(c > 0.0f)) c = 0.0f;
            rgba[i] = (int32_t)c;
        }
        M[o & 1023].u[0] = 4;                       /* isw.x: PRIM 4 (upper 16 bits 0) */
        for (i = 0; i < 4; i++) {
            float P[4] = { W[0] + A[0] * cx[i] + B[0] * cy[i], W[1] + A[1] * cx[i] + B[1] * cy[i],
                           W[2] + A[2] * cx[i] + B[2] * cy[i], 1.0f };
            float s[4], c[4], q;
            nr_qw *st = &M[(o + 1 + 3 * i) & 1023], *col = &M[(o + 2 + 3 * i) & 1023], *xyz = &M[(o + 3 + 3 * i) & 1023];
            mat_mul(s, (const float (*)[4])scr, P);
            mat_mul(c, (const float (*)[4])clp, P);
            {
                float aw = fabsf(c[3]);
                for (j = 0; j < 3; j++)
                    if (!(c[j] <= aw && c[j] >= -aw)) adc = 1;   /* NaN / inf too (the VU has neither) */
                if (!(fabsf(s[3]) > 0.0f) || !isfinite(s[0]) || !isfinite(s[1]) || !isfinite(s[2]) || !isfinite(s[3])) adc = 1;
            }
            q = 1.0f / s[3];
            st->f[0] = us[i] * q; st->f[1] = vs[i] * q; st->f[2] = q; st->f[3] = q;
            for (j = 0; j < 4; j++) col->i[j] = rgba[j];
            xyz->i[0] = ftoi(vu_ftoi4f(s[0] * q));
            xyz->i[1] = ftoi(vu_ftoi4f(s[1] * q));
            xyz->i[2] = ftoi(vu_ftoi4f(s[2] * q));
        }
        for (i = 0; i < 4; i++) M[(o + 3 + 3 * i) & 1023].u[3] = adc ? 0x8000u : 0x7FFFu;
        V.particles++;
        if (adc) V.particles_adc++;
    }
    /* the register packet and the output */
    M[0x3FE].u[1] = M[19].u[1]; M[0x3FE].u[2] = M[19].u[2]; M[0x3FE].u[3] = M[19].u[3];
    M[0x3FE].u[0] = 0x8001;
    M[0x3FF] = M[41];
    if (M[87].u[1] & 0x10) M[0x3FF].u[0] = 0;
    kick(0x3FE);
    kick(out);
}

/* ---- program starts ---------------------------------------------------------- */
static uint64_t code_at(uint32_t pc)
{
    int u = (int)V.owner[pc & 2047] - 1;
    return u >= 0 ? V.up[u].hash : 0;
}
static int which(uint32_t pc)
{
    uint64_t h = code_at(pc);
    if (h == CODE_PROG0 && pc < 88) return P_PROG0;
    if (h == CODE_PT_HEAD && code_at(0x1900 / 8) == CODE_PT_1900 && code_at(0x2100 / 8) == CODE_PT_2100) return P_PARTICLES;
    return P_NONE;
}
static void start(uint32_t cmd, uint32_t imm)
{
    uint32_t pc = cmd == 0x17 ? V.tpc : imm, xtop = V.tops;
    int p;
    V.starts++;
    V.xtop = xtop;
    V.dbf ^= 1;
    V.tops = V.dbf ? V.base + V.ofst : V.base;
    p = which(pc);
    if (p == P_PROG0 && pc == 0) {
        prog0();
        V.tpc = 0x2A0 / 8;                       /* nop[e] b 0x2a0 */
        V.run[P_PROG0]++;
        return;
    }
    if (p == P_PARTICLES) {
        if (pc == 0x320 / 8) { V.tpc = 0x330 / 8; V.run[0]++; return; }    /* nop[e] at 0x320: sets TPC */
        if (pc == 0x328 / 8 || pc == 0x330 / 8) {
            static int lg = -1;
            if (lg < 0) lg = getenv("RG_NR_VUX_LOG") != NULL;
            if (lg) fprintf(stderr, "vux particles frame %u count %u\n", nr_frame_no(), V.mem[xtop & 1023].u[1] & 0xFFFF);
            particles(xtop);
            V.tpc = 0x328 / 8;                   /* nop[e] b 0x328 */
            V.run[P_PARTICLES]++;
            return;
        }
    }
    V.untranslated++;
    {
        uint64_t h = code_at(pc);
        int i;
        for (i = 0; i < 16; i++) {
            if (V.un[i].n && (V.un[i].pc != pc || V.un[i].hash != h)) continue;
            V.un[i].pc = pc;
            V.un[i].hash = h;
            V.un[i].n++;
            break;
        }
    }
}

/* ---- UNPACK -------------------------------------------------------------------- */
static void unpack(uint32_t code, const uint8_t *d, uint32_t words)
{
    uint32_t cmd = (code >> 24) & 0x7F, vn = (cmd >> 2) & 3, vl = cmd & 3, msk = (cmd >> 4) & 1;
    uint32_t num = (code >> 16) & 0xFF, addr = code & 0x3FF, usn = (code >> 14) & 1, flg = (code >> 15) & 1;
    uint32_t comps = vn + 1, bits = vl == 3 ? 16 : 32u >> vl, n, i, c, cyc = 0;
    uint32_t pos = 0, avail = words * 32;           /* bits */
    if (num == 0) num = 256;
    if (flg) addr += V.tops;
    n = num;
    for (i = 0; i < n; i++) {
        uint32_t lane[4] = { 0, 0, 0, 0 };
        uint32_t wr = 1, data = 1;
        uint32_t cl = V.cl ? V.cl : 1, wl = V.wl ? V.wl : 1;
        uint32_t c_in = cyc % wl;
        nr_qw *q;
        if (cl >= wl) data = 1;                     /* skipping write: data for every written qword */
        else data = c_in < cl;                      /* filling write: data for the first CL of each WL */
        if (data) {
            if (vl == 3) {
                uint32_t v;
                if (pos + 16 > avail) break;
                v = (uint32_t)d[pos / 8] | ((uint32_t)d[pos / 8 + 1] << 8);
                pos += 16;
                lane[0] = (v & 0x1F) << 3; lane[1] = ((v >> 5) & 0x1F) << 3; lane[2] = ((v >> 10) & 0x1F) << 3;
                lane[3] = ((v >> 15) & 1) << 7;
            } else {
                for (c = 0; c < comps; c++) {
                    uint32_t v;
                    if (pos + bits > avail) { wr = 0; break; }
                    if (bits == 32) v = rd32(d + pos / 8);
                    else if (bits == 16) {
                        v = (uint32_t)d[pos / 8] | ((uint32_t)d[pos / 8 + 1] << 8);
                        if (!usn && (v & 0x8000)) v |= 0xFFFF0000u;
                    } else {
                        v = d[pos / 8];
                        if (!usn && (v & 0x80)) v |= 0xFFFFFF00u;
                    }
                    pos += bits;
                    lane[c] = v;
                }
                if (!wr) break;
                if (comps == 1) lane[1] = lane[2] = lane[3] = lane[0];
            }
        }
        q = &V.mem[addr & 1023];
        for (c = 0; c < 4; c++) {
            uint32_t m = msk ? (V.mask >> ((c_in < 4 ? c_in : 3) * 8 + c * 2)) & 3 : 0, v;
            if (!data && !msk) m = 1;               /* filling write without a mask: the row */
            if (m == 3) continue;                   /* write-protected */
            if (m == 1) { q->u[c] = V.row[c]; continue; }
            if (m == 2) { q->u[c] = V.col[c < 4 ? (c_in < 4 ? c_in : 3) : 0]; continue; }
            if (!data) continue;
            if (vl != 3 && c >= comps && comps > 1) continue;   /* V2 / V3: the other lanes untouched */
            v = lane[c];
            if (V.mode == 1) v += V.row[c];
            else if (V.mode == 2) { v += V.row[c]; V.row[c] = v; }
            q->u[c] = v;
        }
        V.unpack_qw++;
        cyc++;
        if (cl >= wl && (cyc % wl) == 0 && cl > wl) addr += cl - wl;   /* skipping write: skip CL - WL */
        addr++;
    }
}

/* one whole VIF command (code + payload), as the walker forwards it */
void nr_vux_cmd(const uint8_t *data, uint32_t bytes)
{
    uint32_t c, cmd, imm, num;
    if (bytes < 4) return;
    c = rd32(data);
    cmd = (c >> 24) & 0x7F;
    imm = c & 0xFFFF;
    num = (c >> 16) & 0xFF;
    V.cmds++;
    if (cmd >= 0x60) { unpack(c, data + 4, (bytes - 4) / 4); return; }
    switch (cmd) {
    case 0x01: V.cl = imm & 0xFF; V.wl = (imm >> 8) & 0xFF; break;
    case 0x02: V.ofst = imm & 0x3FF; V.dbf = 0; V.tops = V.base; break;
    case 0x03: V.base = imm & 0x3FF; break;
    case 0x04: V.itop = imm & 0x3FF; break;
    case 0x05: V.mode = imm & 3; break;
    case 0x14: case 0x15: case 0x17: start(cmd, imm); break;
    case 0x20: if (bytes >= 8) V.mask = rd32(data + 4); break;
    case 0x30: if (bytes >= 20) { int k; for (k = 0; k < 4; k++) V.row[k] = rd32(data + 4 + 4 * k); } break;
    case 0x31: if (bytes >= 20) { int k; for (k = 0; k < 4; k++) V.col[k] = rd32(data + 4 + 4 * k); } break;
    case 0x4A: {
        uint32_t n = num ? num : 256u, k, dest = imm, i;
        uint64_t h;
        if (bytes < 4 + n * 8) break;
        h = fnv64(data + 4, n * 8);
        V.mpg++;
        for (i = 0; i < (uint32_t)V.nup; i++)
            if (V.up[i].hash == h && V.up[i].dest == dest && V.up[i].n == n) break;
        if (i == (uint32_t)V.nup) {
            if (V.nup >= 64) {      /* table full: forget everything not resident */
                memset(V.owner, 0, sizeof V.owner);
                V.nup = 0;
                i = 0;
            }
            V.nup++;
            V.up[i].dest = dest;
            V.up[i].n = n;
            V.up[i].hash = h;
        }
        for (k = 0; k < n; k++) V.owner[(dest + k) & 2047] = (uint16_t)(i + 1);
        break;
    }
    default: break;   /* STMASK-less codes, MARK, MSKPATH3, FLUSH*: no state here */
    }
}

/* the VU1 model's XGKICK packets (check mode): compared with the next queued packet of ours;
 * integer lanes exactly, float lanes (STQ) relative 1e-4, XYZ within 1/16 pixel */
void nr_vux_check_bind(nr_vux_p1_fn orig, void *orig_user)
{
    V.check = 1;
    V.p1_fn = orig;
    V.p1_user = orig_user;
}
void nr_vux_p1_tap(void *user, const uint8_t *data, uint32_t bytes, uint32_t vu_addr)
{
    (void)user;
    if (V.qhead < V.qlen) {
        uint32_t n, i, bad = 0, close = 0;
        memcpy(&n, V.q + V.qhead, 4);
        const uint8_t *e = V.q + V.qhead + 4;
        V.qhead += n + 4;
        V.c_pk++;
        if (n != bytes) { V.c_len++; bad = 1; }
        else {
            /* a particle packet (head 4 qwords + 13 per quad: NLOOP at qword 3 = quads | 0x8000): quads the VU
             * marks ADC (never drawn) only need to be ADC in ours too */
            uint32_t nq = (n >= 64 && (rd32(data + 48) & 0x8000) && 4 + 13 * (rd32(data + 48) & 0x7FFF) == n / 16) ? (rd32(data + 48) & 0x7FFF) : 0;
            for (i = 0; i < n / 4; i++) {
                uint32_t a = rd32(data + i * 4), b = rd32(e + i * 4);
                float fa, fb;
                if (a == b) continue;
                if (nq && i / 4 >= 4) {
                    uint32_t k = (i / 4 - 4) / 13, x0 = (4 + 13 * k + 3) * 16 + 12;
                    if ((rd32(data + x0) & 0x8000) && (rd32(e + x0) & 0x8000)) continue;
                    if ((i / 4 - 4) % 13 == 0 && (i & 3)) continue;   /* the PRIM qword: only .x is read */
                }
                memcpy(&fa, &a, 4); memcpy(&fb, &b, 4);
                if (fa == fa && fb == fb && fabsf(fa - fb) <= 1e-4f * fabsf(fa) + 1e-12f) { close++; continue; }
                if ((int32_t)(a - b) >= -1 && (int32_t)(a - b) <= 1) { close++; continue; }
                bad++;
                {
                    int role = 5;
                    if (nq) role = i / 4 < 4 ? 0 : ((i / 4 - 4) % 13 == 0 ? 1 : 2 + ((i / 4 - 4) % 13 - 1) % 3);
                    V.c_role[role]++;
                    if (V.c_rp[role]++ >= 4) continue;
                }
                if (V.c_printed < 40) {
                    V.c_printed++;
                    fprintf(stderr, "nr vux check: packet %llu (%u bytes) qword %u lane %u: VU %08x (%g) ours %08x (%g)\n",
                            (unsigned long long)V.c_pk, n, i / 4, i & 3, a, fa, b, fb);
                }
            }
        }
        if (bad) V.c_bad++;
        else if (close) V.c_close++;
        else V.c_exact++;
    } else {
        V.c_unqueued++;
    }
    if (V.p1_fn) V.p1_fn(V.p1_user, data, bytes, vu_addr);
}

void nr_vux_fwd(void *user, const uint8_t *data, uint32_t bytes)
{
    (void)user;
    nr_vux_cmd(data, bytes);
}

void nr_vux_stats(FILE *f)
{
    int i;
    if (!f || !V.cmds) return;
    fprintf(f, "native render VU1 programs at the walker: %llu commands, UNPACK %llu qwords, MPG %llu, starts %llu "
               "(object constants %llu, particle batches %llu (%llu quads, %llu outside the guard band), TPC-only %llu), "
               "untranslated %llu; %llu kicks, %llu qwords to the GS\n",
            (unsigned long long)V.cmds, (unsigned long long)V.unpack_qw, (unsigned long long)V.mpg,
            (unsigned long long)V.starts, (unsigned long long)V.run[P_PROG0], (unsigned long long)V.run[P_PARTICLES],
            (unsigned long long)V.particles, (unsigned long long)V.particles_adc, (unsigned long long)V.run[0],
            (unsigned long long)V.untranslated, (unsigned long long)V.kicks, (unsigned long long)V.kick_qw);
    if (V.check)
        fprintf(f, "native render VU1 check: packets %llu (exact %llu, within tolerance %llu, different %llu, length %llu), "
                   "VU packets of untranslated programs %llu: %s\n",
                (unsigned long long)V.c_pk, (unsigned long long)V.c_exact, (unsigned long long)V.c_close,
                (unsigned long long)V.c_bad, (unsigned long long)V.c_len, (unsigned long long)V.c_unqueued,
                V.c_bad ? "FAIL" : "PASS");
    if (V.check && V.c_bad)
        fprintf(f, "native render VU1 check: differing words by role: head %llu PRIM %llu STQ %llu RGBA %llu XYZF %llu other %llu\n",
                (unsigned long long)V.c_role[0], (unsigned long long)V.c_role[1], (unsigned long long)V.c_role[2],
                (unsigned long long)V.c_role[3], (unsigned long long)V.c_role[4], (unsigned long long)V.c_role[5]);
    if (V.untranslated) {
        fprintf(f, "native render WARNING: %llu VU1 program starts with untranslated code (each a missing draw):",
                (unsigned long long)V.untranslated);
        for (i = 0; i < 16 && V.un[i].n; i++)
            fprintf(f, " pc 0x%04x code %016llx x %llu;", V.un[i].pc * 8, (unsigned long long)V.un[i].hash,
                    (unsigned long long)V.un[i].n);
        fputc('\n', f);
    }
}
