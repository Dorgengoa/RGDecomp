#include "types.h"

/* Stack locals in REVERSE declaration order: the 4-byte out-parameter at
   0x1F3C is declared first and the 0x60 object last.
   `srl` (not `sra`) on the length makes it unsigned; retail falls through
   into `(n >> 4) + 1`, so THAT is the `if` body and `(n & 0xF)` is the test.
   The 48*n index is mwcc's sll/addu/sll strength reduction of `* 0x30`. */

extern u32 strlen(const char *);
extern char *strcpy(char *, const char *);

typedef struct Hdr {
    char *m00;
    s32 m04;
    void *m08;
} Hdr;

extern s32 ArchiveCountEntries_181bb0(s32);
extern s32 ArchiveFindByExt_181be0(s32, char *, s32 *, s32, s32, s32 *);
extern char *MemStackAllocQw_14d950(s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern void *ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern s32 ArchiveGetFileData_181dd0(s32, char *, s32 *);
extern void TextReaderCtor_15f140(void *);
extern void BuildKeywordHashTable_15f270(void *, char *);
extern void TextReaderOpen_15f1b0(void *, s32, s32);
extern void TextReaderParseAll_15f3f0(void *);
extern void MapModelEntryCtor_1956f0(void);

extern char D_00459FF0[];
extern char D_00459FF8[];
extern char D_0045A000[];
extern char D_0044A9A0[];

extern Hdr *D_00481320;
extern s32 D_00481318;
extern s32 D_0048131C;
extern s32 D_00481324;
extern s32 D_00481328;
extern s32 D_0048132C;
extern s32 D_00481330;
extern s32 D_00481334;
extern s32 D_00481338;

void MapModelCfgLoad_195550(Hdr *p0, const char *p1, s32 p2, s32 p3, s32 p4)
{
    s32 v;
    s32 b1[0x200];
    s32 b0[0x200];
    u8 obj[0xED0];
    u32 n;
    s32 c;
    char *q;
    s32 cnt;
    void *tbl;
    s32 r;

    D_00481320 = p0;
    ArchiveCountEntries_181bb0(p2);
    p0->m04 = ArchiveFindByExt_181be0(p2, D_00459FF0, b1, 0x200, 0, b0);
    p0->m04 = p0->m04 + ArchiveFindByExt_181be0(p2, D_00459FF8, b1, 0x200, 0, b0);
    p0->m00 = 0;
    if (p1 != 0) {
        n = strlen(p1) + 1;
        if (n & 0xF) {
            c = (n >> 4) + 1;
        } else {
            c = n >> 4;
        }
        q = MemStackAllocQw_14d950(p3, c);
        p0->m00 = q;
        strcpy(q, p1);
    }
    cnt = p0->m04;
    tbl = MemStackNew_14e1b0(cnt * 0x30 + 0x10, p3);
    p0->m08 = ConstructNewArray_100710(tbl, MapModelEntryCtor_1956f0, 0, 0x30, cnt);
    D_00481318 = 0;
    D_0048131C = p0->m04;
    D_00481324 = (s32)p0->m08;
    D_0048132C = p3;
    D_00481330 = p2;
    D_00481334 = p4;
    D_00481328 = 0;
    D_00481338 = 0;
    r = ArchiveGetFileData_181dd0(p2, D_0045A000, &v);
    TextReaderCtor_15f140(obj);
    BuildKeywordHashTable_15f270(obj, D_0044A9A0);
    TextReaderOpen_15f1b0(obj, r, v);
    TextReaderParseAll_15f3f0(obj);
}
