/* rgp:protos */
#define RGP_SELF_HunterBountyIterInit_3fcf00 1
#define RGP_SELF_getElem 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    u8 *unk8C;
} Tbl;

typedef struct {
    s32 unk0;
    Tbl *unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 1;
    u8 f5 : 1;
} Obj;

typedef struct {
    u8 pad0[0xC];
    Tbl *unkC;
} C94;

typedef struct {
    u8 pad0[0x94];
    C94 *unk94;
} C8;

typedef struct {
    u8 pad0[8];
    C8 *unk8;
} Arg1;

/*rgp*/

static inline void *getElem(Tbl *t, s32 i)
{
    return (i >= 0 && i < t->unk7C) ? t->unk8C + (i << 5) : NULL;
}

void HunterBountyIterInit_3fcf00(Obj *arg0, Arg1 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    s32 n;
    s32 i;

    if (arg1 == NULL) {
        return;
    }
    arg0->unk4 = arg1->unk8->unk94->unkC;
    arg0->f0 = arg2;
    arg0->f1 = arg3;
    arg0->f2 = arg4;
    arg0->f3 = arg5;
    arg0->f4 = arg6;
    arg0->f5 = arg7;
    arg0->unk8 = 0;
    arg0->unkA = -1;
    arg0->unkC = -1;
    arg0->unk8 = 0;
    n = arg0->unk4->unk7C;
    for (i = 0; i < n; i++) {
        if (((unsigned char)HunterBountyIterMatch_3fd070(arg0, getElem(arg0->unk4, i))) & 0xFF) {
            arg0->unk8++;
        }
    }
}
