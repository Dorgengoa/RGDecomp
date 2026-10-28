/* SPDX-License-Identifier: CC0-1.0 */
/* rg-nr-nmcheck: the native model-program semantics (src/native/render/
 * nr_vu1.c) against the VU1 interpreter, batch by batch, on a corpus written
 * by rg-nr-vutrace --corpus (docs/NATIVE-RENDER.md "Verification").
 *
 *   rg-nr-nmcheck CORPUS.bin [--control N] [--verbose N] [--max N]
 *
 * For every run of the dominant program whose resident pieces nr_vu1 covers,
 * the run's main PATH1 packet (A+D PRIM/PRMODE tag + STQ/RGBAQ/XYZF2 vertices)
 * is compared vertex by vertex with nr_vu1_batch on the run's input memory:
 *   X, Y   12.4 fixed point (ftoi4), within 1 (1/16 pixel)
 *   Z      integer Z, within 1 (or 1 part in 2^20 for large Z)
 *   F      fog byte, within 1
 *   RGBA   within 1
 *   S T Q  relative 1e-4 (absolute 1e-9 near 0)
 * Header words (PRIM, PRMODE, NLOOP) must be equal.
 * --control N: deliberate fault class N, which must FAIL:
 *   1 = UV scale x and y swapped, 2 = fog ignores the clamp,
 *   3 = colour without the material multiplier, 4 = skin weights 1/256,
 *   5 = shadow-volume light direction tilted (the shadow check),
 *   6 = line strands: screen matrix x scaled by 1.001 (the line check).
 * Exit 0 when every compared field is within tolerance.
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr_vu1.h"
#include "nr_vu1sh.h"
#include "nr_vu1ln.h"

static int g_control;

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

/* ---- the shadow-volume program (nr_vu1sh.c) vs the interpreter ------------
 * A run of the 0x4425F0 head (0x10E0 piece 0x4427E0) kicks, per face, the
 * register packet at qw35 or qw38 and then its fan packet at qw104.y (GIF tag
 * + PRIM + PRMODE + vertex tag, four XYZF2).  The C program must produce the
 * same faces in the same order: register packet, and per vertex the four
 * XYZF2 words (exact, or X/Y within 1/16 pixel, Z within 1, fog/ADC equal). */
static struct { uint64_t runs, faces, exact, close, bad, count_bad, reg_bad; int printed; } g_sh;

/* ---- the line-strand program (nr_vu1ln.c) vs the interpreter -----------------
 * One kick per run at qw76.x past TOP: GIF tag, PRIM, PRMODE, vertex tag
 * (NLOOP = records), then per record a PACKED RGBAQ and eight XYZF2.  Every
 * word of every record must be equal. */
static struct { uint64_t runs, recs, exact, bad, count_bad, nopkt; int printed; } g_ln;
static void line_check(const nr_qw *mem, const uint32_t *hdr, const uint8_t *p1, uint32_t nb, int verbose);

static void shadow_check(const nr_qw *mem, const uint32_t *hdr, const uint8_t *p1, uint32_t nb, int verbose)
{
    static float pos[1024][3];
    static nr_shface fc[2048];
    uint32_t top = hdr[2], p, outq = top + mem[76].u[0], k;   /* the head sets qw104.y = TOP + qw76.x */
    int skinned = hdr[10] == 0x400000A1u || hdr[10] == 0x40000090u, n, nf, fi = 0, pending_reg = -1;   /* 0x4393B0 or 0x43A020 */
    n = nr_vu1_decode_positions(mem, top, skinned, pos, 1024);
    if (g_control == 5) {   /* shadow light direction tilted: must FAIL */
        static nr_qw m2[112];
        memcpy(m2, mem, sizeof m2);
        m2[34].f[0] += 0.05f;
        mem = m2;
    }
    nf = nr_vu1sh_faces(mem, (const float (*)[3])pos, (uint32_t)n, fc, 2048);
    g_sh.runs++;
    for (p = 0; p < nb;) {
        uint32_t addr = rd32(p1 + p), by = rd32(p1 + p + 4);
        const uint8_t *d = p1 + p + 8;
        p += 8 + by;
        if (addr == 35u * 16 || addr == 38u * 16) { pending_reg = (int)(addr / 16); continue; }
        if (addr != (outq & 1023) * 16u || by < 128) continue;
        if (fi >= nf) { g_sh.count_bad++; break; }
        g_sh.faces++;
        if (pending_reg != (int)fc[fi].regq) g_sh.reg_bad++;
        {
            int ex = 1, cl = 1;
            for (k = 0; k < 4; k++) {
                const uint8_t *v = d + 64 + 16 * k;
                int32_t X = (int32_t)rd32(v), Y = (int32_t)rd32(v + 4), Z = (int32_t)rd32(v + 8), W = (int32_t)rd32(v + 12);
                if (X != fc[fi].x[k] || Y != fc[fi].y[k] || Z != fc[fi].z[k] || W != fc[fi].w[k]) ex = 0;
                if (abs(X - fc[fi].x[k]) > 1 || abs(Y - fc[fi].y[k]) > 1 || llabs((int64_t)(Z >> 4) - (fc[fi].z[k] >> 4)) > 1 ||
                    ((W ^ fc[fi].w[k]) & 0x8FF0)) cl = 0;
                if (!cl && verbose && g_sh.printed < verbose) {
                    g_sh.printed++;
                    printf("shadow run %u face %d v%u: VU %d %d %d %08X | C %d %d %d %08X\n", hdr[0], fi, k, X, Y, Z, (unsigned)W,
                           fc[fi].x[k], fc[fi].y[k], fc[fi].z[k], (unsigned)fc[fi].w[k]);
                }
            }
            if (ex) g_sh.exact++;
            else if (cl) g_sh.close++;
            else g_sh.bad++;
        }
        fi++;
        pending_reg = -1;
    }
    if (fi != nf) g_sh.count_bad++;
    if (getenv("NR_SHDBG"))
        printf("shadow run %u entry %X top %u sig960 %08X %08X skinned %d j %u n %d: C faces %d, VU faces %d (mem76 %u %u %u %u hdr0 %u %u %u %u)\n", hdr[0], hdr[1], top, hdr[10], hdr[11], skinned, mem[(top + 1) & 1023].u[3], n, nf, fi,
               mem[76].u[0], mem[76].u[1], mem[76].u[2], mem[76].u[3], mem[top].u[0], mem[top].u[1], mem[top].u[2], mem[top].u[3]);
}



int main(int argc, char **argv)
{
    const char *path = NULL;
    int verbose = 0, maxruns = 1 << 30, i;
    FILE *f;
    long fsz;
    uint8_t *b;
    size_t o;
    static nr_qw mem[1024];
    static nr_vout vo[1024];
    uint64_t adc = 0, runs = 0, checked = 0, skipped_var = 0, skipped_path = 0, nopkt = 0, verts = 0;
    uint64_t bad[8] = {0};
    uint64_t var_hist[256] = {0}, var_bad[256] = {0};
    uint64_t skin_bad[8] = {0}, skin_n[8] = {0};
    uint64_t tri_guard[2] = {0}, tri_noguard[2] = {0}, tri_cull[2][2] = {{0}}, tri_cullp[2][2][2][2] = {{{{0}}}};
    static const char *bn[8] = {"hdr", "xy", "z", "fog", "rgba", "stq", "count", "?"};

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--control") && i + 1 < argc) g_control = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--verbose") && i + 1 < argc) verbose = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--max") && i + 1 < argc) maxruns = atoi(argv[++i]);
        else path = argv[i];
    }
    if (!path) { fprintf(stderr, "usage: rg-nr-nmcheck CORPUS.bin [--control N] [--verbose N]\n"); return 2; }
    f = fopen(path, "rb");
    if (!f) { fprintf(stderr, "cannot open %s\n", path); return 77; }
    fseek(f, 0, SEEK_END); fsz = ftell(f); fseek(f, 0, SEEK_SET);
    b = (uint8_t *)malloc((size_t)fsz);
    if (fread(b, 1, (size_t)fsz, f) != (size_t)fsz) return 1;
    fclose(f);
    if (memcmp(b, "NRCORP1\0", 8)) { fprintf(stderr, "not a corpus\n"); return 1; }
    o = 8;
    while (o + 4 <= (size_t)fsz && (int)runs < maxruns) {
        uint32_t hdr[18], top, cnt, nb, p, n, k;
        const uint8_t *p1;
        int var;
        const uint8_t *mainpk = NULL;
        uint32_t mainbytes = 0;
        if (memcmp(b + o, "RUN1", 4)) { fprintf(stderr, "bad record at %lu\n", (unsigned long)o); return 1; }
        memcpy(hdr, b + o + 4, sizeof hdr);
        o += 4 + sizeof hdr;
        memcpy(mem, b + o, 0x4000);
        o += 0x4000 + 0x200 + 16 + 32;
        cnt = rd32(b + o); nb = rd32(b + o + 4); o += 8;
        p1 = b + o; o += nb;
        runs++;
        if (nr_vu1sh_is_shadow_sig(hdr + 8)) { shadow_check(mem, hdr, p1, nb, verbose); continue; }
        if (nr_vu1ln_is_line_sig(hdr + 8)) { line_check(mem, hdr, p1, nb, verbose); continue; }
        var = nr_vu1_variant_from_sig(hdr + 8);
        if (var < 0) { skipped_var++; continue; }
        var_hist[var & 255]++;
        top = hdr[2];
        /* the main packet: the head kicks it at top + qw76.x (its qw104.y) */
        for (p = 0; p < nb;) {
            uint32_t addr = rd32(p1 + p), by = rd32(p1 + p + 4);
            if (addr == ((top + mem[NRQ_BATCH].u[0]) & 1023) * 16u && by >= 64) { mainpk = p1 + p + 8; mainbytes = by; }
            p += 8 + by;
        }
        (void)cnt;
        if (!mainpk) { nopkt++; continue; }
        /* deliberate faults */
        if (g_control == 1) { float t = mem[NRQ_UVSCALE].f[0]; mem[NRQ_UVSCALE].f[0] = mem[NRQ_UVSCALE].f[1]; mem[NRQ_UVSCALE].f[1] = t; }
        if (g_control == 2) { mem[NRQ_FOG].f[1] = 1e30f; mem[NRQ_FOG].f[2] = -1e30f; }
        if (g_control == 3) { for (k = 0; k < 4; k++) mem[NRQ_COLMUL].f[k] = 1.0f; mem[NRQ_MATCOL].f[0] *= 0.5f; mem[NRQ_MATCOL2].f[0] *= 0.5f; }
        if (g_control == 4) { /* weights 1/256: shrink skinned positions by 255/256 */
            mem[NRQ_POSSCALE].f[0] *= 0.99f; }
        n = (uint32_t)nr_vu1_batch(mem, top, var, vo, 1024);
        if ((int)n < 0) { skipped_path++; continue; }
        checked++;
        {
            /* tag 0: A+D x2 (PRIM, PRMODE); tag 1: vertices */
            const uint8_t *t1 = mainpk + 48;
            uint32_t nloop = rd32(t1) & 0x7FFF;
            int rb = 0;
            if (rd32(mainpk + 16) != nr_vu1_prim(mem, top) || rd32(mainpk + 32) != mem[NRQ_MAT].u[0]) { bad[0]++; rb = 1; }
            if (nloop != n || 64 + n * 48 > mainbytes) { bad[6]++; continue; }
            for (k = 0; k < n; k++) {
                const uint8_t *v = t1 + 16 + k * 48;
                float s = 0, t = 0, q = 0;
                int32_t X = (int32_t)rd32(v + 32), Y = (int32_t)rd32(v + 36), Z = (int32_t)rd32(v + 40);
                uint32_t W = rd32(v + 44);
                const nr_vout *e = &vo[k];
                int32_t ex = (int32_t)(e->sx * 16.0f), ey = (int32_t)(e->sy * 16.0f), ez = (int32_t)(e->sz * 16.0f);
                int32_t ef = (int32_t)(e->fog * 16.0f);
                int fb = 0;
                memcpy(&s, v, 4); memcpy(&t, v + 4, 4); memcpy(&q, v + 8, 4);
                verts++;
                /* vertices the program marks ADC are never drawn (outside the
                 * guard band, behind the camera, back faces): their values
                 * are huge or meaningless, so only their count is reported */
                if (W & 0x8000) { adc++; continue; }
                if (abs((int16_t)(X - ex)) > 1 || abs((int16_t)(Y - ey)) > 1) fb |= 1 << 1;
                {
                    int64_t dz = (int64_t)(Z >> 4) - (int64_t)(ez >> 4);
                    int64_t tol = 1 + (llabs((int64_t)(Z >> 4)) >> 20);
                    if (dz > tol || dz < -tol) fb |= 1 << 2;
                }
                if (abs((int)((W >> 4) & 0xFF) - (int)((ef >> 4) & 0xFF)) > 1) fb |= 1 << 3;
                {
                    float ec[4] = { e->r, e->g, e->b, e->a };
                    int c;
                    for (c = 0; c < 4; c++)
                        if (abs((int32_t)rd32(v + 16 + 4 * c) - (int32_t)ec[c]) > 1) fb |= 1 << 4;
                }
                {
                    float es[3] = { e->s, e->t, e->q }, gs[3] = { s, t, q };
                    int c;
                    for (c = 0; c < 3; c++) {
                        float d = fabsf(es[c] - gs[c]), m = fabsf(gs[c]);
                        if (d > 1e-4f * m && d > 2e-6f * fabsf(q) + 1e-12f) fb |= 1 << 5;
                    }
                }
                {
                    int c;
                    for (c = 1; c < 6; c++) if (fb & (1 << c)) bad[c]++;
                    if (fb) var_bad[var & 255]++;
                    if (var & NRV_SKIN) { uint32_t j = mem[NRQ_BATCH].u[2] ? mem[(top + 1) & 1023].u[3] & 7 : 7; skin_n[j]++; if (fb) skin_bad[j]++; }
                }
                if (fb && verbose > 0) {
                    verbose--;
                    printf("run %u var %02X v%u: got X %d Y %d Z %d W %04X rgba %d %d %d %d stq %g %g %g | ref X %d Y %d Z %d F %d rgba %.1f %.1f %.1f %.1f stq %g %g %g (bits %x)\n",
                           hdr[0], var, k, (int16_t)X, (int16_t)Y, Z >> 4, W, (int)rd32(v + 16), (int)rd32(v + 20),
                           (int)rd32(v + 24), (int)rd32(v + 28), s, t, q, (int16_t)ex, (int16_t)ey, ez >> 4, ef >> 4,
                           e->r, e->g, e->b, e->a, e->s, e->t, e->q, fb);
                }
            }
            (void)rb;
            /* triangle ADC: guard band (|(s + qw110) * qw109| > 1 for a vertex)
             * and, in the CULL variants, back faces.  Tabulated against the
             * sign the native rasterizer uses: area * qw111.z * (87.y & 0x1000
             * ? -1 : 1) * (strip parity ? -1 : 1), area = screen-space cross
             * product (GS y down) of (v1 - v0) x (v2 - v0) */
            if (var & NRV_GUARD) {
                uint32_t prim = nr_vu1_prim(mem, top) & 7, ntri = prim == 3 ? n / 3 : (n >= 2 ? n - 2 : 0), tI;
                float hand = mem[NRQ_HAND].f[2] * ((mem[NRQ_MAT].u[1] & 0x1000) ? -1.0f : 1.0f);
                for (tI = 0; tI < ntri; tI++) {
                    uint32_t i0 = prim == 3 ? 3 * tI : tI, i1 = i0 + 1, i2 = i0 + 2, c;
                    const nr_vout *a = &vo[i0], *bb = &vo[i1], *cc = &vo[i2];
                    int gout = 0, adcb = (rd32(t1 + 16 + i2 * 48 + 44) & 0x8000) != 0;
                    float area, sgn;
                    const nr_vout *tv[3] = { a, bb, cc };
                    if (prim != 3 && prim != 4) break;
                    for (c = 0; c < 3; c++) {
                        float g0 = (tv[c]->sx + mem[NRQ_GUARD + 1].f[0]) * mem[NRQ_GUARD].f[0];
                        float g1 = (tv[c]->sy + mem[NRQ_GUARD + 1].f[1]) * mem[NRQ_GUARD].f[1];
                        float g2 = (tv[c]->sz + mem[NRQ_GUARD + 1].f[2]) * mem[NRQ_GUARD].f[2];
                        if (fabsf(g0) > 1.0f || fabsf(g1) > 1.0f || fabsf(g2) > 1.0f) gout = 1;
                    }
                    area = (bb->sx - a->sx) * (cc->sy - a->sy) - (bb->sy - a->sy) * (cc->sx - a->sx);
                    sgn = area * hand * ((prim == 4 && (tI & 1)) ? -1.0f : 1.0f);
                    if (gout) { tri_guard[adcb]++; continue; }
                    if (var & NRV_CULL) { tri_cull[sgn < 0][adcb]++; tri_cullp[prim == 4][tI & 1][area * hand < 0][adcb]++; }
                    else tri_noguard[adcb]++;
                }
            }
        }
    }
    printf("guard-band triangles (ADC no/yes): %llu/%llu; inside, non-cull variants: %llu/%llu; cull variants by native sign (neg: no/yes, pos: no/yes): %llu/%llu %llu/%llu\n",
           (unsigned long long)tri_guard[0], (unsigned long long)tri_guard[1], (unsigned long long)tri_noguard[0],
           (unsigned long long)tri_noguard[1], (unsigned long long)tri_cull[1][0], (unsigned long long)tri_cull[1][1],
           (unsigned long long)tri_cull[0][0], (unsigned long long)tri_cull[0][1]);
    for (i = 0; i < 16; i++)
        if (tri_cullp[i >> 3][(i >> 2) & 1][(i >> 1) & 1][0] + tri_cullp[i >> 3][(i >> 2) & 1][(i >> 1) & 1][1] && !(i & 1))
            printf("  %s parity %d area*hand %s: ADC no %llu yes %llu\n", i >> 3 ? "strip" : "list", (i >> 2) & 1, (i >> 1) & 1 ? "neg" : "pos",
                   (unsigned long long)tri_cullp[i >> 3][(i >> 2) & 1][(i >> 1) & 1][0], (unsigned long long)tri_cullp[i >> 3][(i >> 2) & 1][(i >> 1) & 1][1]);
    printf("runs %llu: checked %llu, other variants %llu, uncovered path %llu, no main packet %llu; vertices %llu (ADC %llu)\n",
           (unsigned long long)runs, (unsigned long long)checked, (unsigned long long)skipped_var,
           (unsigned long long)skipped_path, (unsigned long long)nopkt, (unsigned long long)verts, (unsigned long long)adc);
    printf("variants checked (runs/bad vertices):");
    for (i = 0; i < 256; i++) if (var_hist[i]) printf(" %02X:%llu/%llu", i, (unsigned long long)var_hist[i], (unsigned long long)var_bad[i]);
    printf("; skin path (vertices/bad):");
    for (i = 0; i < 8; i++) if (skin_n[i]) printf(" j%d:%llu/%llu", i, (unsigned long long)skin_n[i], (unsigned long long)skin_bad[i]);
    printf("\nshadow volumes: runs %llu, faces %llu (exact %llu, within tolerance %llu, different %llu), face count wrong in %llu runs, register packet wrong %llu",
           (unsigned long long)g_sh.runs, (unsigned long long)g_sh.faces, (unsigned long long)g_sh.exact,
           (unsigned long long)g_sh.close, (unsigned long long)g_sh.bad, (unsigned long long)g_sh.count_bad,
           (unsigned long long)g_sh.reg_bad);
    printf("\nline strands: runs %llu (no packet %llu), records %llu (exact %llu, different %llu), record count wrong in %llu runs",
           (unsigned long long)g_ln.runs, (unsigned long long)g_ln.nopkt, (unsigned long long)g_ln.recs,
           (unsigned long long)g_ln.exact, (unsigned long long)g_ln.bad, (unsigned long long)g_ln.count_bad);
    printf("\nmismatches:");
    {
        uint64_t tot = 0;
        for (i = 0; i < 7; i++) { printf(" %s %llu", bn[i], (unsigned long long)bad[i]); tot += bad[i]; }
        tot += g_sh.bad + g_sh.count_bad + g_sh.reg_bad + g_ln.bad + g_ln.count_bad + g_ln.nopkt;
        printf("\n%s\n", tot == 0 && checked > 0 ? "PASS" : "FAIL");
        return tot == 0 && checked > 0 ? 0 : 1;
    }
}

static void line_check(const nr_qw *mem, const uint32_t *hdr, const uint8_t *p1, uint32_t nb, int verbose)
{
    static float pos[1024][3];
    static nr_lnrec rec[1024];
    uint32_t top = hdr[2], outq = top + mem[76].u[0], p, k;
    int skinned = hdr[10] == 0x400000A1u || hdr[10] == 0x40000090u, n, nr, four = mem[top & 1023].u[0] == 0x13, i;
    const uint8_t *pk = NULL;
    uint32_t pkb = 0;
    n = nr_vu1_decode_positions(mem, top, skinned, pos, 1024);
    if (g_control == 6) {   /* fade slope doubled: must FAIL */
        static nr_qw m2[112];
        memcpy(m2, mem, sizeof m2);
        m2[68].f[0] *= 1.001f;
        mem = m2;
    }
    nr = nr_vu1ln_records(mem, (const float (*)[3])pos, (uint32_t)n, four, rec, 1024);
    g_ln.runs++;
    for (p = 0; p < nb;) {
        uint32_t addr = rd32(p1 + p), by = rd32(p1 + p + 4);
        if (addr == (outq & 1023) * 16u) { pk = p1 + p + 8; pkb = by; }
        p += 8 + by;
    }
    if (!pk) { g_ln.nopkt++; return; }
    if ((rd32(pk + 48) & 0x7FFF) != (uint32_t)nr || pkb < 64 + (uint32_t)nr * 144) { g_ln.count_bad++; return; }
    for (i = 0; i < nr; i++) {
        const uint8_t *r = pk + 64 + i * 144;
        int ok = rd32(r) == 16 && rd32(r + 4) == 16 && rd32(r + 8) == 16 && rd32(r + 12) == rec[i].alpha;
        for (k = 0; k < 8; k++) {
            const uint8_t *v = r + 16 + 16 * k;
            if ((int32_t)rd32(v) != rec[i].x[k] || (int32_t)rd32(v + 4) != rec[i].y[k] || (int32_t)rd32(v + 8) != rec[i].z[k] ||
                rd32(v + 12) != (uint32_t)rec[i].adc)
                ok = 0;
        }
        g_ln.recs++;
        if (ok) g_ln.exact++;
        else {
            g_ln.bad++;
            if (verbose && g_ln.printed < verbose) {
                g_ln.printed++;
                printf("line run %u rec %d (four %d): VU a %u v0 %d %d %d %08X v1 %d %d | C a %u v0 %d %d %d %08X v1 %d %d\n", hdr[0], i, four,
                       rd32(r + 12), (int32_t)rd32(r + 16), (int32_t)rd32(r + 20), (int32_t)rd32(r + 24), rd32(r + 28),
                       (int32_t)rd32(r + 32), (int32_t)rd32(r + 36), rec[i].alpha, rec[i].x[0], rec[i].y[0], rec[i].z[0],
                       (unsigned)rec[i].adc, rec[i].x[1], rec[i].y[1]);
            }
        }
    }
}
