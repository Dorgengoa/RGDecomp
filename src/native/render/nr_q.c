/* SPDX-License-Identifier: CC0-1.0 */
/* The native renderer's worker (nr_gs.h "worker"; docs/NATIVE-RENDER.md "Checkpoint 10"):
 * a single-producer ring of calls a worker thread runs in order.  The GS worker of the
 * emulated path (src/ps2/gs/gs_async.c) without the GS model behind it: no GIF data, no
 * path scan, no events (the GIF input raises SIGNAL / FINISH on the EE thread); the records,
 * IMAGE data and presentation are calls. */
#include "nr_gs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
typedef SRWLOCK nq_mutex;
typedef CONDITION_VARIABLE nq_cond;
#define MTX_INIT(m) InitializeSRWLock(m)
#define MTX_LOCK(m) AcquireSRWLockExclusive(m)
#define MTX_UNLOCK(m) ReleaseSRWLockExclusive(m)
#define COND_INIT(c) InitializeConditionVariable(c)
#define COND_WAIT(c, m) SleepConditionVariableSRW(c, m, INFINITE, 0)
#define COND_SIGNAL(c) WakeAllConditionVariable(c)
#else
#include <pthread.h>
typedef pthread_mutex_t nq_mutex;
typedef pthread_cond_t nq_cond;
#define MTX_INIT(m) pthread_mutex_init(m, NULL)
#define MTX_LOCK(m) pthread_mutex_lock(m)
#define MTX_UNLOCK(m) pthread_mutex_unlock(m)
#define COND_INIT(c) pthread_cond_init(c, NULL)
#define COND_WAIT(c, m) pthread_cond_wait(c, m)
#define COND_SIGNAL(c) pthread_cond_broadcast(c)
#endif

enum { NQ_RING = 64u << 20 };
enum { NQ_CALL = 1, NQ_PAD = 2 };

typedef struct nq_hdr {
    uint32_t kind, bytes;       /* bytes of payload after the header */
    nr_q_fn fn;
    void *user;
} nq_hdr;
#define NQ_HDR 32u   /* every entry a multiple of 32 bytes (a pad entry always fits its header) */
_Static_assert(sizeof(nq_hdr) <= NQ_HDR, "nq_hdr");

typedef volatile uint64_t nq_u64 __attribute__((aligned(8)));
static struct {
    uint8_t *ring;
    _Alignas(8) volatile uint64_t head;   /* bytes queued (only grows) */
    _Alignas(8) volatile uint64_t tail;   /* bytes run */
    volatile int worker_sleeping, producer_waiting;
    int stop, on;
    nq_mutex m;
    nq_cond c_work, c_space;
#ifdef _WIN32
    HANDLE th;
#else
    pthread_t th;
#endif
    uint64_t entries, bytes, drains;
    double wait_ms;
    /* the tick (nr_q_set_tick): a function the worker runs between calls and while idle once its
     * time has come.  hold: the producer drained and may use the device itself (no tick until it
     * queues again); tick_running: a tick in progress (a drain waits for it too) */
    nr_q_tick_fn tick_fn;
    void *tick_user;
    double tick_due;                     /* (worker) now_ms() at which the tick runs next */
    volatile int hold, tick_running, tick_kick;
    uint64_t ticks;
#ifdef _WIN32
    HANDLE ev_work, tmr;                 /* tick mode's idle wait: new work or the tick's time */
#endif
} Q;

static double now_ms(void)
{
#ifdef _WIN32
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1.0e6;
#endif
}

static uint64_t ld64(nq_u64 *p) { return __atomic_load_n(p, __ATOMIC_SEQ_CST); }
static void st64(nq_u64 *p, uint64_t v) { __atomic_store_n(p, v, __ATOMIC_SEQ_CST); }
static int ldi(volatile int *p) { return __atomic_load_n(p, __ATOMIC_SEQ_CST); }
static void sti(volatile int *p, int v) { __atomic_store_n(p, v, __ATOMIC_SEQ_CST); }

static void wake_producer(void)
{
    if (ldi(&Q.producer_waiting)) {
        MTX_LOCK(&Q.m);
        COND_SIGNAL(&Q.c_space);
        MTX_UNLOCK(&Q.m);
    }
}
static void wake_worker(void)
{
    if (ldi(&Q.worker_sleeping)) {
        MTX_LOCK(&Q.m);
        COND_SIGNAL(&Q.c_work);
        MTX_UNLOCK(&Q.m);
#ifdef _WIN32
        if (Q.ev_work) SetEvent(Q.ev_work);
#endif
    }
}
static void run_tick(void)
{
    double r;
    sti(&Q.tick_running, 1);
    sti(&Q.tick_kick, 0);
    if (ldi(&Q.hold) || !Q.tick_fn) {
        sti(&Q.tick_running, 0);
        Q.tick_due = now_ms() + 1.0;
        wake_producer();
        return;
    }
    r = Q.tick_fn(Q.tick_user);
    Q.ticks++;
    Q.tick_due = r < 0.0 ? 1e300 : now_ms() + r;
    sti(&Q.tick_running, 0);
    wake_producer();
}
static int tick_now(void) { return Q.tick_fn && (ldi(&Q.tick_kick) || now_ms() >= Q.tick_due); }
static void producer_wait_tail(uint64_t want)
{
    if (ld64(&Q.tail) >= want) return;
    MTX_LOCK(&Q.m);
    sti(&Q.producer_waiting, 1);
    while (ld64(&Q.tail) < want) COND_WAIT(&Q.c_space, &Q.m);
    sti(&Q.producer_waiting, 0);
    MTX_UNLOCK(&Q.m);
}
/* (drain) no tick in progress */
static void producer_wait_tick(void)
{
    if (!ldi(&Q.tick_running)) return;
    MTX_LOCK(&Q.m);
    sti(&Q.producer_waiting, 1);
    while (ldi(&Q.tick_running)) COND_WAIT(&Q.c_space, &Q.m);
    sti(&Q.producer_waiting, 0);
    MTX_UNLOCK(&Q.m);
}

#ifdef _WIN32
static DWORD WINAPI worker(LPVOID arg)
#else
static void *worker(void *arg)
#endif
{
    uint64_t t = ld64(&Q.tail), since = 0;
    (void)arg;
    for (;;) {
        uint64_t h = ld64(&Q.head);
#ifdef _WIN32
        if (h == t && Q.tick_fn && Q.ev_work) {
            /* tick mode: idle until new work, the tick's time or a kick */
            for (;;) {
                double w;
                if (tick_now()) run_tick();
                if ((h = ld64(&Q.head)) != t || Q.stop) break;
                sti(&Q.worker_sleeping, 1);
                if ((h = ld64(&Q.head)) != t || Q.stop || ldi(&Q.tick_kick)) {
                    sti(&Q.worker_sleeping, 0);
                    if (h != t || Q.stop) break;
                    continue;
                }
                w = Q.tick_due - now_ms();
                if (w > 0.0 && w < 1e9 && Q.tmr) {
                    LARGE_INTEGER due;
                    HANDLE hs[2];
                    due.QuadPart = -(LONGLONG)(w * 10000.0);   /* 100 ns units, relative */
                    SetWaitableTimer(Q.tmr, &due, 0, NULL, NULL, FALSE);
                    hs[0] = Q.ev_work;
                    hs[1] = Q.tmr;
                    WaitForMultipleObjects(2, hs, FALSE, 50);
                } else if (w > 0.0) {
                    WaitForSingleObject(Q.ev_work, 50);
                }
                sti(&Q.worker_sleeping, 0);
            }
            if (h == t && Q.stop) break;
            if (h == t) continue;
        }
#else
        if (h == t && Q.tick_fn) {
            /* tick mode, portable: the work condition with a timeout (the tick's time) */
            for (;;) {
                double w;
                if (tick_now()) run_tick();
                if ((h = ld64(&Q.head)) != t || Q.stop) break;
                MTX_LOCK(&Q.m);
                sti(&Q.worker_sleeping, 1);
                if ((h = ld64(&Q.head)) == t && !Q.stop && !ldi(&Q.tick_kick)) {
                    struct timespec ts;
                    w = Q.tick_due - now_ms();
                    if (w > 50.0 || !(w > 0.0)) w = w > 0.0 ? 50.0 : 0.0;
                    if (w > 0.0) {
                        long long ns;
                        clock_gettime(CLOCK_REALTIME, &ts);   /* (pthread_cond_timedwait's clock) */
                        ns = (long long)ts.tv_nsec + (long long)(w * 1e6);
                        ts.tv_sec += (time_t)(ns / 1000000000LL);
                        ts.tv_nsec = (long)(ns % 1000000000LL);
                        pthread_cond_timedwait(&Q.c_work, &Q.m, &ts);
                    }
                }
                sti(&Q.worker_sleeping, 0);
                MTX_UNLOCK(&Q.m);
                h = ld64(&Q.head);
                if (h != t || Q.stop) break;
            }
            if (h == t && Q.stop) break;
            if (h == t) continue;
        }
#endif
        if (h == t) {
            int done;
            MTX_LOCK(&Q.m);
            sti(&Q.worker_sleeping, 1);
            while ((h = ld64(&Q.head)) == t && !Q.stop) COND_WAIT(&Q.c_work, &Q.m);
            sti(&Q.worker_sleeping, 0);
            done = h == t && Q.stop;
            MTX_UNLOCK(&Q.m);
            if (done) break;
        }
        while (t != h) {
            nq_hdr *e = (nq_hdr *)(Q.ring + (t % NQ_RING));
            if (e->kind == NQ_CALL) e->fn(e->user, (const uint8_t *)e + NQ_HDR);
            t += NQ_HDR + e->bytes;
            since += NQ_HDR + e->bytes;
            if (Q.tick_fn && tick_now()) {
                st64(&Q.tail, t);   /* (what ran is done: the tick sees the state after it) */
                since = 0;
                run_tick();
            }
            if (since >= (256u << 10)) {
                st64(&Q.tail, t);
                since = 0;
                wake_producer();
            }
        }
        st64(&Q.tail, t);
        since = 0;
        wake_producer();
    }
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

int nr_q_start(void)
{
    if (Q.on) return 0;
    Q.ring = (uint8_t *)malloc(NQ_RING);
    if (!Q.ring) return -1;
    Q.head = Q.tail = 0;
    Q.stop = 0;
    MTX_INIT(&Q.m);
    COND_INIT(&Q.c_work);
    COND_INIT(&Q.c_space);
#ifdef _WIN32
    Q.th = CreateThread(NULL, 1u << 20, worker, NULL, 0, NULL);
    if (!Q.th) { free(Q.ring); Q.ring = NULL; return -1; }
#else
    if (pthread_create(&Q.th, NULL, worker, NULL) != 0) { free(Q.ring); Q.ring = NULL; return -1; }
#endif
    Q.on = 1;
    return 0;
}

void nr_q_drain(void)
{
    uint64_t h;
    if (!Q.on) return;
    /* no tick while the producer waits either (default: the producer's wait is not lengthened by
     * a present; $RG_Q_HOLD_EARLY=0: ticks due during the wait still run, more presents, the game
     * thread waits longer: measured 2026-10-30, gs_wait 5.5 -> 9 ms per field) */
    static int early = -1;
    if (early < 0) { const char *e = getenv("RG_Q_HOLD_EARLY"); early = !(e && e[0] == '0'); }
    if (early) sti(&Q.hold, 1);
    h = ld64(&Q.head);
    if (ld64(&Q.tail) != h || ldi(&Q.tick_running)) {
        double t0 = now_ms();
        Q.drains++;
        producer_wait_tail(h);   /* (ticks due meanwhile still run: the worker's presents keep their slots) */
        sti(&Q.hold, 1);         /* the caller may use the device now: no tick until it queues again */
        producer_wait_tick();
        Q.wait_ms += now_ms() - t0;
    }
    sti(&Q.hold, 1);
}

void nr_q_set_tick(nr_q_tick_fn fn, void *user)
{
    if (!Q.on) return;
    nr_q_drain();   /* (the worker is idle and holds off ticks while the function changes) */
#ifdef _WIN32
    if (fn && !Q.ev_work) {
        Q.ev_work = CreateEventW(NULL, FALSE, FALSE, NULL);
#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif
        Q.tmr = CreateWaitableTimerExW(NULL, NULL, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
        if (!Q.tmr) Q.tmr = CreateWaitableTimerExW(NULL, NULL, 0, TIMER_ALL_ACCESS);
        if (!Q.ev_work) return;
    }
#endif
    Q.tick_user = user;
    Q.tick_due = 0.0;
    __atomic_store_n(&Q.tick_fn, fn, __ATOMIC_SEQ_CST);
    nr_q_tick_kick();
}

void nr_q_tick_kick(void)
{
    if (!Q.on || !Q.tick_fn) return;
    sti(&Q.tick_kick, 1);
#ifdef _WIN32
    if (Q.ev_work) SetEvent(Q.ev_work);
#else
    if (ldi(&Q.worker_sleeping)) {
        MTX_LOCK(&Q.m);
        COND_SIGNAL(&Q.c_work);
        MTX_UNLOCK(&Q.m);
    }
#endif
}

uint64_t nr_q_ticks(void) { return Q.ticks; }

void nr_q_stop(void)
{
    if (!Q.on) return;
    nr_q_drain();
    MTX_LOCK(&Q.m);
    Q.stop = 1;
    COND_SIGNAL(&Q.c_work);
    MTX_UNLOCK(&Q.m);
#ifdef _WIN32
    WaitForSingleObject(Q.th, INFINITE);
    CloseHandle(Q.th);
#else
    pthread_join(Q.th, NULL);
#endif
    free(Q.ring);
    Q.ring = NULL;
    Q.on = 0;
#ifdef _WIN32
    if (Q.ev_work) CloseHandle(Q.ev_work);
    if (Q.tmr) CloseHandle(Q.tmr);
    Q.ev_work = Q.tmr = NULL;
#endif
    Q.tick_fn = NULL;
}

int nr_q_on(void) { return Q.on; }
double nr_q_wait_ms(void) { return Q.wait_ms; }
void nr_q_stats(uint64_t out[4])
{
    out[0] = Q.entries;
    out[1] = Q.bytes;
    out[2] = Q.drains;
    out[3] = 0;
}

void nr_q_call2(nr_q_fn fn, void *user, const void *a, uint32_t abytes, const void *b, uint32_t bbytes)
{
    uint32_t bytes = abytes + bbytes, pay = (bytes + 31u) & ~31u, need = NQ_HDR + pay, pos;
    uint64_t h;
    nq_hdr *e;
    if (!Q.on || need > NQ_RING / 4) {
        uint8_t *tmp = (uint8_t *)malloc(bytes ? bytes : 1);
        nr_q_drain();
        if (!tmp) return;
        if (abytes) memcpy(tmp, a, abytes);
        if (bbytes) memcpy(tmp + abytes, b, bbytes);
        fn(user, tmp);
        free(tmp);
        return;
    }
    h = ld64(&Q.head);
    pos = (uint32_t)(h % NQ_RING);
    if (pos + need > NQ_RING) {
        /* an entry never wraps: pad to the ring's end first */
        uint32_t pad = NQ_RING - pos;
        if (h + pad > NQ_RING) producer_wait_tail(h + pad - NQ_RING);
        e = (nq_hdr *)(Q.ring + pos);
        e->kind = NQ_PAD;
        e->bytes = pad - NQ_HDR;
        h += pad;
        st64(&Q.head, h);
        wake_worker();
        pos = 0;
    }
    if (h + need > NQ_RING) producer_wait_tail(h + need - NQ_RING);
    e = (nq_hdr *)(Q.ring + pos);
    e->kind = NQ_CALL;
    e->bytes = pay;
    e->fn = fn;
    e->user = user;
    if (abytes) memcpy((uint8_t *)e + NQ_HDR, a, abytes);
    if (bbytes) memcpy((uint8_t *)e + NQ_HDR + abytes, b, bbytes);
    st64(&Q.head, h + need);
    sti(&Q.hold, 0);   /* (the worker owns the device again: ticks may run) */
    wake_worker();
    Q.entries++;
    Q.bytes += bytes;
}

void nr_q_call(nr_q_fn fn, void *user, const void *data, uint32_t bytes)
{
    nr_q_call2(fn, user, data, bytes, NULL, 0);
}

uint64_t nr_q_mark(void) { return Q.on ? ld64(&Q.head) : 0; }

void nr_q_wait_mark(uint64_t mark)
{
    double t0;
    if (!Q.on || ld64(&Q.tail) >= mark) return;
    t0 = now_ms();
    producer_wait_tail(mark);
    Q.wait_ms += now_ms() - t0;
}
