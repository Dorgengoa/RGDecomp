/* SPDX-License-Identifier: CC0-1.0 */
/* CDVD model, drive half: one pending N-command (read/seek) completed on a virtual
 * clock. See cdvd.h and docs/CDVD.md. */
#include "cdvd.h"

#include <string.h>

/* Rough DVD figures: ~5.5 MB/s sustained (2048 bytes in ~370 us), plus a fixed command
 * cost. Only load-time pacing depends on them. */
static const cdvd_timing k_default_timing = {1000u, 370u};

static struct {
    cdvd_disc *disc;
    cdvd_timing timing;
    uint64_t now;
    int busy;
    int func;
    uint64_t due;
    uint32_t lsn, count;
    void *buf;
    int pending_error; /* decided at submit (bad parameters), applied at completion */
    int error;
    cdvd_done_fn done;
    void *done_ctx;
    cdvd_wait_fn wait;
    void *wait_ctx;
} g = {NULL, {1000u, 370u}, 0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL, NULL, NULL, NULL};

void cdvd_drive_reset(cdvd_disc *disc) {
    g.disc = disc;
    g.busy = 0;
    g.error = CDVD_ERR_NONE;
    g.buf = NULL;
}

cdvd_disc *cdvd_drive_disc(void) { return g.disc; }

void cdvd_drive_set_timing(const cdvd_timing *t) { g.timing = t ? *t : k_default_timing; }

void cdvd_drive_set_done(cdvd_done_fn fn, void *ctx) {
    g.done = fn;
    g.done_ctx = ctx;
}

void cdvd_drive_set_wait_hook(cdvd_wait_fn fn, void *ctx) {
    g.wait = fn;
    g.wait_ctx = ctx;
}

static void start(int func, uint32_t lsn, uint32_t count, void *buf, int err) {
    g.busy = 1;
    g.func = func;
    g.lsn = lsn;
    g.count = count;
    g.buf = buf;
    g.pending_error = err;
    g.due = g.now + g.timing.command_us + (uint64_t)g.timing.sector_us * (err ? 0 : count);
}

int cdvd_drive_read(uint32_t lsn, uint32_t count, void *buf) {
    int err = CDVD_ERR_NONE;
    if (g.busy) return 0;
    if (!g.disc)
        err = CDVD_ERR_NODISC;
    else if (!buf || count == 0)
        err = CDVD_ERR_PARAM;
    else if (lsn >= cdvd_disc_lsn_end(g.disc) || count > cdvd_disc_lsn_end(g.disc) - lsn)
        err = CDVD_ERR_POSITION;
    if (err != CDVD_ERR_NONE)
        cdvd_log(CDVD_LOG_WARN, "read LSN %u x %u rejected (error 0x%02x)", (unsigned)lsn, (unsigned)count, err);
    start(CDVD_FUNC_READ, lsn, count, buf, err);
    return 1;
}

int cdvd_drive_seek(uint32_t lsn) {
    int err = CDVD_ERR_NONE;
    if (g.busy) return 0;
    if (!g.disc)
        err = CDVD_ERR_NODISC;
    else if (lsn >= cdvd_disc_lsn_end(g.disc))
        err = CDVD_ERR_POSITION;
    start(CDVD_FUNC_SEEK, lsn, 0, NULL, err);
    return 1;
}

static void complete(int err) {
    int func = g.func;
    g.busy = 0;
    g.error = err;
    g.buf = NULL;
    if (g.done) g.done(g.done_ctx, func, err);
}

void cdvd_drive_break(void) {
    if (g.busy) complete(CDVD_ERR_ABORT);
}

int cdvd_drive_busy(void) { return g.busy; }
int cdvd_drive_error(void) { return g.error; }
uint64_t cdvd_now(void) { return g.now; }
void cdvd_drive_set_clock(uint64_t now_us) { g.now = now_us; }

int cdvd_next_event(uint64_t *due) {
    if (!g.busy) return 0;
    if (due) *due = g.due;
    return 1;
}

void cdvd_poll(uint64_t now_us) {
    int err;
    if (now_us > g.now) g.now = now_us;
    if (!g.busy || g.now < g.due) return;
    err = g.pending_error;
    if (err == CDVD_ERR_NONE && g.func == CDVD_FUNC_READ) {
        uint32_t unmapped = 0;
        int rc = cdvd_disc_read(g.disc, g.lsn, g.count, g.buf, &unmapped);
        if (rc == CDVD_E_RANGE)
            err = CDVD_ERR_POSITION;
        else if (rc != CDVD_OK)
            err = CDVD_ERR_READ;
    }
    complete(err);
}

void cdvd_drive_wait(void) {
    while (g.busy) {
        uint64_t due = g.due;
        if (g.wait)
            g.wait(g.wait_ctx, due);
        else
            cdvd_poll(due); /* no kernel: jump the drive's clock */
    }
}
