/* SPDX-License-Identifier: CC0-1.0 */
/* SIF HLE core (PLAN.md D4, docs/SIF.md).
 *
 * The SIF is the EE<->IOP link. Here it is modelled as:
 *   - the SIF registers the SDK reads (MSCOM/SMCOM/MSFLAG/SMFLAG, software sregs),
 *   - SIF1 DMA (EE -> IOP): a sceSifDmaData list copied into IOP RAM at each
 *     tag's IOP address; completion time = submit + cost on the SIF clock,
 *   - SIF0 (IOP -> EE): writes into EE buffers (host pointers on i686) delivered
 *     as *events* that run at their due time in "interrupt" context,
 *   - the RPC protocol: a registry of host "IOP servers" by SID, bind, call with
 *     send/receive buffers, completion events (reply copy, end function),
 *     pending status; plus EE-side servers that IOP code calls back into,
 *   - raw SIF commands in both directions (sceSifSendCmd / sceSifAddCmdHandler).
 *
 * The core knows nothing about the EE kernel. Two hooks connect it:
 *   now()      - the clock (bus cycles); default: an internal counter that only
 *                sif_advance() moves,
 *   schedule() - "please call sif_deliver() at or after `due`". src/sce/sif maps it
 *                to a DMAC SIF0 (channel 5) interrupt through ps2k, whose handler
 *                calls sif_deliver(). Without hooks, call sif_deliver()/sif_advance()
 *                yourself (the tests do).
 * Single host thread; nothing here locks. EE addresses are host pointers (i686). */
#ifndef RG_PS2_SIF_H
#define RG_PS2_SIF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- setup ------------------------------------------------------------- */
typedef struct sif_hooks {
    uint64_t (*now)(void *user);
    void (*schedule)(uint64_t due, void *user);
    void *user;
} sif_hooks;

typedef struct sif_config {
    uint64_t rpc_latency;    /* cycles from sceSifCallRpc to reply delivery (default 0) */
    uint64_t dma_setup;      /* fixed cycles per SIF DMA list (default 0) */
    uint64_t dma_cycles_per_qword; /* default 0 */
    uint64_t boot_latency;   /* reboot -> SMFLAG.BOOTEND (default 0) */
} sif_config;

void sif_default_config(sif_config *cfg);
/* Resets every SIF table (servers, events, DMA, registers, logs). The IOP model is
 * reset separately (iop_reset). Marks the IOP as booted (SMFLAG = SIFINIT|CMDINIT|BOOTEND). */
void sif_init(const sif_config *cfg);
void sif_set_hooks(const sif_hooks *hooks); /* NULL -> internal clock, no scheduling */
const sif_config *sif_get_config(void);
uint64_t sif_now(void);

/* ---- registers ---------------------------------------------------------- */
#define SIF_REG_MSCOM  1u /* EE -> IOP address register (SIF "main" command addr) */
#define SIF_REG_SMCOM  2u /* IOP -> EE address register */
#define SIF_REG_MSFLAG 3u /* EE writes set bits */
#define SIF_REG_SMFLAG 4u /* IOP sets bits, EE writes clear bits */
#define SIF_REG_CTRL   5u
#define SIF_SREG_BASE  0x80000000u /* software registers 0x80000000..0x8000001F */
#define SIF_STAT_SIFINIT 0x10000u
#define SIF_STAT_CMDINIT 0x20000u
#define SIF_STAT_BOOTEND 0x40000u
uint32_t sif_reg_get(uint32_t reg);
uint32_t sif_reg_set(uint32_t reg, uint32_t value); /* returns the previous value */
void sif_iop_set_smflag(uint32_t bits);             /* IOP side: set bits */

/* ---- IOP lifecycle -------------------------------------------------------- */
/* sceSifRebootIop / sceSifResetIop: clears SMFLAG boot bits, reboots the IOP model
 * (iop_reboot: RAM, heap, module list) and re-raises SIFINIT|CMDINIT|BOOTEND after
 * boot_latency. Pending events are kept (so no waiter hangs). Registered servers
 * stay (the HLE servers are pre-registered and survive reboots); their buffers are
 * re-reserved in the cleared IOP RAM. */
void sif_iop_reboot(const char *image);
int sif_iop_booted(void); /* SMFLAG & BOOTEND */

/* ---- events -------------------------------------------------------------- */
typedef void (*sif_event_fn)(void *arg);
/* Queue fn(arg) to run at now + delay (FIFO among equal times). 0 on success. */
int sif_post(uint64_t delay, sif_event_fn fn, void *arg);
int sif_deliver(void);        /* run every event due at sif_now(); returns count */
int sif_deliver_all(void);    /* run every queued event regardless of time */
int sif_pending_events(void);
uint64_t sif_next_due(void);  /* UINT64_MAX if none */
/* Internal clock only (no now hook): move time forward and deliver. */
void sif_advance(uint64_t cycles);
int sif_in_delivery(void);    /* 1 while sif_deliver runs an event ("interrupt" context) */

/* ---- SIF DMA ------------------------------------------------------------- */
typedef struct sif_dma_xfer { /* == sceSifDmaData */
    uint32_t data;  /* EE source address (host pointer) */
    uint32_t addr;  /* IOP destination address */
    uint32_t size;  /* bytes */
    uint32_t mode;  /* SIF_DMA_* attributes (recorded, not acted on) */
} sif_dma_xfer;
#define SIF_DMA_INT_I 0x2u
#define SIF_DMA_INT_O 0x4u
#define SIF_DMA_ERT   0x40u
/* SIF1: copy each element into IOP RAM now; the transfer *completes* at
 * now + dma_setup + qwords * dma_cycles_per_qword. Returns a non-zero id, or 0 if
 * any element is out of IOP RAM (nothing is copied then). */
uint32_t sif1_dma(const sif_dma_xfer *list, int count);
/* > 0 queued/in flight, < 0 complete (or unknown id), as sceSifDmaStat. */
int sif_dma_stat(uint32_t id);
/* SIF0 immediate write into an EE buffer (IOP code that pushes data to the EE,
 * e.g. FILEIO read). Counted in the stats. */
void sif0_write(void *ee_dst, const void *src, uint32_t size);

/* ---- RPC: servers ---------------------------------------------------------- */
typedef struct sif_rpc_ctx {
    uint32_t sid, fno;
    void *data;         /* the server's receive buffer (IOP RAM), holding the send data */
    uint32_t data_iop;  /* its IOP address */
    uint32_t size;      /* bytes received (ssize, clipped to the buffer) */
    uint32_t rsize;     /* bytes the caller wants back */
    void *ee_recv;      /* caller's EE receive buffer (servers that SIF0-write directly) */
    int unknown;        /* server sets 1: function number not implemented (reported) */
} sif_rpc_ctx;
/* Returns a pointer to the reply (rsize bytes are copied from it to the EE receive
 * buffer when the call completes), or NULL for no reply data. */
typedef void *(*sif_server_fn)(sif_rpc_ctx *ctx, void *user);

typedef struct sif_server_info {
    uint32_t sid;
    char name[32];
    uint32_t buf_iop, bufsize;
    sif_server_fn fn;
    void *user;
    uint32_t binds, calls, unknown_calls;
} sif_server_info;

#define SIF_MAX_SERVERS 32
/* Register (or replace) a server. bufsize bytes of IOP RAM are reserved for its
 * receive buffer (0 = no buffer: send data is not copied). 0 ok, -1 table full. */
int sif_server_register(uint32_t sid, const char *name, uint32_t bufsize, sif_server_fn fn, void *user);
int sif_server_unregister(uint32_t sid);
const sif_server_info *sif_server_find(uint32_t sid);
int sif_server_count(void);
const sif_server_info *sif_server_get(int index);

/* ---- RPC: client calls ------------------------------------------------------ */
/* Bind: 0 and the server's token (non-zero) if registered; -1 (reported) if not. */
int sif_rpc_bind(uint32_t sid, uint32_t *token);

typedef void (*sif_done_fn)(void *arg);
typedef struct sif_call {
    uint32_t sid, fno;
    const void *send; uint32_t ssize;
    void *recv; uint32_t rsize;
    sif_done_fn done; void *done_arg; /* run at completion, after the reply copy */
} sif_call;
/* Run the server now (send data is copied into its buffer, its function runs), then
 * queue the completion (reply copy into recv, then done()) at now + rpc_latency.
 * Returns a ticket (> 0), or 0 for an unknown SID (reported; done() is still queued
 * so a waiter never hangs, and recv is left untouched). */
uint32_t sif_rpc_call(const sif_call *c);
int sif_rpc_busy(uint32_t ticket); /* 1 until the completion has been delivered */

/* ---- RPC: EE-side servers (IOP -> EE calls, e.g. sdr_driver -> 0x80000704) --- */
typedef void (*sif_ee_sink_fn)(uint32_t sid, uint32_t fno, const void *data, uint32_t size, void *user);
int sif_ee_server_attach(uint32_t sid, sif_ee_sink_fn fn, void *user); /* replaces */
int sif_ee_server_detach(uint32_t sid);
int sif_ee_server_present(uint32_t sid);
/* From host IOP code: deliver (copy of) data to the EE server as an event after
 * rpc_latency. 0 ok, -1 no EE server with that SID (reported). */
int sif_iop_call_ee(uint32_t sid, uint32_t fno, const void *data, uint32_t size);

/* ---- raw SIF commands ------------------------------------------------------- */
#define SIF_CMD_SYS 0x80000000u
#define SIF_CMD_CHANGE_SADDR (SIF_CMD_SYS | 0u)
#define SIF_CMD_SET_SREG     (SIF_CMD_SYS | 1u)
#define SIF_CMD_INIT_CMD     (SIF_CMD_SYS | 2u)
#define SIF_CMD_RESET        (SIF_CMD_SYS | 3u)
typedef void (*sif_cmd_fn)(uint32_t cid, const void *pkt, uint32_t size, void *user);
int sif_ee_cmd_set(uint32_t cid, sif_cmd_fn fn, void *user);  /* EE handler (AddCmdHandler); fn NULL removes */
int sif_iop_cmd_set(uint32_t cid, sif_cmd_fn fn, void *user); /* IOP handler */
/* EE -> IOP: optional extra data is SIF1-copied to extra_dest (IOP) first, then the
 * IOP handler runs at once. SET_SREG is handled internally. Returns a non-zero id
 * (sceSifSendCmd semantics), 0 on error. */
uint32_t sif_ee_send_cmd(uint32_t cid, const void *pkt, uint32_t psize,
                         const void *extra_src, uint32_t extra_dest, uint32_t extra_size);
/* IOP -> EE: queue the packet for the EE handler as an event. 0 ok, -1 no handler. */
int sif_iop_send_cmd(uint32_t cid, const void *pkt, uint32_t psize);

/* ---- reporting, log, stats -------------------------------------------------- */
enum sif_report_kind {
    SIF_REP_UNKNOWN_SERVER = 0, /* bind/call to a SID nobody registered */
    SIF_REP_UNKNOWN_FNO,        /* server flagged the function number */
    SIF_REP_BAD_ADDR,           /* DMA/command outside IOP RAM */
    SIF_REP_TRUNCATED,          /* send data larger than the server buffer */
    SIF_REP_NO_EE_SERVER,       /* IOP called an EE SID nobody registered */
    SIF_REP_NO_HANDLER,         /* command id without a handler */
    SIF_REP_OTHER,
    SIF_REP_KINDS
};
typedef void (*sif_report_fn)(int kind, uint32_t sid, uint32_t fno, const char *msg, void *user);
void sif_set_report(sif_report_fn fn, void *user); /* NULL -> stderr */
uint32_t sif_report_count(int kind);

typedef struct sif_call_rec {
    uint32_t seq, sid, fno, ssize, rsize;
    uint64_t when;
    int status; /* 0 ok, 1 unknown server, 2 unknown fno */
} sif_call_rec;
#define SIF_CALL_LOG 256
int sif_call_log_count(void);                     /* calls since init (log keeps the last 256) */
const sif_call_rec *sif_call_log_get(int back);   /* 0 = most recent */
uint32_t sif_call_count(uint32_t sid, uint32_t fno); /* per (sid, fno) */

typedef struct sif_stats {
    uint32_t dma1_xfers, dma1_bytes, sif0_writes, sif0_bytes;
    uint32_t rpc_calls, rpc_binds, ee_calls, cmds_to_iop, cmds_to_ee;
} sif_stats;
const sif_stats *sif_get_stats(void);
/* Optional trace line sink for every RPC/DMA/command (NULL = off). */
void sif_set_trace(void (*fn)(const char *line, void *user), void *user);

#ifdef __cplusplus
}
#endif
#endif
