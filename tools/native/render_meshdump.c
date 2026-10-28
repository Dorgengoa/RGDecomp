/* SPDX-License-Identifier: CC0-1.0 */
/* rg-nr-meshdump: inspect a mesh packet dumped with RG_NR_DUMP=DIR
 * (docs/NATIVE-RENDER.md "Tools").
 *
 *   rg-nr-meshdump FILE.vif [--skin] [--verts N]
 *
 * Lists the VIF commands (STCYCL, UNPACK format/address/count, MSCNT), then
 * the decoder's verdict and, per batch, the header and the first N decoded
 * vertices. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nr_mesh.h"

static int g_nverts = 4, g_batch;

static void on_batch(void *user, const nr_qw *img, const uint8_t *wr)
{
    int i;
    (void)user;
    printf("batch %d: hdr0 %08X %08X %08X %08X hdr1 %08X %08X %08X %08X\n", g_batch++, img[0].u[0], img[0].u[1],
           img[0].u[2], img[0].u[3], img[1].u[0], img[1].u[1], img[1].u[2], img[1].u[3]);
    {
        uint32_t sk = 2 + img[1].u[2];
        for (i = 0; i < g_nverts && sk + 2 * i + 1 < 1024; i++)
            printf("  skin %03X [%x] %d %d %d %d | [%x] %d %d %d %d\n", sk + 2 * i, wr[sk + 2 * i], img[sk + 2 * i].i[0],
                   img[sk + 2 * i].i[1], img[sk + 2 * i].i[2], img[sk + 2 * i].i[3], wr[sk + 2 * i + 1],
                   img[sk + 2 * i + 1].i[0], img[sk + 2 * i + 1].i[1], img[sk + 2 * i + 1].i[2], img[sk + 2 * i + 1].i[3]);
    }
    for (i = 2; i < 2 + g_nverts; i++)
        printf("  qw %03X [%x] %d %d %d %d\n", i, wr[i], img[i].i[0], img[i].i[1], img[i].i[2], img[i].i[3]);
}

int main(int argc, char **argv)
{
    const char *path = NULL;
    int skin = 0, i;
    FILE *f;
    long n;
    uint32_t *w, pos = 0, cl = 1, wl = 1;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--skin")) skin = 1;
        else if (!strcmp(argv[i], "--verts") && i + 1 < argc) g_nverts = atoi(argv[++i]);
        else path = argv[i];
    }
    if (!path || !(f = fopen(path, "rb"))) { fprintf(stderr, "usage: rg-nr-meshdump FILE.vif [--skin]\n"); return 2; }
    fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
    w = (uint32_t *)malloc((size_t)n + 4);
    if (fread(w, 1, (size_t)n, f) != (size_t)n) return 1;
    fclose(f);
    n /= 4;
    while (pos < (uint32_t)n) {
        uint32_t c = w[pos], cmd = (c >> 24) & 0x7F, num = (c >> 16) & 0xFF, imm = c & 0xFFFF, pw = 0;
        if (cmd == 0x01) { cl = c & 0xFF; wl = (c >> 8) & 0xFF; printf("%5u STCYCL cl %u wl %u\n", pos, cl, wl); }
        else if (cmd >= 0x60) {
            uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, nn = num ? num : 256, bits = (32u >> vl) * (vn + 1);
            uint32_t el = wl <= cl ? nn : cl * (nn / wl) + (nn % wl < cl ? nn % wl : cl);
            pw = (el * bits + 31) / 32;
            printf("%5u UNPACK V%u-%u addr %03X num %u%s%s%s\n", pos, vn + 1, 32 >> vl, imm & 0x3FF, nn,
                   imm & 0x4000 ? " usn" : "", imm & 0x8000 ? " flg" : "", cmd & 0x10 ? " MASK" : "");
        } else if (cmd == 0x17) printf("%5u MSCNT\n", pos);
        else if (cmd == 0x20) pw = 1;
        else if (cmd == 0x30 || cmd == 0x31) pw = 4;
        else if (cmd == 0x4A) pw = (num ? num : 256) * 2;
        else if (cmd == 0x50 || cmd == 0x51) pw = (imm ? imm : 65536) * 4;
        if (cmd != 0 && cmd != 0x01 && cmd < 0x60 && cmd != 0x17) printf("%5u cmd %02X %08X\n", pos, cmd, c);
        pos += 1 + pw;
    }
    {
        nr_mesh *m = nr_mesh_decode_words(w, (uint32_t)n, skin, on_batch, NULL);
        printf("decoder: %s%s, %u vertices, %u indices, %u batches, missing %x, skinned %d\n",
               m->bad ? "BAD: " : "ok", m->bad ? m->why : "", m->nvtx, m->nidx, m->nbatch, m->missing, m->skinned);
        for (i = 0; i < (int)m->nvtx && i < g_nverts; i++) {
            const nr_vtx *v = &m->vtx[i];
            printf("  v%d pos %d %d %d nrm %d %d %d uv %u %u col %u %u %u %u bone %u %u %u %u w %u %u %u %u\n", i,
                   v->px, v->py, v->pz, v->nx, v->ny, v->nz, v->u, v->v, v->r, v->g, v->b, v->a, v->bone[0],
                   v->bone[1], v->bone[2], v->bone[3], v->wgt[0], v->wgt[1], v->wgt[2], v->wgt[3]);
        }
    }
    return 0;
}
