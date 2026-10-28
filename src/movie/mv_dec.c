/* SPDX-License-Identifier: CC0-1.0 */
/* MPEG-2 program stream demultiplexer + MPEG-2 video decoder for the converted movies
 * (docs/MOVIE.md). Written from ISO/IEC 13818-1/-2 and docs/MVI.md.
 *
 * Supported (everything the 89 retail movies use, see the stream survey in MOVIE.md):
 * MPEG-2 MP@ML, 4:2:0, frame pictures (picture_structure 3) with frame_pred_frame_dct = 1,
 * I/P/B, both intra VLC tables, any intra_dc_precision, both q_scale_types, matrices from
 * the sequence header or a quant matrix extension, open and closed GOPs, skipped
 * macroblocks, half-pel motion compensation, mismatch control.
 * Refused with RG_MV_ERR_UNSUPPORTED: field pictures, frame_pred_frame_dct = 0 (field
 * motion / field DCT / dual prime), concealment motion vectors, alternate scan, D pictures,
 * non-4:2:0 chroma, scalable/MPEG-1 streams. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mv_internal.h"

#define IN_CHUNK (64 * 1024)
#define ES_PAD 16
#define MAX_PTS 256

typedef struct pts_rec {
    uint64_t start, end;   /* ES byte range of the PES payload */
    int64_t pts;
    int used;
} pts_rec;

typedef struct mv_frame {
    uint8_t *y, *cb, *cr;
    int64_t pts;
    int has_pts;
    int type;
} mv_frame;

typedef struct bits {
    const uint8_t *buf;   /* readable (with zero padding) well past `end` */
    uint32_t pos;         /* bit position */
    uint32_t end;         /* bit position of the unit's end */
} bits;

struct rg_mvdec {
    /* input */
    FILE *fp;
    char path[520];          /* fp's file (save states reopen it: rg_mvdec_ss_reopen) */
    const uint8_t *mem;
    size_t memsize, mempos;
    int src_eof;
    uint8_t *in;
    size_t in_pos, in_len, in_cap;
    int ps_end;              /* program end code seen, or input exhausted */
    /* video elementary stream */
    uint8_t *es;
    size_t es_pos, es_len, es_cap;
    uint64_t es_base;        /* absolute ES offset of es[0] */
    pts_rec pts[MAX_PTS];
    int npts;
    /* sequence */
    rg_mvdec_info info;
    int have_seq, have_seqext;
    int mbw, mbh, ystride, cstride, aw, ah;
    uint8_t qm_intra[64], qm_inter[64];   /* natural order */
    /* GOP / picture */
    int closed_gop, broken_link;
    int ptype, fcode[2][2], dc_prec, pstruct, fpfd, cmv, qst, ivf, alt;
    /* frames: 3 buffers. ref_old/ref_new = forward/backward references; pending = the
     * newest reference, not yet output (display order lags decode order by one ref). */
    mv_frame fb[3];
    int ref_old, ref_new, pending;
    uint32_t out_index;
    int64_t last_out_pts;
    int have_out_pts;
    uint32_t npics;
    /* slice state */
    int qscale;
    int dc_pred[3];
    int pmv[2][2];           /* [fwd/bwd][h/v], half-pel */
    int last_flags;          /* macroblock_type of the previous MB (B skipped MBs) */
    int mv[2][2];            /* vectors of the previous MB */
    int32_t blk[64];
    mv_tables *tab;
    char err[192];
};

/* ------------------------------------------------------------------ errors */

static int fail(rg_mvdec *d, int code, const char *fmt, const char *a, long n)
{
    char tmp[160];
    snprintf(tmp, sizeof tmp, fmt, a, n);
    snprintf(d->err, sizeof d->err, "%s", tmp);
    return code;
}

/* ------------------------------------------------------------------- input */

static int src_fill(rg_mvdec *d, size_t need)
{
    while (d->in_len - d->in_pos < need && !d->src_eof) {
        if (d->in_pos > 0) {
            memmove(d->in, d->in + d->in_pos, d->in_len - d->in_pos);
            d->in_len -= d->in_pos;
            d->in_pos = 0;
        }
        size_t want = need > IN_CHUNK ? need : IN_CHUNK;
        if (d->in_cap < d->in_len + want) {
            size_t cap = d->in_len + want;
            uint8_t *p = (uint8_t *)realloc(d->in, cap);
            if (!p) return RG_MV_ERR_NOMEM;
            d->in = p;
            d->in_cap = cap;
        }
        size_t got;
        if (d->fp) {
            got = fread(d->in + d->in_len, 1, d->in_cap - d->in_len, d->fp);
            if (got == 0) {
                if (ferror(d->fp)) return fail(d, RG_MV_ERR_IO, "read error%s", "", 0);
                d->src_eof = 1;
            }
        } else {
            got = d->memsize - d->mempos;
            if (got > d->in_cap - d->in_len) got = d->in_cap - d->in_len;
            memcpy(d->in + d->in_len, d->mem + d->mempos, got);
            d->mempos += got;
            if (got == 0) d->src_eof = 1;
        }
        d->in_len += got;
    }
    return 0;
}

static int es_append(rg_mvdec *d, const uint8_t *p, size_t n, int has_pts, int64_t pts)
{
    if (d->es_pos > 0 && d->es_pos >= d->es_len / 2) {
        /* compact: drop consumed bytes */
        memmove(d->es, d->es + d->es_pos, d->es_len - d->es_pos);
        d->es_base += d->es_pos;
        d->es_len -= d->es_pos;
        d->es_pos = 0;
        int k = 0;
        for (int i = 0; i < d->npts; i++)
            if (d->pts[i].end > d->es_base) d->pts[k++] = d->pts[i];
        d->npts = k;
    }
    if (d->es_cap < d->es_len + n + ES_PAD) {
        size_t cap = (d->es_len + n + ES_PAD) * 2;
        uint8_t *q = (uint8_t *)realloc(d->es, cap);
        if (!q) return RG_MV_ERR_NOMEM;
        d->es = q;
        d->es_cap = cap;
    }
    if (has_pts) {
        if (d->npts == MAX_PTS) {
            memmove(d->pts, d->pts + 1, (MAX_PTS - 1) * sizeof(pts_rec));
            d->npts--;
        }
        pts_rec *r = &d->pts[d->npts++];
        r->start = d->es_base + d->es_len;
        r->end = r->start + n;
        r->pts = pts;
        r->used = 0;
    }
    memcpy(d->es + d->es_len, p, n);
    d->es_len += n;
    memset(d->es + d->es_len, 0, ES_PAD);
    return 0;
}

/* Demultiplex packets until at least one more video payload byte arrived (or the end).
 * Returns 1 if data was added, 0 at the end, <0 on error. */
static int demux_more(rg_mvdec *d)
{
    while (!d->ps_end) {
        int r = src_fill(d, 6);
        if (r) return r;
        size_t avail = d->in_len - d->in_pos;
        if (avail < 4) {
            d->ps_end = 1;
            break;
        }
        const uint8_t *b = d->in + d->in_pos;
        if (b[0] != 0 || b[1] != 0 || b[2] != 1)
            return fail(d, RG_MV_ERR_FORMAT, "program stream sync lost%s at packet %ld", "",
                        (long)d->in_pos);
        uint8_t sid = b[3];
        if (sid == 0xB9) {
            d->ps_end = 1;
            break;
        }
        if (sid == 0xBA) {
            if ((r = src_fill(d, 14))) return r;
            b = d->in + d->in_pos;
            if (d->in_len - d->in_pos < 14) return fail(d, RG_MV_ERR_FORMAT, "truncated pack header%s", "", 0);
            if ((b[4] & 0xC0) != 0x40) return fail(d, RG_MV_ERR_UNSUPPORTED, "MPEG-1 system stream%s", "", 0);
            d->in_pos += 14 + (b[13] & 7);
            continue;
        }
        if (avail < 6) return fail(d, RG_MV_ERR_FORMAT, "truncated packet%s", "", 0);
        size_t len = ((size_t)b[4] << 8) | b[5];
        if ((r = src_fill(d, 6 + len))) return r;
        b = d->in + d->in_pos;
        if (d->in_len - d->in_pos < 6 + len)
            return fail(d, RG_MV_ERR_FORMAT, "truncated packet%s (stream %ld)", "", sid);
        d->in_pos += 6 + len;
        if (sid != 0xE0) continue;    /* padding, system header, audio */
        if (len < 3 || (b[6] & 0xC0) != 0x80)
            return fail(d, RG_MV_ERR_FORMAT, "bad PES header%s", "", 0);
        size_t hl = b[8];
        if (3 + hl > len) return fail(d, RG_MV_ERR_FORMAT, "bad PES header length%s", "", 0);
        int has_pts = (b[7] & 0x80) != 0;
        int64_t pts = 0;
        if (has_pts) {
            const uint8_t *p = b + 9;
            pts = ((int64_t)((p[0] >> 1) & 7) << 30) | ((int64_t)p[1] << 22) |
                  ((int64_t)(p[2] >> 1) << 15) | ((int64_t)p[3] << 7) | (p[4] >> 1);
        }
        size_t plen = len - 3 - hl;
        if (plen == 0) continue;
        if ((r = es_append(d, b + 9 + hl, plen, has_pts, pts))) return r;
        return 1;
    }
    return 0;
}

/* Find the next start code (00 00 01) at or after es offset `from`. Returns its offset,
 * or (size_t)-1 at the end of the stream. Demuxes as needed. */
static size_t find_start(rg_mvdec *d, size_t from, int *err)
{
    *err = 0;
    for (;;) {
        size_t n = d->es_len;
        const uint8_t *e = d->es;
        size_t i = from;
        while (i + 3 < n) {
            if (e[i + 2] > 1) {
                i += 3;   /* no start code can begin at i, i+1 or i+2 */
                continue;
            }
            if (e[i + 2] == 1 && e[i] == 0 && e[i + 1] == 0) return i;
            i++;
        }
        size_t old_pos = d->es_pos;
        int r = demux_more(d);
        if (r < 0) {
            *err = r;
            return (size_t)-1;
        }
        from = i - (old_pos - d->es_pos);   /* es_append may have compacted: rebase */
        if (r == 0) return (size_t)-1;      /* end of stream */
    }
}

/* Ensure at least `n` bytes from es offset `at` are buffered (or the stream ended).
 * Returns the (possibly rebased) offset. */
static size_t ensure(rg_mvdec *d, size_t at, size_t n, int *err)
{
    *err = 0;
    while (d->es_len - at < n) {
        size_t old_pos = d->es_pos;
        int r = demux_more(d);
        if (r < 0) {
            *err = r;
            return at;
        }
        at -= old_pos - d->es_pos;
        if (r == 0) break;
    }
    return at;
}

/* -------------------------------------------------------------- bit reader */

static inline uint32_t load_be32(const uint8_t *p)
{
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | p[3];
}

static inline uint32_t show(const bits *b, int n)   /* 1 <= n <= 24 */
{
    uint32_t v = load_be32(b->buf + (b->pos >> 3)) << (b->pos & 7);
    return v >> (32 - n);
}

static inline void skip(bits *b, int n) { b->pos += (uint32_t)n; }

static inline uint32_t get(bits *b, int n)
{
    uint32_t v = show(b, n);
    b->pos += (uint32_t)n;
    return v;
}

static inline int overrun(const bits *b) { return b->pos > b->end; }

/* --------------------------------------------------------------- headers */

static const int k_fr[9][2] = {{0, 1},     {24000, 1001}, {24, 1},       {25, 1}, {30000, 1001},
                               {30, 1},    {50, 1},       {60000, 1001}, {60, 1}};

static void load_matrix(bits *b, uint8_t *m)
{
    for (int i = 0; i < 64; i++) m[mv_zigzag[i]] = (uint8_t)get(b, 8);
}

static int parse_seq(rg_mvdec *d, bits *b)
{
    int w = (int)get(b, 12), h = (int)get(b, 12);
    int ar = (int)get(b, 4), frc = (int)get(b, 4);
    uint32_t br = get(b, 18);
    skip(b, 1);
    skip(b, 10); /* vbv_buffer_size */
    skip(b, 1);  /* constrained_parameters_flag */
    if (get(b, 1)) load_matrix(b, d->qm_intra);
    else memcpy(d->qm_intra, mv_default_intra_q, 64);
    if (get(b, 1)) load_matrix(b, d->qm_inter);
    else memset(d->qm_inter, 16, 64);
    if (w <= 0 || h <= 0 || w > 720 || h > 576 || frc < 1 || frc > 8)
        return fail(d, RG_MV_ERR_FORMAT, "implausible sequence header%s (%ldx...)", "", w);
    if (d->have_seq && (w != d->info.width || h != d->info.height))
        return fail(d, RG_MV_ERR_UNSUPPORTED, "picture size change%s", "", 0);
    d->info.width = w;
    d->info.height = h;
    d->info.aspect_code = ar;
    d->info.fps_num = k_fr[frc][0];
    d->info.fps_den = k_fr[frc][1];
    d->info.bit_rate = br * 400u;
    d->info.pts_step = (int)(90000LL * d->info.fps_den / d->info.fps_num);
    if (!d->have_seq) {
        d->mbw = (w + 15) / 16;
        d->mbh = (h + 15) / 16;
        d->aw = d->mbw * 16;
        d->ah = d->mbh * 16;
        d->ystride = d->aw;
        d->cstride = d->aw / 2;
        for (int i = 0; i < 3; i++) {
            size_t ys = (size_t)d->ystride * d->ah, cs = (size_t)d->cstride * (d->ah / 2);
            uint8_t *p = (uint8_t *)malloc(ys + 2 * cs);
            if (!p) return RG_MV_ERR_NOMEM;
            memset(p, 16, ys);
            memset(p + ys, 128, 2 * cs);
            d->fb[i].y = p;
            d->fb[i].cb = p + ys;
            d->fb[i].cr = p + ys + cs;
        }
    }
    d->have_seq = 1;
    return 0;
}

static int parse_ext(rg_mvdec *d, bits *b, int in_picture)
{
    int id = (int)get(b, 4);
    switch (id) {
    case 1: { /* sequence extension */
        int pl = (int)get(b, 8);
        skip(b, 1); /* progressive_sequence */
        int cf = (int)get(b, 2);
        int hx = (int)get(b, 2), vx = (int)get(b, 2);
        uint32_t brx = get(b, 12);
        skip(b, 1);
        skip(b, 8);
        skip(b, 1); /* low_delay */
        int fn = (int)get(b, 2), fd = (int)get(b, 5);
        (void)pl;
        if (cf != 1) return fail(d, RG_MV_ERR_UNSUPPORTED, "chroma_format %s%ld", "", cf);
        if (hx || vx) return fail(d, RG_MV_ERR_UNSUPPORTED, "size extension%s", "", 0);
        d->info.bit_rate += (brx << 18) * 400u;
        d->info.fps_num *= fn + 1;
        d->info.fps_den *= fd + 1;
        d->info.pts_step = (int)(90000LL * d->info.fps_den / d->info.fps_num);
        d->have_seqext = 1;
        return 0;
    }
    case 3: /* quant matrix extension */
        if (get(b, 1)) load_matrix(b, d->qm_intra);
        if (get(b, 1)) load_matrix(b, d->qm_inter);
        return 0;
    case 8: { /* picture coding extension */
        if (!in_picture) return 0;
        d->fcode[0][0] = (int)get(b, 4);
        d->fcode[0][1] = (int)get(b, 4);
        d->fcode[1][0] = (int)get(b, 4);
        d->fcode[1][1] = (int)get(b, 4);
        d->dc_prec = (int)get(b, 2);
        d->pstruct = (int)get(b, 2);
        skip(b, 1); /* top_field_first */
        d->fpfd = (int)get(b, 1);
        d->cmv = (int)get(b, 1);
        d->qst = (int)get(b, 1);
        d->ivf = (int)get(b, 1);
        d->alt = (int)get(b, 1);
        /* repeat_first_field, chroma_420_type, progressive_frame, composite: display only */
        if (d->pstruct != 3) return fail(d, RG_MV_ERR_UNSUPPORTED, "field picture%s", "", 0);
        if (!d->fpfd) return fail(d, RG_MV_ERR_UNSUPPORTED, "frame_pred_frame_dct = 0%s", "", 0);
        if (d->cmv) return fail(d, RG_MV_ERR_UNSUPPORTED, "concealment motion vectors%s", "", 0);
        if (d->alt) return fail(d, RG_MV_ERR_UNSUPPORTED, "alternate scan%s", "", 0);
        return 0;
    }
    case 2: /* sequence display */
    case 7: /* picture display */
    case 4: /* copyright */
        return 0;
    default:
        return fail(d, RG_MV_ERR_UNSUPPORTED, "extension id %s%ld", "", id);
    }
}

/* ----------------------------------------------------- motion compensation */

/* Predict a w x h block from ref (stride rs, plane size pw x ph) at integer (ix, iy) with
 * half-pel flags; average into dst when avg. Out-of-picture samples repeat the edge. */
static uint32_t g_oob_count; /* statistics only (racy across threads, never read for decoding) */

static void mc(uint8_t *dst, int ds, const uint8_t *ref, int rs, int pw, int ph, int ix, int iy,
               int hx, int hy, int w, int h, int avg)
{
    uint8_t tmp[17 * 17];
    const uint8_t *s;
    int ss;
    if (ix < 0 || iy < 0 || ix + w + hx > pw || iy + h + hy > ph) {
        g_oob_count++;
        for (int y = 0; y < h + 1; y++) {
            int sy = iy + y;
            sy = sy < 0 ? 0 : sy >= ph ? ph - 1 : sy;
            for (int x = 0; x < w + 1; x++) {
                int sx = ix + x;
                sx = sx < 0 ? 0 : sx >= pw ? pw - 1 : sx;
                tmp[y * 17 + x] = ref[sy * rs + sx];
            }
        }
        s = tmp;
        ss = 17;
    } else {
        s = ref + iy * rs + ix;
        ss = rs;
    }
    for (int y = 0; y < h; y++) {
        const uint8_t *a = s + y * ss, *c = a + ss;
        uint8_t *o = dst + y * ds;
        for (int x = 0; x < w; x++) {
            int p;
            if (!hx && !hy) p = a[x];
            else if (hx && !hy) p = (a[x] + a[x + 1] + 1) >> 1;
            else if (!hx) p = (a[x] + c[x] + 1) >> 1;
            else p = (a[x] + a[x + 1] + c[x] + c[x + 1] + 2) >> 2;
            o[x] = (uint8_t)(avg ? (o[x] + p + 1) >> 1 : p);
        }
    }
}

static void predict(rg_mvdec *d, const mv_frame *ref, mv_frame *cur, int mbx, int mby, int mvx, int mvy,
                    int avg)
{
    int x = mbx * 16, y = mby * 16;
    mc(cur->y + y * d->ystride + x, d->ystride, ref->y, d->ystride, d->aw, d->ah, x + (mvx >> 1),
       y + (mvy >> 1), mvx & 1, mvy & 1, 16, 16, avg);
    int cmx = mvx / 2, cmy = mvy / 2; /* 7.6.3.7: truncation toward zero */
    int cx = mbx * 8, cy = mby * 8;
    int cw = d->aw / 2, ch = d->ah / 2;
    mc(cur->cb + cy * d->cstride + cx, d->cstride, ref->cb, d->cstride, cw, ch, cx + (cmx >> 1),
       cy + (cmy >> 1), cmx & 1, cmy & 1, 8, 8, avg);
    mc(cur->cr + cy * d->cstride + cx, d->cstride, ref->cr, d->cstride, cw, ch, cx + (cmx >> 1),
       cy + (cmy >> 1), cmx & 1, cmy & 1, 8, 8, avg);
}

/* ---------------------------------------------------------------- blocks */

/* Decode one block's coefficients into d->blk (dequantized, natural order, mismatch
 * control applied). Returns the row mask, or -1 on a bitstream error. */
static int decode_block(rg_mvdec *d, bits *b, int intra, int cc)
{
    int32_t *blk = d->blk;
    const uint8_t *qm = intra ? d->qm_intra : d->qm_inter;
    int qs = d->qscale;
    int sum, i;
    unsigned rows = 0;
    memset(blk, 0, 64 * sizeof(int32_t));
    const mv_dct_tab *t;
    if (intra) {
        const mv_vlc *e = cc ? &d->tab->dcc[show(b, MV_DCC_BITS)] : &d->tab->dcl[show(b, MV_DCL_BITS)];
        if (!e->len) return -1;
        skip(b, e->len);
        int size = e->val, diff = 0;
        if (size) {
            diff = (int)get(b, size);
            if (diff < (1 << (size - 1))) diff = diff - (1 << size) + 1;
        }
        d->dc_pred[cc] += diff;
        blk[0] = d->dc_pred[cc] * (8 >> d->dc_prec);
        if (blk[0] < -2048 || blk[0] > 2047) return -1;
        sum = blk[0];
        rows = 1;
        i = 0;
        t = d->ivf ? &d->tab->dct1 : &d->tab->dct0;
    } else {
        sum = 0;
        i = -1;
        t = &d->tab->dct0;
        if (show(b, 1)) { /* first coefficient: "1s" = run 0, level 1 */
            skip(b, 1);
            int s = (int)get(b, 1);
            int lv = s ? -1 : 1;
            int w = qm[0];
            int v = ((2 * lv + (lv > 0 ? 1 : -1)) * w * qs) / 32;
            blk[0] = v;
            sum = v;
            rows = 1;
            i = 0;
        }
    }
    for (;;) {
        uint32_t v = show(b, 16);
        const mv_dct_ent *e = (v & 0xFF00) ? &t->a[v >> 4] : &t->b[v & 0xFF];
        if (!e->len) return -1;
        int run, level;
        if (e->run == MV_RUN_EOB) {
            skip(b, e->len);
            break;
        }
        if (e->run == MV_RUN_ESC) {
            skip(b, 6);
            run = (int)get(b, 6);
            level = (int)get(b, 12);
            if (level >= 2048) level -= 4096;
            if (level == 0 || level == -2048) return -1;
        } else {
            skip(b, e->len);
            run = e->run;
            level = get(b, 1) ? -(int)e->level : (int)e->level;
        }
        i += run + 1;
        if (i > 63) return -1;
        int pos = mv_zigzag[i];
        int val;
        if (intra) val = (level * qm[pos] * qs * 2) / 32;
        else val = ((2 * level + (level > 0 ? 1 : -1)) * qm[pos] * qs) / 32;
        if (val > 2047) val = 2047;
        if (val < -2048) val = -2048;
        blk[pos] = val;
        sum += val;
        rows |= 1u << (pos >> 3);
        if (overrun(b)) return -1;
    }
    if (!(sum & 1)) { /* 7.4.4 mismatch control */
        blk[63] += (blk[63] & 1) ? -1 : 1;
        rows |= 0x80;
    }
    return (int)rows;
}

/* ------------------------------------------------------------ macroblocks */

static int motion_component(rg_mvdec *d, bits *b, int r, int t)
{
    int fcode = d->fcode[r][t];
    int rsize = fcode - 1;
    const mv_vlc *e = &d->tab->mc[show(b, MV_MC_BITS)];
    if (!e->len) return -1;
    skip(b, e->len);
    int code = e->val;
    if (code && get(b, 1)) code = -code;
    int delta;
    if (rsize == 0 || code == 0) {
        delta = code;
    } else {
        int res = (int)get(b, rsize);
        delta = ((code < 0 ? -code : code) - 1) * (1 << rsize) + res + 1;
        if (code < 0) delta = -delta;
    }
    int f = 1 << rsize;
    int high = 16 * f - 1, low = -16 * f, range = 32 * f;
    int p = d->pmv[r][t] + delta;
    if (p > high) p -= range;
    else if (p < low) p += range;
    d->pmv[r][t] = p;
    return 0;
}

static int decode_mb(rg_mvdec *d, bits *b, mv_frame *cur, int mbx, int mby)
{
    const mv_frame *fwd = NULL, *bwd = NULL;
    if (d->ptype == 2) fwd = &d->fb[d->ref_new];
    else if (d->ptype == 3) {
        bwd = &d->fb[d->ref_new];
        fwd = d->ref_old >= 0 ? &d->fb[d->ref_old] : bwd; /* broken-link leading B */
    }
    const mv_vlc *e = &d->tab->mbt[d->ptype - 1][show(b, MV_MBT_BITS)];
    if (!e->len) return -1;
    skip(b, e->len);
    int fl = e->val;
    if (fl & MB_QUANT) {
        int q = (int)get(b, 5);
        if (!q) return -1;
        d->qscale = d->qst ? mv_nonlinear_qscale[q] : 2 * q;
    }
    if (fl & MB_FWD) {
        if (motion_component(d, b, 0, 0) || motion_component(d, b, 0, 1)) return -1;
    }
    if (fl & MB_BWD) {
        if (motion_component(d, b, 1, 0) || motion_component(d, b, 1, 1)) return -1;
    }
    int cbp;
    if (fl & MB_PAT) {
        const mv_vlc *c = &d->tab->cbp[show(b, MV_CBP_BITS)];
        if (!c->len) return -1;
        skip(b, c->len);
        cbp = c->val;
    } else {
        cbp = (fl & MB_INTRA) ? 0x3F : 0;
    }
    int ys = d->ystride, cs = d->cstride;
    uint8_t *py = cur->y + mby * 16 * ys + mbx * 16;
    uint8_t *pcb = cur->cb + mby * 8 * cs + mbx * 8;
    uint8_t *pcr = cur->cr + mby * 8 * cs + mbx * 8;
    if (fl & MB_INTRA) {
        d->pmv[0][0] = d->pmv[0][1] = d->pmv[1][0] = d->pmv[1][1] = 0;
        for (int k = 0; k < 6; k++) {
            int cc = k < 4 ? 0 : k - 3;
            int rows = decode_block(d, b, 1, cc);
            if (rows < 0) return -1;
            uint8_t *dst = k < 4 ? py + (k >> 1) * 8 * ys + (k & 1) * 8 : (k == 4 ? pcb : pcr);
            mv_idct_put(d->blk, (unsigned)rows, dst, k < 4 ? ys : cs);
        }
        d->last_flags = fl;
        return 0;
    }
    /* non-intra: reset the DC predictors, form the prediction, add residuals */
    int dcr = 1 << (7 + d->dc_prec);
    d->dc_pred[0] = d->dc_pred[1] = d->dc_pred[2] = dcr;
    if (d->ptype == 2) {
        if (!(fl & MB_FWD)) d->pmv[0][0] = d->pmv[0][1] = 0; /* 7.6.3.4: P "No MC" */
        predict(d, fwd, cur, mbx, mby, d->pmv[0][0], d->pmv[0][1], 0);
    } else {
        int avg = 0;
        if (fl & MB_FWD) {
            predict(d, fwd, cur, mbx, mby, d->pmv[0][0], d->pmv[0][1], 0);
            avg = 1;
        }
        if (fl & MB_BWD) predict(d, bwd, cur, mbx, mby, d->pmv[1][0], d->pmv[1][1], avg);
    }
    d->mv[0][0] = d->pmv[0][0];
    d->mv[0][1] = d->pmv[0][1];
    d->mv[1][0] = d->pmv[1][0];
    d->mv[1][1] = d->pmv[1][1];
    d->last_flags = fl;
    for (int k = 0; k < 6; k++) {
        if (!(cbp & (32 >> k))) continue;
        int cc = k < 4 ? 0 : k - 3;
        int rows = decode_block(d, b, 0, cc);
        if (rows < 0) return -1;
        uint8_t *dst = k < 4 ? py + (k >> 1) * 8 * ys + (k & 1) * 8 : (k == 4 ? pcb : pcr);
        mv_idct_add(d->blk, (unsigned)rows, dst, k < 4 ? ys : cs);
    }
    return 0;
}

static void skipped_mb(rg_mvdec *d, mv_frame *cur, int mbx, int mby)
{
    int dcr = 1 << (7 + d->dc_prec);
    d->dc_pred[0] = d->dc_pred[1] = d->dc_pred[2] = dcr;
    if (d->ptype == 2) {
        d->pmv[0][0] = d->pmv[0][1] = 0;
        predict(d, &d->fb[d->ref_new], cur, mbx, mby, 0, 0, 0);
        return;
    }
    /* B: same prediction type and vectors as the previous macroblock */
    const mv_frame *bwd = &d->fb[d->ref_new];
    const mv_frame *fwd = d->ref_old >= 0 ? &d->fb[d->ref_old] : bwd;
    int avg = 0;
    if (d->last_flags & MB_FWD) {
        predict(d, fwd, cur, mbx, mby, d->mv[0][0], d->mv[0][1], 0);
        avg = 1;
    }
    if (d->last_flags & MB_BWD) predict(d, bwd, cur, mbx, mby, d->mv[1][0], d->mv[1][1], avg);
}

static int decode_slice(rg_mvdec *d, bits *b, mv_frame *cur, int row)
{
    if (row >= d->mbh) return -1;
    int q = (int)get(b, 5);
    if (!q) return -1;
    d->qscale = d->qst ? mv_nonlinear_qscale[q] : 2 * q;
    if (get(b, 1)) { /* intra_slice_flag ...: 8 bits, then extra_information_slice bytes */
        skip(b, 7);
        while (get(b, 1)) skip(b, 8);
    }
    int dcr = 1 << (7 + d->dc_prec);
    d->dc_pred[0] = d->dc_pred[1] = d->dc_pred[2] = dcr;
    d->pmv[0][0] = d->pmv[0][1] = d->pmv[1][0] = d->pmv[1][1] = 0;
    d->last_flags = 0;
    int addr = row * d->mbw - 1;
    int first = 1;
    int nmb = d->mbw * d->mbh;
    for (;;) {
        int inc = 0;
        for (;;) {
            const mv_vlc *e = &d->tab->mba[show(b, MV_MBA_BITS)];
            if (!e->len) return -1;
            skip(b, e->len);
            if (e->val == 34) {
                inc += 33;
                continue;
            }
            inc += e->val;
            break;
        }
        if (first) {
            addr += inc;
            first = 0;
        } else {
            if (inc > 1 && d->ptype == 1) return -1; /* no skipped MBs in I pictures */
            for (int k = 1; k < inc; k++) {
                int a = addr + k;
                if (a >= nmb) return -1;
                skipped_mb(d, cur, a % d->mbw, a / d->mbw);
            }
            addr += inc;
        }
        if (addr >= nmb) return -1;
        if (decode_mb(d, b, cur, addr % d->mbw, addr / d->mbw)) return -1;
        if (overrun(b)) return -1;
        /* the slice ends where the next 23 bits are zero (a start code prefix, possibly
         * after zero stuffing). A final macroblock can be shorter than 23 bits, so only the
         * zero test decides; the bytes past the unit end are the next start code or the
         * buffer's zero padding. */
        if (b->pos >= b->end || show(b, 23) == 0) break;
    }
    return 0;
}

/* --------------------------------------------------------------- pictures */

static int64_t take_pts(rg_mvdec *d, uint64_t abs_off, int *has)
{
    for (int i = 0; i < d->npts; i++) {
        pts_rec *r = &d->pts[i];
        if (abs_off >= r->start && abs_off < r->end) {
            if (r->used) break;
            r->used = 1;
            *has = 1;
            return r->pts;
        }
    }
    *has = 0;
    return 0;
}

static void emit(rg_mvdec *d, const mv_frame *fr, rg_mvframe *f, int pixels)
{
    f->y = pixels ? fr->y : NULL;
    f->cb = pixels ? fr->cb : NULL;
    f->cr = pixels ? fr->cr : NULL;
    f->ystride = d->ystride;
    f->cstride = d->cstride;
    f->width = d->info.width;
    f->height = d->info.height;
    f->index = d->out_index++;
    f->type = fr->type;
    if (fr->has_pts) f->pts = fr->pts;
    else f->pts = d->have_out_pts ? d->last_out_pts + d->info.pts_step : 0;
    d->last_out_pts = f->pts;
    d->have_out_pts = 1;
}

/* Decode the picture whose start code is at es offset p and whose unit ends at `end`.
 * Returns 1 if a frame was output into *f, 0 if not, <0 on error. */
static int decode_picture(rg_mvdec *d, size_t p, size_t end, rg_mvframe *f, int want_pixels)
{
    int has_pts;
    int64_t pts = take_pts(d, d->es_base + p, &has_pts);
    bits b;
    b.buf = d->es;
    b.pos = (uint32_t)(p + 4) * 8;
    b.end = (uint32_t)end * 8;
    skip(&b, 10); /* temporal_reference */
    int type = (int)get(&b, 3);
    skip(&b, 16);
    if (type < 1 || type > 3) return fail(d, RG_MV_ERR_UNSUPPORTED, "picture_coding_type %s%ld", "", type);
    if (type >= 2) skip(&b, 4);
    if (type == 3) skip(&b, 4);
    while (get(&b, 1)) skip(&b, 8);
    d->ptype = type;
    /* the picture coding extension and any other headers before the first slice */
    size_t q = p + 4;
    int have_pce = 0;
    int err;
    for (;;) {
        q = find_start(d, q, &err);
        if (err) return err;
        if (q == (size_t)-1 || q >= end) break;
        int code = d->es[q + 3];
        if (code >= 0x01 && code <= 0xAF) break;
        if (code == 0xB5) {
            bits e = {d->es, (uint32_t)(q + 4) * 8, (uint32_t)end * 8};
            int r = parse_ext(d, &e, 1);
            if (r) return r;
            if (d->es[q + 4] >> 4 == 8) have_pce = 1;
        }
        q += 4;
    }
    if (!have_pce) return fail(d, RG_MV_ERR_UNSUPPORTED, "MPEG-1 picture%s (no coding extension)", "", 0);
    if (type >= 2 && d->ref_new < 0)
        return fail(d, RG_MV_ERR_FORMAT, "predicted picture%s without a reference", "", 0);

    int skip_decode = (type == 3 && !want_pixels);
    int target;
    if (type == 3) {
        target = 3 - d->ref_old - d->ref_new; /* the buffer that is neither reference */
        if (d->ref_old < 0) target = d->ref_new == 0 ? 1 : 0;
    } else {
        /* new reference: overwrite the old forward reference (or a free buffer) */
        if (d->ref_old >= 0) target = d->ref_old;
        else if (d->ref_new >= 0) target = d->ref_new == 0 ? 1 : 0;
        else target = 0;
    }
    mv_frame *cur = &d->fb[target];
    cur->type = type;
    cur->pts = pts;
    cur->has_pts = has_pts;
    d->npics++;

    if (!skip_decode) {
        /* slices */
        while (q != (size_t)-1 && q < end) {
            int code = d->es[q + 3];
            if (code >= 0x01 && code <= 0xAF) {
                bits s = {d->es, (uint32_t)(q + 4) * 8, (uint32_t)end * 8};
                if (decode_slice(d, &s, cur, code - 1))
                    return fail(d, RG_MV_ERR_BITSTREAM, "bitstream error%s in picture %ld", "",
                                (long)d->npics - 1);
            }
            q = find_start(d, q + 4, &err);
            if (err) return err;
        }
    }

    if (type == 3) {
        emit(d, cur, f, want_pixels);
        return 1;
    }
    int out = 0;
    if (d->pending >= 0) {
        emit(d, &d->fb[d->pending], f, 1);
        out = 1;
    }
    d->ref_old = d->ref_new;
    d->ref_new = target;
    d->pending = target;
    return out;
}

/* ------------------------------------------------------------------ public */

static int dec_init(rg_mvdec *d, char *err, size_t errcap);

int rg_mvdec_next(rg_mvdec *d, rg_mvframe *f, int want_pixels)
{
    memset(f, 0, sizeof *f);
    int err;
    for (;;) {
        size_t p = find_start(d, d->es_pos, &err);
        if (err) return err;
        if (p == (size_t)-1) {
            d->es_pos = d->es_len;
            if (d->pending >= 0) {
                emit(d, &d->fb[d->pending], f, 1);
                d->pending = -1;
                return RG_MV_OK;
            }
            return RG_MV_EOF;
        }
        int code = d->es[p + 3];
        if (code == 0x00) {
            /* the picture unit runs to the next picture / sequence / GOP / end code.
             * es_pos = p first, so a compaction while demuxing keeps the picture. */
            d->es_pos = p;
            size_t q = p + 4;
            size_t end;
            for (;;) {
                q = find_start(d, q, &err);
                if (err) return err;
                if (q == (size_t)-1) {
                    end = d->es_len;
                    break;
                }
                int c = d->es[q + 3];
                if (c == 0x00 || c == 0xB3 || c == 0xB7 || c == 0xB8) {
                    end = q;
                    break;
                }
                q += 4;
            }
            p = d->es_pos;   /* rebased if the buffer was compacted */
            if (!d->have_seq || !d->have_seqext)
                return fail(d, RG_MV_ERR_FORMAT, "picture before the sequence header%s", "", 0);
            int r = decode_picture(d, p, end, f, want_pixels);
            d->es_pos = end;
            if (r < 0) return r;
            if (r == 1) return RG_MV_OK;
            continue;
        }
        size_t at = ensure(d, p, 512, &err);
        if (err) return err;
        p = at;
        bits b = {d->es, (uint32_t)(p + 4) * 8, (uint32_t)d->es_len * 8};
        int r = 0;
        if (code == 0xB3) r = parse_seq(d, &b);
        else if (code == 0xB5) r = parse_ext(d, &b, 0);
        else if (code == 0xB8) {
            skip(&b, 25);
            d->closed_gop = (int)get(&b, 1);
            d->broken_link = (int)get(&b, 1);
            if (d->broken_link || d->closed_gop) {
                /* leading B pictures may not use the old forward reference */
            }
        } else if (code == 0xB7) {
            /* sequence end: flush */
        } else if (code >= 0x01 && code <= 0xAF) {
            r = fail(d, RG_MV_ERR_FORMAT, "slice outside a picture%s", "", 0);
        }
        if (r) return r;
        d->es_pos = p + 4;
    }
}

static void reset_state(rg_mvdec *d)
{
    d->ref_old = d->ref_new = d->pending = -1;
    d->out_index = 0;
    d->have_out_pts = 0;
    d->last_out_pts = 0;
    d->npics = 0;
    d->es_pos = d->es_len = 0;
    d->es_base = 0;
    d->npts = 0;
    d->in_pos = d->in_len = 0;
    d->src_eof = 0;
    d->ps_end = 0;
    d->mempos = 0;
}

static int dec_init(rg_mvdec *d, char *err, size_t errcap)
{
    d->tab = (mv_tables *)malloc(sizeof(mv_tables));
    if (!d->tab || mv_tables_build(d->tab)) {
        if (err) snprintf(err, errcap, "VLC table build failed");
        return RG_MV_ERR_NOMEM;
    }
    reset_state(d);
    /* read up to the first picture header so that info is known */
    int e;
    for (;;) {
        size_t p = find_start(d, d->es_pos, &e);
        if (e || p == (size_t)-1) {
            if (err) snprintf(err, errcap, "%s", e ? d->err : "no picture in stream");
            return e ? e : RG_MV_ERR_FORMAT;
        }
        int code = d->es[p + 3];
        if (code == 0x00) break;
        p = ensure(d, p, 512, &e);
        if (e) {
            if (err) snprintf(err, errcap, "%s", d->err);
            return e;
        }
        bits b = {d->es, (uint32_t)(p + 4) * 8, (uint32_t)d->es_len * 8};
        int r = 0;
        if (code == 0xB3) r = parse_seq(d, &b);
        else if (code == 0xB5) r = parse_ext(d, &b, 0);
        if (r) {
            if (err) snprintf(err, errcap, "%s", d->err);
            return r;
        }
        d->es_pos = p + 4;
    }
    if (!d->have_seq || !d->have_seqext) {
        if (err) snprintf(err, errcap, "no MPEG-2 sequence header/extension before the first picture");
        return RG_MV_ERR_UNSUPPORTED;
    }
    return 0;
}

int rg_mvdec_rewind(rg_mvdec *d)
{
    if (d->fp && fseek(d->fp, 0, SEEK_SET) != 0) return fail(d, RG_MV_ERR_IO, "seek failed%s", "", 0);
    reset_state(d);
    /* sequence state stays (one sequence header per file); headers are re-read anyway */
    return 0;
}

int rg_mvdec_open(rg_mvdec **out, const char *path, char *err, size_t errcap)
{
    *out = NULL;
    rg_mvdec *d = (rg_mvdec *)calloc(1, sizeof *d);
    if (!d) return RG_MV_ERR_NOMEM;
    d->fp = fopen(path, "rb");
    snprintf(d->path, sizeof d->path, "%s", path);
    if (!d->fp) {
        if (err) snprintf(err, errcap, "cannot open %s", path);
        free(d);
        return RG_MV_ERR_IO;
    }
    int r = dec_init(d, err, errcap);
    if (r) {
        rg_mvdec_close(d);
        return r;
    }
    *out = d;
    return 0;
}

int rg_mvdec_open_memory(rg_mvdec **out, const void *data, size_t size, char *err, size_t errcap)
{
    *out = NULL;
    rg_mvdec *d = (rg_mvdec *)calloc(1, sizeof *d);
    if (!d) return RG_MV_ERR_NOMEM;
    d->mem = (const uint8_t *)data;
    d->memsize = size;
    int r = dec_init(d, err, errcap);
    if (r) {
        rg_mvdec_close(d);
        return r;
    }
    *out = d;
    return 0;
}

void rg_mvdec_close(rg_mvdec *d)
{
    if (!d) return;
    if (d->fp) fclose(d->fp);
    free(d->in);
    free(d->es);
    free(d->fb[0].y);
    free(d->fb[1].y);
    free(d->fb[2].y);
    free(d->tab);
    free(d);
}

const rg_mvdec_info *rg_mvdec_get_info(const rg_mvdec *d) { return &d->info; }
const char *rg_mvdec_error(const rg_mvdec *d) { return d->err; }
uint32_t rg_mvdec_pictures_decoded(const rg_mvdec *d) { return d->npics; }
uint32_t rg_mvdec_oob_predictions(void) { return g_oob_count; }

/* ---- save states (docs/TEST-FIXTURES.md): the FILE is host state.  The
 * decoder struct comes back raw with the saver's (dead) FILE pointer; the
 * movie hook reopens the file at the saved position. */
int64_t rg_mvdec_ss_tell(const rg_mvdec *d)
{
    if (!d || !d->fp) return -1;
#ifdef _WIN32
    return _ftelli64(d->fp);
#else
    return (int64_t)ftello(d->fp);
#endif
}

int rg_mvdec_ss_reopen(rg_mvdec *d, int64_t pos)
{
    if (!d || !d->path[0]) return -1;
    d->fp = fopen(d->path, "rb");
    if (!d->fp) return -1;
#ifdef _WIN32
    return _fseeki64(d->fp, pos, SEEK_SET) == 0 ? 0 : -1;
#else
    return fseeko(d->fp, (off_t)pos, SEEK_SET) == 0 ? 0 : -1;
#endif
}
