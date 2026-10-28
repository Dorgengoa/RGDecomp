/* rg-override: replaces game/src/main/file/CdDatArchiveOpen_183110.cpp sha256 473bc0af9658626d5889d0909599b60f5e9f8fe705c77f0009b98ae27fd5980f
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): the archive index (<name>.HD6) is
 *      read whole by name through the host file service, and the data archive
 *      (<name>.DAT) is opened by name: its rg_fs handle goes to rg_cddat_fd[slot] and
 *      Buf.w0 (was the archive's disc LSN) is 0, so a member's block offset is relative
 *      to its archive.  No sceCdSearchFile / sceCdRead / sceCdSync. */
/* rgp:spin */ extern "C" void rg_spin_hint(unsigned int); extern "C" void rg_spin_halt(unsigned int);
#line 1
#include "types.h"
#include "port/native_fs.h"
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
void Qsort_132d08(u8 *, s32, s32, void *);
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

/* rg-override: rg_fs handle of the data archive opened into each D_00495FB0 slot
 * (read by FileSlotOpenPath_1810a0's "cddat:" lookup); -1 = none */
int rg_cddat_fd[2] = {-1, -1};
extern u8 D_00495FB0[];

/* open by name or stop (rg_fs_open_or_die): retail retried the disc search forever */
static int OpenOrDie(const char *name) { return rg_fs_open_or_die(name, "CdDatArchiveOpen"); }

static inline s32 GetLang(void) {
    if (D_004811DC == 0) return 0;
    return D_004811E0;
}


s32 CdDatArchiveOpen_183110(Buf *buf, char *name, s32 minSize) {
    u8 mode[3];
    f32 names[2];
    char path[256] __attribute__((aligned(16)));
    char full[256] __attribute__((aligned(16)));
    CdFile f1 __attribute__((aligned(16)));
    CdFile f2 __attribute__((aligned(16)));
    s32 size;
    s32 r;
    u8 *d;
    s8 *p;
    u32 i;
    s32 h14;
    u8 *a0v;
    s32 a1v;
    int h;

    *(NA *)names = D_0047E010;
    *(Path256 *)path = *(Path256 *)D_0044A510;
    strcpy(full, ((char **)names)[GetLang() == 1]);
    strcat(full, path);
    strcat(path, name);
    strcat(path, D_00459780);
    strcat(full, name);
    strcat(full, D_00459788);
    /* rg-override: the index by name (was: search retried until the disc answered) */
    h = OpenOrDie(&full[7]);
    f1.lsn = 0;
    f1.size = (s32)rg_fs_size(h);
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
            for (; (rg_spin_halt(0x00183308), 1);) {
            }
        }
        buf->size = size;
    }
    /* rg-override: one host read of the whole index, zero-filled to the block size
     * (was: sceCdRead(lsn, size / 0x800) + sceCdSync(0), retried) */
    rg_fs_read_fill(h, 0, buf->data, size);
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
    Qsort_132d08(a0v, a1v, 8, (void *)CdDatEntryCompareName_183480);
    /* rg-override: the data archive by name; members are addressed relative to it */
    h = OpenOrDie(path);
    {
        s32 slot = (s32)(((u8 *)buf - D_00495FB0) / 12);
        if (slot >= 0 && slot < 2) rg_cddat_fd[slot] = h;
    }
    buf->w0 = 0;
    return 1;
}
}
