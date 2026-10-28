/* rg-override: replaces game/src/main/file/FileReqThread_182c30.c sha256 bf6ba70d67c17c115859c9b8fc0e03713e2e81f59f4ce1b28259ff34fa43ce04
 * why: native frame driver (docs/NATIVE-THREADS.md "Slice 3"): the request thread is a driven
 *      step run at the main flow's wake signal; its reads are native-FS async host jobs
 *      started when a request is queued and completed at that wake (block comment below);
 *      the thread entry keeps the generated loop for the other modes */
/* rgp:protos */
#define RGP_SELF_FileReqThread_182c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

s32 DisableIntr_120660(void);
void EnableIntr_1206b0(void);
/*rgp*/
void SignalSema(s32);
void WaitSema(s32);
/*rgp*/
extern s32 D_0047E020;
extern s32 D_0047E024;
extern s32 D_004811E8;
extern s32 D_004811F8;
extern s32 D_004811FC;
extern s32 D_00481204;
extern u8 D_00495FD0[];

/* ---- rg-override: native frame driver + native-FS async reads ------------------------
 * The request thread is a driven step (docs/NATIVE-THREADS.md "Slice 3").  Its wake sema
 * is signalled by the main flow (FileReqThreadResume, FileReqAnyIncomplete,
 * FileReqCancelAll, FileReqThreadShutdown); the HLE switched to this priority-19 thread at
 * that signal and it read every pending request before the signaller went on, so the
 * driver runs the step there (rg_thread_conv.sync) and the game sees each request
 * complete at exactly the same point as before.
 *
 * The reads themselves are native-FS async host jobs started EARLIER, when the request is
 * queued (FileReqSubmit_1827a0 calls rg_FileReqPrefetch): one job per 1 MB chunk, the reads
 * FileReadChunked_180400 -> FileSlotRead_180aa0 would make (same offsets, same buffer
 * extent).  The step waits for them (host wait; usually already done) and completes the
 * requests (slot closed, result, done flags) in queue order.  So host I/O overlaps the game
 * between queueing and wake, and nothing the game sees depends on host timing.  A cancel
 * or shutdown (D_00481204) finishes the jobs but completes nothing, as the generated loop
 * read nothing then.  Requests that are not cdrom:/cddat: files, or that the chunk loop
 * would treat as an error, take the generated synchronous path at the wake. */

/* the file-slot entry as the native-FS lane's FileSlotRead_180aa0 override reads it */
typedef struct rg_FrEntry {
    u8 used;
    u8 type;
    u8 pad2[2];
    s32 handle;     /* cdrom/cddat: rg_fs handle */
    s32 pad8;
    s32 lsn;        /* cdrom/cddat: first 2048-byte block in that file */
    s32 nsect;
    u8 pad14[0x58];
    u32 pos;
    u32 bsize;
    u32 flags;
    u8 busy;
    u8 pad79[3];
} rg_FrEntry;
extern rg_FrEntry D_0049B100[12];
void FileReqThread_182c30(void);

typedef void (*rg_fs_done_fn)(void *user, int req, long long result);
extern int rg_fs_read_async(int h, long long off, void *buf, long long len, rg_fs_done_fn cb, void *user);
extern long long rg_fs_wait(int req);
extern long long rg_fs_read_fill(int h, long long off, void *buf, long long len);

#define RG_FR_MAXJOBS 256
static s32 rg_fr_job_req[RG_FR_MAXJOBS];  /* host request ids in issue order (0 = finished) */
static s32 rg_fr_njobs;
static s32 rg_fr_order[32];               /* prefetched request slots in queue order */
static s32 rg_fr_norder;
static s32 rg_fr_busy[32];                /* prefetched, not completed for the game yet */
static s32 rg_fr_total[32];               /* what the chunk loop returns */
static s32 rg_fr_fail[32];                /* a host read failed: result -1 */
static u32 rg_fr_issued, rg_fr_sync, rg_fr_dropped; /* counters (RG_THREADS_LOG) */

static void rg_fr_done(void *user, int req, long long result)
{
    (void)req;
    if (result < 0)
        rg_fr_fail[(s32)(long)user] = 1;
}

/* host side: every issued job finished (callbacks above); nothing told to the game */
static void rg_FileReqDrain(void)
{
    s32 k;
    for (k = 0; k < rg_fr_njobs; k++) {
        if (rg_fr_job_req[k] > 0) {
            rg_fs_wait(rg_fr_job_req[k]);
            rg_fr_job_req[k] = 0;
        }
    }
    rg_fr_njobs = 0;
}

/* forget every prefetch without completing it (cancel / shutdown / a reused slot) */
static void rg_FileReqDrop(void)
{
    s32 k;
    rg_FileReqDrain();
    for (k = 0; k < rg_fr_norder; k++) {
        rg_fr_busy[rg_fr_order[k]] = 0;
        rg_fr_fail[rg_fr_order[k]] = 0;
        rg_fr_dropped++;
    }
    rg_fr_norder = 0;
}

/* the step: complete every prefetched request, in queue order, as the generated loop did
 * right after its FileReadChunked (only requests still queued: m120 != 0, unread) */
static void rg_FileReqComplete(void)
{
    s32 k, idx, r, t;
    u8 *p;

    if (rg_fr_norder == 0)
        return;
    rg_FileReqDrain();
    for (k = 0; k < rg_fr_norder; k++) {
        idx = rg_fr_order[k];
        p = D_00495FD0 + idx * 0x128;
        rg_fr_busy[idx] = 0;
        if (*(s32 *)(p + 0x120) == 0 || *(s32 *)(p + 4) != 0 || *(s32 *)(p + 8) != 0) {
            rg_fr_fail[idx] = 0;
            rg_fr_dropped++; /* released before the wake: the generated loop never read it */
            continue;
        }
        r = rg_fr_fail[idx] ? -1 : rg_fr_total[idx];
        rg_fr_fail[idx] = 0;
        FileSlotCloseThunk_180540(*(s32 *)(p + 0x124));
        *(s32 *)(p + 0x124) = -1;
        if (r < *(s32 *)(p + 0x114)) {
            *(s32 *)(p + 0x110) = r;
        }
        t = DisableIntr_120660();
        *(s32 *)(p + 4) = 1;
        *(s32 *)(p + 8) = 1;
        if (t != 0) {
            EnableIntr_1206b0();
        }
    }
    rg_fr_norder = 0;
}

/* start the reads of request slot idx as host jobs; 0 = leave it to the generated path */
static int rg_FileReqIssue(u8 *p, s32 idx)
{
    s32 fd = *(s32 *)(p + 0x124);
    s32 size = *(s32 *)(p + 0x114);
    u8 *buf = (u8 *)(unsigned long)(u32) * (s32 *)(p + 0x10C);
    rg_FrEntry *e;
    s32 rem, n, k, sect, total;
    u32 pos;

    if (fd < 0 || fd >= 12)
        return 0;
    e = &D_0049B100[fd];
    if (e->used == 0 || e->busy != 0 || (e->type != 1 && e->type != 4) || e->bsize != 0x800)
        return 0;
    /* FileReadChunked's loop over FileSlotRead, planned first: any error path -> generated code */
    pos = e->pos;
    rem = size;
    while (rem > 0) {
        n = rem > 0x100000 ? 0x100000 : rem;
        sect = pos / e->bsize;
        k = n / e->bsize + (n % e->bsize != 0);
        if (e->nsect < sect + k)
            k = e->nsect - sect;
        if (k < 0)
            return 0;
        n = k * e->bsize;
        pos += n;
        rem -= n;
        if (rem <= 0 || n == 0)
            break;
    }
    if (rg_fr_njobs + (size >> 20) + 2 > RG_FR_MAXJOBS)
        return 0;
    /* issue */
    pos = e->pos;
    rem = size;
    total = 0;
    while (rem > 0) {
        n = rem > 0x100000 ? 0x100000 : rem;
        sect = pos / e->bsize;
        k = n / e->bsize + (n % e->bsize != 0);
        if (e->nsect < sect + k)
            k = e->nsect - sect;
        if (k > 0) {
            long long off = ((long long)e->lsn + sect) * 0x800;
            int req = rg_fs_read_async(e->handle, off, buf + total, (long long)k * 0x800, rg_fr_done,
                                       (void *)(long)idx);
            if (req > 0) {
                rg_fr_job_req[rg_fr_njobs++] = req;
            } else if (rg_fs_read_fill(e->handle, off, buf + total, (long long)k * 0x800) < 0) {
                rg_fr_fail[idx] = 1; /* no worker: the same read, synchronously */
            }
        }
        n = k * e->bsize;
        pos += n;
        rem -= n;
        total += n;
        if (rem <= 0 || n == 0)
            break;
    }
    e->pos = pos; /* the slot position after FileReadChunked; nothing else reads this slot */
    rg_fr_total[idx] = total;
    rg_fr_busy[idx] = 1;
    rg_fr_order[rg_fr_norder++] = idx;
    rg_fr_issued++;
    return 1;
}

/* rg-override: called by FileReqSubmit_1827a0 once request slot p is queued (m120 = 1) */
void rg_FileReqPrefetch(u8 *p)
{
    s32 idx = (s32)((p - D_00495FD0) / 0x128);

    if (idx < 0 || idx >= 32 || !rg_frame_is_driven((void *)FileReqThread_182c30))
        return;
    if (rg_fr_busy[idx])
        rg_FileReqDrop(); /* cannot happen with the game's slot reuse; be safe */
    rg_FileReqIssue(p, idx);
}

/* rg-override: the loop's condition (the sema to wait on, or -1 = leave the loop) */
int rg_FileReqWait(void *arg)
{
    (void)arg;
    return D_004811F8 != 0 ? D_0047E020 : -1;
}

/* rg-override: the loop body after WaitSema (the generated loop); drv = 1 (driven step):
 * prefetched requests complete first, in queue order */
static void rg_FileReqBody(int drv)
{
    s32 i;
    s32 t;
    s32 r;
    u8 *p;

    if (drv) {
        if (D_00481204 != 0)
            rg_FileReqDrop(); /* cancel / shutdown: the generated loop reads nothing */
        else
            rg_FileReqComplete();
    }
    while (!D_00481204) {
        t = DisableIntr_120660();
        p = D_00495FD0;
        for (i = 0; i < 0x20; i++) {
            p = D_00495FD0 + ((D_004811E8 + i) % 32) * 0x128;
            if (*(s32 *)(p + 0x120) == 0) {
                continue;
            }
            if ((*(s32 *)(p + 4) != 0 && *(s32 *)(p + 8) == 0) ||
                (*(s32 *)(p + 4) == 0 && *(s32 *)(p + 8) == 0)) {
                break;
            }
        }
        if (t != 0) {
            EnableIntr_1206b0();
        }
        if (i == 0x20) {
            break;
        }
        if (*(s32 *)(p + 4) == 0) {
            if (drv)
                rg_fr_sync++;
            r = FileReadChunked_180400(*(s32 *)(p + 0x124), *(s32 *)(p + 0x10C), *(s32 *)(p + 0x114));
            FileSlotCloseThunk_180540(*(s32 *)(p + 0x124));
            *(s32 *)(p + 0x124) = -1;
            if (r < *(s32 *)(p + 0x114)) {
                *(s32 *)(p + 0x110) = r;
            }
            t = DisableIntr_120660();
            *(s32 *)(p + 4) = 1;
            *(s32 *)(p + 8) = 1;
            if (t != 0) {
                EnableIntr_1206b0();
            }
        }
    }
    if (D_00481204 != 0) {
        D_00481204 = 0;
        SignalSema(D_0047E024);
    }
}

void rg_FileReqStep(void *arg)
{
    (void)arg;
    rg_FileReqBody(1);
}

static void rg_FileReqExit(void *arg)
{
    (void)arg;
    rg_FileReqDrop();
    D_004811FC = 1;
}

void FileReqThread_182c30(void)
{
    s32 s;

    while ((s = rg_FileReqWait(0)) >= 0) {
        WaitSema(s);
        rg_FileReqBody(0);
    }
    D_004811FC = 1;
}

/* rg-override: frame driver conversion (old priority P-1 = 19) */
static const rg_thread_conv rg_FileReqConv = {
    (void *)FileReqThread_182c30, "FileReqThread_182c30", rg_FileReqWait, rg_FileReqStep, rg_FileReqExit, 0, 0,
    19, 1 /* sync */, 0, rg_FileReqDrain
};
extern int printf(const char *, ...);
extern char *getenv(const char *);
extern int atexit(void (*)(void));
static void rg_FileReqReport(void)
{
    printf("rg_frame:   FileReqThread_182c30: %u requests prefetched as async host jobs, %u read on the "
           "generated sync path, %u prefetches dropped\n",
           rg_fr_issued, rg_fr_sync, rg_fr_dropped);
}
__attribute__((constructor)) static void rg_FileReqRegister(void)
{
    rg_threads_convertible(&rg_FileReqConv);
    if (getenv("RG_THREADS_LOG"))
        atexit(rg_FileReqReport);
}
