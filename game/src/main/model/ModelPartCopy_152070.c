/* rgp:protos */
#define RGP_SELF_ModelPartCopy_152070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    u32 w[4];
} Quad0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 *unk8;
    s32 unkC;
    s32 unk10;
    u8 pad14[0x20 - 0x14];
    u128 unk20;
    u128 unk30;
    s32 unk40;
    s32 unk44;
} Obj0Arg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ModelPartCopy_152070(Obj0Arg *arg0, Obj0Arg *arg1, s32 arg2)
{
    s32 *o;
    s32 n;
    s32 i;
    s32 e;

    if (arg2 == 0) {
        arg1->unk0 = arg0->unk0;
        arg1->unk4 = arg0->unk4;
        arg1->unk8 = arg0->unk8;
        arg1->unkC = arg0->unkC;
        arg1->unk10 = arg0->unk10;
        arg1->unk20 = arg0->unk20;
        arg1->unk30 = arg0->unk30;
        arg1->unk40 = arg0->unk40;
        arg1->unk44 = arg0->unk44;
    } else {
        arg1->unk0 = arg0->unk0;
        arg1->unk4 = arg0->unk4;
        arg1->unk8 = arg0->unk8;
        while (arg0->unk8 != NULL) {
            n = *arg0->unk8;
            o = ((s32 *)MemStackNew_14e230(0x10, arg2));
            if (o != NULL) {
                ParallelArray3Clear_1531a0(o);
            }
            arg1->unk8 = o;
            if (o == NULL) {
                break;
            }
            if (ParallelArray3Alloc_153030(o, n, arg2) == 0) {
                break;
            }
            for (i = 0; i < n; i++) {
                e = ArrayGetChecked_153160(arg0->unk8, i);
                if (e != 0) {
                    ArraySetChecked_153120(arg1->unk8, i, ((s32)ModelPartEntryClone_14a990(e, arg2)));
                }
            }
            break;
        }
        arg1->unkC = arg0->unkC;
        arg1->unk10 = arg0->unk10;
        arg1->unk20 = arg0->unk20;
        arg1->unk30 = arg0->unk30;
        arg1->unk40 = arg0->unk40;
        arg1->unk44 = arg0->unk44;
    }
}
