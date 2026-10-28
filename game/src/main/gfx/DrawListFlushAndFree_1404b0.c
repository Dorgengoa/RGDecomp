/* rgp:protos */
#define RGP_SELF_DrawListFlushAndFree_1404b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Owner0014dad0 {
    u8 pad0[0x8];
    s32 unk8;
} Owner0014dad0;

typedef struct Obj0014dad0 {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x34 - 0x30];
    s32 unk34;
    Owner0014dad0 *unk38;
} Obj0014dad0;

typedef struct Link1404b0 {
    struct Link1404b0 *a;
    struct Link1404b0 *b;
} Link1404b0;

typedef struct T1404b0 {
    u8 pad0[0x3BA4];
    Obj0014dad0 *f3BA4;
    Link1404b0 *f3BA8;
    s32 f3BAC;
    s32 *f3BB0;
    u8 pad_BB4[0x3BBC - 0x3BB4];
    s32 f3BBC;
} T1404b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void DrawListFlushAndFree_1404b0(T1404b0 *p)
{
    s32 i;
    s32 *arr;
    s32 val;

    if (p->f3BA4 == 0) {
        return;
    }
    if (p->f3BAC == 0) {
        DrawListSortBuckets_140890(p);
        for (i = 0; i < p->f3BBC; i++) {
            arr = p->f3BB0;
            val = (arr != 0) ? arr[i] : i;
            DrawListAddTexLoad_1418c0(p, val, 1.0f);
            DrawListEmitBucket_1405a0(p, i);
        }
    }
    MemStackReturnToOwnerMaybe_14dad0(p->f3BA4);
    MemStackHeapFree_14dcb0(p->f3BA4, p->f3BA8);
    p->f3BA4 = 0;
}
