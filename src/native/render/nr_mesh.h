/* SPDX-License-Identifier: CC0-1.0 */
/* Native mesh cache (docs/NATIVE-RENDER.md "Mesh cache"): a model mesh's
 * static VIF packet (vertex batches for the dominant VU1 program) decoded
 * once into a vertex array and a triangle-list index array. */
#ifndef RG_NR_MESH_H
#define RG_NR_MESH_H

#include <stdint.h>

#include "nr_vu1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* one vertex, the program's raw quantised inputs (scales are applied by the
 * shader exactly where the VU applies them); 28 bytes, matches nr_draw.hlsl */
typedef struct nr_vtx {
    int16_t px, py, pz, pw;   /* V3-16 position (pw 0) */
    int8_t nx, ny, nz, nw;    /* V3-8 normal */
    int16_t u, v;             /* UV as the VU holds it (ITOF15 input): V2-8 unsigned or V2-16 (tiling maps) */
    uint8_t r, g, b, a;       /* V4-8 unsigned colour (0x80 = 1.0) */
    uint8_t bone[4];          /* skin: bone matrix row - 768 (rows 768..899) */
    uint8_t wgt[4];           /* skin: weights (/255); unused bones 0 */
} nr_vtx;

enum { NR_MISS_NRM = 1, NR_MISS_UV = 2, NR_MISS_COL = 4 };

typedef struct nr_mesh {
    uint32_t id;              /* unique, never reused (GPU buffer key) */
    uint32_t pkt;             /* the packet address it was decoded from */
    uint32_t hash;            /* FNV-1a of the packet's bytes */
    uint32_t shash;           /* sparse FNV-1a (tags, block heads, 1 qword in 32): revalidation */
    uint32_t pkt_bytes;
    uint32_t nvtx, nidx;
    nr_vtx *vtx;
    uint32_t *idx;            /* triangle list, winding of the even strip triangles */
    uint32_t nbatch;
#define NR_MESH_MAXB 128
    struct { uint32_t first, count, prim; } batch[NR_MESH_MAXB];   /* the first 128 batches (verification, line strands) */
    int batch_overflow;       /* more batches than batch[] holds */
    uint32_t last_prim;       /* header .x of the last batch (the PRIM the program leaves) */
    uint32_t prim_mask;       /* 1 << header .x of every batch */
    int skinned;              /* any batch with skin records */
    int missing;              /* NR_MISS_*: arrays some batch did not unpack (left zero) */
    int skipwrite;            /* some UNPACK used STCYCL CL > WL */
    int bad;                  /* not drawable natively (reason in why) */
    const char *why;
    float bbox[6];            /* raw position bounds (min xyz, max xyz) */
} nr_mesh;

/* The mesh decoded from the packet at host address pkt (cached; the cache
 * re-decodes when the packet's bytes change).  skinned_variant: the decode
 * piece resident is the skinned one (skin records are read).  Never NULL;
 * check ->bad.  Meshes are never freed (records in flight point at them). */
const nr_mesh *nr_mesh_get(uint32_t pkt, int skinned_variant);

/* decode without the cache (tests); caller frees with nr_mesh_free */
nr_mesh *nr_mesh_decode(uint32_t pkt, int skinned_variant);
/* decode a bare VIF word stream (tests: render_meshcheck); cb, when not NULL,
 * sees every batch image (TOP-relative qwords and which ones were written)
 * at its MSCNT */
typedef void (*nr_batch_cb)(void *user, const nr_qw *img, const uint8_t *written);
nr_mesh *nr_mesh_decode_words(const uint32_t *w, uint32_t n, int skinned_variant, nr_batch_cb cb, void *user);
void nr_mesh_free(nr_mesh *m);

typedef struct nr_mesh_stats {
    uint64_t lookups, decodes, rehash, bad;
    uint64_t bytes_hashed;
} nr_mesh_stats;
const nr_mesh_stats *nr_mesh_get_stats(void);

#ifdef __cplusplus
}
#endif
#endif
