/* SPDX-License-Identifier: CC0-1.0 */
/* mcserv HLE: the IOP memory card RPC server (MCSERV.IRX 2.16 over MCMAN 2.38) on
 * SIF id 0x80000400, backed by mccard.c. docs/PADMC.md.
 *
 * The request/reply layouts are the port's own (the EE libmc in src/sce/padmc is a
 * reimplementation, see docs/SIF.md "Open issues"); the function numbers follow
 * retail libmc (census/platform_sif_rpc.tsv). Each reply carries the virtual time
 * the operation takes on the card (`cost`); the EE side completes the call that
 * much later on the virtual clock. */
#ifndef RG_PS2_MCSERV_H
#define RG_PS2_MCSERV_H
#include <stdint.h>

#include "mccard.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MCSERV_SID 0x80000400u

enum {
    MCSERV_FNO_GETINFO = 0x01,
    MCSERV_FNO_OPEN = 0x02,
    MCSERV_FNO_CLOSE = 0x03,
    MCSERV_FNO_SEEK = 0x04,
    MCSERV_FNO_READ = 0x05,
    MCSERV_FNO_WRITE = 0x06,
    MCSERV_FNO_FLUSH = 0x0A,
    MCSERV_FNO_CHDIR = 0x0C,
    MCSERV_FNO_GETDIR = 0x0D,
    MCSERV_FNO_SETINFO = 0x0E, /* also rename (flags MC_INFO_NAME) */
    MCSERV_FNO_DELETE = 0x0F,
    MCSERV_FNO_FORMAT = 0x10,
    MCSERV_FNO_UNFORMAT = 0x11,
    MCSERV_FNO_ENTSPACE = 0x12,
    MCSERV_FNO_SLOTMAX = 0x15,
    MCSERV_FNO_INIT = 0xFE
};

#define MCSERV_VERSION 0x0210 /* 2.16: libmc wants >= 0x20A */
#define MCMAN_VERSION  0x0226 /* 2.38: libmc wants >= 0x20E */

typedef struct mcserv_req {
    int32_t port, slot;
    int32_t a, b, c;   /* mode | fd | size | offset | whence | maxent | flags | cont */
    uint32_t ee_buf;   /* EE address: data / sceMcTblGetDir table / SetFileInfo struct */
    char name[MC_PATH_MAX];
    char name2[MC_NAME_MAX];
} mcserv_req;

typedef struct mcserv_rep {
    int32_t result;
    uint32_t cost;     /* virtual bus cycles the operation takes */
    int32_t r1, r2, r3; /* GETINFO: type, free, format; INIT: mcserv, mcman versions */
    char path[MC_PATH_MAX]; /* CHDIR: the previous current directory */
} mcserv_rep;
#define MCSERV_REP_SHORT 20 /* reply bytes without `path` */

/* The card time model is the native save service's (mccard.h mc_time_*): these are
 * the same configuration under the HLE's names. */
typedef mc_time_config mcserv_config;
void mcserv_default_config(mcserv_config *c);
void mcserv_configure(const mcserv_config *c); /* NULL = defaults */
const mcserv_config *mcserv_get_config(void);

/* Register 0x80000400 (replaces the src/ps2/iop placeholder). 0 ok. */
int mcserv_install(void);
int mcserv_installed(void);
uint32_t mcserv_calls(uint32_t fno);

/* The server function itself (tests drive it without the SIF). */
void mcserv_handle(uint32_t fno, const mcserv_req *rq, mcserv_rep *rp);

#ifdef __cplusplus
}
#endif
#endif
