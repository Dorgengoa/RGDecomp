/* rg-override: replaces game/src/main/file/FileSlotOpenPath_1810a0.c sha256 934b2c831c9d1800d70b3cdcf69862c57854f1a0175920166ffd3300a3411234
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): "cdrom:" files and "cddat:" archive
 *      members are opened by name through the host file service (rg_fs_open) instead of
 *      sceCdSearchFile LSNs.  The slot keeps its layout: u.info.f0 = rg_fs handle (was 0),
 *      f2 = first 2048-byte block inside that file (was the disc LSN), f1/f3/f4/f5 as before. */
/* rgp:protos */
#define RGP_SELF_FileSlotOpenPath_1810a0 1
#define RGP_SELF_lookup 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_fs.h"

typedef struct { s32 f0, f1, f2, f3, f4, f5; } Info;
typedef struct { s32 x0, x4, x8, xC, x10, x14, x18, x1C; } DirEnt;
typedef struct { s32 x0, x4, pad[10]; } Stat;
typedef struct { u8 b[12]; } Dev;

typedef struct {
    u8 active;
    u8 type;
    u8 x2;
    u8 x3;
    union {
        Info info;
        struct { s32 a, b; char name[0x60]; } n;
    } u;
    s32 x6C;
    s32 x70;
    s32 x74;
} File;

s32 sceOpen_11b928(char *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 SignalSema(s32);
s32 WaitSema(s32);
char *strcpy(char *, const char *);
u32 strlen(const char *);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern s32 D_004811CC;
extern s32 D_004811DC;
extern s32 D_004811E0;
extern Dev D_00495FB0[];

#define LOCK() { if (D_0047E028 >= 0) WaitSema(D_0047E028); D_004811C4++; }
#define UNLOCK() { if (D_0047E028 >= 0) SignalSema(D_0047E028); D_004811C4--; }

/* rg-override: the archive's rg_fs handle per D_00495FB0 slot (CdDatArchiveOpen_183110) */
extern int rg_cddat_fd[2];

/* returns the matching archive's index + 1 (was: 1) */
static inline s32 lookup(char *p, DirEnt *ent) {
    s32 i;
    for (i = 0; i < D_004811CC; i++) {
        if (DirTableFindFile_182f70(&D_00495FB0[i], ent, p)) return i + 1;
    }
    return 0;
}

#pragma opt_propagation off
s32 FileSlotOpenPath_1810a0(File *f, u8 type, char *path, s32 arg3) {
    DirEnt ent __attribute__((aligned(16)));
    Info info __attribute__((aligned(16)));
    Stat st __attribute__((aligned(16)));
    s32 err;
    char *p;
    char *q;
    s8 c;
    s32 r;
    s32 e;
    s32 n;
    s32 k;

    f->type = type;
    f->x2 = 0;
    f->x6C = 0;
    err = 0;
    if (f->type == 1 || f->type == 4) {
        p = path;
        while ((c = *p++) != 0) {
            if (c == ':') break;
        }
        if (f->type == 1) {
            k = lookup(p, &ent);
            if (!k) return -1;
            /* rg-override: the member's file is the archive; ent.x4 is its block offset
             * in it (the archive's base, Buf.w0, is 0 under rg_fs) */
            info.f0 = (k - 1) < 2 ? rg_cddat_fd[k - 1] : -1;
            if (info.f0 < 0) return -1;
            info.f1 = ent.x8;
            info.f3 = (u32)ent.x8 >> 11;
            if (ent.x8 & 0x7FF) info.f3++;
            info.f2 = ent.x4;
            info.f4 = ent.x10;
            info.f5 = ent.xC;
        }
        if (f->type == 4) {
            Strupr_136390(p);
            q = p;
            while ((c = *q) != 0) {
                if (c == '/') *q = 0x5C;
                q++;
            }
            /* rg-override: by name through rg_fs (was: sceCd(Layer)SearchFile retried
             * until the disc answered).  A missing file fails at once, as the retail
             * search's "not found" (error 0) did. */
            LOCK();
            r = rg_fs_open(p);
            UNLOCK();
            if (r < 0) return -1;
            info.f0 = r;
            info.f1 = (s32)rg_fs_size(r);
            info.f3 = (u32)info.f1 >> 11;
            if (info.f1 & 0x7FF) info.f3++;
            info.f2 = 0;
            info.f4 = 0;
            info.f5 = info.f1;
        }
    }
    switch (f->type) {
    case 0:
        LOCK();
        f->u.n.a = sceOpen_11b928(path, 1);
        UNLOCK();
        if (f->u.n.a < 0) err = 1;
        f->x70 = 1;
        break;
    case 2:
        n = strlen(path) < 0x60;
        if (!n) {
            err = 1;
        } else {
            k = ':';
            while ((c = *path++) != 0) {
                if (c == k) break;
            }
            f->u.n.a = 999;
            if ((f->u.n.b = FileNetOpenStub_1850d0()) <= 0) err = 1;
            strcpy(f->u.n.name, path);
            f->x70 = 1;
        }
        break;
    case 4:
        f->u.info.f0 = info.f0;
        f->u.info.f1 = info.f1;
        f->u.info.f2 = info.f2;
        f->u.info.f3 = info.f3;
        f->u.info.f4 = info.f4;
        f->u.info.f5 = info.f5;
        f->x70 = 0x800;
        break;
    case 1:
        f->u.info.f0 = info.f0;
        f->u.info.f1 = info.f1;
        f->u.info.f2 = info.f2;
        f->u.info.f3 = info.f3;
        f->u.info.f4 = info.f4;
        f->u.info.f5 = info.f5;
        f->x70 = 0x800;
        break;
    default:
        err = 1;
        break;
    }
    if (err != 0) return -1;
    f->x74 = arg3;
    f->active = 1;
    return 0;
}
