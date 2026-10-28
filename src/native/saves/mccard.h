/* SPDX-License-Identifier: CC0-1.0 */
/* PS2 memory card model backed by a host directory per slot (docs/PADMC.md,
 * docs/SAVES.md).
 *
 *   <root>/card<N>/            the card in slot N (1, 2): PS2 directories and files
 *                              are plain host directories and files (icon.sys, *.ico,
 *                              the save file), names %XX-escaped where the host
 *                              cannot hold them
 *   <root>/card<N>.card        metadata: formatted flag, per-entry attributes,
 *                              creation/modification times, creation order
 *   <root>/card<N>.txt         generated index: one line per save directory with
 *                              its icon.sys title (read-only, for people)
 *   <root>/backups/card<N>/<save dir>/<stamp>/
 *                              automatic copies of a save directory taken before
 *                              the game first changes it (backup_keep newest kept)
 *
 * Host writes are crash-safe: a file opened for writing is buffered and replaces the
 * host file atomically (temp file + rename) on sceMcFlush / sceMcClose; metadata and
 * the index are written the same way. A killed process never leaves a half-written
 * file; `durable` extends that to power loss. Older layouts (<root>/slot0, slot1) are moved
 * to card1 / card2 on load.
 *
 * What the game can observe follows the PS2 card: type 2 (PS2), an 8 MB card of
 * 1 KB clusters (free space accounting below), formatted / unformatted state,
 * directory entries with the sceMcTblGetDir stat/attr/time fields, listing in
 * creation order with "." and "..", wildcard (* ?) GetDir patterns, and the libmc
 * error codes. Kernel-agnostic and synchronous.
 *
 * This is the native save service (docs/NATIVE-IOP.md): libmc calls it directly in
 * RG_IOP=native (the default); the mcserv HLE (src/ps2/padmc/mcserv.c, the RG_IOP=hle
 * oracle) calls the same functions from its SIF server.  The card time model below
 * (how long an operation takes on the virtual clock) is shared by both.
 */
#ifndef RG_PS2_MCCARD_H
#define RG_PS2_MCCARD_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MC_PORTS    2
#define MC_PATH_MAX 1024
#define MC_NAME_MAX 32 /* including the NUL */

/* libmc / mcman result codes */
#define MC_RES_SUCCEED       0
#define MC_RES_CHANGEDCARD  (-1)
#define MC_RES_NOFORMAT     (-2)
#define MC_RES_FULLDEVICE   (-3)
#define MC_RES_NOENTRY      (-4)
#define MC_RES_DENIEDPERMIT (-5)
#define MC_RES_NOTEMPTY     (-6)
#define MC_RES_UPLIMITHANDLE (-7)
#define MC_RES_FAILREPLACE  (-8)
/* No card in the slot. The game (McGetInfoStep_375640) treats result < -10 as
 * "no card"; -12 is mcman's detect failure. Unverified against a trace. */
#define MC_RES_NOCARD       (-12)

/* card types (sceMcGetInfo *type) */
#define MC_TYPE_NONE 0
#define MC_TYPE_PS1  1
#define MC_TYPE_PS2  2

/* open modes */
#define MC_O_RDONLY 0x0001
#define MC_O_WRONLY 0x0002
#define MC_O_RDWR   0x0003
#define MC_O_MKDIR  0x0040 /* sceMcMkdir = sceMcOpen(.., 0x40) */
#define MC_O_CREAT  0x0200
#define MC_O_TRUNC  0x0400
#define MC_O_EXCL   0x0800

/* attributes (sceMcFileAttr*) */
#define MC_ATTR_READABLE   0x0001
#define MC_ATTR_WRITEABLE  0x0002
#define MC_ATTR_EXECUTABLE 0x0004
#define MC_ATTR_DUPPROHIBIT 0x0008
#define MC_ATTR_FILE       0x0010
#define MC_ATTR_SUBDIR     0x0020
#define MC_ATTR_CLOSED     0x0080
#define MC_ATTR_0400       0x0400
#define MC_ATTR_PDAEXEC    0x0800
#define MC_ATTR_PS1        0x1000
#define MC_ATTR_HIDDEN     0x2000
#define MC_ATTR_EXISTS     0x8000
#define MC_ATTR_DEFAULT_FILE 0x8497u
#define MC_ATTR_DEFAULT_DIR  0x8427u
#define MC_ATTR_USER_MASK (MC_ATTR_READABLE | MC_ATTR_WRITEABLE | MC_ATTR_EXECUTABLE | \
                           MC_ATTR_DUPPROHIBIT | MC_ATTR_PDAEXEC | MC_ATTR_PS1 | MC_ATTR_HIDDEN)

/* SetFileInfo flags */
#define MC_INFO_CTIME 0x01
#define MC_INFO_MTIME 0x02
#define MC_INFO_ATTR  0x04
#define MC_INFO_NAME  0x10

typedef struct mc_datetime { /* sceMcStDateTime */
    uint8_t resv, sec, min, hour, day, month;
    uint16_t year;
} mc_datetime;

typedef struct mc_dirent { /* sceMcTblGetDir, 64 bytes */
    mc_datetime created;   /* 0x00 */
    mc_datetime modified;  /* 0x08 */
    uint32_t size;         /* 0x10 files: bytes; directories: entry count incl. . and .. */
    uint16_t attr;         /* 0x14 */
    uint16_t resv1;        /* 0x16 */
    uint32_t resv2;        /* 0x18 */
    uint32_t pda_apl_no;   /* 0x1C */
    char name[MC_NAME_MAX];/* 0x20 */
} mc_dirent;

/* Slot policies (what is in the slot at start-up) */
enum {
    MC_SLOT_AUTO = 0,     /* card present; created formatted and empty if the host dir is missing */
    MC_SLOT_IF_EXISTS,    /* card present only if the host dir exists */
    MC_SLOT_EMPTY,        /* no card */
    MC_SLOT_UNFORMATTED   /* card present; created unformatted if missing */
};

typedef void (*mc_clock_fn)(void *user, mc_datetime *out);

typedef struct mccard_config {
    const char *root;        /* NULL -> env RG_SAVES, else "saves" */
    int slot_policy[MC_PORTS]; /* default {AUTO, IF_EXISTS} */
    uint32_t free_clusters;  /* free 1 KB clusters on an empty formatted card (default 8000) */
    int max_fds;             /* open file limit (default 16) */
    mc_clock_fn clock;       /* timestamps; NULL -> fixed 2006-01-31 12:00:00 */
    void *clock_user;
    int backup_keep;         /* backups kept per save directory (default 5; < 0 = none) */
    const char *backup_root; /* NULL -> <root>/backups */
    int durable;             /* 1: force each committed save file to the disk before the
                              * rename (power-loss safe; slow on HDDs). Env RG_MC_DURABLE */
} mccard_config;

void mccard_default_config(mccard_config *c);
/* (Re)load both slots from the host directory. Closes every open file first.
 * Env RG_MC_SLOT1 / RG_MC_SLOT2 = auto | ifexists | none | unformatted override the
 * slot policies (a host can run the game with no card or an unformatted one). */
int mccard_init(const mccard_config *c);
void mccard_shutdown(void); /* close files, flush metadata */
int mccard_inited(void);
const mccard_config *mccard_get_config(void);
const char *mccard_root(void);

/* hot-plug (tests / host UI). Ejecting drops writes not yet flushed or closed (the
 * host files keep their last committed contents); descriptors open on the card then
 * fail with MC_RES_NOCARD until closed. */
int mccard_insert(int port, int policy); /* load the slot dir (created per policy) */
void mccard_eject(int port);
/* Fault injection (tests, host "pull the card" UI): the `after`-th card operation on
 * `port` from now (1 = the next one) fails with `result` instead of running.
 * MC_RES_NOCARD also ejects the card at that moment, as pulling it mid-save does.
 * after <= 0 disarms. */
void mccard_inject_fault(int port, int after, int result);
int mccard_present(int port);
int mccard_formatted(int port);
uint32_t mccard_free(int port);  /* free clusters (0 if no card / unformatted) */

/* ---- card operations: >= 0 success, MC_RES_* on error -------------------------- */
int mccard_getinfo(int port, int *type, int *free_clusters, int *format);
int mccard_open(int port, const char *path, int mode); /* fd, or 0 for MC_O_MKDIR */
int mccard_close(int fd);
int mccard_seek(int fd, int32_t offset, int whence);   /* 0 SET, 1 CUR, 2 END -> new pos */
int mccard_read(int fd, void *dst, int size);
int mccard_write(int fd, const void *src, int size);
int mccard_flush(int fd);
int mccard_chdir(int port, const char *path, char *prev_out /* MC_PATH_MAX or NULL */);
/* cont == 0 starts a listing of `path` (last component may hold * ?); cont != 0
 * continues the previous listing of that port. Returns the number of entries written. */
int mccard_getdir(int port, const char *path, int cont, int maxent, mc_dirent *out);
int mccard_setinfo(int port, const char *path, const mc_dirent *info, unsigned flags);
int mccard_delete(int port, const char *path);
int mccard_format(int port);
int mccard_unformat(int port);
int mccard_entspace(int port, const char *path);
int mccard_open_count(void);

/* ---- card time: virtual bus cycles an operation takes (docs/PADMC.md "Timing") ---- */
typedef struct mc_time_config {
    uint64_t op_cycles;           /* every operation (default 1 ms) */
    uint64_t read_cycles_per_kb;  /* default 2.5 ms per KB (~400 KB/s) */
    uint64_t write_cycles_per_kb; /* default 6 ms per KB (~170 KB/s) */
    uint64_t format_cycles;       /* default 2 s */
} mc_time_config;
void mc_time_default_config(mc_time_config *c);
void mc_time_configure(const mc_time_config *c); /* NULL = defaults */
const mc_time_config *mc_time_get_config(void);
/* Operations (numbered as retail libmc's RPC function numbers). */
enum {
    MC_OP_GETINFO = 0x01, MC_OP_OPEN = 0x02, MC_OP_CLOSE = 0x03, MC_OP_SEEK = 0x04,
    MC_OP_READ = 0x05, MC_OP_WRITE = 0x06, MC_OP_FLUSH = 0x0A, MC_OP_CHDIR = 0x0C,
    MC_OP_GETDIR = 0x0D, MC_OP_SETINFO = 0x0E, MC_OP_DELETE = 0x0F, MC_OP_FORMAT = 0x10,
    MC_OP_UNFORMAT = 0x11, MC_OP_ENTSPACE = 0x12, MC_OP_SLOTMAX = 0x15, MC_OP_INIT = 0xFE
};
/* Cost of `op` that returned `result` (bytes for READ / WRITE). */
uint64_t mc_time_cost(int op, int result);

/* host path of a card path (tests / tools); 0 ok */
int mccard_host_path(int port, const char *card_path, char *out, int outlen);
/* host directory holding the backups of one save directory (`top` = "/NAME"); 0 ok */
int mccard_backup_dir(int port, const char *top, char *out, int outlen);
/* number of backups currently kept for `top` */
int mccard_backup_count(int port, const char *top);
/* cumulative host I/O done by the card (diagnostics: RG_MC_TRACE in libmc.c) */
typedef struct mccard_io_stats {
    uint32_t files_written; /* atomic temp+rename writes (save files, metadata, index) */
    uint32_t bytes_written;
    uint32_t files_read;    /* whole-file reads (icon.sys titles, backup copies) */
    uint32_t meta_saves;    /* card metadata + index rewrites */
    uint32_t backups;       /* save-directory snapshots taken */
} mccard_io_stats;
void mccard_get_io_stats(mccard_io_stats *out);
/* host name of the per-slot card directory: "card1" / "card2" */
const char *mccard_slot_name(int port);

#ifdef __cplusplus
}
#endif
#endif
