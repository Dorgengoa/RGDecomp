#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x6C];
    u8    m6C[0x30];
    char *m9C;
    u8    pad0A0[0xC];
    void *mAC;
    s32   mB0;
} Pool;

extern Pool *D_004830F8;
extern s32   SlotGetInt_15f720(R8 *q);
extern char *DataTableStoreString_368ab0(Pool *p, s32 h);
extern s32   strlen(const char *s);
extern void  Sprintf_1343b8(char *dst, const char *src, s32 c, s32 d);
extern void *ArenaStrDup_3701d0(void *m, char *s, s32 c, s32 d, s32 e);

s32 DataTableCmdFormatText_423300(R8 *a)
{
    Pool *p = D_004830F8;
    char  buf[0x200];
    s32   n;

    p->m9C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(a));
    if (p->m9C != 0) {
        if (strlen(p->m9C) > 0x1F0) p->m9C[0x1EF] = 0;
        Sprintf_1343b8(buf, p->m9C, 0x3E7, 0x5A);
        n = strlen(buf) + 1;
        p->mAC = ArenaStrDup_3701d0(p->m6C, buf, -1, 1, 1);
        p->mB0 = n;
    } else {
        p->mAC = 0;
        p->mB0 = 0;
    }
    return 1;
}
