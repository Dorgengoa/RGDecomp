/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_fs: the native host file service (docs/NATIVE-FS.md, PLAN.md D9 "Native end
 * state": "File reads by name/offset from data/ through the host file system").
 *
 * The game opens its disc files by NAME and reads them by BYTE OFFSET.  There are
 * no sectors, no LSNs, no layers, no drive model and no simulated latency here:
 * a mount indexes the extracted folder (data/) by path, an open is a hash lookup,
 * a read is one positional host read.
 *
 *   rg_fs_mount("data");
 *   int h = rg_fs_open("cdrom0:\\DATA0_0.HD6;1");   // any game spelling
 *   rg_fs_read_fill(h, off, buf, len);               // sync
 *   int r = rg_fs_read_async(h, off, buf, len, cb, user);
 *   ... rg_fs_poll(r, &res) / rg_fs_wait(r) / rg_fs_pump();
 *
 * Names: an optional "device:" prefix is dropped, '\' becomes '/', leading '/'
 * and a trailing ";<version>" are removed, and the match ignores ASCII case.
 *
 * Async model: requests run on a host worker thread; their RESULTS become
 * visible only through rg_fs_poll / rg_fs_wait / rg_fs_pump on the caller's
 * thread, and completion callbacks run there too.  So the moment the game sees a
 * completion is decided by the game (when it polls), never by host I/O timing:
 * the game stays deterministic.
 *
 * Thread safety: every function may be called from any thread.  Callbacks and
 * read hooks run on the thread that calls the sync read / poll / wait / pump.
 */
#ifndef RG_NATIVE_FS_H
#define RG_NATIVE_FS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- mount ---- */
/* Index every regular file under data_dir (recursively; a top-level
 * "converted/" folder and MANIFEST.tsv are not game files and are skipped).
 * Replaces an earlier mount.  Returns the number of files, or -1. */
int rg_fs_mount(const char *data_dir);
void rg_fs_unmount(void);
int rg_fs_mounted(void);
const char *rg_fs_root(void);

/* ---- files ---- */
/* Handle (>= 0) of a file by game name, or -1 if there is none.  Handles stay
 * valid until unmount; opening the same file twice returns the same handle;
 * there is no close.  The host file is opened on first read. */
int rg_fs_open(const char *name);
/* rg_fs_open, or report "<who>: <name> is not in the data folder" and abort() */
int rg_fs_open_or_die(const char *name, const char *who);
int64_t rg_fs_size(int h);            /* -1 for a bad handle */
const char *rg_fs_name(int h);        /* indexed relative path ("BIN/NORMAL.BIN") */
/* Canonical form of a game name (see above) into out; returns out. */
char *rg_fs_canon(const char *name, char *out, size_t outlen);

/* Synchronous read of len bytes at byte offset off into buf.  Bytes past the end
 * of the file are zero-filled, so the whole [buf, buf+len) is always written.
 * Returns the number of bytes that came from the file (0..len), -1 on a bad
 * handle or a host I/O error (buf is then zero-filled). */
int64_t rg_fs_read_fill(int h, int64_t off, void *buf, int64_t len);

/* ---- async ---- */
typedef void (*rg_fs_done_fn)(void *user, int req, int64_t result);
/* Queue a read with rg_fs_read_fill's semantics.  Returns a request id > 0, or -1
 * (bad handle, no worker, or 256 requests in flight).  buf must stay valid until the request completes. */
int rg_fs_read_async(int h, int64_t off, void *buf, int64_t len, rg_fs_done_fn cb, void *user);
/* 1: done (result in *result if non-NULL; the callback has run; the id is
 * released), 0: still pending, -1: unknown id. */
int rg_fs_poll(int req, int64_t *result);
/* Block until the request is done; runs its callback; releases the id.
 * Returns the result (-1 also for an unknown id). */
int64_t rg_fs_wait(int req);
/* Deliver every finished request (callbacks run here); returns how many. */
int rg_fs_pump(void);
/* Requests queued or running. */
int rg_fs_pending(void);

/* ---- observers (timing record, oracle) ---- */
/* Called after each completed read (sync: inside rg_fs_read_fill; async: when
 * delivered) with the file's indexed path and the bytes now in buf. */
typedef void (*rg_fs_read_hook)(void *user, int h, const char *path, int64_t off,
                                int64_t len, int64_t got, const void *buf);
int rg_fs_add_read_hook(rg_fs_read_hook fn, void *user);    /* 0 ok, -1 table full */
void rg_fs_remove_read_hook(rg_fs_read_hook fn, void *user);

typedef struct rg_fs_stats {
    uint64_t opens, open_misses;
    uint64_t reads, async_reads, bytes, errors;
    uint64_t read_ns;      /* host time inside reads (sync + worker) */
    uint32_t files;        /* indexed */
} rg_fs_stats;
void rg_fs_get_stats(rg_fs_stats *out);

#ifdef __cplusplus
}
#endif
#endif
