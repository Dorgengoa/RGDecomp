#include "types.h"

typedef struct Obj {
    s32 h;
    s32 dev;
    s32 x8;
    s32 pad0C;
    s32 x10;
    s32 x14;
} Obj;

extern char *Index_1308f0(char *, s32);
extern void Sprintf_1343b8(char *, const char *, ...);
extern s32 Strncasecmp_134ce8(char *, const char *, s32);
extern s8 Toupper_1363e0(s8);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, s32);
extern char *strcat(char *, const char *);
extern s32 strcmp(const char *, const char *);
extern s32 strlen(const char *);
extern s32 GetSoundStreamTable_1bf7c0(void);
extern void SoundStreamHandleCreate_1bf990(s32 *, s32, s32, s32);
extern void SoundStreamHandleResolve_1bfa50(s32 *arg0, s32 arg1, s32 *arg2);
extern void SoundStreamLockDtor_1bfab0(s32 *arg0, s32 arg1);
extern s32 SoundStreamLockAcquire_1bfb40(s32 *arg0);
extern void SoundStreamQueueOpen_1c0360(s32, char *);
extern s32 SoundStreamWaitFileSize_1c02a0(s32);
extern char D_0045B1B8[];
extern char D_0045B1C0[];
extern char D_0045B1C8[];
extern char D_0045B1D0[];
extern char D_0045B1D8[];
extern char D_0045B1E0[];
extern char D_0045B1F0[];
extern char D_0045B1F8[];
extern s32 D_004817F0;

s32 MovieStreamOpen_1d3700(Obj *o, char *path)
{
    s32 sp1CC;
    s32 sp1C8;
    s32 sp1C4;
    char full[0x104];
    char dev[0x40];
    char *c;
    s32 n;
    s32 len;
    s32 i;
    char *q;
    char *ext;
    char *p;
    s32 h;

    c = Index_1308f0(path, ':');
    if (c != 0) {
        n = c - path;
        strncpy(dev, path, n);
        dev[n] = 0;
        if (strcmp(dev, D_0045B1B8) == 0) {
            len = strlen(c + 1);
            ext = D_0045B1C0;
            o->dev = 1;
            for (i = 0; i < len; i++) {
                if ((c + i)[1] == '/') (c + i)[1] = 0x5C;
                q = (c + (u32)i) + 1;
                *q = Toupper_1363e0(*q);
            }
            Sprintf_1343b8(full, D_0045B1C8, c + 1, ext);
        } else {
            o->dev = 0;
            Sprintf_1343b8(full, D_0045B1D0, dev, c + 1);
        }
    } else {
        strcpy(dev, D_0045B1D8);
        o->dev = 0;
        Sprintf_1343b8(full, D_0045B1D0, dev, path);
    }
    o->dev = 1;
    strcpy(full, D_0045B1E0);
    len = strlen(path);
    for (i = 0; i < len; i++) {
        q = path + i;
        *q = Toupper_1363e0(*q);
    }
    strcat(full, path);
    strcat(full, D_0045B1F0);
    D_004817F0 = 0;
    for (p = full; *p != 0; p++) {
        if (Strncasecmp_134ce8(p, D_0045B1F8, 4) == 0) {
            D_004817F0 = 1;
            break;
        }
    }
    h = GetSoundStreamTable_1bf7c0();
    SoundStreamHandleCreate_1bf990(&sp1C8, h, o->x10, o->x14);
    sp1C4 = o->h = sp1C8;
    SoundStreamHandleResolve_1bfa50(&sp1CC, h, &sp1C4);
    if (sp1CC != 0) {
        SoundStreamQueueOpen_1c0360(SoundStreamLockAcquire_1bfb40(&sp1CC), full);
        o->x8 = SoundStreamWaitFileSize_1c02a0(SoundStreamLockAcquire_1bfb40(&sp1CC));
    }
    SoundStreamLockDtor_1bfab0(&sp1CC, -1);
    return 1;
}
