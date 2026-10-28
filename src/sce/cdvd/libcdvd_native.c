/* SPDX-License-Identifier: CC0-1.0 */
/* libcdvd for RG_NATIVE_ONLY builds (docs/NATIVE-ONLY.md): the same entry points as
 * libcdvd.c, with no CDVD sector / drive model behind them.  The game's file layer
 * reads through the native file service (docs/NATIVE-FS.md) and calls none of these on
 * the default path except sceCdChangeThreadPriority; the rest stay defined because
 * game objects that are linked (but not run) still name them.
 *
 * The "no drive" contract: the data folder is a PS2 DVD that is always ready (dual
 * layer, as the native CdDatArchivesInit override reports), searches answer by name
 * from rg_fs (lsn 0: there are no sectors), a sector read is refused (command not
 * accepted, reported once on stderr as an unconverted disc user), the drive is idle. */
#include "libcdvd.h"

#include <stdio.h>
#include <string.h>

#include "rg_fs.h"

static struct {
    sceCdCBFunc callback;
    void (*poff)(void *);
    void *poff_arg;
    int mmode;
    int warned_read;
} s;

int sceCdHleMount(const char *data_dir) { return rg_fs_mounted() || rg_fs_mount(data_dir) >= 0; }
void sceCdHleUnmount(void) {}

void sceCdHlePowerOff(void)
{
    if (s.poff)
        s.poff(s.poff_arg);
}

void sceCdHleSetReadHook(sceCdHleReadHook fn, void *user)
{
    (void)fn; /* nothing reads sectors: the hook would never fire (and is not model state) */
    (void)user;
}

int sceCdInit(int mode)
{
    if (mode == SCECdEXIT)
        s.callback = NULL;
    return 1;
}

int sceCdMmode(int media)
{
    s.mmode = media;
    return 1;
}

int sceCdChangeThreadPriority(int priority)
{
    (void)priority; /* the IOP-side CDVD thread does not exist */
    return 1;
}

int sceCdGetDiskType(void) { return SCECdPS2DVD; }

int sceCdDiskReady(int mode)
{
    (void)mode;
    return SCECdComplete;
}

int sceCdTrayReq(int param, uint32_t *traychk)
{
    (void)param;
    if (traychk)
        *traychk = 0;
    return 1;
}

int sceCdReadDvdDualInfo(int *on_dual, uint32_t *layer1_start)
{
    if (on_dual)
        *on_dual = 1;
    if (layer1_start)
        *layer1_start = 0;
    return 1;
}

int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer)
{
    (void)layer;
    if (!fp || !name)
        return 0;
    int h = rg_fs_open(name);
    if (h < 0)
        return 0;
    memset(fp, 0, sizeof *fp);
    fp->lsn = 0; /* no sectors */
    fp->size = (uint32_t)rg_fs_size(h);
    const char *base = strrchr(rg_fs_name(h), '/');
    base = base ? base + 1 : rg_fs_name(h);
    size_t n = strlen(base);
    if (n > 13)
        n = 13;
    memcpy(fp->name, base, n);
    memcpy(fp->name + n, ";1", 2);
    return 1;
}

int sceCdSearchFile(sceCdlFILE *fp, const char *name) { return sceCdLayerSearchFile(fp, name, 0); }

int sceCdRead(uint32_t lsn, uint32_t sectors, void *buf, sceCdRMode *mode)
{
    (void)buf;
    (void)mode;
    if (!s.warned_read) {
        s.warned_read = 1;
        fprintf(stderr, "libcdvd: sceCdRead(lsn %u, %u sectors) refused: native-only build has no "
                        "sector model (an unconverted disc reader)\n", (unsigned)lsn, (unsigned)sectors);
    }
    return 0;
}

int sceCdSeek(uint32_t lsn)
{
    (void)lsn;
    return 1;
}

int sceCdSync(int mode)
{
    (void)mode;
    return 0; /* idle */
}

int sceCdGetError(void) { return SCECdErNO; }
int sceCdBreak(void) { return 1; }

sceCdCBFunc sceCdCallback(sceCdCBFunc func)
{
    sceCdCBFunc old = s.callback;
    s.callback = func;
    return old;
}

void *sceCdPOffCallback(void (*func)(void *), void *userdata)
{
    void *old = (void *)s.poff;
    s.poff = func;
    s.poff_arg = userdata;
    return old;
}
