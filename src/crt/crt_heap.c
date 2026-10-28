/* SPDX-License-Identifier: CC0-1.0 */
/* malloc/free/memalign for the game (Malloc_130dd8, Free_130e30,
 * Memalign_130ba8): the retail allocator, rewritten from the retail code.
 *
 * Retail links newlib's malloc (Doug Lea's dlmalloc 2.6.x as newlib ships it:
 * MallocR_1310d0, FreeR_12f9f8, MallocExtendTop_130e78, MallocTrim_12fcf0,
 * MemalignR_130c10) over sbrk, which hands out the EE RAM between the end of
 * .bss (0x00528200) and the main thread's stack (crt0's SetupHeap).  The game
 * sizes its own big arenas from that heap (SysCalcFreeHeapMaybe probes it with
 * a malloc of "everything", then a 25 MB malloc/free; GameDataHeapInit,
 * MenuResStackInit and SysBootInit memalign their stacks out of it), and the
 * last of those (25.9 MB) fits only if every earlier step behaves exactly as
 * retail's, including free() trimming the top back to the system with sbrk(-n)
 * (docs/BRINGUP.md "Heap").
 *
 * This file follows the retail functions decision for decision, so the port's
 * heap has the retail layout: the same chunk addresses (host = base + PS2
 * address), the same 8-byte headers (prev_size, size|PREV_INUSE), the same
 * bins, binblocks, last-remainder and top handling, page rounding and trim
 * threshold, the same sbrk calls.  Constants read from the retail code:
 * SIZE_SZ 4, MALLOC_ALIGNMENT 16, MINSIZE 16, pagesize 0x1000, 128 bins
 * (small bins below 0x200, BINBLOCKWIDTH 4), trim_threshold 0x20000,
 * top_pad 0.  On i686 a pointer is 32 bits, so a chunk's fd/bk links have the
 * retail size.
 *
 * State: retail keeps it in .data (av_ at 0x00449868, trim_threshold
 * 0x00449C70, top_pad 0x00449C78, sbrk_base 0x00449C80, max_sbrked_mem
 * 0x00449C88, max_total_mem 0x00449C90, current_mallinfo 0x00449C98 whose
 * first word is sbrked_mem).  The game link binds those data objects with
 * rg_crt_heap_bind() (src/game/rg_game_main.c), so free chunks link to the
 * bins at their retail data addresses; otherwise (tests) a private copy is
 * used.  "long" in newlib is 64 bits on the EE: remainders are computed as
 * int64_t here, and the 64-bit statistics are written as two words.
 * Single host thread (the EE scheduler is cooperative): no locking. */
#include "crt.h"
/* x64 (docs/X64-PLAN.md): size parameters from the game are 32-bit values */
#if defined(_WIN64)
#define RG_GSIZE(x) ((x) = (size_t)(uint32_t)(x))
#else
#define RG_GSIZE(x) ((void)0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void *sbrk(intptr_t incr);

#define SIZE_SZ 4u
#define MALLOC_ALIGNMENT 16u
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1u)
#define MINSIZE 16u
#define PAGESZ 0x1000u
#define NAV 128
#define MAX_SMALLBIN_SIZE 512u
#define SMALLBIN_WIDTH 8u
#define BINBLOCKWIDTH 4
#define PREV_INUSE 1u
#define SIZE_BITS 3u

/* x64 (docs/X64-PLAN.md): the chunks and bins live in game memory with the retail
 * layout, so their links are 4-byte pointers there (empty on i686) */
#ifndef CRT_P32 /* crt.h */
#if defined(__x86_64__)
#define CRT_P32 __ptr32 __uptr
#else
#define CRT_P32
#endif
#endif
typedef struct mchunk {
    uint32_t prev_size;
    uint32_t size;
    struct mchunk * CRT_P32 fd;
    struct mchunk * CRT_P32 bk;
} mchunk;

typedef char rg_heap_chunk_layout[(sizeof(mchunk) == 16) ? 1 : -1]; /* i686: retail layout */

/* ---- state (retail .data, or the private copy) ---- */
static uint32_t own_av[NAV * 2 + 2];
static uint32_t own_params[20]; /* 0x00449C70..0x00449CC0 */
static uint32_t *av_;           /* bins: bin_at(i) = (mchunk *)&av_[2 * i] */
static uint32_t *params;        /* [0..1] trim_threshold, [2..3] top_pad, [4] sbrk_base,
                                   [6..7] max_sbrked_mem, [8..9] max_total_mem,
                                   [10..19] current_mallinfo ([10] arena = sbrked_mem) */

#define bin_at(i) ((mchunk *)(void *)&av_[2 * (i)])
#define next_bin(b) ((mchunk *)((char *)(b) + 8))
#define prev_bin(b) ((mchunk *)((char *)(b) - 8))
#define top (bin_at(0)->fd)
#define initial_top (bin_at(0))
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define trim_threshold (params[0])
#define top_pad (params[2])
#define sbrk_base (*(char **)(void *)&params[4])
#define sbrked_mem (params[10])

static void heap_state(void)
{
    int i;
    if (av_)
        return;
    av_ = own_av;
    params = own_params;
    memset(own_av, 0, sizeof own_av);
    for (i = 0; i < NAV; i++)
        bin_at(i)->fd = bin_at(i)->bk = bin_at(i);
    memset(own_params, 0, sizeof own_params);
    trim_threshold = 0x20000;
    sbrk_base = (char *)-1;
}

void rg_crt_heap_bind(void *av, void *prm)
{
    av_ = (uint32_t *)av;
    params = (uint32_t *)prm;
}

static void set_u64(uint32_t *w, uint64_t v)
{
    w[0] = (uint32_t)v;
    w[1] = (uint32_t)(v >> 32);
}
static uint64_t get_u64(const uint32_t *w) { return w[0] | ((uint64_t)w[1] << 32); }

#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define mem2chunk(m) ((mchunk *)((char *)(m) - 2 * SIZE_SZ))
#define chunk_at_offset(p, s) ((mchunk *)((char *)(p) + (int32_t)(s)))
#define chunksize(p) ((p)->size & ~SIZE_BITS)
#define next_chunk(p) ((mchunk *)((char *)(p) + ((p)->size & ~PREV_INUSE)))
#define inuse_bit_at_offset(p, s) (chunk_at_offset(p, s)->size & PREV_INUSE)
#define set_inuse_bit_at_offset(p, s) (chunk_at_offset(p, s)->size |= PREV_INUSE)
#define set_head(p, s) ((p)->size = (uint32_t)(s))
#define set_head_size(p, s) ((p)->size = ((p)->size & PREV_INUSE) | (uint32_t)(s))
#define set_foot(p, s) (chunk_at_offset(p, s)->prev_size = (uint32_t)(s))

static uint32_t request2size(size_t req)
{
    uint32_t r = (uint32_t)req + SIZE_SZ + MALLOC_ALIGN_MASK; /* 32-bit, as retail */
    return r < MINSIZE + MALLOC_ALIGN_MASK ? MINSIZE : (r & ~MALLOC_ALIGN_MASK);
}

static int bin_index(uint32_t sz)
{
    uint32_t q = sz >> 9;
    if (q == 0) return (int)(sz >> 3);
    if (q <= 4) return 56 + (int)(sz >> 6);
    if (q <= 20) return 91 + (int)q;
    if (q <= 84) return 110 + (int)(sz >> 12);
    if (q <= 340) return 119 + (int)(sz >> 15);
    if (q <= 1364) return 124 + (int)(sz >> 18);
    return 126;
}

#define mark_binblock(ii) (binblocks |= (uint32_t)(1u << ((ii) / BINBLOCKWIDTH)))

static void unlink_chunk(mchunk *p)
{
    mchunk *bk = p->bk, *fd = p->fd;
    fd->bk = bk;
    bk->fd = fd;
}

static void link_last_remainder(mchunk *p)
{
    last_remainder->fd = last_remainder->bk = p;
    p->fd = p->bk = last_remainder;
}

#define clear_last_remainder (last_remainder->fd = last_remainder->bk = last_remainder)

static void frontlink(mchunk *p, uint32_t s)
{
    mchunk *bk, *fd;
    int idx;
    if (s < MAX_SMALLBIN_SIZE) {
        idx = (int)(s >> 3);
        mark_binblock(idx);
        bk = bin_at(idx);
        fd = bk->fd;
    } else {
        idx = bin_index(s);
        bk = bin_at(idx);
        fd = bk->fd;
        if (fd == bk) {
            mark_binblock(idx);
        } else {
            while (fd != bk && s < chunksize(fd))
                fd = fd->fd;
            bk = fd->bk;
        }
    }
    p->bk = bk;
    p->fd = fd;
    fd->bk = bk->fd = p;
}

static void free_r(void *mem);

/* MallocExtendTop_130e78 */
static void malloc_extend_top(uint32_t nb)
{
    char *brk, *new_brk;
    uint32_t front_misalign, correction;
    mchunk *old_top = top;
    uint32_t old_top_size = chunksize(old_top);
    char *old_end = (char *)chunk_at_offset(old_top, old_top_size);
    uint32_t sbrk_size = nb + top_pad + MINSIZE;
    uint64_t v;

    if (sbrk_base != (char *)-1)
        sbrk_size = (sbrk_size + (PAGESZ - 1)) & ~(PAGESZ - 1);
    brk = (char *)sbrk((intptr_t)(int32_t)sbrk_size);
    if (brk == (char *)-1 || (brk < old_end && old_top != initial_top))
        return;
    sbrked_mem += sbrk_size;
    if (brk == old_end) {
        set_head(top, (sbrk_size + old_top_size) | PREV_INUSE);
    } else {
        if (sbrk_base == (char *)-1)
            sbrk_base = brk;
        else
            sbrked_mem += (uint32_t)(brk - old_end);
        front_misalign = (uint32_t)(uintptr_t)chunk2mem(brk) & MALLOC_ALIGN_MASK;
        if (front_misalign > 0) {
            correction = MALLOC_ALIGNMENT - front_misalign;
            brk += correction;
        } else {
            correction = 0;
        }
        correction += PAGESZ - ((uint32_t)(uintptr_t)(brk + sbrk_size) & (PAGESZ - 1));
        new_brk = (char *)sbrk((intptr_t)(int32_t)correction);
        if (new_brk == (char *)-1)
            return;
        sbrked_mem += correction;
        top = (mchunk *)brk;
        set_head(top, ((uint32_t)(new_brk - brk) + correction) | PREV_INUSE);
        if (old_top != initial_top) {
            if (old_top_size < MINSIZE) {
                set_head(top, PREV_INUSE);
                return;
            }
            old_top_size = (old_top_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
            set_head_size(old_top, old_top_size);
            chunk_at_offset(old_top, old_top_size)->size = SIZE_SZ | PREV_INUSE;
            chunk_at_offset(old_top, old_top_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;
            if (old_top_size >= MINSIZE)
                free_r(chunk2mem(old_top));
        }
    }
    v = sbrked_mem;
    if (v > get_u64(&params[6]))
        set_u64(&params[6], v);
    if (v > get_u64(&params[8]))
        set_u64(&params[8], v);
}

/* MallocR_1310d0 */
static void *malloc_r(size_t bytes)
{
    mchunk *victim, *bin, *q, *remainder;
    uint32_t victim_size, nb = request2size(bytes);
    int idx, startidx;
    int64_t remainder_size;
    uint64_t block;

    if (nb < MAX_SMALLBIN_SIZE - SMALLBIN_WIDTH) {
        idx = (int)(nb >> 3);
        q = bin_at(idx);
        victim = q->bk;
        if (victim != q) {
            victim_size = chunksize(victim);
            unlink_chunk(victim);
            set_inuse_bit_at_offset(victim, victim_size);
            return chunk2mem(victim);
        }
        idx += 2;
    } else {
        idx = bin_index(nb);
        bin = bin_at(idx);
        for (victim = bin->bk; victim != bin; victim = victim->bk) {
            victim_size = chunksize(victim);
            remainder_size = (int64_t)victim_size - (int64_t)nb;
            if (remainder_size >= (int64_t)MINSIZE) {
                --idx;
                break;
            } else if (remainder_size >= 0) {
                unlink_chunk(victim);
                set_inuse_bit_at_offset(victim, victim_size);
                return chunk2mem(victim);
            }
        }
        ++idx;
    }

    if ((victim = last_remainder->fd) != last_remainder) {
        victim_size = chunksize(victim);
        remainder_size = (int64_t)victim_size - (int64_t)nb;
        if (remainder_size >= (int64_t)MINSIZE) {
            remainder = chunk_at_offset(victim, nb);
            set_head(victim, nb | PREV_INUSE);
            link_last_remainder(remainder);
            set_head(remainder, (uint32_t)remainder_size | PREV_INUSE);
            set_foot(remainder, (uint32_t)remainder_size);
            return chunk2mem(victim);
        }
        clear_last_remainder;
        if (remainder_size >= 0) {
            set_inuse_bit_at_offset(victim, victim_size);
            return chunk2mem(victim);
        }
        frontlink(victim, victim_size);
    }

    block = (uint64_t)1 << (idx / BINBLOCKWIDTH);
    if (block <= binblocks) {
        if ((block & binblocks) == 0) {
            idx = (idx & ~(BINBLOCKWIDTH - 1)) + BINBLOCKWIDTH;
            block <<= 1;
            while ((block & binblocks) == 0) {
                idx += BINBLOCKWIDTH;
                block <<= 1;
            }
        }
        for (;;) {
            startidx = idx;
            q = bin = bin_at(idx);
            do {
                for (victim = bin->bk; victim != bin; victim = victim->bk) {
                    victim_size = chunksize(victim);
                    remainder_size = (int64_t)victim_size - (int64_t)nb;
                    if (remainder_size >= (int64_t)MINSIZE) {
                        remainder = chunk_at_offset(victim, nb);
                        set_head(victim, nb | PREV_INUSE);
                        unlink_chunk(victim);
                        link_last_remainder(remainder);
                        set_head(remainder, (uint32_t)remainder_size | PREV_INUSE);
                        set_foot(remainder, (uint32_t)remainder_size);
                        return chunk2mem(victim);
                    } else if (remainder_size >= 0) {
                        set_inuse_bit_at_offset(victim, victim_size);
                        unlink_chunk(victim);
                        return chunk2mem(victim);
                    }
                }
                bin = next_bin(bin);
            } while ((++idx & (BINBLOCKWIDTH - 1)) != 0);

            do {
                if ((startidx & (BINBLOCKWIDTH - 1)) == 0) {
                    binblocks &= ~(uint32_t)block;
                    break;
                }
                --startidx;
                q = prev_bin(q);
            } while (q->fd == q);

            if ((block <<= 1) <= binblocks && block != 0) {
                while ((block & binblocks) == 0) {
                    idx += BINBLOCKWIDTH;
                    block <<= 1;
                }
            } else {
                break;
            }
        }
    }

    if ((remainder_size = (int64_t)chunksize(top) - (int64_t)nb) < (int64_t)MINSIZE) {
        malloc_extend_top(nb);
        if ((remainder_size = (int64_t)chunksize(top) - (int64_t)nb) < (int64_t)MINSIZE)
            return NULL;
    }
    victim = top;
    set_head(victim, nb | PREV_INUSE);
    top = chunk_at_offset(victim, nb);
    set_head(top, (uint32_t)remainder_size | PREV_INUSE);
    return chunk2mem(victim);
}

/* MallocTrim_12fcf0 */
static int malloc_trim(uint32_t pad)
{
    int64_t top_size = chunksize(top);
    int64_t extra = (((top_size - (int64_t)pad + (int64_t)(PAGESZ - MINSIZE - 1)) >> 12) - 1) << 12;
    char *current_brk, *new_brk;
    if (extra < (int64_t)PAGESZ)
        return 0;
    current_brk = (char *)sbrk(0);
    if (current_brk != (char *)top + (int32_t)top_size)
        return 0;
    new_brk = (char *)sbrk(-(intptr_t)(int32_t)extra);
    if (new_brk == (char *)-1) {
        current_brk = (char *)sbrk(0);
        top_size = current_brk - (char *)top;
        if (top_size >= (int64_t)MINSIZE) {
            sbrked_mem = (uint32_t)(current_brk - sbrk_base);
            set_head(top, (uint32_t)top_size | PREV_INUSE);
        }
        return 0;
    }
    set_head(top, (uint32_t)(top_size - extra) | PREV_INUSE);
    sbrked_mem -= (uint32_t)extra;
    return 1;
}

/* FreeR_12f9f8 */
static void free_r(void *mem)
{
    mchunk *p, *next;
    uint32_t hd, sz, nextsz, prevsz;
    int islr;

    if (!mem)
        return;
    p = mem2chunk(mem);
    hd = p->size;
    sz = hd & ~PREV_INUSE;
    next = chunk_at_offset(p, sz);
    nextsz = chunksize(next);

    if (next == top) {
        sz += nextsz;
        if (!(hd & PREV_INUSE)) {
            prevsz = p->prev_size;
            p = chunk_at_offset(p, -(int32_t)prevsz);
            sz += prevsz;
            unlink_chunk(p);
        }
        set_head(p, sz | PREV_INUSE);
        top = p;
        if (sz >= trim_threshold)
            malloc_trim(top_pad);
        return;
    }

    set_head(next, nextsz);
    islr = 0;
    if (!(hd & PREV_INUSE)) {
        prevsz = p->prev_size;
        p = chunk_at_offset(p, -(int32_t)prevsz);
        sz += prevsz;
        if (p->fd == last_remainder)
            islr = 1;
        else
            unlink_chunk(p);
    }
    if (!inuse_bit_at_offset(next, nextsz)) {
        sz += nextsz;
        if (!islr && next->fd == last_remainder) {
            islr = 1;
            link_last_remainder(p);
        } else {
            unlink_chunk(next);
        }
    }
    set_head(p, sz | PREV_INUSE);
    set_foot(p, sz);
    if (!islr)
        frontlink(p, sz);
}

/* MemalignR_130c10 */
static void *memalign_r(size_t alignment, size_t bytes)
{
    uint32_t nb, newsize, leadsize;
    int64_t remainder_size;
    char *m, *brk;
    mchunk *p, *newp, *remainder;

    if (alignment <= MALLOC_ALIGNMENT)
        return malloc_r(bytes);
    if (alignment < MINSIZE)
        alignment = MINSIZE;
    nb = request2size(bytes);
    m = (char *)malloc_r(nb + alignment + MINSIZE);
    if (!m)
        return NULL;
    p = mem2chunk(m);
    if (((uint32_t)(uintptr_t)m % alignment) != 0) {
        brk = (char *)mem2chunk(((uintptr_t)(m + alignment - 1)) & (uintptr_t)(-(intptr_t)alignment));
        if ((int32_t)(brk - (char *)p) < (int32_t)MINSIZE)
            brk += alignment;
        newp = (mchunk *)brk;
        leadsize = (uint32_t)(brk - (char *)p);
        newsize = chunksize(p) - leadsize;
        set_head(newp, newsize | PREV_INUSE);
        set_inuse_bit_at_offset(newp, newsize);
        set_head_size(p, leadsize);
        free_r(chunk2mem(p));
        p = newp;
    }
    remainder_size = (int64_t)chunksize(p) - (int64_t)nb;
    if (remainder_size >= (int64_t)MINSIZE) {
        remainder = chunk_at_offset(p, nb);
        set_head(remainder, (uint32_t)remainder_size | PREV_INUSE);
        set_head_size(p, nb);
        free_r(chunk2mem(remainder));
    }
    return chunk2mem(p);
}

/* ---- RG_HEAP_LOG=1: one stderr line per game-level call, with the PS2
 * address (host - RAM base) and the caller's image RVA (resolve with
 * rg-game.map; build/boot/rva.py).  Diagnostic only. ---- */
#ifdef _WIN32
extern char __ImageBase;
#define RG_RVA(ra) ((unsigned)((uintptr_t)(ra) - (uintptr_t)&__ImageBase))
#else
#define RG_RVA(ra) ((unsigned)(uintptr_t)(ra))
#endif
static int log_state = -1;
static uintptr_t log_base; /* host address of PS2 0 (sbrk_base - 0x00528200) */
static int heap_log_on(void)
{
    if (log_state < 0) {
        const char *e = getenv("RG_HEAP_LOG");
        log_state = (e && *e && *e != '0') ? 1 : 0;
    }
    return log_state;
}
static unsigned ps2a(const void *p)
{
    if (!p)
        return 0;
    if (!log_base && sbrk_base != (char *)-1)
        log_base = (uintptr_t)sbrk_base - 0x00528200u;
    return (unsigned)((uintptr_t)p - log_base);
}

void *Malloc_130dd8(size_t n)
{ RG_GSIZE(n);
    void *r;
    heap_state();
    r = malloc_r(n);
    if (heap_log_on())
        fprintf(stderr, "HEAP malloc %#x -> %08x ra %08x\n", (unsigned)n, ps2a(r),
                RG_RVA(__builtin_return_address(0)));
    return r;
}

void Free_130e30(void *p)
{
    heap_state();
    if (heap_log_on())
        fprintf(stderr, "HEAP free %08x ra %08x\n", ps2a(p), RG_RVA(__builtin_return_address(0)));
    free_r(p);
}

void *Memalign_130ba8(size_t align, size_t n)
{ RG_GSIZE(align); RG_GSIZE(n);
    void *r;
    heap_state();
    r = memalign_r(align, n);
    if (heap_log_on())
        fprintf(stderr, "HEAP memalign %#x %#x -> %08x ra %08x\n", (unsigned)align, (unsigned)n,
                ps2a(r), RG_RVA(__builtin_return_address(0)));
    return r;
}

/* free bytes: every binned chunk + the last remainder + top */
size_t rg_crt_heap_free_bytes(void)
{
    size_t n = 0;
    int i;
    mchunk *b, *c;
    heap_state();
    for (i = 1; i < NAV; i++) {
        b = bin_at(i);
        for (c = b->fd; c != b; c = c->fd)
            n += chunksize(c);
    }
    if (top != initial_top)
        n += chunksize(top);
    return n;
}

/* consistency walk from the first chunk to top: 0 = ok, else the number of
 * the first failed rule */
int rg_crt_heap_check(void)
{
    mchunk *c, *b, *f;
    size_t nfree = 0, nlist = 0;
    int i, prev_free = 0;
    heap_state();
    if (sbrk_base == (char *)-1)
        return 0;
    c = (mchunk *)(((uintptr_t)sbrk_base + 2 * SIZE_SZ + MALLOC_ALIGN_MASK) & ~(uintptr_t)MALLOC_ALIGN_MASK);
    c = mem2chunk(c);
    while (c != top) {
        uint32_t sz = chunksize(c);
        if ((char *)c > (char *)top)
            return 4;
        if (sz < MINSIZE || (sz & MALLOC_ALIGN_MASK))
            return 1;
        if ((!(c->size & PREV_INUSE)) != prev_free)
            return 2; /* PREV_INUSE bit disagrees with the previous chunk */
        if (!inuse_bit_at_offset(c, sz)) {
            if (prev_free)
                return 3; /* two adjacent free chunks: missed coalesce */
            if (chunk_at_offset(c, sz)->prev_size != sz)
                return 7; /* foot */
            nfree++;
            prev_free = 1;
        } else {
            prev_free = 0;
        }
        c = chunk_at_offset(c, sz);
    }
    if (!(top->size & PREV_INUSE))
        return 8; /* top always follows an in-use chunk */
    for (i = 1; i < NAV; i++) {
        b = bin_at(i);
        for (f = b->fd; f != b; f = f->fd) {
            nlist++;
            if (f->fd->bk != f)
                return 5;
            if (inuse_bit_at_offset(f, chunksize(f)))
                return 5;
        }
    }
    return nfree == nlist ? 0 : 6;
}
