/* SPDX-License-Identifier: CC0-1.0 */
/* libsdr "sdremote" (EE side of sdr_driver, SDRDRV.IRX) over SIF RPC 0x80000701,
 * plus the EE-side callback server 0x80000704 that sdr_driver calls back into.
 *
 * Argument packing follows the retail sceSdRemote (asm unit sceSdRemote_1229e8):
 *   buf[0] = EE address of buf, buf[1..6] = the six arguments after `command`;
 *   sync != 0 -> blocking call, sync == 0 -> SIF_RPCM_NOWAIT.
 *   0x8130/0x81A0/0x81B0: fno = command | arg1, send = (void*)arg2 (64 B), recv = buf (64 B)
 *   0x8140:               fno = command | arg1, send = recv = (void*)arg2 (64 B), returns 0
 *   0x9000..0x90F0:       fno = command, send = (void*)arg1, ssize = arg2, recv = buf (16 B)
 *   0x8160/0x8170:        record the EE handler locally, then the generic call; return the old handler
 *   anything else:        fno = command, send = buf (64 B), recv = buf (16 B)
 *   return value: buf[0] after the call (the IOP's first reply word).
 * The callback server dispatches on request word 0: 0x100 -> trans handler core 0,
 * 0x200 -> trans handler core 1, 0x400 -> SPU2 handler(word 1) (SdrCallbackRpcDispatch). */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "libsif.h"
#include "ps2k.h"
#include "sif.h"
#include "sif_internal.h"

#define SDR_SID 0x80000701u
#define SDR_CB_SID 0x80000704u

#if RG_IOP_ORACLE /* RG_NATIVE_ONLY: no sdremote client (docs/NATIVE-ONLY.md) */
static struct {
    int bound;
    uint32_t buf[16];
    sceSdTransIntrHandler trans[2];
    void *trans_arg[2];
    sceSdSpu2IntrHandler spu2;
    void *spu2_arg;
    int cb_thread;
    sceSifQueueData qd;
    sceSifServeData sd;
    uint32_t cb_buf[16];
    sceSifClientData cd;
} R = {.cb_thread = -1};

void sdr_reset(void)
{
    memset(&R, 0, sizeof R);
    R.cb_thread = -1;
}
#endif

int sceSdRemoteInit(int unused)
{
    RG_IOP_API("sceSdRemoteInit");
    (void)unused;
    if (rg_iop_native()) {
        /* the native audio engine is called by the game's sound API (docs/NATIVE-AUDIO.md):
         * sdremote reaching here in native mode is an unconverted sound path */
        rg_iop_unconverted("sceSdRemoteInit", 0);
        return 0;
    }
#if RG_IOP_ORACLE
    sceSifInitRpc(0);
    uint32_t tok;
    if (sif_rpc_bind(SDR_SID, &tok) < 0)
        return -1; /* retail would spin re-binding; the report already names the SID */
    R.bound = 1;
    return 0;
#endif
}

int sceSdRemote(int sync, int command, ...)
{
    RG_IOP_API_ID("sceSdRemote", (unsigned)command);
    va_list ap;
    uint32_t a[6];
    va_start(ap, command);
    for (int i = 0; i < 6; i++)
        a[i] = va_arg(ap, uint32_t);
    va_end(ap);
    if (rg_iop_native()) {
        rg_iop_unconverted("sceSdRemote", (uint32_t)command);
        (void)sync;
        return 0;
    }
#if RG_IOP_ORACLE
    if (!R.bound && sceSdRemoteInit(0) < 0)
        return -1;
    uint32_t *buf = R.buf;
    memset(buf, 0, sizeof R.buf);
    buf[0] = (uint32_t)(uintptr_t)buf;
    for (int i = 0; i < 6; i++)
        buf[1 + i] = a[i];
    unsigned mode = sync ? 0 : SIF_RPCM_NOWAIT;
    uint32_t cmd = (uint32_t)command;
    uint32_t old = 0;
    sceSifClientData *cdp = &R.cd;
    cdp->command = SDR_SID;

    if (cmd == 0x8160u) { /* SetTransIntrHandler(core, func, arg) */
        int core = a[0] ? 1 : 0;
        old = (uint32_t)(uintptr_t)R.trans[core];
        R.trans[core] = (sceSdTransIntrHandler)(uintptr_t)a[1];
        R.trans_arg[core] = (void *)(uintptr_t)a[2];
    } else if (cmd == 0x8170u) { /* SetSpu2IntrHandler(func, arg) */
        old = (uint32_t)(uintptr_t)R.spu2;
        R.spu2 = (sceSdSpu2IntrHandler)(uintptr_t)a[0];
        R.spu2_arg = (void *)(uintptr_t)a[1];
    }

    int ret;
    if (cmd == 0x8130u || cmd == 0x81A0u || cmd == 0x81B0u) {
        sceSifCallRpc(cdp, cmd | a[0], mode, (void *)(uintptr_t)a[1], 0x40, buf, 0x40, NULL, NULL);
        ret = (int)buf[0];
    } else if (cmd == 0x8140u) {
        sceSifCallRpc(cdp, cmd | a[0], mode, (void *)(uintptr_t)a[1], 0x40, (void *)(uintptr_t)a[1], 0x40, NULL, NULL);
        ret = 0;
    } else if (cmd >= 0x9000u && cmd <= 0x90F0u) {
        sceSifCallRpc(cdp, cmd, mode, (void *)(uintptr_t)a[0], (int)a[1], buf, 0x10, NULL, NULL);
        ret = (int)buf[0];
    } else {
        sceSifCallRpc(cdp, cmd, mode, buf, 0x40, buf, 0x10, NULL, NULL);
        ret = (int)buf[0];
    }
    if (cmd == 0x8160u || cmd == 0x8170u)
        ret = (int)old;
    return ret;
#endif
}

/* ---- callback server 0x80000704 ----------------------------------------------------- */
#if RG_IOP_ORACLE
static void *sdr_cb_dispatch(unsigned int fno, void *data, int size)
{
    (void)fno;
    (void)size;
    const uint32_t *w = (const uint32_t *)data;
    if ((w[0] & 0x100u) && R.trans[0])
        R.trans[0](0, R.trans_arg[0]);
    if ((w[0] & 0x200u) && R.trans[1])
        R.trans[1](1, R.trans_arg[1]);
    if ((w[0] & 0x400u) && R.spu2)
        R.spu2((int)w[1], R.spu2_arg);
    return NULL;
}

static void sdr_cb_thread(void *arg)
{
    (void)arg;
    sceSifInitRpc(0);
    sceSifSetRpcQueue(&R.qd, ps2k_get_thread_id());
    sceSifRegisterRpc(&R.sd, SDR_CB_SID, sdr_cb_dispatch, R.cb_buf, NULL, NULL, &R.qd);
    sceSifRpcLoop(&R.qd);
}
#endif

int sceSdRemoteCallbackInit(int priority)
{
    RG_IOP_API("sceSdRemoteCallbackInit");
    if (rg_iop_native()) {
        rg_iop_unconverted("sceSdRemoteCallbackInit", 0);
        (void)priority;
        return -1;
    }
#if RG_IOP_ORACLE
    if (R.cb_thread >= 0)
        return -1; /* retail returns -1 when the thread already exists */
    memset(R.trans, 0, sizeof R.trans);
    R.spu2 = NULL;
    sceSdRemote(1, 0xE620);
    static uint8_t stack[0x1000];
    int id = ps2k_create_thread(sdr_cb_thread, stack, (int32_t)sizeof stack, NULL, priority, 0, 0);
    if (id < 0)
        return -1;
    R.cb_thread = id;
    if (ps2k_start_thread(id, NULL) < 0)
        return -1;
    return id;
#endif
}

void sceSdRemoteCallbackQuit(void)
{
    RG_IOP_API("sceSdRemoteCallbackQuit");
    if (rg_iop_native())
        return;
#if RG_IOP_ORACLE
    if (R.cb_thread < 0)
        return;
    sceSdRemote(1, 0xE630);
    ps2k_terminate_thread(R.cb_thread, 0);
    ps2k_delete_thread(R.cb_thread);
    sif_ee_server_detach(SDR_CB_SID);
    R.cb_thread = -1;
#endif
}
