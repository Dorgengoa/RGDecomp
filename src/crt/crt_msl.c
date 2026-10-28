/* SPDX-License-Identifier: CC0-1.0 */
/* MSL C++ runtime entry points the game calls, under the game's names
 * (docs/BINDINGS.md).  The game's C++ was compiled by mwcc; its runtime
 * helpers are called from game code as plain functions, with the
 * constructor/destructor pointers of game classes as (this, flag) callbacks
 * (flag 1 = construct, -1 = destroy complete object, the mwcc convention). */
#include <stdio.h>

#include "crt.h"
/* x64 (docs/X64-PLAN.md): size parameters from the game are 32-bit values */
#if defined(_WIN64)
#define RG_GSIZE(x) ((x) = (size_t)(uint32_t)(x))
#else
#define RG_GSIZE(x) ((void)0)
#endif

/* operator new(size): malloc(size ? size : 1); on failure retail calls the
 * new_handler or throws bad_alloc when EH is on (it is off: the flag byte at
 * 0x00445E80 is 0 in retail data and no handler is installed), so NULL comes
 * back (the port builds with -fcheck-new, PLAN.md hazards). */
void *OperatorNew_100990(size_t n)
{ RG_GSIZE(n);
    return Malloc_130dd8(n ? n : 1);
}

void OperatorDelete_100840(void *p)
{
    Free_130e30(p);
}

/* __construct_new_array(block, ctor, dtor, size, n): a 16-byte cookie
 * {size, n, dtor, -} in front of the array; returns block + 16 (NULL when
 * block is NULL).  The EH unwind half (destroy the constructed prefix when a
 * ctor throws) cannot run: game ctors do not throw. */
void *ConstructNewArray_100710(void *block, rg_xtor_fn ctor, rg_xtor_fn dtor, size_t size, size_t n)
{ RG_GSIZE(size); RG_GSIZE(n);
    uint32_t *cookie = (uint32_t *)block;
    char *p;
    size_t i;
    if (!block)
        return NULL;
    cookie[0] = (uint32_t)size;
    cookie[1] = (uint32_t)n;
    cookie[2] = (uint32_t)(uintptr_t)dtor;
    p = (char *)block + 16;
    if (ctor)
        for (i = 0; i < n; i++)
            ctor(p + i * size, 1);
    return p;
}

/* __construct_array(ptr, ctor, dtor, size, n): no cookie */
void ConstructArray_100620(void *ptr, rg_xtor_fn ctor, rg_xtor_fn dtor, size_t size, size_t n)
{ RG_GSIZE(size); RG_GSIZE(n);
    size_t i;
    (void)dtor;
    for (i = 0; i < n; i++)
        ctor((char *)ptr + i * size, 1);
}

/* __destroy_arr(ptr, dtor, size, n): last element first */
void DestroyArray_1005b0(void *ptr, rg_xtor_fn dtor, size_t size, size_t n)
{ RG_GSIZE(size); RG_GSIZE(n);
    char *p = (char *)ptr + size * n;
    while (n--) {
        p -= size;
        dtor(p, -1);
    }
}

/* The global-destructor chain RegisterGlobalObject_100dc0 (game C) links
 * through: {next, dtor, object} nodes, head at 0x004853D0 (D_004853D0, MSL
 * .bss).  DestroyGlobalChain pops each node before calling dtor(object, -1).
 * The argument is unused (retail reads the global head). */
typedef struct global_node {  /* game memory: 4-byte words on x64 (CRT_P32) */
    struct global_node *CRT_P32 next;
    rg_xtor_fn CRT_P32 dtor;
    void *CRT_P32 object;
} global_node;
extern struct { global_node *CRT_P32 head; int32_t pad[3]; } D_004853D0;

void DestroyGlobalChain_100d60(void *unused)
{
    global_node *n;
    (void)unused;
    while ((n = D_004853D0.head) != NULL) {
        D_004853D0.head = n->next;
        rg_xtor_fn dtor = n->dtor; /* x64: no call through a __ptr32 function pointer (R1) */
        dtor(n->object, -1);
    }
}

/* ios_base::Init / wios_base::Init constructors (one static object per C++
 * TU, 217 static-init sites each): retail builds cin/cout/cerr/clog (and the
 * wide ones) over newlib FILEs on the first call.  The port does not model
 * MSL's standard streams: the game's only ostream users are the
 * MotionEvent*WriteText debug dumpers (flush/sentry below; docs/BINDINGS.md). */
void *IosBaseInitCtor_102bd0(void *self) { return self; }
void *WIosBaseInitCtor_103110(void *self) { return self; }

/* ---- basic_ostream flush / sentry (MSL, narrow and wide) ----------------
 * The game's ostream users are the MotionEvent*WriteText debug dumpers
 * (OstreamWriteCStr_1a1dd0, OstreamWriteBool_1b2710, OstreamWriteFloat_1b25c0,
 * compiled game C) and IosBaseInitDtor_102ee0, which flushes cout/cerr/clog.
 * Ported from the retail asm (OstreamFlush_1040b0, OstreamSentryCtor_106230,
 * WOstreamFlush_104320, WOstreamSentryCtor_106510: the wide pair is the same
 * code with the wide flush in the tie step).
 *
 * Layout read by the asm: an ostream's word 0 points at its basic_ios, which
 * has rdbuf at +0x20, fmtflags (u16) at +0x38 (0x2000 = unitbuf), the state
 * byte at +0x3A (1 badbit, 2 eofbit, 4 failbit), the exception mask at
 * +0x3B and tie at +0x40.  The sentry is {u8 ok; u8 flushed; u8 pad[2];
 * ostream *os}.  pubsync is the streambuf's vtable slot 4 (+0x18, the mwcc
 * layout of include/port/vcall.h).
 *
 * Deviations: (1) retail throws ios_base::failure("ios_base failure in
 * clear") when state & exceptions; nothing in the game catches it, so here it
 * prints that and aborts (the same thing the decomp's OstreamWriteCStr does
 * for its own throw site).  (2) An ostream whose basic_ios pointer is NULL is
 * left alone: the standard streams are never constructed in the port
 * (IosBaseInitCtor above is a no-op), so IosBaseInitDtor's flushes of them
 * must not dereference .bss zeros. */
typedef struct rg_ostream_sentry {
    uint8_t ok;
    uint8_t flushed;
    uint8_t pad[2];
    void *CRT_P32 os; /* the game's stack object (retail 8 bytes) */
} rg_ostream_sentry;

#define RG_IOS(os)        (*(uint8_t **)(os))
#define RG_IOS_RDBUF(i)   (*(uint32_t *)((i) + 0x20))
#define RG_IOS_FLAGS(i)   (*(uint16_t *)((i) + 0x38))
#define RG_IOS_STATE(i)   (*(uint8_t *)((i) + 0x3A))
#define RG_IOS_EXCEPT(i)  (*(uint8_t *)((i) + 0x3B))
#define RG_IOS_TIE(i)     (*(uint32_t *)((i) + 0x40))

/* basic_ios::setstate(bits) == clear(rdstate() | bits) */
static void rg_ios_setstate(uint8_t *ios, unsigned bits)
{
    uint8_t st = (uint8_t)(RG_IOS_STATE(ios) | bits);
    RG_IOS_STATE(ios) = st;
    if (RG_IOS_RDBUF(ios) == 0)
        RG_IOS_STATE(ios) = st = (uint8_t)(st | 1);
    if (st & RG_IOS_EXCEPT(ios)) {
        fprintf(stderr, "ios_base failure in clear\n");
        Abort_12de80();
    }
}

typedef void *(*rg_ostream_flush_fn)(void *os);

static rg_ostream_sentry *rg_sentry_ctor(rg_ostream_sentry *s, void *os, rg_ostream_flush_fn flush)
{
    uint8_t *ios;
    s->ok = 0;
    s->flushed = 0;
    s->os = os;
    if (!os || !RG_IOS(os))
        return s; /* deviation (2) */
    ios = RG_IOS(os);
    if (RG_IOS_STATE(ios) != 0) {
        rg_ios_setstate(ios, 4); /* failbit */
        return s;
    }
    if (RG_IOS_TIE(ios) != 0)
        flush((void *)(uintptr_t)RG_IOS_TIE(ios));
    ios = RG_IOS(s->os);
    if (RG_IOS_STATE(ios) == 0)
        s->ok = 1;
    else
        rg_ios_setstate(ios, 4);
    return s;
}

static void *rg_ostream_flush(void *os, rg_ostream_flush_fn self)
{
    rg_ostream_sentry s;
    uint8_t *ios;
    uint32_t sb;
    if (!os || !RG_IOS(os))
        return os; /* deviation (2) */
    rg_sentry_ctor(&s, os, self);
    s.flushed = 1;
    ios = RG_IOS(os);
    sb = RG_IOS_RDBUF(ios);
    if (sb != 0) {
        /* rdbuf()->pubsync(): vtable word at +0x18 */
        uint32_t fn = *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)sb + 0x18);
        if (((int (*)(void *))(uintptr_t)fn)((void *)(uintptr_t)sb) == -1)
            rg_ios_setstate(RG_IOS(os), 1); /* badbit */
    }
    /* ~sentry: unitbuf flush unless already flushing (never taken here) */
    ios = RG_IOS(s.os);
    if ((RG_IOS_STATE(ios) & 5) == 0 && (RG_IOS_FLAGS(ios) & 0x2000) && !s.flushed)
        self(s.os);
    return os;
}

void *OstreamFlush_1040b0(void *os) { return rg_ostream_flush(os, OstreamFlush_1040b0); }
void *WOstreamFlush_104320(void *os) { return rg_ostream_flush(os, WOstreamFlush_104320); }

void *OstreamSentryCtor_106230(void *sentry, void *os)
{
    return rg_sentry_ctor((rg_ostream_sentry *)sentry, os, OstreamFlush_1040b0);
}

void *WOstreamSentryCtor_106510(void *sentry, void *os)
{
    return rg_sentry_ctor((rg_ostream_sentry *)sentry, os, WOstreamFlush_104320);
}
