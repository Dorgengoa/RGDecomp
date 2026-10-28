/* SPDX-License-Identifier: CC0-1.0 */
/* mcserv HLE server on SIF 0x80000400. See mcserv.h and docs/PADMC.md. */
#include "mcserv.h"

#include <stdlib.h>
#include <string.h>

#include "sif.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */

static struct {
    uint32_t calls[256];
    mcserv_rep rep;
} S;

void mcserv_default_config(mcserv_config *c) { mc_time_default_config(c); }
void mcserv_configure(const mcserv_config *c) { mc_time_configure(c); }
const mcserv_config *mcserv_get_config(void) { return mc_time_get_config(); }

uint32_t mcserv_calls(uint32_t fno) { return S.calls[fno & 0xFF]; }

void mcserv_handle(uint32_t fno, const mcserv_req *q, mcserv_rep *p)
{
    RG_IOP_HLE("mcserv_handle");
    memset(p, 0, sizeof *p);
    S.calls[fno & 0xFF]++;
    switch (fno) {
    case MCSERV_FNO_INIT:
        p->result = 0;
        p->r1 = MCSERV_VERSION;
        p->r2 = MCMAN_VERSION;
        break;
    case MCSERV_FNO_GETINFO:
        p->result = mccard_getinfo(q->port, &p->r1, &p->r2, &p->r3);
        break;
    case MCSERV_FNO_OPEN:
        p->result = mccard_open(q->port, q->name, q->a);
        break;
    case MCSERV_FNO_CLOSE:
        p->result = mccard_close(q->a);
        break;
    case MCSERV_FNO_SEEK:
        p->result = mccard_seek(q->a, q->b, q->c);
        break;
    case MCSERV_FNO_READ: {
        int n = q->b;
        void *tmp = n > 0 ? malloc((size_t)n) : NULL;
        if (n > 0 && !tmp) {
            p->result = MC_RES_DENIEDPERMIT;
            break;
        }
        p->result = mccard_read(q->a, tmp, n);
        if (p->result > 0 && q->ee_buf)
            sif0_write((void *)(uintptr_t)q->ee_buf, tmp, (uint32_t)p->result);
        free(tmp);
        break;
    }
    case MCSERV_FNO_WRITE:
        /* EE -> IOP data (retail: SIF DMA from the EE buffer) */
        p->result = q->ee_buf ? mccard_write(q->a, (const void *)(uintptr_t)q->ee_buf, q->b) : MC_RES_DENIEDPERMIT;
        break;
    case MCSERV_FNO_FLUSH:
        p->result = mccard_flush(q->a);
        break;
    case MCSERV_FNO_CHDIR:
        p->result = mccard_chdir(q->port, q->name, p->path);
        break;
    case MCSERV_FNO_GETDIR: {
        int maxent = q->b > 0 ? q->b : 0;
        mc_dirent *tmp = maxent ? (mc_dirent *)calloc((size_t)maxent, sizeof *tmp) : NULL;
        p->result = mccard_getdir(q->port, q->name, q->a, maxent, tmp);
        if (p->result > 0 && q->ee_buf && tmp)
            sif0_write((void *)(uintptr_t)q->ee_buf, tmp, (uint32_t)p->result * (uint32_t)sizeof *tmp);
        free(tmp);
        break;
    }
    case MCSERV_FNO_SETINFO: {
        mc_dirent info;
        memset(&info, 0, sizeof info);
        unsigned flags = (unsigned)q->a;
        if (q->ee_buf)
            memcpy(&info, (const void *)(uintptr_t)q->ee_buf, sizeof info);
        if (flags & MC_INFO_NAME) {
            memset(info.name, 0, sizeof info.name);
            memcpy(info.name, q->name2, MC_NAME_MAX);
            info.name[MC_NAME_MAX - 1] = 0;
        }
        p->result = mccard_setinfo(q->port, q->name, &info, flags);
        break;
    }
    case MCSERV_FNO_DELETE:
        p->result = mccard_delete(q->port, q->name);
        break;
    case MCSERV_FNO_FORMAT:
        p->result = mccard_format(q->port);
        break;
    case MCSERV_FNO_UNFORMAT:
        p->result = mccard_unformat(q->port);
        break;
    case MCSERV_FNO_ENTSPACE:
        p->result = mccard_entspace(q->port, q->name);
        break;
    case MCSERV_FNO_SLOTMAX:
        p->result = 1;
        break;
    default:
        p->result = MC_RES_DENIEDPERMIT;
        break;
    }
    /* card time: the save service's model (unknown functions take none) */
    p->cost = (uint32_t)mc_time_cost((int)fno, p->result);
}

static void *srv_mcserv(sif_rpc_ctx *c, void *user)
{
    (void)user;
    static mcserv_req q;
    memset(&q, 0, sizeof q);
    memcpy(&q, c->data, c->size < sizeof q ? c->size : sizeof q);
    q.name[MC_PATH_MAX - 1] = 0;
    switch (c->fno) {
    case MCSERV_FNO_INIT: case MCSERV_FNO_GETINFO: case MCSERV_FNO_OPEN: case MCSERV_FNO_CLOSE:
    case MCSERV_FNO_SEEK: case MCSERV_FNO_READ: case MCSERV_FNO_WRITE: case MCSERV_FNO_FLUSH:
    case MCSERV_FNO_CHDIR: case MCSERV_FNO_GETDIR: case MCSERV_FNO_SETINFO: case MCSERV_FNO_DELETE:
    case MCSERV_FNO_FORMAT: case MCSERV_FNO_UNFORMAT: case MCSERV_FNO_ENTSPACE: case MCSERV_FNO_SLOTMAX:
        break;
    default:
        c->unknown = 1;
        break;
    }
    mcserv_handle(c->fno, &q, &S.rep);
    return &S.rep;
}

int mcserv_install(void)
{
    RG_IOP_HLE("mcserv_install");
    mcserv_get_config();
    return sif_server_register(MCSERV_SID, "mcserv", (uint32_t)sizeof(mcserv_req), srv_mcserv, NULL);
}

int mcserv_installed(void)
{
    const sif_server_info *s = sif_server_find(MCSERV_SID);
    return s && s->fn == srv_mcserv;
}
