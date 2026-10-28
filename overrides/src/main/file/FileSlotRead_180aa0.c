/* rg-override: replaces game/src/main/file/FileSlotRead_180aa0.c sha256 ed2d4fee6a834d2f724641427daefc98c0e8faf192b97fc3921318a9917e1e02
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): "cdrom:"/"cddat:" slots read their
 *      2048-byte blocks with one host read by byte offset (rg_fs_read_fill on the slot's
 *      rg_fs handle) instead of sceCdRead(lsn + block) + sceCdSync(0).  Same bytes, same
 *      buffer extent (whole blocks, zeros past the end of the file), same result. */
/* rgp:protos */
#define RGP_SELF_FileSlotRead_180aa0 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_fs.h"
#pragma divbyzerocheck on

typedef struct Entry {
    u8 used;
    u8 type;
    u8 pad2[2];
    s32 handle;     /* cdrom/cddat: rg_fs handle (rg-override) */
    s32 pad8;
    s32 lsn;        /* cdrom/cddat: first block in that file (rg-override) */
    s32 nsect;
    u8 pad14[0x58];
    u32 pos;
    u32 bsize;
    u32 flags;
    u8 busy;
    u8 pad79[3];
} Entry;

typedef struct CdMode {
    u8 trycount;
    u8 spindlctrl;
    u8 datapattern;
    u8 pad;
} CdMode;

extern void WaitSema(s32);
extern void SignalSema(s32);
extern s32 sceRead_11bf70(s32, void *, u32);
/*rgp*/
/*rgp*/
extern void DelayThread_117618(s32);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern s32 D_004811DC;
extern Entry D_0049B100[12];
extern u8 D_0049B178[0x400];

static inline Entry *get(s32 fd) {
    Entry *e;
    if (fd < 0 || fd >= 12) {
        return 0;
    }
    e = &D_0049B100[fd];
    if (e->used == 0) {
        return 0;
    }
    if (D_0049B178[fd * 0x7C] != 0) {
        return 0;
    }
    return e;
}

s32 FileSlotRead_180aa0(s32 fd, void *buf, u32 size) {
    CdMode mode __attribute__((aligned(16)));
    s32 sect;
    Entry *e;
    s32 n;
    s32 err;
    s32 r;
    s32 k;

    e = get(fd);
    if (e == 0) {
        return -1;
    }
    if (D_0047E028 >= 0) {
        WaitSema(D_0047E028);
    }
    D_004811C4++;
    switch (e->type) {
    case 0:
        n = sceRead_11bf70(e->handle, buf, size);
        if (n >= 0) {
            e->pos += n;
        }
        break;
    case 2:
        n = FileNetReadStub_1850c0();
        if (n >= 0) {
            e->pos += n;
        }
        break;
    case 4:
    case 1:
        sect = e->pos / e->bsize;
        k = size / e->bsize;
        if (size % e->bsize != 0) {
            k++;
        }
        if (e->nsect < sect + k) {
            k = e->nsect - sect;
        }
        /* rg-override: one positional host read (was: sceCdRead + sceCdSync(0),
         * retried with CdWaitFileFound/DelayThread until the drive succeeded) */
        if (k > 0) {
            if (rg_fs_read_fill(e->handle, ((long long)e->lsn + sect) * 0x800, buf,
                                (long long)k * 0x800) < 0) {
                k = -1;
            }
        }
        if (k < 0) {
            n = k;
        } else {
            n = k * e->bsize;
            e->pos += n;
        }
        break;
    default:
        n = -1;
        break;
    }
    if (D_0047E028 >= 0) {
        SignalSema(D_0047E028);
    }
    D_004811C4--;
    return n;
}
