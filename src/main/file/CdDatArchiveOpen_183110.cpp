#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Names { f32 a; f32 b; } Names;
typedef struct Path256 { char s[256]; } Path256;
typedef struct CdFile { s32 lsn; s32 size; u8 pad[0x28]; } CdFile;
typedef struct Buf { s32 w0; u8 *data; s32 size; } Buf;

void OperatorDeleteArray_100820(u8 *);
u8 *OperatorNewArray_100900(s32);
void DelayThread_117618(s32);
s32 sceCdLayerSearchFile_1297e0(CdFile *, char *, s32);
s32 sceCdSearchFile_129ae0(CdFile *, char *);
s32 sceCdRead_12a728(s32, s32, u8 *, u8 *);
s32 sceCdGetError_12aa98(void);
void Qsort_132d08(u8 *, s32, s32, void *);
s32 sceCdSync(s32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
extern char D_0044A510[];
extern char D_00459780[];
extern char D_00459788[];
typedef struct NP { char *a; char *b; } NP;
typedef struct NA { char *p[2]; } NA;
extern NA D_0047E010 __attribute__((section(".sdata")));
extern u8 *D_004811C8;
extern s32 D_004811DC;
extern s32 D_004811E0;
void CdDatEntryCompareName_183480(void);

static inline s32 GetLang(void) {
    if (D_004811DC == 0) return 0;
    return D_004811E0;
}

static inline bool ReadOk(s32 lsn, s32 n, u8 *dst, u8 *mode) {
    return sceCdRead_12a728(lsn, n, dst, mode);
}

s32 CdDatArchiveOpen_183110(Buf *buf, char *name, s32 minSize) {
    u8 mode[3];
    f32 names[2];
    char path[256];
    char full[256];
    CdFile f1;
    CdFile f2;
    s32 size;
    s32 r;
    u8 *d;
    s8 *p;
    u32 i;
    s32 h14;
    u8 *a0v;
    s32 a1v;

    *(NA *)names = D_0047E010;
    *(Path256 *)path = *(Path256 *)D_0044A510;
    strcpy(full, ((char **)names)[GetLang() == 1]);
    strcat(full, path);
    strcat(path, name);
    strcat(path, D_00459780);
    strcat(full, name);
    strcat(full, D_00459788);
    do {
        do {
            if (D_004811DC == 0) {
                r = sceCdSearchFile_129ae0(&f1, &full[7]);
            } else {
                r = sceCdLayerSearchFile_1297e0(&f1, &full[7], GetLang());
            }
        } while (r == 0);
        sceCdSync(0);
    } while (sceCdGetError_12aa98() != 0);
    size = f1.size;
    if (size % 0x800 != 0) {
        size = (size / 0x800 + 1) * 0x800;
    }
    if (minSize % 0x800 != 0) {
        minSize = (minSize / 0x800 + 1) * 0x800;
    }
    if (minSize > 0 && size < minSize) {
        size = minSize;
    }
    if (minSize == 0 || buf->size < size) {
        OperatorDeleteArray_100820(buf->data);
        buf->data = NULL;
        buf->size = 0;
        buf->data = OperatorNewArray_100900(size / 16 * 16);
        if (buf->data == NULL) {
            for (;;) {
            }
        }
        buf->size = size;
    }
    mode[0] = 0;
    if (D_004811DC) {
        mode[1] = 0;
    } else {
        mode[1] = 1;
    }
    mode[2] = 0;
    for (;;) {
        if (ReadOk(f1.lsn, size / 0x800, buf->data, mode)) {
            sceCdSync(0);
            r = sceCdGetError_12aa98();
        } else {
            r = -1;
        }
        if (r == 0) break;
        DelayThread_117618(100);
    }
    d = buf->data;
    p = (s8 *)(d + *(s32 *)(d + 4));
    for (i = 0; i < *(u32 *)(d + 8); i++) {
        if (p[i] == 0x5C) {
            p[i] = 0x2F;
        }
    }
    h14 = *(s32 *)(d + 0x14);
    a0v = d + *(s32 *)(d + 0x28);
    a1v = *(s32 *)(d + 0x24);
    D_004811C8 = d + h14;
    Qsort_132d08(a0v, a1v, 8, CdDatEntryCompareName_183480);
    do {
        do {
            if (D_004811DC == 0) {
                r = sceCdSearchFile_129ae0(&f2, path);
            } else {
                r = sceCdLayerSearchFile_1297e0(&f2, path, GetLang());
            }
        } while (r == 0);
        sceCdSync(0);
    } while (sceCdGetError_12aa98() != 0);
    buf->w0 = f2.lsn;
    return 1;
}
}
