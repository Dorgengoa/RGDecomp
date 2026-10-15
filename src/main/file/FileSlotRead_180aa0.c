#include "types.h"
#pragma divbyzerocheck on

typedef struct Entry {
    u8 used;
    u8 type;
    u8 pad2[2];
    s32 handle;
    s32 pad8;
    s32 lsn;
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
extern s32 FileNetReadStub_1850c0(void *, void *, u32, u32);
extern s32 sceCdRead_12a728(s32, s32, void *, CdMode *);
extern void sceCdSync(s32);
extern s32 sceCdGetError_12aa98(void);
extern void CdWaitFileFound_180290(void);
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
    CdMode mode;
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
        n = FileNetReadStub_1850c0(&e->lsn, buf, e->pos, size);
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
        mode.trycount = 0;
        if (D_004811DC != 0) {
            mode.spindlctrl = 0;
        } else {
            mode.spindlctrl = 1;
            if (e->flags & 1) {
                mode.spindlctrl = 0;
            }
        }
        mode.datapattern = 0;
        while (k != 0) {
            err = 0;
            if (sceCdRead_12a728(e->lsn + sect, k, buf, &mode) != 0) {
                sceCdSync(0);
                r = sceCdGetError_12aa98();
            } else {
                r = -1;
                err = 1;
            }
            if (r == 0) {
                break;
            }
            if (r == 0x31 || err != 0) {
                CdWaitFileFound_180290();
            }
            DelayThread_117618(100);
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
