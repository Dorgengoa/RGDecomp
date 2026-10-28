/* SPDX-License-Identifier: CC0-1.0 */
/* IOP model for the HLE (PLAN.md D4, docs/SIF.md).
 *
 * There is no R3000 here. The IOP is:
 *   - 2 MiB of addressable RAM (sound banks, stream slots, movie audio and RPC
 *     server buffers live in it; the EE writes it by SIF1 DMA),
 *   - a sysmem-style heap over that RAM (sceSifAllocIopHeap),
 *   - a log of the modules the game asks to load and of IOP reboots,
 *   - host C "servers" registered by SIF RPC id (src/ps2/sif/sif.h), installed by
 *     iop_hle_install() (iop_hle.c).
 *
 * IOP addresses are 32-bit. KSEG0/KSEG1 aliases (0x80000000, 0xA0000000, and the
 * 0xBC000000 IOP-RAM mirror) are folded to the physical address. Single host thread:
 * nothing here locks. */
#ifndef RG_PS2_IOP_H
#define RG_PS2_IOP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOP_RAM_SIZE 0x200000u /* 2 MiB */

/* ---- RAM ---------------------------------------------------------------- */
uint8_t *iop_ram(void);                       /* base of the 2 MiB array */
uint32_t iop_phys(uint32_t addr);             /* fold KSEG/mirror aliases */
/* Host pointer to [addr, addr+len) or NULL (and a report) if it leaves RAM. */
void *iop_ptr(uint32_t addr, uint32_t len);
int iop_write(uint32_t addr, const void *src, uint32_t len); /* 0 ok, -1 range */
int iop_read(uint32_t addr, void *dst, uint32_t len);
uint32_t iop_addr_of(const void *host_ptr); /* inverse of iop_ptr; 0xFFFFFFFF if outside */
void iop_ram_clear(void);
/* Time source for the logs (the SIF layer installs its clock). NULL -> always 0. */
void iop_set_clock(uint64_t (*now)(void));
/* Out-of-range / bad-address reports go here (default: stderr). */
void iop_set_report(void (*fn)(const char *msg));
uint32_t iop_report_count(void);

/* ---- heap (sysmem AllocSysMemory / FreeSysMemory semantics) ------------- */
/* Blocks are 256-byte aligned (sysmem granularity). Default arena
 * [IOP_HEAP_BASE, IOP_HEAP_END); the region below it holds HLE server buffers
 * (iop_static_alloc), modelling the space the real modules occupy. */
#define IOP_STATIC_BASE 0x00010000u
#define IOP_HEAP_BASE   0x000C0000u
#define IOP_HEAP_END    0x001F0000u
void iop_heap_reset(void);
uint32_t iop_heap_alloc(uint32_t size); /* IOP address, 0 on failure */
int iop_heap_free(uint32_t addr);       /* 0 ok, -1 not an allocated block */
uint32_t iop_heap_free_total(void);
uint32_t iop_heap_max_free(void);
uint32_t iop_heap_block_size(uint32_t addr); /* 0 if not allocated */
int iop_heap_count(void);                   /* live blocks */
/* Bump allocator below the heap for server buffers; survives iop_heap_reset,
 * cleared by iop_reset(). 64-byte aligned. 0 on failure. */
uint32_t iop_static_alloc(uint32_t size);

/* ---- modules and reboots ------------------------------------------------ */
#define IOP_MOD_MAX 64
typedef struct iop_module_rec {
    int id;             /* > 0, assigned in load order since the last reboot */
    char path[256];     /* as the game passed it */
    char name[32];      /* upper-case base name without extension/version, "SDRDRV" */
    char args[256];     /* argument block, NULs turned into '|' */
    int argsz;
    int known;          /* 1 = the HLE provides this module's services (or needs none) */
    const char *hle;    /* what stands in for it ("fileio", "placeholder", ...) */
    uint64_t when;      /* SIF clock at load */
} iop_module_rec;

typedef struct iop_reboot_rec {
    char image[256];    /* "" = plain reset */
    uint64_t when;
} iop_reboot_rec;

/* Clears RAM, heap, static area, module list. Does not touch the reboot log. */
void iop_reset(void);
/* Record an IOP reboot (sceSifRebootIop / sceSifResetIop): iop_reset() plus a log entry. */
void iop_reboot(const char *image);
/* Record a module load. Returns the module id (> 0), or -1 if the table is full. */
int iop_module_load(const char *path, const char *args, int argsz);
int iop_module_count(void);
const iop_module_rec *iop_module_get(int index); /* 0-based, NULL past the end */
const iop_module_rec *iop_module_find(const char *name);
int iop_reboot_count(void);
const iop_reboot_rec *iop_reboot_get(int index);
void iop_log_clear(void); /* forget modules and reboots */
/* Print the module table ("what the game loads") to a FILE*; f == NULL -> stderr. */
void iop_module_dump(void *file);

/* ---- HLE servers (iop_hle.c) -------------------------------------------- */
typedef struct iop_hle_config {
    /* Host directory that "cdrom0:\" resolves to for FILEIO opens (the extracted
     * data/ folder, PLAN D8). NULL -> env RG_DATA, else "data". */
    const char *cdrom_root;
    /* Host directory for "host0:"/"host:" paths and writes. NULL -> cdrom_root. */
    const char *host_root;
    int install_sound_placeholders; /* sdr_driver 0x80000701 + pcm_mixer 0x123456 */
} iop_hle_config;

void iop_hle_default_config(iop_hle_config *cfg);
/* Register every HLE server (FILEIO, iopheap, LOADFILE, padman, mcserv and,
 * unless disabled, the sound placeholders). Safe to call again (re-registers). */
int iop_hle_install(const iop_hle_config *cfg);
/* Boot-time installer for the full HLE modules that live outside src/ps2/iop
 * (padman/mcserv in src/ps2/padmc, sound in src/ps2/iop/sound): called at the
 * end of every iop_hle_install, so the real servers replace the placeholders
 * from boot instead of from the game's first Init (src/runtime sets it).
 * NULL removes it. */
typedef void (*iop_hle_post_install_fn)(void *user);
void iop_hle_set_post_install(iop_hle_post_install_fn fn, void *user);

/* Individual servers (iop_srv_*.c). Each returns 0 on success. */
int iop_srv_fileio_install(const char *cdrom_root, const char *host_root); /* 0x80000001 */
int iop_srv_iopheap_install(void);                                         /* 0x80000003 */
int iop_srv_loadfile_install(void);                                        /* 0x80000006 */
int iop_srv_padman_install(void);                                          /* 0x80000100/101 */
int iop_srv_mcserv_install(void);                                          /* 0x80000400 */
int iop_srv_sound_placeholders_install(void);                              /* 0x80000701, 0x123456 */

/* FILEIO packet layout between src/sce/sif/fileio.c and the FILEIO server. This is
 * the port's own layout (both ends are host code); the retail packets differ. */
enum {
    IOP_FIO_OPEN = 0, IOP_FIO_CLOSE = 1, IOP_FIO_READ = 2, IOP_FIO_WRITE = 3,
    IOP_FIO_LSEEK = 4, IOP_FIO_INIT = 0xFF
};
typedef struct iop_fio_req {
    int32_t fd;
    int32_t a;      /* open: flags; read/write: size; lseek: offset */
    int32_t b;      /* open: mode;  lseek: whence */
    uint32_t ee_buf;/* read: EE destination (SIF0 target); write: EE source */
    char name[1024 - 16];
} iop_fio_req;

/* Calls logged by the placeholder servers (padman, mcserv, sound). */
typedef struct iop_placeholder_stats {
    uint32_t calls;
    uint32_t last_sid;
    uint32_t last_fno;
} iop_placeholder_stats;
const iop_placeholder_stats *iop_placeholder_get_stats(void);

#ifdef __cplusplus
}
#endif
#endif
