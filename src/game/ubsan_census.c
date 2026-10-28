/* SPDX-License-Identifier: CC0-1.0
 *
 * UB census runtime for RG_UBSAN builds (cmake/game.cmake, docs/UB-AUDIT.md).
 *
 * LLVM ships no i386 UBSan runtime for Windows, so this file provides the
 * __ubsan_handle_* entry points clang emits for -fsanitize=undefined
 * -fsanitize-recover=all.  Every handler records its check site (the static
 * data block clang passes is unique per site) once:
 *
 *   NEW <kind> <sub> <file> <line> <col> <detail> <caller>
 *
 * is appended (and flushed) to $RG_UBSAN_LOG (default ubsan_census.tsv in the
 * working directory) the first time a site fires, and at exit one
 *
 *   COUNT <kind> <sub> <file> <line> <col> <hits>
 *
 * row per site.  Execution then continues as without the check (recoverable
 * checks), except builtin_unreachable / missing_return, which log and abort
 * (code after them is undefined).  Never part of a shipping build: compiled
 * without sanitizers, no malloc (the state heap would route it), one lock.
 */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <process.h>
#define ub_getpid() ((long)_getpid())
#else
#include <unistd.h>
#define ub_getpid() ((long)getpid())
#endif

typedef struct {
    const char *file;
    uint32_t line;
    uint32_t col;
} ub_loc;

typedef struct {
    uint16_t kind;
    uint16_t info;
    char name[1];
} ub_type;

typedef uintptr_t ub_val;

#define UB_SITES 16384u

typedef struct {
    const void *data;          /* clang's per-site static block */
    const char *kind;
    const char *sub;
    const char *file;
    uint32_t line, col;
    uint32_t hits;
} ub_site;

static ub_site g_sites[UB_SITES];
static uint32_t g_nsites;
static uint32_t g_dropped;
static FILE *g_log;
static int g_init;
/* The process that opened g_log.  rg-game save states capture the game statics, this file's
 * included: after --load-state g_log / g_init are the SAVING process's (a FILE * that does
 * not exist here; the first NEW row crashed in _lock_file, soak 2026-10-25).  A pid mismatch
 * means "restored from a state": reopen (append) and register the exit dump again.  The site
 * table is kept, so sites the saver already logged are not repeated. */
static long g_log_pid;
static volatile long g_lock;

static void ub_lock(void)
{
    while (__sync_lock_test_and_set(&g_lock, 1)) {
    }
}
static void ub_unlock(void) { __sync_lock_release(&g_lock); }

static void ub_dump(void)
{
    uint32_t i;
    ub_lock();
    if (g_log && g_log_pid == ub_getpid()) {
        for (i = 0; i < UB_SITES; i++) {
            const ub_site *s = &g_sites[i];
            if (s->data)
                fprintf(g_log, "COUNT\t%s\t%s\t%s\t%u\t%u\t%u\n", s->kind, s->sub,
                        s->file ? s->file : "?", s->line, s->col, s->hits);
        }
        fprintf(g_log, "END\tsites=%u\tdropped=%u\n", g_nsites, g_dropped);
        fflush(g_log);
    }
    ub_unlock();
}

/* Exported so a host can flush before a hard exit (rg-game exits through exit()). */
void rg_ubsan_dump(void) { ub_dump(); }

static void ub_open(void)
{
    const char *p;
    g_init = 1;
    g_log_pid = ub_getpid();
    p = getenv("RG_UBSAN_LOG");
    g_log = fopen(p && *p ? p : "ubsan_census.tsv", "a");
    if (g_log)
        fprintf(g_log, "BEGIN\n");
    atexit(ub_dump);
}

static void ub_hit(const void *data, const ub_loc *loc, const char *kind, const char *sub,
                   const char *detail, void *caller)
{
    uint32_t h, i;
    ub_lock();
    if (!g_init || g_log_pid != ub_getpid())
        ub_open();
    h = (uint32_t)((uintptr_t)data >> 2) * 2654435761u;
    for (i = 0; i < UB_SITES; i++) {
        ub_site *s = &g_sites[(h + i) & (UB_SITES - 1)];
        if (s->data == data && s->sub == sub) {
            s->hits++;
            ub_unlock();
            return;
        }
        if (!s->data) {
            if (g_nsites >= UB_SITES - UB_SITES / 8) {
                g_dropped++;
                break;
            }
            g_nsites++;
            s->data = data;
            s->kind = kind;
            s->sub = sub;
            s->file = loc ? loc->file : 0;
            s->line = loc ? loc->line : 0;
            s->col = loc ? loc->col : 0;
            s->hits = 1;
            if (g_log) {
                fprintf(g_log, "NEW\t%s\t%s\t%s\t%u\t%u\t%s\t%p\n", kind, sub,
                        s->file ? s->file : "?", s->line, s->col, detail ? detail : "",
                        caller);
                fflush(g_log);
            }
            break;
        }
    }
    ub_unlock();
}

#define CALLER __builtin_return_address(0)
#define LOC(d) ((const ub_loc *)(d))
#define TYNAME(t) ((t) ? (t)->name : "?")

/* ---- handlers.  Each has a recoverable and an _abort spelling; both log and
 * return (the _abort ones are only emitted for checks not in -fsanitize-recover). */
#define UB_PAIR(name, params, body)                                                    \
    void __ubsan_handle_##name params body                                             \
    void __ubsan_handle_##name##_abort params body

static const char *tc_kind[] = {"load", "store", "ref", "member", "call", "ctor",
                                "downcast-ptr", "downcast-ref", "upcast", "vbase-cast",
                                "nonnull-bind", "dynamic"};

typedef struct {
    ub_loc loc;
    const ub_type *type;
    unsigned char log_align;
    unsigned char kind;
} ub_tm_data;

static void type_mismatch(void *d, ub_val ptr, void *caller)
{
    const ub_tm_data *t = (const ub_tm_data *)d;
    uintptr_t align = (uintptr_t)1 << t->log_align;
    const char *sub;
    char det[160];
    if (!ptr)
        sub = "null";
    else if (t->log_align && (ptr & (align - 1)))
        sub = "misaligned";
    else
        sub = "objsize";
    snprintf(det, sizeof det, "%s %s ptr=%08lx align=%lu",
             t->kind < 12 ? tc_kind[t->kind] : "?", TYNAME(t->type), (unsigned long)ptr,
             (unsigned long)align);
    ub_hit(d, &t->loc, "type_mismatch", sub, det, caller);
}
UB_PAIR(type_mismatch_v1, (void *d, ub_val ptr), { type_mismatch(d, ptr, CALLER); })

typedef struct {
    ub_loc loc;
    const ub_type *type;
} ub_ov_data;

static void overflow(void *d, const char *op, ub_val a, ub_val b, void *caller)
{
    const ub_ov_data *o = (const ub_ov_data *)d;
    char det[160];
    snprintf(det, sizeof det, "%s %08lx %08lx", TYNAME(o->type), (unsigned long)a,
             (unsigned long)b);
    ub_hit(d, &o->loc, "overflow", op, det, caller);
}
UB_PAIR(add_overflow, (void *d, ub_val a, ub_val b), { overflow(d, "add", a, b, CALLER); })
UB_PAIR(sub_overflow, (void *d, ub_val a, ub_val b), { overflow(d, "sub", a, b, CALLER); })
UB_PAIR(mul_overflow, (void *d, ub_val a, ub_val b), { overflow(d, "mul", a, b, CALLER); })
UB_PAIR(negate_overflow, (void *d, ub_val a), { overflow(d, "neg", a, 0, CALLER); })
UB_PAIR(divrem_overflow, (void *d, ub_val a, ub_val b),
        { overflow(d, b ? "divrem-min" : "divrem-zero", a, b, CALLER); })

typedef struct {
    ub_loc loc;
    const ub_type *lhs;
    const ub_type *rhs;
} ub_shift_data;

static void shift_oob(void *d, ub_val a, ub_val b, void *caller)
{
    const ub_shift_data *s = (const ub_shift_data *)d;
    char det[160];
    unsigned w = 0;
    const char *sub;
    /* TypeDescriptor info for integers: bit 0 = signed, bits 1.. = log2(width) */
    if (s->lhs && s->lhs->kind == 0)
        w = 1u << (s->lhs->info >> 1);
    if ((intptr_t)b < 0 && s->rhs && (s->rhs->info & 1))
        sub = "count-negative";
    else if (w && b >= w)
        sub = "count-ge-width";
    else if (s->lhs && (s->lhs->info & 1) && (intptr_t)a < 0)
        sub = "lhs-negative";
    else
        sub = "lhs-overflow";
    snprintf(det, sizeof det, "%s<<>>%s lhs=%08lx rhs=%ld", TYNAME(s->lhs), TYNAME(s->rhs),
             (unsigned long)a, (long)b);
    ub_hit(d, &s->loc, "shift", sub, det, caller);
}
UB_PAIR(shift_out_of_bounds, (void *d, ub_val a, ub_val b), { shift_oob(d, a, b, CALLER); })

typedef struct {
    ub_loc loc;
    const ub_type *array;
    const ub_type *index;
} ub_oob_data;

static void oob(void *d, ub_val i, void *caller)
{
    const ub_oob_data *o = (const ub_oob_data *)d;
    char det[200];
    snprintf(det, sizeof det, "%s [%ld]", TYNAME(o->array), (long)i);
    ub_hit(d, &o->loc, "bounds", "index", det, caller);
}
UB_PAIR(out_of_bounds, (void *d, ub_val i), { oob(d, i, CALLER); })

static void fatal_site(void *d, const char *kind, void *caller)
{
    ub_hit(d, LOC(d), kind, "-", "", caller);
    ub_dump();
    abort();
}
void __ubsan_handle_builtin_unreachable(void *d) { fatal_site(d, "unreachable", CALLER); }
void __ubsan_handle_missing_return(void *d) { fatal_site(d, "missing_return", CALLER); }

static void simple(void *d, const char *kind, const char *sub, ub_val v, void *caller)
{
    char det[64];
    snprintf(det, sizeof det, "%08lx", (unsigned long)v);
    ub_hit(d, LOC(d), kind, sub, det, caller);
}
UB_PAIR(vla_bound_not_positive, (void *d, ub_val v), { simple(d, "vla_bound", "-", v, CALLER); })
UB_PAIR(float_cast_overflow, (void *d, ub_val v), { simple(d, "float_cast", "-", v, CALLER); })
UB_PAIR(load_invalid_value, (void *d, ub_val v), { simple(d, "invalid_value", "-", v, CALLER); })
UB_PAIR(implicit_conversion, (void *d, ub_val a, ub_val b),
        { simple(d, "implicit_conversion", "-", a, CALLER); })
UB_PAIR(invalid_builtin, (void *d), { simple(d, "invalid_builtin", "-", 0, CALLER); })
UB_PAIR(nonnull_arg, (void *d), { simple(d, "nonnull_arg", "-", 0, CALLER); })
UB_PAIR(nullability_arg, (void *d), { simple(d, "nullability_arg", "-", 0, CALLER); })
UB_PAIR(pointer_overflow, (void *d, ub_val base, ub_val res),
        { simple(d, "pointer_overflow", res < base ? "wrap-down" : "wrap-up", base, CALLER); })
UB_PAIR(alignment_assumption, (void *d, ub_val p, ub_val a, ub_val o),
        { simple(d, "alignment_assumption", "-", p, CALLER); })

/* nonnull/nullability return: the site location is the second argument. */
UB_PAIR(nonnull_return_v1, (void *d, ub_loc *loc),
        { ub_hit(d, loc, "nonnull_return", "-", "", CALLER); })
UB_PAIR(nullability_return_v1, (void *d, ub_loc *loc),
        { ub_hit(d, loc, "nullability_return", "-", "", CALLER); })
