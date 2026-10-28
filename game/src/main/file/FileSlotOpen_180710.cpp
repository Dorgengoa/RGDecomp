#include "types.h"

typedef struct Info {
    u8 m0;
    u8 m1;
    u8 m2;
    u8 m3;
    s32 m4[2];
    s8 name[0x60];
    s32 m6C;
    s32 m70;
    s32 m74;
    u8 m78;
} Info;

typedef struct B24 { s32 w[6]; } B24;
typedef struct B60 { s8 c[0x60]; } B60;

extern "C" {
s32 FilePathGetDeviceIndex_181a80(const char *);
s32 FileSlotAlloc_1814d0(void);
void FilePathApplyAlias_181590(char *, const char *);
s32 FileSlotOpenPath_1810a0(Info *, s32, const char *, s32);
void WaitSema(s32);
void SignalSema(s32);
char *strcpy(char *, const char *);
u32 strlen(const char *);
extern s32 D_0047E02C;
extern s32 D_00481214;
extern Info D_0049B100[12];
}

static inline Info *get(s32 i)
{
    if (i < 0 || i >= 12) {
        return 0;
    }
    if (D_0049B100[i].m0 == 0) {
        return 0;
    }
    if (D_0049B100[i].m78 != 0) {
        return 0;
    }
    return &D_0049B100[i];
}

static inline void clear(Info *p)
{
    p->m3 = 0;
    p->m2 = 0;
    p->m1 = 0;
    p->m0 = 0;
    p->m6C = 0;
    p->m70 = 1;
    p->m78 = 0;
}

struct Lock {
    s32 pad[3];
    s32 held;
};

static inline void lock_init(Lock *l, s32 nowait)
{
    *(volatile s32 *)&l->held = 0;
    if (!nowait) {
        if (D_0047E02C >= 0) {
            WaitSema(D_0047E02C);
        }
        *(volatile s32 *)&l->held = 1;
    }
}

static inline void lock_release(Lock *l)
{
    if (l->held) {
        if (D_0047E02C >= 0) {
            SignalSema(D_0047E02C);
        }
    }
    *(volatile s32 *)&l->held = 0;
}


#pragma opt_propagation off
extern "C" s32 FileSlotOpen_180710(const char *path, s32 arg1)
{
        Lock lk __attribute__((aligned(16)));
    char buf[0x100] __attribute__((aligned(16)));
    char tmp[0x100] __attribute__((aligned(16)));
    Info info __attribute__((aligned(16)));
    s32 h;
    s32 slot;
    s32 nw;
    Info *ip;
    Info *src;
    char *p;
    char c;

    h = FilePathGetDeviceIndex_181a80(path);
    if (h < 0) {
        return -1;
    }
    strcpy(buf, path);
    for (p = buf; (c = *p) != 0; p++) {
        if (c == 0x5C) {
            *p = '/';
        }
        if (*p == ' ') {
            return -1;
        }
    }
    path = buf;
    if (D_00481214 > 0) {
        { u8 *p_ = (u8 *)tmp; u32 n_ = 0x100; if (p_) do { *p_ = 0; n_--; p_++; } while (n_); }
        if (strlen(path) + 0x40 < 0x100) {
            FilePathApplyAlias_181590(tmp, path);
            path = tmp;
            h = FilePathGetDeviceIndex_181a80(path);
            if (h < 0) {
                return -1;
            }
        }
    }
    slot = FileSlotAlloc_1814d0();
    if (slot < 0) {
        return -1;
    }
    ip = &info;
    clear(&info);
    if (FileSlotOpenPath_1810a0(ip, h, path, arg1) < 0) {
        Info *e;
        if (D_0047E02C >= 0) {
            WaitSema(D_0047E02C);
        }
        e = get(slot);
        if (e != 0) {
            clear(e);
        }
        if (D_0047E02C >= 0) {
            SignalSema(D_0047E02C);
        }
        return -1;
    }
    nw = 0;
    {
        lock_init(&lk, nw);
        Info *e = get(slot);
        src = ip;
        e->m0 = src->m0;
        e->m1 = src->m1;
        e->m2 = src->m2;
        e->m3 = src->m3;
        *(B24 *)e->m4 = *(B24 *)src->m4;
        *(B60 *)e->name = *(B60 *)src->name;
        e->m6C = src->m6C;
        e->m70 = src->m70;
        e->m74 = src->m74;
        e->m78 = src->m78;
        lock_release(&lk);
        lock_release(&lk);
    }
    return slot;
}
