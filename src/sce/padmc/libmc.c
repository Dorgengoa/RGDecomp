/* SPDX-License-Identifier: CC0-1.0 */
/* EE libmc over the mcserv HLE. See libmc.h and docs/PADMC.md.
 *
 * RG_IOP=native (the default, docs/NATIVE-IOP.md): every entry point calls the native
 * save service (src/native/saves: mccard + the card time model) directly: no mcserv
 * server, no SIF RPC, no semaphores.  What the game sees is kept: one operation in
 * flight (-200 busy until sceMcSync collects it), the issue-time error codes, the
 * function number sceMcSync reports, completion after the card time on the virtual
 * clock (polled sceMcSync charges poll_cycles), outputs of GetInfo / Chdir written at
 * completion.  The mcserv path below is the oracle (RG_IOP=hle). */
#include "libmc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libsif.h"
#include "mccard.h"
#include "mcserv.h"
#include "ps2k.h"
#include "rg_iop.h"
#include "sif.h"

static struct {
    rg_mc_config cfg;
    int cfg_set;
    int lock;  /* retail 0x449558-8: taken at issue, given back by sceMcSync */
    int done;  /* signalled by the completion (retail end function: iSignalSema) */
    int cmd;   /* function number of the operation in flight, 0 = none */
    sceSifClientData cd;
    mcserv_req req;
    mcserv_rep rep;
    int *o_type, *o_free, *o_format; /* sceMcGetInfo outputs */
    char *o_pwd;                     /* sceMcChdir output */
} C = {.lock = -1, .done = -1};

/* RG_IOP=native state (docs/NATIVE-IOP.md) */
static struct {
    int inited;      /* a successful sceMcInit ran (HLE: the mcserv binding) */
    int session;     /* between sceMcInit and sceMcEnd (HLE: the semaphores exist) */
    int busy;        /* an operation holds the lock until sceMcSync collects it */
    int cmd;         /* function number in flight, 0 = none */
    int result;
    uint64_t issued, due;
    int r1, r2, r3;  /* GetInfo outputs */
    char pwd[MC_PATH_MAX];
    int *o_type, *o_free, *o_format;
    char *o_pwd;
} NM;

static void nm_reset(void) { memset(&NM, 0, sizeof NM); }

void rg_mc_default_config(rg_mc_config *c)
{
    c->poll_cycles = 2000;
    c->timing = 1;
}

void rg_mc_configure(const rg_mc_config *c)
{
    if (c)
        C.cfg = *c;
    else
        rg_mc_default_config(&C.cfg);
    C.cfg_set = 1;
}

static const rg_mc_config *cfg(void)
{
    if (!C.cfg_set)
        rg_mc_configure(NULL);
    return &C.cfg;
}

void rg_mc_reset(void)
{
    nm_reset();
    rg_mc_config keep = C.cfg;
    int set = C.cfg_set;
    memset(&C, 0, sizeof C);
    C.lock = C.done = -1;
    C.cfg = keep;
    C.cfg_set = set;
}

void rg_mc_debug_state(int *lock_sema, int *done_sema, int *pending_cmd)
{
    if (rg_iop_native()) { /* no semaphores natively: -1 / -1, the function in flight */
        if (lock_sema)
            *lock_sema = -1;
        if (done_sema)
            *done_sema = -1;
        if (pending_cmd)
            *pending_cmd = NM.cmd;
        return;
    }
#if RG_IOP_ORACLE
    if (lock_sema)
        *lock_sema = C.lock;
    if (done_sema)
        *done_sema = C.done;
    if (pending_cmd)
        *pending_cmd = C.cmd;
#endif
}

/* ---- virtual-clock timestamps ------------------------------------------------------ */
static int days_in(int y, int m)
{
    static const int d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
        return 29;
    return d[m - 1];
}

void rg_mc_virtual_clock(void *user, struct mc_datetime *out)
{
    (void)user;
    uint64_t s = ps2k_now() / PS2K_BUSCLK + 12u * 3600u; /* base 2006-01-31 00:00:00 */
    int y = 2006, mo = 1, d = 31;
    uint64_t days = s / 86400u;
    uint32_t r = (uint32_t)(s % 86400u);
    while (days--) {
        if (++d > days_in(y, mo)) {
            d = 1;
            if (++mo > 12) {
                mo = 1;
                y++;
            }
        }
    }
    memset(out, 0, sizeof *out);
    out->year = (uint16_t)y;
    out->month = (uint8_t)mo;
    out->day = (uint8_t)d;
    out->hour = (uint8_t)(r / 3600u);
    out->min = (uint8_t)(r / 60u % 60u);
    out->sec = (uint8_t)(r % 60u);
}

/* ---- completion ------------------------------------------------------------------------ */
static int in_thread(void) { return ps2k_get_thread_id() > 0 && !ps2k_in_handler(); }

#if RG_IOP_ORACLE /* RG_NATIVE_ONLY: no mcserv client (docs/NATIVE-ONLY.md) */
static void mc_complete(void *arg)
{
    (void)arg;
    if (C.o_type)
        *C.o_type = C.rep.r1;
    if (C.o_free)
        *C.o_free = C.rep.r2;
    if (C.o_format)
        *C.o_format = C.rep.r3;
    if (C.o_pwd)
        memcpy(C.o_pwd, C.rep.path, MC_PATH_MAX);
    C.o_type = C.o_free = C.o_format = NULL;
    C.o_pwd = NULL;
    if (C.done >= 0)
        ps2k_signal_sema(C.done, ps2k_in_handler());
}

/* SIF end function: runs at the RPC completion (SIF0 interrupt context). The
 * operation itself ends `cost` cycles later on the card. */
static void mc_end(void *arg)
{
    (void)arg;
    if (cfg()->timing && C.rep.cost)
        sif_post(C.rep.cost, mc_complete, NULL);
    else
        mc_complete(NULL);
}

/* block until the completion signals `done` */
static void mc_wait_done(void)
{
    if (in_thread()) {
        ps2k_wait_sema(C.done);
        return;
    }
    /* host context (setup code, tools): drive the SIF events directly */
    for (int i = 0; i < 1000000; i++) {
        if (ps2k_poll_sema(C.done, 0) >= 0)
            return;
        if (!sif_deliver_all() && sif_pending_events() == 0)
            break;
    }
}
#endif

/* ---- RG_IOP=native ------------------------------------------------------------------- */

static int nm_done(void)
{
    if (!in_thread())
        return 1; /* host context: no clock to wait on */
    uint64_t now = ps2k_now();
    /* the HLE completes on the SIF0 event at issue + card time, seen by the caller in
     * the first event pass at or after it (never on the issuing pass itself) */
    return now >= NM.due && now > NM.issued;
}

static void nm_collect_outputs(void)
{
    if (NM.o_type)
        *NM.o_type = NM.r1;
    if (NM.o_free)
        *NM.o_free = NM.r2;
    if (NM.o_format)
        *NM.o_format = NM.r3;
    if (NM.o_pwd)
        memcpy(NM.o_pwd, NM.pwd, MC_PATH_MAX);
    NM.o_type = NM.o_free = NM.o_format = NULL;
    NM.o_pwd = NULL;
}

static int nm_sync(int mode, int *cmd, int *result)
{
    if (NM.cmd == 0)
        return sceMcExecIdle;
    int done = nm_done();
    if (!done && mode == 0) {
        ps2k_wait_until(NM.due > NM.issued ? NM.due : NM.issued + 1);
        done = 1;
    }
    if (cmd)
        *cmd = NM.cmd;
    if (!done) {
        if (in_thread() && cfg()->poll_cycles)
            ps2k_charge(cfg()->poll_cycles); /* a polled status lets virtual time pass */
        return sceMcExecRun;
    }
    nm_collect_outputs();
    NM.cmd = 0;
    if (result)
        *result = NM.result;
    NM.busy = 0;
    return sceMcExecFinish;
}

/* RG_MC_TRACE=1: one stderr line per card operation with its host wall time and
 * host I/O (diagnostics for slow saves; the game-visible card time is unchanged) */
static int nm_trace = -1;
static mccard_io_stats nm_tr_io;
static struct timespec nm_tr_t0;

/* RG_MC_TRACE host clock: C11 timespec_get on Windows; clock_gettime elsewhere (the Linux
 * target builds with -std=gnu99, where glibc hides timespec_get / TIME_UTC: docs/LINUX.md) */
static void mc_wall_ts(struct timespec *ts)
{
#ifdef _WIN32
    timespec_get(ts, TIME_UTC);
#else
    clock_gettime(CLOCK_REALTIME, ts);
#endif
}

static int nm_begin(void)
{
    if (!NM.inited)
        return sceMcErrNoInit;
    if (!NM.session || NM.busy)
        return sceMcErrBusy;
    if (nm_trace < 0) {
        const char *e = getenv("RG_MC_TRACE");
        nm_trace = e && *e && *e != '0';
    }
    if (nm_trace) {
        mccard_get_io_stats(&nm_tr_io);
        mc_wall_ts(&nm_tr_t0);
    }
    NM.busy = 1;
    NM.o_type = NM.o_free = NM.o_format = NULL;
    NM.o_pwd = NULL;
    return 0;
}

static int nm_bad_name(const char *name)
{
    if (name && name[0])
        return 0;
    NM.busy = 0;
    return 1;
}

/* the operation runs on the card now; it completes after its card time */
static int nm_issue(int op, int cmdno, int result)
{
    if (nm_trace > 0) {
        struct timespec t1;
        mc_wall_ts(&t1);
        mccard_io_stats io;
        mccard_get_io_stats(&io);
        long long us = (t1.tv_sec - nm_tr_t0.tv_sec) * 1000000LL + (t1.tv_nsec - nm_tr_t0.tv_nsec) / 1000;
        fprintf(stderr, "mctrace: op %02X res %d host %lld us; wrote %u files %u B, read %u, meta %u, backup %u\n",
                op, result, us, io.files_written - nm_tr_io.files_written, io.bytes_written - nm_tr_io.bytes_written,
                io.files_read - nm_tr_io.files_read, io.meta_saves - nm_tr_io.meta_saves,
                io.backups - nm_tr_io.backups);
    }
    NM.result = result;
    NM.issued = ps2k_now();
    NM.due = NM.issued + (cfg()->timing ? mc_time_cost(op, result) : 0);
    NM.cmd = cmdno;
    return 0;
}

static void nm_name(char *dst, const char *src, size_t n)
{
    strncpy(dst, src, n - 1);
    dst[n - 1] = 0;
}

static void nm_card_init(void)
{
    if (!mccard_inited()) {
        mccard_config mc;
        mccard_default_config(&mc);
        mc.clock = rg_mc_virtual_clock;
        mccard_init(&mc);
    }
}

static int nm_init(void)
{
    if (!NM.session) {
        NM.session = 1;
        NM.busy = 0;
    }
    nm_sync(0, NULL, NULL);
    nm_card_init();
    NM.inited = 1;
    return 0; /* mcserv 2.16 / mcman 2.38: versions accepted */
}

static int nm_end(void)
{
    if (NM.session) {
        nm_sync(0, NULL, NULL);
        NM.session = 0;
        NM.busy = 0;
    }
    return 1;
}

static int nm_getinfo(int port, int *type, int *free, int *format)
{
    int r = nm_begin();
    if (r)
        return r;
    NM.o_type = type;
    NM.o_free = free;
    NM.o_format = format;
    int res = mccard_getinfo(port, &NM.r1, &NM.r2, &NM.r3);
    return nm_issue(MC_OP_GETINFO, sceMcFuncNoCardInfo, res);
}

static int nm_open(int port, const char *name, int mode, int cmdno)
{
    int r = nm_begin();
    if (r)
        return r;
    if (nm_bad_name(name))
        return sceMcErrBadName;
    char n[MC_PATH_MAX];
    nm_name(n, name, sizeof n);
    return nm_issue(MC_OP_OPEN, cmdno, mccard_open(port, n, mode));
}

static int nm_fd_op(int op, int cmdno, int fd, int b, int c, void *buf)
{
    int r = nm_begin();
    if (r)
        return r;
    int res;
    switch (op) {
    case MC_OP_CLOSE: res = mccard_close(fd); break;
    case MC_OP_SEEK: res = mccard_seek(fd, b, c); break;
    case MC_OP_FLUSH: res = mccard_flush(fd); break;
    case MC_OP_READ: {
        void *tmp = b > 0 ? malloc((size_t)b) : NULL;
        if (b > 0 && !tmp) {
            res = MC_RES_DENIEDPERMIT;
            break;
        }
        res = mccard_read(fd, tmp, b);
        if (res > 0 && buf)
            memcpy(buf, tmp, (size_t)res);
        free(tmp);
        break;
    }
    case MC_OP_WRITE: res = buf ? mccard_write(fd, buf, b) : MC_RES_DENIEDPERMIT; break;
    default: res = MC_RES_DENIEDPERMIT; break;
    }
    return nm_issue(op, cmdno, res);
}

static int nm_chdir(int port, const char *dir, char *cur)
{
    int r = nm_begin();
    if (r)
        return r;
    if (nm_bad_name(dir))
        return sceMcErrBadName;
    char n[MC_PATH_MAX];
    nm_name(n, dir, sizeof n);
    memset(NM.pwd, 0, sizeof NM.pwd);
    NM.o_pwd = cur;
    return nm_issue(MC_OP_CHDIR, sceMcFuncNoChDir, mccard_chdir(port, n, NM.pwd));
}

static int nm_getdir(int port, const char *name, unsigned mode, int maxent, sceMcTblGetDir *table)
{
    int r = nm_begin();
    if (r)
        return r;
    if (nm_bad_name(name))
        return sceMcErrBadName;
    char n[MC_PATH_MAX];
    nm_name(n, name, sizeof n);
    int m = maxent > 0 ? maxent : 0;
    mc_dirent *tmp = m ? (mc_dirent *)calloc((size_t)m, sizeof *tmp) : NULL;
    int res = mccard_getdir(port, n, (int)mode, m, tmp);
    if (res > 0 && table && tmp)
        memcpy(table, tmp, (size_t)res * sizeof *tmp);
    free(tmp);
    return nm_issue(MC_OP_GETDIR, sceMcFuncNoGetDir, res);
}

static int nm_setinfo(int port, const char *name, const void *info_src, const char *name2, unsigned flags,
                      int cmdno)
{
    char n[MC_PATH_MAX];
    nm_name(n, name, sizeof n);
    mc_dirent info;
    memset(&info, 0, sizeof info);
    if (info_src)
        memcpy(&info, info_src, sizeof info);
    if (flags & MC_INFO_NAME) {
        char n2[MC_NAME_MAX];
        nm_name(n2, name2 ? name2 : "", sizeof n2);
        memset(info.name, 0, sizeof info.name);
        memcpy(info.name, n2, MC_NAME_MAX);
        info.name[MC_NAME_MAX - 1] = 0;
    }
    return nm_issue(MC_OP_SETINFO, cmdno, mccard_setinfo(port, n, &info, flags));
}

static int nm_port_op(int op, int cmdno, int port, const char *name)
{
    int r = nm_begin();
    if (r)
        return r;
    char n[MC_PATH_MAX] = {0};
    if (name) {
        if (nm_bad_name(name))
            return sceMcErrBadName;
        nm_name(n, name, sizeof n);
    }
    int res;
    switch (op) {
    case MC_OP_DELETE: res = mccard_delete(port, n); break;
    case MC_OP_FORMAT: res = mccard_format(port); break;
    case MC_OP_UNFORMAT: res = mccard_unformat(port); break;
    case MC_OP_ENTSPACE: res = mccard_entspace(port, n); break;
    default: res = MC_RES_DENIEDPERMIT; break;
    }
    return nm_issue(op, cmdno, res);
}

int sceMcSync(int mode, int *cmd, int *result)
{
    RG_IOP_API("sceMcSync");
    if (rg_iop_native())
        return nm_sync(mode, cmd, result);
#if RG_IOP_ORACLE
    if (C.cmd == 0)
        return sceMcExecIdle;
    int done = ps2k_poll_sema(C.done, 0) >= 0;
    if (!done && mode == 0) {
        mc_wait_done();
        done = 1;
    }
    if (cmd)
        *cmd = C.cmd;
    if (!done) {
        /* a polled status: let virtual time pass (docs/SPIN.md) */
        if (in_thread() && cfg()->poll_cycles)
            ps2k_charge(cfg()->poll_cycles);
        return sceMcExecRun;
    }
    C.cmd = 0;
    if (result)
        *result = C.rep.result;
    ps2k_signal_sema(C.lock, 0);
    return sceMcExecFinish;
#endif
}

/* ---- issue ------------------------------------------------------------------------------ */
#if RG_IOP_ORACLE
static int mc_begin(void)
{
    if (!C.cd.serve)
        return sceMcErrNoInit;
    if (C.lock < 0 || ps2k_poll_sema(C.lock, 0) < 0)
        return sceMcErrBusy;
    memset(&C.req, 0, sizeof C.req);
    C.o_type = C.o_free = C.o_format = NULL;
    C.o_pwd = NULL;
    return 0;
}

static int mc_bad_name(const char *name)
{
    if (name && name[0])
        return 0;
    ps2k_signal_sema(C.lock, 0);
    return 1;
}

static int mc_send(uint32_t fno, int cmdno, int rsize)
{
    memset(&C.rep, 0, sizeof C.rep);
    int r = sceSifCallRpc(&C.cd, fno, SIF_RPCM_NOWAIT, &C.req, (int)sizeof C.req, &C.rep, rsize, mc_end, NULL);
    if (r != 0) {
        ps2k_signal_sema(C.lock, 0);
        return sceMcErrRpc;
    }
    C.cmd = cmdno;
    return 0;
}

static void set_name(char *dst, const char *src, size_t n)
{
    strncpy(dst, src, n - 1);
    dst[n - 1] = 0;
}
#endif


int sceMcInit(void)
{
    RG_IOP_API("sceMcInit");
    if (rg_iop_native())
        return nm_init();
#if RG_IOP_ORACLE
    if (C.lock < 0) {
        C.lock = ps2k_create_sema(1, 1, 0, 0);
        if (C.lock < 0)
            return sceMcIniErrKernel;
        C.done = ps2k_create_sema(0, 1, 0, 0);
        if (C.done < 0) {
            ps2k_delete_sema(C.lock, 0);
            C.lock = C.done;
            return sceMcIniErrKernel;
        }
    }
    sceMcSync(0, NULL, NULL);
    if (in_thread())
        ps2k_wait_sema(C.lock);
    else
        ps2k_poll_sema(C.lock, 0);
    sceSifInitRpc(0);
    if (!mccard_inited()) {
        mccard_config mc;
        mccard_default_config(&mc);
        mc.clock = rg_mc_virtual_clock;
        mccard_init(&mc);
    }
    if (!mcserv_installed())
        mcserv_install();
    sceSifBindRpc(&C.cd, MCSERV_SID, 0);
    if (!C.cd.serve) {
        fprintf(stderr, "[libmc] sceMcInit: mcserv 0x%08X not bound\n", MCSERV_SID);
        ps2k_signal_sema(C.lock, 0);
        return sceMcErrRpc;
    }
    memset(&C.rep, 0, sizeof C.rep);
    int r = sceSifCallRpc(&C.cd, MCSERV_FNO_INIT, 0, &C.req, 0x30, &C.rep, MCSERV_REP_SHORT, NULL, NULL);
    ps2k_signal_sema(C.lock, 0);
    if (r < 0) {
        C.cd.serve = NULL;
        return sceMcErrRpc;
    }
    if (C.rep.r1 < 0x20A) {
        C.cd.serve = NULL;
        return sceMcIniOldMcserv;
    }
    if (C.rep.r2 < 0x20E) {
        C.cd.serve = NULL;
        return sceMcIniOldMcman;
    }
    return C.rep.result;
#endif
}

int sceMcEnd(void)
{
    RG_IOP_API("sceMcEnd");
    if (rg_iop_native())
        return nm_end();
#if RG_IOP_ORACLE
    if (C.lock >= 0) {
        sceMcSync(0, NULL, NULL);
        ps2k_delete_sema(C.lock, 0);
        C.lock = -1;
        ps2k_delete_sema(C.done, 0);
    }
    return 1;
#endif
}

int sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    RG_IOP_API("sceMcGetInfo");
    if (rg_iop_native()) {
        (void)slot; /* recorded and ignored, as the HLE */
        return nm_getinfo(port, type, free, format);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    C.req.port = port;
    C.req.slot = slot;
    C.o_type = type;
    C.o_free = free;
    C.o_format = format;
    return mc_send(MCSERV_FNO_GETINFO, sceMcFuncNoCardInfo, MCSERV_REP_SHORT);
#endif
}

int sceMcOpen(int port, int slot, const char *name, int mode)
{
    RG_IOP_API("sceMcOpen");
    if (rg_iop_native()) {
        (void)slot;
        return nm_open(port, name, mode, sceMcFuncNoOpen);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (mc_bad_name(name))
        return sceMcErrBadName;
    C.req.port = port;
    C.req.slot = slot;
    C.req.a = mode;
    set_name(C.req.name, name, sizeof C.req.name);
    return mc_send(MCSERV_FNO_OPEN, sceMcFuncNoOpen, MCSERV_REP_SHORT);
#endif
}

int sceMcMkdir(int port, int slot, const char *name)
{
    RG_IOP_API("sceMcMkdir");
    if (rg_iop_native()) {
        (void)slot;
        return nm_open(port, name, 0x40, sceMcFuncNoMkdir);
    }
#if RG_IOP_ORACLE
    int r = sceMcOpen(port, slot, name, 0x40);
    if (r == 0)
        C.cmd = sceMcFuncNoMkdir;
    return r;
#endif
}

static int fd_op(uint32_t fno, int cmdno, int fd, int b, int c, uint32_t buf)
{
    RG_IOP_API_ID("sceMc(fd op)", cmdno);
    if (rg_iop_native())
        return nm_fd_op((int)fno, cmdno, fd, b, c, (void *)(uintptr_t)buf);
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    C.req.a = fd;
    C.req.b = b;
    C.req.c = c;
    C.req.ee_buf = buf;
    return mc_send(fno, cmdno, MCSERV_REP_SHORT);
#endif
}

int sceMcClose(int fd) { return fd_op(MCSERV_FNO_CLOSE, sceMcFuncNoClose, fd, 0, 0, 0); }
int sceMcSeek(int fd, int offset, int origin) { return fd_op(MCSERV_FNO_SEEK, sceMcFuncNoSeek, fd, offset, origin, 0); }
int sceMcRead(int fd, void *buff, int size)
{
    return fd_op(MCSERV_FNO_READ, sceMcFuncNoRead, fd, size, 0, (uint32_t)(uintptr_t)buff);
}
int sceMcWrite(int fd, const void *buff, int size)
{
    return fd_op(MCSERV_FNO_WRITE, sceMcFuncNoWrite, fd, size, 0, (uint32_t)(uintptr_t)buff);
}
int sceMcFlush(int fd) { return fd_op(MCSERV_FNO_FLUSH, sceMcFuncNoFlush, fd, 0, 0, 0); }

int sceMcChdir(int port, int slot, const char *newDir, char *currentDir)
{
    RG_IOP_API("sceMcChdir");
    if (rg_iop_native()) {
        (void)slot;
        return nm_chdir(port, newDir, currentDir);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (mc_bad_name(newDir))
        return sceMcErrBadName;
    C.req.port = port;
    C.req.slot = slot;
    set_name(C.req.name, newDir, sizeof C.req.name);
    C.o_pwd = currentDir;
    return mc_send(MCSERV_FNO_CHDIR, sceMcFuncNoChDir, (int)sizeof C.rep);
#endif
}

int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, sceMcTblGetDir *table)
{
    RG_IOP_API("sceMcGetDir");
    if (rg_iop_native()) {
        (void)slot;
        return nm_getdir(port, name, mode, maxent, table);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (mc_bad_name(name))
        return sceMcErrBadName;
    C.req.port = port;
    C.req.slot = slot;
    C.req.a = (int)mode;
    C.req.b = maxent;
    C.req.ee_buf = (uint32_t)(uintptr_t)table;
    set_name(C.req.name, name, sizeof C.req.name);
    return mc_send(MCSERV_FNO_GETDIR, sceMcFuncNoGetDir, MCSERV_REP_SHORT);
#endif
}

int sceMcSetFileInfo(int port, int slot, const char *name, const sceMcTblGetDir *info, unsigned int valid)
{
    RG_IOP_API("sceMcSetFileInfo");
    if (rg_iop_native()) {
        (void)slot;
        int r = nm_begin();
        if (r)
            return r;
        if (!(name && name[0]) || !info) {
            NM.busy = 0;
            return sceMcErrBadName;
        }
        return nm_setinfo(port, name, info, (valid & MC_INFO_NAME) ? (const char *)info->EntryName : NULL, valid,
                          sceMcFuncNoFileInfo);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (mc_bad_name(name) || !info) {
        if (!(name && name[0]))
            return sceMcErrBadName;
        ps2k_signal_sema(C.lock, 0);
        return sceMcErrBadName;
    }
    C.req.port = port;
    C.req.slot = slot;
    C.req.a = (int)valid;
    C.req.ee_buf = (uint32_t)(uintptr_t)info;
    set_name(C.req.name, name, sizeof C.req.name);
    if (valid & MC_INFO_NAME)
        set_name(C.req.name2, (const char *)info->EntryName, sizeof C.req.name2);
    return mc_send(MCSERV_FNO_SETINFO, sceMcFuncNoFileInfo, MCSERV_REP_SHORT);
#endif
}

int sceMcRename(int port, int slot, const char *oldName, const char *newName)
{
    RG_IOP_API("sceMcRename");
    if (rg_iop_native()) {
        (void)slot;
        int r = nm_begin();
        if (r)
            return r;
        if (!oldName || !oldName[0] || !newName) {
            NM.busy = 0;
            return sceMcErrBadName;
        }
        return nm_setinfo(port, oldName, NULL, newName, MC_INFO_NAME, sceMcFuncNoRename);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (!oldName || !oldName[0] || !newName) {
        ps2k_signal_sema(C.lock, 0);
        return sceMcErrBadName;
    }
    C.req.port = port;
    C.req.slot = slot;
    C.req.a = MC_INFO_NAME;
    set_name(C.req.name, oldName, sizeof C.req.name);
    set_name(C.req.name2, newName, sizeof C.req.name2);
    return mc_send(MCSERV_FNO_SETINFO, sceMcFuncNoRename, MCSERV_REP_SHORT);
#endif
}

int sceMcDelete(int port, int slot, const char *name)
{
    RG_IOP_API("sceMcDelete");
    if (rg_iop_native()) {
        (void)slot;
        return nm_port_op(MC_OP_DELETE, sceMcFuncNoDelete, port, name);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    if (mc_bad_name(name))
        return sceMcErrBadName;
    C.req.port = port;
    C.req.slot = slot;
    set_name(C.req.name, name, sizeof C.req.name);
    return mc_send(MCSERV_FNO_DELETE, sceMcFuncNoDelete, MCSERV_REP_SHORT);
#endif
}

static int port_op(uint32_t fno, int cmdno, int port, int slot, const char *name)
{
    RG_IOP_API_ID("sceMc(port op)", cmdno);
    if (rg_iop_native()) {
        (void)slot;
        return nm_port_op((int)fno, cmdno, port, name);
    }
#if RG_IOP_ORACLE
    int r = mc_begin();
    if (r)
        return r;
    C.req.port = port;
    C.req.slot = slot;
    if (name) {
        if (mc_bad_name(name))
            return sceMcErrBadName;
        set_name(C.req.name, name, sizeof C.req.name);
    }
    return mc_send(fno, cmdno, MCSERV_REP_SHORT);
#endif
}

int sceMcFormat(int port, int slot) { return port_op(MCSERV_FNO_FORMAT, sceMcFuncNoFormat, port, slot, NULL); }
int sceMcUnformat(int port, int slot) { return port_op(MCSERV_FNO_UNFORMAT, sceMcFuncNoUnformat, port, slot, NULL); }
int sceMcGetEntSpace(int port, int slot, const char *path)
{
    if (!path)
        path = "";
    return port_op(MCSERV_FNO_ENTSPACE, sceMcFuncNoEntSpace, port, slot, path);
}

/* retail: a synchronous call that does not take the operation lock */
int sceMcGetSlotMax(int port)
{
    RG_IOP_API("sceMcGetSlotMax");
    if (rg_iop_native()) {
        (void)port;
        return NM.inited ? 1 : sceMcErrNoInit; /* a synchronous answer, no lock */
    }
#if RG_IOP_ORACLE
    if (!C.cd.serve)
        return sceMcErrNoInit;
    mcserv_req q;
    mcserv_rep p;
    memset(&q, 0, sizeof q);
    q.port = port;
    if (sceSifCallRpc(&C.cd, MCSERV_FNO_SLOTMAX, 0, &q, 0x30, &p, MCSERV_REP_SHORT, NULL, NULL) < 0)
        return sceMcErrRpc;
    return p.result;
#endif
}

/* ---- game-tree names --------------------------------------------------------------------- */
int sceMcInit_12c648(void) { return sceMcInit(); }
int sceMcEnd_12c870(void) { return sceMcEnd(); }
int sceMcGetSlotMax_12c998(int port) { return sceMcGetSlotMax(port); }
int sceMcOpen_12ca58(int port, int slot, const char *name, int mode) { return sceMcOpen(port, slot, name, mode); }
int sceMcClose_12cbb8(int fd) { return sceMcClose(fd); }
int sceMcSeek_12cc78(int fd, int offset, int origin) { return sceMcSeek(fd, offset, origin); }
int sceMcRead_12ce08(int fd, void *buff, int size) { return sceMcRead(fd, buff, size); }
int sceMcWrite_12cf20(int fd, const void *buff, int size) { return sceMcWrite(fd, buff, size); }
int sceMcSync_12d098(int mode, int *cmd, int *result) { return sceMcSync(mode, cmd, result); }
int sceMcGetInfo_12d1b8(int port, int slot, int *type, int *free, int *format)
{
    return sceMcGetInfo(port, slot, type, free, format);
}
int sceMcGetDir_12d3a8(int port, int slot, const char *name, unsigned int mode, int maxent, sceMcTblGetDir *table)
{
    return sceMcGetDir(port, slot, name, mode, maxent, table);
}
int sceMcChdir_12d588(int port, int slot, const char *newDir, char *currentDir)
{
    return sceMcChdir(port, slot, newDir, currentDir);
}
int sceMcFormat_12d6c8(int port, int slot) { return sceMcFormat(port, slot); }
int sceMcDelete_12d798(int port, int slot, const char *name) { return sceMcDelete(port, slot, name); }
int sceMcFlush_12d8b8(int fd) { return sceMcFlush(fd); }
int sceMcSetFileInfo_12d978(int port, int slot, const char *name, const sceMcTblGetDir *info, unsigned int valid)
{
    return sceMcSetFileInfo(port, slot, name, info, valid);
}
int sceMcRename_12db48(int port, int slot, const char *oldName, const char *newName)
{
    return sceMcRename(port, slot, oldName, newName);
}
int sceMcUnformat_12dca0(int port, int slot) { return sceMcUnformat(port, slot); }
int sceMcGetEntSpace_12dd70(int port, int slot, const char *path) { return sceMcGetEntSpace(port, slot, path); }
