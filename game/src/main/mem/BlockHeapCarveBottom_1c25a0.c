/* rgp:protos */
#define RGP_SELF_BlockHeapCarveBottom_1c25a0 1
#define RGP_SELF_getfree 1
#define RGP_SELF_isfree 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
typedef struct Blk001c25a0 {
    u32 unk0;
    s32 unk4;
    u32 unk8;
    struct Blk001c25a0 *unkC;
    struct Blk001c25a0 *unk10;
} Blk001c25a0;

typedef struct S001c25a0 {
    s32 unk0;
    Blk001c25a0 *unk4;
    u8 pad8[0x24 - 8];
    Blk001c25a0 *unk24;
} S001c25a0;

static inline u8 isfree(Blk001c25a0 *b) { return !(b->unk0 != 0); }
static inline Blk001c25a0 *getfree(S001c25a0 *a)
{
    s32 i;
    if (a->unk4 == NULL) {
        return NULL;
    }
    for (i = 0; i < a->unk0; i++) {
        if (isfree(&a->unk4[i])) {
            return &a->unk4[i];
        }
    }
    return NULL;
}

u32 *BlockHeapCarveBottom_1c25a0(S001c25a0 *arg0, u32 arg1, u32 arg2)
{
    Blk001c25a0 *var_2;
    Blk001c25a0 *var_8;
    Blk001c25a0 *temp_3;
    u32 temp_4;
    u32 temp_hi;
    u32 var_7;

    if (arg0->unk24 == NULL) {
        return NULL;
    }
    var_2 = getfree(arg0);
    if (var_2 == NULL) {
        return NULL;
    }
    var_2->unk10 = NULL;
    var_2->unkC = NULL;
    var_2->unk0 = 0;
    var_2->unk8 = 0U;
    var_2->unk4 = 0;
    var_8 = arg0->unk24;
    while (var_8 != NULL) {
        var_7 = var_8->unk4;
        temp_hi = var_7 % arg2;
        if (temp_hi != 0) {
            var_7 += arg2 - temp_hi;
        }
        temp_4 = var_8->unk8;
        if ((temp_4 >= var_7) && ((u32) (temp_4 - var_7) >= arg1)) {
            var_2->unk0 = var_7;
            var_2->unk4 = (s32) (var_7 + arg1);
            var_2->unk8 = var_8->unk8;
            var_8->unk8 = var_2->unk0;
            temp_3 = var_8->unkC;
            var_2->unkC = temp_3;
            if (temp_3 != NULL) {
                temp_3->unk10 = var_2;
            }
            var_8->unkC = var_2;
            var_2->unk10 = var_8;
            return (u32 *) var_2;
        }
        var_8 = var_8->unkC;
    }
    return NULL;
}
