/* SPDX-License-Identifier: CC0-1.0 */
/* libcdvd over the CDVD model (src/ps2/cdvd). Written from the libcdvd documentation
 * and the game's call sites, not from Sony's code. See docs/CDVD.md. */
#include "libcdvd.h"

#include <stdlib.h>
#include <string.h>

#include "cdvd.h"

static struct {
    cdvd_disc *disc;
    sceCdCBFunc callback;
    void (*poff)(void *);
    void *poff_arg;
    int mmode;
} s;

static void on_done(void *ctx, int func, int error) {
    (void)ctx;
    (void)error;
    if (s.callback) s.callback(func);
}

int sceCdHleMount(const char *data_dir) {
    char err[512];
    cdvd_disc *d = cdvd_disc_open(data_dir, err, sizeof err);
    if (!d) {
        cdvd_log(CDVD_LOG_ERROR, "%s", err);
        return 0;
    }
    sceCdHleUnmount();
    s.disc = d;
    cdvd_drive_reset(d);
    cdvd_drive_set_done(on_done, NULL);
    cdvd_log(CDVD_LOG_INFO, "mounted %s: %u files, %s, layer1_start %u", data_dir,
             (unsigned)cdvd_disc_file_count(d), cdvd_disc_dual(d) ? "dual layer" : "single layer",
             (unsigned)cdvd_disc_layer1_start(d));
    return 1;
}

void sceCdHleUnmount(void) {
    if (!s.disc) return;
    cdvd_drive_reset(NULL);
    cdvd_disc_close(s.disc);
    s.disc = NULL;
}

void sceCdHlePowerOff(void) {
    if (s.poff) s.poff(s.poff_arg);
}

int sceCdInit(int mode) {
    if (mode == SCECdEXIT) {
        s.callback = NULL;
        return 1;
    }
    if (!s.disc) {
        const char *dir = getenv("RG_DATA");
        if (!sceCdHleMount(dir && *dir ? dir : "data")) return 0;
    }
    cdvd_drive_set_done(on_done, NULL);
    return 1;
}

int sceCdMmode(int media) {
    s.mmode = media;
    return 1;
}

int sceCdChangeThreadPriority(int priority) {
    (void)priority; /* the IOP-side CDVD thread does not exist here */
    return 1;
}

int sceCdGetDiskType(void) { return s.disc ? SCECdPS2DVD : SCECdNODISC; }

int sceCdDiskReady(int mode) {
    (void)mode;
    return s.disc ? SCECdComplete : SCECdNotReady;
}

int sceCdTrayReq(int param, uint32_t *traychk) {
    (void)param;
    if (traychk) *traychk = 0; /* the tray has not been opened */
    return 1;
}

int sceCdReadDvdDualInfo(int *on_dual, uint32_t *layer1_start) {
    int dual = s.disc && cdvd_disc_dual(s.disc);
    if (on_dual) *on_dual = dual;
    if (layer1_start) *layer1_start = dual ? cdvd_disc_layer1_start(s.disc) : 0;
    return 1;
}

int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer) {
    cdvd_file_info fi;
    const char *base;
    if (!s.disc || !fp || !name) return 0;
    /* libcdvd refuses a search while an N-command is pending (it checks sceCdSync(1)) and
     * the game retries in a loop. Nothing advances virtual time inside such a loop, so let
     * the pending command finish first instead; only the timing differs. */
    if (cdvd_drive_busy()) cdvd_drive_wait();
    if (!cdvd_disc_find(s.disc, name, layer, &fi)) {
        cdvd_log(CDVD_LOG_WARN, "sceCdSearchFile: '%s' not found on layer %d", name, layer);
        return 0;
    }
    memset(fp, 0, sizeof *fp);
    {
        int l = (cdvd_disc_dual(s.disc) && layer == 1) ? 1 : 0;
        fp->lsn = fi.lsn[l] == CDVD_NO_LSN ? 0 : fi.lsn[l]; /* an empty file has no sector */
    }
    fp->size = (uint32_t)fi.size;
    base = strrchr(fi.path, '/');
    base = base ? base + 1 : fi.path;
    {
        size_t n = strlen(base);
        if (n > 13) n = 13;
        memcpy(fp->name, base, n);
        memcpy(fp->name + n, ";1", 2);
    }
    return 1;
}

int sceCdSearchFile(sceCdlFILE *fp, const char *name) { return sceCdLayerSearchFile(fp, name, 0); }

static sceCdHleReadHook g_read_hook;
static void *g_read_hook_user;

void sceCdHleSetReadHook(sceCdHleReadHook fn, void *user) {
    g_read_hook = fn;
    g_read_hook_user = user;
}

int sceCdRead(uint32_t lsn, uint32_t sectors, void *buf, sceCdRMode *mode) {
    if (g_read_hook)
        g_read_hook(g_read_hook_user, lsn, sectors, buf, mode ? mode->datapattern : 0);
    if (mode && mode->datapattern != SCECdSecS2048) {
        cdvd_log(CDVD_LOG_WARN, "sceCdRead: sector pattern %d not supported", mode->datapattern);
        return cdvd_drive_read(lsn, 0, buf); /* accepted, completes with SCECdErPRM */
    }
    return cdvd_drive_read(lsn, sectors, buf);
}

int sceCdSeek(uint32_t lsn) { return cdvd_drive_seek(lsn); }

int sceCdSync(int mode) {
    if ((mode & 1) == 0) { /* 0 (and 16): block until the N-command completes */
        cdvd_drive_wait();
        return 0;
    }
    return cdvd_drive_busy() ? 1 : 0;
}

int sceCdGetError(void) { return cdvd_drive_error(); }

int sceCdBreak(void) {
    cdvd_drive_break();
    return 1;
}

sceCdCBFunc sceCdCallback(sceCdCBFunc func) {
    sceCdCBFunc old = s.callback;
    s.callback = func;
    return old;
}

void *sceCdPOffCallback(void (*func)(void *), void *userdata) {
    void *old = (void *)s.poff;
    s.poff = func;
    s.poff_arg = userdata;
    return old;
}
