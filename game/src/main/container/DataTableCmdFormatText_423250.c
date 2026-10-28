/* rgp:protos */
#define RGP_SELF_DataTableCmdFormatText_423250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x6C];
    u8    m6C[0x34];
    char *mA0;
    u8    pad0A4[0x10];
    void *mB4;
    s32   mB8;
} Pool;

extern Pool *D_004830F8;
/*rgp*/
/*rgp*/
extern s32   strlen(const char *s);
extern void  Sprintf_1343b8(char *dst, const char *src, s32 c, s32 d, s32 e);
/*rgp*/

s32 DataTableCmdFormatText_423250(R8 *a)
{
    Pool *p = D_004830F8;
    char  buf[0x200] __attribute__((aligned(16)));
    s32   n;

    p->mA0 = ((char *)DataTableStoreString_368ab0(p, SlotGetInt_15f720(a)));
    if (p->mA0 != 0) {
        if (strlen(p->mA0) > 0x1F0) p->mA0[0x1EF] = 0;
        Sprintf_1343b8(buf, p->mA0, 0x3E7, 0x5A, 0x270F);
        n = strlen(buf) + 1;
        p->mB4 = ArenaStrDup_3701d0(p->m6C, buf, -1, 1, 1);
        p->mB8 = n;
    } else {
        p->mB4 = 0;
        p->mB8 = 0;
    }
    return 1;
}
