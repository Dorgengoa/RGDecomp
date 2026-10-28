/* SPDX-License-Identifier: CC0-1.0 */
/* rg-nr-meshcheck: the native mesh decoder (src/native/render/nr_mesh.c)
 * against the VIF interpreter on a retail capture (docs/NATIVE-RENDER.md
 * "Verification").
 *
 *   rg-nr-meshcheck CAPTURE.vifcap [--control] [--verbose N]
 *
 * Replays the capture's VIF1 stream through the VIF + VU1 models.  The words
 * after each MSCAL 0x320 (a mesh packet of the dominant model program: STCYCL,
 * UNPACK..., MSCNT per batch) also go through nr_mesh_decode_words; at every
 * MSCNT the decoder's batch image (the qwords its UNPACKs wrote) must equal
 * VU1 data memory at TOPS bit for bit.  Also prints the decoder's verdicts
 * (meshes decodable / why not).
 * --control: the decoder sees every UNPACK's first payload word with bit 3
 * flipped (must FAIL).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr_mesh.h"
#include "vif.h"
#include "vu.h"

typedef struct rec { uint32_t kind, bytes; const uint8_t *p; } rec;
static uint8_t *g_file;
static rec g_rec[64];
static int g_nrec;
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static int load(const char *path)
{
    FILE *f = fopen(path, "rb");
    long n;
    uint32_t i, cnt, off;
    if (!f) return 0;
    fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
    g_file = (uint8_t *)malloc((size_t)n);
    if (fread(g_file, 1, (size_t)n, f) != (size_t)n) { fclose(f); return 0; }
    fclose(f);
    if (n < 12 || memcmp(g_file, "VIFCAP1\0", 8) != 0) return 0;
    cnt = rd32(g_file + 8); off = 12;
    for (i = 0; i < cnt && g_nrec < 64; i++) {
        rec r;
        r.kind = rd32(g_file + off); r.bytes = rd32(g_file + off + 4); r.p = g_file + off + 8;
        off += 8 + r.bytes;
        if (off > (uint32_t)n) return 0;
        g_rec[g_nrec++] = r;
    }
    return 1;
}
static const rec *find(uint32_t kind)
{
    int i;
    for (i = 0; i < g_nrec; i++) if (g_rec[i].kind == kind) return &g_rec[i];
    return NULL;
}

/* one segment: its words and the VU memory snapshot at each MSCNT */
#define MAXB 256
static uint32_t *g_seg; static size_t g_segn, g_segcap;
static uint8_t *g_snap[MAXB]; static uint32_t g_tops[MAXB]; static int g_nb;
static int g_bi, g_verbose;
static uint64_t g_batches, g_qw_cmp, g_qw_bad, g_meshes, g_bad_meshes;
static struct { const char *why; uint64_t n; } g_why[32]; static int g_nwhy;

static void on_batch(void *user, const nr_qw *img, const uint8_t *wr)
{
    uint32_t a;
    (void)user;
    if (g_bi >= g_nb) return;
    g_batches++;
    for (a = 0; a < 1024; a++) {
        const uint8_t *m;
        if (!wr[a]) continue;
        m = g_snap[g_bi] + ((g_tops[g_bi] + a) & 1023) * 16;
        g_qw_cmp++;
        {
            /* only the lanes the UNPACK wrote (a V3 UNPACK's W lane is not
             * part of the data: docs/VU.md "V3 W lane") */
            int c, diff = 0;
            for (c = 0; c < 4; c++)
                if (((wr[a] >> c) & 1) && rd32(m + 4 * c) != img[a].u[c]) diff = 1;
            if (!diff) continue;
        }
        {
            g_qw_bad++;
            if (g_verbose > 0) {
                g_verbose--;
                printf("batch %llu qw %03X: decoder %08X %08X %08X %08X vif %08X %08X %08X %08X\n",
                       (unsigned long long)g_batches, a, img[a].u[0], img[a].u[1], img[a].u[2], img[a].u[3],
                       rd32(m), rd32(m + 4), rd32(m + 8), rd32(m + 12));
            }
        }
    }
    g_bi++;
}

static void seg_end(void)
{
    nr_mesh *m;
    int i;
    if (!g_segn) { g_nb = 0; return; }
    g_bi = 0;
    m = nr_mesh_decode_words(g_seg, (uint32_t)g_segn, 0, on_batch, NULL);
    g_meshes++;
    if (m->bad) {
        g_bad_meshes++;
        for (i = 0; i < g_nwhy; i++) if (!strcmp(g_why[i].why, m->why)) break;
        if (i == g_nwhy && g_nwhy < 32) { g_why[g_nwhy].why = m->why; g_why[g_nwhy].n = 0; g_nwhy++; }
        if (i < 32) g_why[i].n++;
    }
    nr_mesh_free(m);
    g_segn = 0;
    g_nb = 0;
}

static void seg_add(const uint32_t *w, size_t n, int control)
{
    size_t i;
    if (g_segn + n > g_segcap) { g_segcap = (g_segn + n) * 2 + 1024; g_seg = (uint32_t *)realloc(g_seg, g_segcap * 4); }
    for (i = 0; i < n; i++) g_seg[g_segn + i] = w[i];
    if (control && n > 1 && ((w[0] >> 24) & 0x7F) >= 0x60) g_seg[g_segn + 1] ^= 8u;
    g_segn += n;
}

int main(int argc, char **argv)
{
    static vu_state vu;
    static vif_state vif;
    const char *path = NULL;
    const rec *r1, *r2, *r3;
    uint32_t nwords, pos = 0, k;
    const uint32_t *words;
    int control = 0, inseg = 0, i;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--control")) control = 1;
        else if (!strcmp(argv[i], "--verbose") && i + 1 < argc) g_verbose = atoi(argv[++i]);
        else path = argv[i];
    }
    if (!path || !load(path)) { fprintf(stderr, "usage: rg-nr-meshcheck CAPTURE [--control]\n"); return 77; }
    r1 = find(1); r2 = find(2); r3 = find(3);
    if (!r1 || !r2 || !r3) return 1;
    vu_init(&vu, 1);
    vif_init(&vif, 1, &vu);
    {
        const uint8_t *p = r1->p;
        memcpy(vu.mem, p, 0x4000);
        vu_load_code(&vu, 0, p + 0x4000, 0x4000);
        p += 0x8000;
        memcpy(vu.vf, p, 0x200); p += 0x200;
        for (k = 0; k < 16; k++) { uint16_t v; memcpy(&v, p + 2 * k, 2); vu.vi[k] = v; }
        p += 32 + 16;
        vu.q = rd32(p); vu.p = rd32(p + 4); vu.i = rd32(p + 8); vu.r = rd32(p + 12);
        vu.tpc = rd32(p + 28);
        vu.vf[0].u[0] = vu.vf[0].u[1] = vu.vf[0].u[2] = 0; vu.vf[0].u[3] = 0x3F800000u;
        vu.vi[0] = 0;
    }
    {
        const uint8_t *p = r2->p;
        vif.cl = rd32(p); vif.wl = rd32(p + 4); vif.mode = rd32(p + 8); vif.mask = rd32(p + 12);
        for (k = 0; k < 4; k++) { vif.row[k] = rd32(p + 16 + 4 * k); vif.col[k] = rd32(p + 32 + 4 * k); }
        vif.base = rd32(p + 48); vif.ofst = rd32(p + 52); vif.tops = rd32(p + 56);
        vif.itops = rd32(p + 60); vif.dbf = rd32(p + 64);
    }
    for (i = 0; i < MAXB; i++) g_snap[i] = (uint8_t *)malloc(0x4000);
    nwords = r3->bytes / 4;
    words = (const uint32_t *)r3->p;
    while (pos < nwords) {
        uint32_t code = words[pos], cmd = (code >> 24) & 0x7F;
        long n = vif_payload_words(code, vif.cl, vif.wl);
        int meshcmd;
        if (n < 0) break;
        /* a mesh packet ends at the first command that is not part of one
         * (the next object's packets: MSCAL, DIRECT, UNPACK without FLG) */
        meshcmd = cmd == 0x00 || cmd == 0x01 || cmd == 0x05 || cmd == 0x10 || cmd == 0x11 || cmd == 0x13 ||
                  cmd == 0x17 || (cmd >= 0x60 && (code & 0x8000));
        if (inseg && !meshcmd) { seg_end(); inseg = 0; }
        if (inseg) {
            if (cmd == 0x17 && g_nb < MAXB) {
                memcpy(g_snap[g_nb], vu.mem, 0x4000);
                g_tops[g_nb] = vif.tops;
                g_nb++;
            }
            seg_add(words + pos, (size_t)(1 + n), control);
        }
        vif_write(&vif, words + pos, 1 + (uint32_t)n);
        if ((cmd == 0x14 || cmd == 0x15) && (code & 0xFFFF) * 8 == 0x320) { inseg = 1; g_segn = 0; g_nb = 0; }
        pos += 1 + (uint32_t)n;
    }
    if (inseg) seg_end();
    printf("mesh packets %llu (not decodable %llu), batches %llu, qwords compared %llu, different %llu\n",
           (unsigned long long)g_meshes, (unsigned long long)g_bad_meshes, (unsigned long long)g_batches,
           (unsigned long long)g_qw_cmp, (unsigned long long)g_qw_bad);
    for (i = 0; i < g_nwhy; i++) printf("  not decodable: %llu x %s\n", (unsigned long long)g_why[i].n, g_why[i].why);
    printf("%s\n", g_qw_bad == 0 && g_qw_cmp > 0 ? "PASS" : "FAIL");
    return g_qw_bad == 0 && g_qw_cmp > 0 ? 0 : 1;
}
