/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryBlob_413270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Tok {
    s32 a;
    s32 b;
} Tok;

extern void *D_004830F8;
extern s16 D_004830FC;

/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *dst, const void *src, s32 n);

s32 DataTableCmdEntryBlob_413270(Tok *p)
{
    u8 buf[0x2000] __attribute__((aligned(16)));
    u8 *ctx;
    u8 *ent;
    s32 n;
    s32 i;
    s32 len;
    void *q;

    ctx = (u8 *)D_004830F8;
    n = *(s16 *)(ctx + 0x7C);
    if (n <= 0) {
        return 1;
    }
    i = D_004830FC - 1;
    if (i >= n) {
        return 1;
    }
    ent = *(u8 **)(ctx + 0x8C) + i * 32;
    len = Base64Decode_36a700(buf, SlotGetInt_15f720(p));
    *(s16 *)(ent + 0x14) = len;
    *(void **)(ent + 0x18) = 0;
    if (len > 0) {
        q = ArenaAlloc_3702f0(ctx + 0x6C, len, 1);
        *(void **)(ent + 0x18) = q;
        memcpy(q, buf, len);
    }
    return 1;
}
