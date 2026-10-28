/* SPDX-License-Identifier: CC0-1.0 */
/* HLE IOP servers registered with the SIF core: FILEIO (0x80000001), iopheap
 * (0x80000003), LOADFILE (0x80000006), and logging placeholders for padman
 * (0x80000100/101), mcserv (0x80000400), sdr_driver (0x80000701) and pcm_mixer
 * (0x123456). Request layouts are the port's own (both ends are host code), see
 * iop.h and docs/SIF.md. */
#include "iop.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sif.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */
#include "rg_iop_fio.h" /* host files of FILEIO (native service, shared) */

/* ---- iopheap 0x80000003 -------------------------------------------------- */
static uint32_t g_word_reply[4];

static void *srv_iopheap(sif_rpc_ctx *c, void *user)
{
    (void)user;
    const uint32_t *in = (const uint32_t *)c->data;
    uint32_t a0 = c->size >= 4 ? in[0] : 0;
    memset(g_word_reply, 0, sizeof g_word_reply);
    switch (c->fno) {
    case 1: g_word_reply[0] = iop_heap_alloc(a0); break;                    /* AllocIopHeap(size) */
    case 2: g_word_reply[0] = (uint32_t)iop_heap_free(a0); break;           /* FreeIopHeap(addr) */
    case 4: g_word_reply[0] = iop_heap_alloc(a0); break;                    /* AllocSysMemory */
    case 5: g_word_reply[0] = IOP_RAM_SIZE; break;                          /* QueryMemSize */
    case 6: g_word_reply[0] = iop_heap_max_free(); break;                   /* QueryMaxFreeMemSize */
    case 7: g_word_reply[0] = iop_heap_free_total(); break;                 /* QueryTotalFreeMemSize */
    case 9: g_word_reply[0] = iop_heap_block_size(a0); break;               /* QueryBlockSize */
    default: c->unknown = 1; return NULL;
    }
    return g_word_reply;
}

int iop_srv_iopheap_install(void) { return sif_server_register(0x80000003u, "iopheap", 0x40, srv_iopheap, NULL); }

/* ---- LOADFILE 0x80000006 ------------------------------------------------- */
/* fno 0 request: { s32 argsz; char path[252]; char args[252]; } -> reply { s32 id; s32 result } */
static void *srv_loadfile(sif_rpc_ctx *c, void *user)
{
    (void)user;
    memset(g_word_reply, 0, sizeof g_word_reply);
    switch (c->fno) {
    case 0: {
        const uint8_t *p = (const uint8_t *)c->data;
        int32_t argsz;
        char path[253], args[253];
        memcpy(&argsz, p, 4);
        memcpy(path, p + 4, 252);
        path[252] = 0;
        memcpy(args, p + 256, 252);
        args[252] = 0;
        if (argsz > 252)
            argsz = 252;
        int id = iop_module_load(path, args, argsz);
        g_word_reply[0] = (uint32_t)id;
        g_word_reply[1] = 0; /* module start result: RESIDENT_END */
        break;
    }
    case 0xFF: break; /* bind/init */
    default: c->unknown = 1; return NULL;
    }
    return g_word_reply;
}

int iop_srv_loadfile_install(void) { return sif_server_register(0x80000006u, "loadfile", 0x200, srv_loadfile, NULL); }

/* ---- FILEIO 0x80000001 --------------------------------------------------- */
/* The device mapping and the stdio calls are the native fileio service's
 * (src/native/iop/rg_iop_fio.c, docs/NATIVE-IOP.md); this server is only the
 * transport: request decoding and the SIF0 write of read data into the EE buffer. */
static void *srv_fileio(sif_rpc_ctx *c, void *user)
{
    (void)user;
    iop_fio_req *r = (iop_fio_req *)c->data;
    int32_t res = -EINVAL;
    memset(g_word_reply, 0, sizeof g_word_reply);
    switch (c->fno) {
    case IOP_FIO_INIT: res = 0; break;
    case IOP_FIO_OPEN:
        r->name[sizeof r->name - 1] = 0;
        res = rg_fio_open(r->name, r->a);
        break;
    case IOP_FIO_CLOSE: res = rg_fio_close(r->fd); break;
    case IOP_FIO_READ: {
        int32_t want = r->a > 0 ? r->a : 0;
        uint8_t tmp[16384];
        uint8_t *dst = (uint8_t *)(uintptr_t)r->ee_buf;
        res = rg_fio_read(r->fd, tmp, 0); /* -EBADF check */
        while (res >= 0 && want > 0) {
            int chunk = want < (int32_t)sizeof tmp ? want : (int32_t)sizeof tmp;
            int got = rg_fio_read(r->fd, tmp, chunk);
            if (got <= 0)
                break;
            sif0_write(dst + res, tmp, (uint32_t)got); /* IOP -> EE buffer */
            res += got;
            want -= got;
            if (got < chunk)
                break;
        }
        break;
    }
    case IOP_FIO_WRITE: res = rg_fio_write(r->fd, (const void *)(uintptr_t)r->ee_buf, r->a); break;
    case IOP_FIO_LSEEK: res = rg_fio_lseek(r->fd, r->a, r->b); break;
    default: c->unknown = 1; return NULL;
    }
    g_word_reply[0] = (uint32_t)res;
    return g_word_reply;
}

int iop_srv_fileio_install(const char *cdrom_root, const char *host_root)
{
    rg_fio_set_roots(cdrom_root, host_root);
    return sif_server_register(0x80000001u, "fileio", (uint32_t)sizeof(iop_fio_req), srv_fileio, NULL);
}

/* ---- placeholders ------------------------------------------------------------ */
static iop_placeholder_stats g_ph;
static uint8_t g_ph_reply[0x400];
#define PH_SEEN 128
static struct { uint32_t sid, fno; } g_seen[PH_SEEN];
static int g_nseen;

const iop_placeholder_stats *iop_placeholder_get_stats(void) { return &g_ph; }

static void *srv_placeholder(sif_rpc_ctx *c, void *user)
{
    const char *name = (const char *)user;
    g_ph.calls++;
    g_ph.last_sid = c->sid;
    g_ph.last_fno = c->fno;
    int seen = 0;
    for (int i = 0; i < g_nseen; i++)
        if (g_seen[i].sid == c->sid && g_seen[i].fno == c->fno)
            seen = 1;
    if (!seen) {
        if (g_nseen < PH_SEEN) {
            g_seen[g_nseen].sid = c->sid;
            g_seen[g_nseen].fno = c->fno;
            g_nseen++;
        }
        const uint32_t *w = (const uint32_t *)c->data;
        if (getenv("RG_IOP_QUIET") == NULL)
            fprintf(stderr, "[iop] placeholder %s sid=0x%08X fno=0x%X size=0x%X w0..3=%08X %08X %08X %08X (first call)\n",
                    name, c->sid, c->fno, c->size, c->size >= 4 ? w[0] : 0, c->size >= 8 ? w[1] : 0,
                    c->size >= 12 ? w[2] : 0, c->size >= 16 ? w[3] : 0);
    }
    memset(g_ph_reply, 0, sizeof g_ph_reply);
    return c->rsize <= sizeof g_ph_reply ? g_ph_reply : NULL;
}

int iop_srv_padman_install(void)
{
    int r = sif_server_register(0x80000100u, "padman", 0x80, srv_placeholder, (void *)"padman");
    r |= sif_server_register(0x80000101u, "padman-ext", 0x80, srv_placeholder, (void *)"padman-ext");
    return r;
}

int iop_srv_mcserv_install(void)
{
    return sif_server_register(0x80000400u, "mcserv", 0x400, srv_placeholder, (void *)"mcserv");
}

int iop_srv_sound_placeholders_install(void)
{
    int r = sif_server_register(0x80000701u, "sdr_driver", 0x400, srv_placeholder, (void *)"sdr_driver");
    r |= sif_server_register(0x00123456u, "pcm_mixer", 0x400, srv_placeholder, (void *)"pcm_mixer");
    return r;
}

/* ---- install ----------------------------------------------------------------- */
void iop_hle_default_config(iop_hle_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->install_sound_placeholders = 1;
}

static iop_hle_post_install_fn g_post_install;
static void *g_post_install_user;

int iop_hle_install(const iop_hle_config *cfg)
{
    RG_IOP_HLE("iop_hle_install");
    iop_hle_config d;
    if (!cfg) {
        iop_hle_default_config(&d);
        cfg = &d;
    }
    const char *root = cfg->cdrom_root;
    if (!root)
        root = getenv("RG_DATA");
    if (!root)
        root = "data";
    int r = 0;
    r |= iop_srv_fileio_install(root, cfg->host_root);
    r |= iop_srv_iopheap_install();
    r |= iop_srv_loadfile_install();
    r |= iop_srv_padman_install();
    r |= iop_srv_mcserv_install();
    if (cfg->install_sound_placeholders)
        r |= iop_srv_sound_placeholders_install();
    g_nseen = 0;
    memset(&g_ph, 0, sizeof g_ph);
    if (g_post_install)
        g_post_install(g_post_install_user);
    return r;
}

void iop_hle_set_post_install(iop_hle_post_install_fn fn, void *user)
{
    RG_IOP_HLE("iop_hle_set_post_install");
    g_post_install = fn;
    g_post_install_user = user;
}
