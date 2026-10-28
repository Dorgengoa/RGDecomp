/* SPDX-License-Identifier: CC0-1.0 */
/* CDVD model: serves PS2 disc sector reads from the extracted data/ folder.
 *
 * Two parts:
 *   - the disc (cdvd_disc_*): data/MANIFEST.tsv turned into a map from a disc sector
 *     number (LSN, as libcdvd reports and accepts it) to (file, byte offset), plus
 *     file lookup by ISO path and layer;
 *   - the drive (cdvd_drive_*, cdvd_poll): one asynchronous N-command at a time (read or
 *     seek) that completes on a virtual clock the EE kernel advances with cdvd_poll().
 *
 * Layer-1 addressing (docs/CDVD.md): on a dual-layer PS2 DVD, CDVDMAN reports
 * layer1_start = L (the number of layer-0 sectors, sceCdReadDvdDualInfo), returns
 * L + r for a layer-1 file whose ISO extent is r, and subtracts 16 from every LSN >= L
 * before it goes to the drive. The disc image is a linear dump of the drive's sectors, so
 * image sector = LSN for LSN < L and LSN - 16 for LSN >= L.
 *
 * Not thread-safe: the EE runs one thread at a time (PLAN.md P2), and all calls come
 * from it. */
#ifndef RG_PS2_CDVD_H
#define RG_PS2_CDVD_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CDVD_SECTOR 2048u
/* Sectors of a layer-1 ISO volume that precede its PVD and do not exist on layer 1
 * (CDVDMAN's sceCdLsnDualChg subtracts this for LSNs >= layer1_start). */
#define CDVD_L1_SYSTEM_AREA 16u
#define CDVD_NO_LSN 0xFFFFFFFFu

/* ---- logging (shared by the disc and the drive) ---- */
enum { CDVD_LOG_INFO = 0, CDVD_LOG_WARN = 1, CDVD_LOG_ERROR = 2 };
typedef void (*cdvd_log_fn)(void *ctx, int level, const char *msg);
/* NULL restores the default (stderr). */
void cdvd_set_log(cdvd_log_fn fn, void *ctx);
void cdvd_log(int level, const char *fmt, ...);

/* ---- the disc ---- */
typedef struct cdvd_disc cdvd_disc;

/* cdvd_read() results. */
enum {
    CDVD_OK = 0,
    CDVD_E_RANGE = -1, /* LSN range runs past the end of the disc; nothing read */
    CDVD_E_IO = -2,    /* a data/ file could not be opened or read */
};

typedef struct cdvd_file_info {
    const char *path;   /* manifest path, "BIN/NORMAL.BIN" */
    uint64_t size;      /* bytes */
    uint32_t lsn[2];    /* LSN of the copy on layer 0 / layer 1, CDVD_NO_LSN if none */
    uint32_t image[2];  /* the same copies as image sectors (the manifest's numbers) */
} cdvd_file_info;

/* Opens <data_dir>/MANIFEST.tsv (v1 or v2). Returns NULL with a message in err. */
cdvd_disc *cdvd_disc_open(const char *data_dir, char *err, size_t errlen);
void cdvd_disc_close(cdvd_disc *d);

int cdvd_disc_dual(const cdvd_disc *d);              /* 1 on a dual-layer disc */
uint32_t cdvd_disc_layer1_start(const cdvd_disc *d); /* LSN of layer 1 (0 if single) */
uint32_t cdvd_disc_lsn_end(const cdvd_disc *d);      /* first LSN past the disc */
uint32_t cdvd_disc_image_sectors(const cdvd_disc *d);

/* LSN <-> image sector (the layer-1 rule above). image_to_lsn needs the layer because
 * the 16 sectors before the layer-1 PVD are reachable both ways. */
uint32_t cdvd_lsn_to_image(const cdvd_disc *d, uint32_t lsn);
uint32_t cdvd_image_to_lsn(const cdvd_disc *d, uint32_t image, int layer);

size_t cdvd_disc_file_count(const cdvd_disc *d);
int cdvd_disc_file(const cdvd_disc *d, size_t i, cdvd_file_info *out);

/* Finds an ISO path on one layer, as sceCdLayerSearchFile does. Accepts the game's
 * spelling ("\\BIN\\NORMAL.BIN;1", with or without "cdrom0:") and "BIN/NORMAL.BIN";
 * case-insensitive. Returns 1 and fills out, or 0. */
int cdvd_disc_find(const cdvd_disc *d, const char *name, int layer, cdvd_file_info *out);

/* Maps one LSN to (file, byte offset of the sector in it). Returns 1, or 0 for a sector
 * that is in no file (directories, volume descriptors, gaps) or past the end. */
int cdvd_disc_map(const cdvd_disc *d, uint32_t lsn, const char **path, uint64_t *offset);

/* Reads `count` 2048-byte sectors starting at `lsn` into buf. Bytes past the end of a
 * file in its last sector, and sectors in no file, read as zero; the latter are counted
 * in *unmapped (may be NULL) and logged as a warning. */
int cdvd_disc_read(cdvd_disc *d, uint32_t lsn, uint32_t count, void *buf, uint32_t *unmapped);
/* Measurement only (RG_AUDIO_LOG, docs/SOUND.md "Load-screen audio"): with a
 * clock installed, cdvd_disc_read adds its wall time to the counters.  The
 * counters never feed back into the model. */
typedef struct cdvd_io_stats {
    uint64_t reads, sectors, wall_ns;
} cdvd_io_stats;
void cdvd_set_io_clock(uint64_t (*now_ns)(void)); /* NULL = off (default) */
void cdvd_get_io_stats(cdvd_io_stats *out);

/* ---- the drive ---- */

/* N-command function codes, as passed to the completion callback (libcdvd SCECdFunc*). */
enum { CDVD_FUNC_READ = 1, CDVD_FUNC_SEEK = 4 };
/* Drive error codes (the values libcdvd's sceCdGetError reports). */
enum {
    CDVD_ERR_NONE = 0x00,
    CDVD_ERR_ABORT = 0x01,
    CDVD_ERR_NODISC = 0x12,
    CDVD_ERR_POSITION = 0x20, /* illegal LSN */
    CDVD_ERR_PARAM = 0x22,
    CDVD_ERR_READ = 0x30,
};

typedef struct cdvd_timing {
    uint32_t command_us; /* fixed cost of each N-command */
    uint32_t sector_us;  /* per 2048-byte sector read */
} cdvd_timing;

/* Called from cdvd_poll() when an N-command completes (func = CDVD_FUNC_*). */
typedef void (*cdvd_done_fn)(void *ctx, int func, int error);
/* Called by cdvd_drive_wait() while a command is pending. It must not return before
 * cdvd_poll() has been called with a time >= due (the EE kernel blocks the calling
 * thread and runs others until then). With no hook installed, the drive advances its
 * own clock to `due` and completes the command at once. */
typedef void (*cdvd_wait_fn)(void *ctx, uint64_t due);

/* Inserts a disc (NULL = tray empty) and resets the drive. The drive does not own it. */
void cdvd_drive_reset(cdvd_disc *disc);
cdvd_disc *cdvd_drive_disc(void);
void cdvd_drive_set_timing(const cdvd_timing *t); /* NULL = defaults */
void cdvd_drive_set_done(cdvd_done_fn fn, void *ctx);
void cdvd_drive_set_wait_hook(cdvd_wait_fn fn, void *ctx);

/* Start an N-command. Return 1 if accepted, 0 if another is still pending (the
 * request is dropped, as on hardware). A rejected parameter is accepted and completes
 * with an error, like the real drive. Data is written into buf at completion. */
int cdvd_drive_read(uint32_t lsn, uint32_t count, void *buf);
int cdvd_drive_seek(uint32_t lsn);
/* Abort the pending command (it completes with CDVD_ERR_ABORT, no data). */
void cdvd_drive_break(void);

int cdvd_drive_busy(void);
int cdvd_drive_error(void);   /* error of the last completed N-command */
void cdvd_drive_wait(void);   /* returns when no command is pending */

/* The completion hook for the EE kernel: advance the drive's clock to now_us (virtual
 * microseconds; it never goes backwards) and complete what is due. */
void cdvd_poll(uint64_t now_us);
/* 1 and *due if a command is pending (the time the kernel should next poll at). */
int cdvd_next_event(uint64_t *due);
uint64_t cdvd_now(void);
/* Set the drive's clock (virtual microseconds), e.g. 0 when a new kernel run starts.
 * A pending command keeps its due time. */
void cdvd_drive_set_clock(uint64_t now_us);

#ifdef __cplusplus
}
#endif
#endif
