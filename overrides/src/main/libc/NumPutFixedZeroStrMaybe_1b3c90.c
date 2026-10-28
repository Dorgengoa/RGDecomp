/* rg-override: replaces game/src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c sha256 66f3066daa985433c7a3e7529367183597d48415c6e4d22653b7b1856cb6622d
 * why: the file's own view passed the size as u64 (8 stack bytes) to StringReplaceRange_1b3da0(void *, s32 x5):
 *      on i686 every later argument landed one slot off (the range became (0, &sp4F) -> StringReplace read
 *      first = 0).  Retail 1b3d40: a1 = size, a2 = 0, a3 = &sp4F, t0 = &sp4F + 1, t1 = lb tag (sign-extended).
 *      protos_irabi.py BUG-kind (2026-10-25 protos manual-row close-out); the view kept a by-value Tag, so
 *      the stage left the call (manual-call). MSL num_put fixed-format padding: not on a tested path. */
/* rgp:protos */
#define RGP_SELF_NumPutFixedZeroStrMaybe_1b3c90 1
#define RGP_SELF_StringReplaceRange_1b3da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef union {
    struct {
        unsigned char flag : 1;
        unsigned char size : 7;
    } __attribute__((aligned(8))) s;
    struct {
        u32 flag;
        s32 size;
        u8 *data;
    } l;
} Str001B3C90;

typedef struct {
    u8 pad0[0x28];
    s64 unk28;
    u8 pad30[0x38 - 0x30];
    u16 unk38;
} Obj001B3C90;

typedef struct { s8 x; } Tag001B3C90;
/*rgp*/          /* extern */
void StringReplaceRange_1b3da0(Str001B3C90 *, s32, s32, s8 *, s8 *, s32); /* the definition's shape */

void NumPutFixedZeroStrMaybe_1b3c90(Obj001B3C90 *arg0, s8 arg1, s8 arg2, Str001B3C90 *arg3) {
    s8 sp4F;
    Tag001B3C90 tag __attribute__((aligned(16)));
    s64 temp_16;
    u8 *var_7;

    temp_16 = arg0->unk28;
    if (arg3->l.flag & 1) {
        var_7 = arg3->l.data;
        arg3->l.size = 1;
    } else {
        var_7 = (u8 *) arg3 + 1;
        arg3->s.size = 1;
    }
    var_7[0] = arg1;
    var_7[1] = 0;
    if ((u16)(arg0->unk38 & 0x400) || (temp_16 > 0)) {
        sp4F = arg2;
        StringReplaceRange_1b3da0(arg3, (arg3->l.flag & 1) ? (s32)arg3->l.size : (s32)arg3->s.size, 0, &sp4F, &sp4F + 1, (s32)tag.x);
    }
    StringReplaceFill_1075d0(arg3, (unsigned int)((arg3->l.flag & 1) ? (u64)arg3->l.size : (u64)arg3->s.size), 0, (unsigned int)((s32)temp_16), arg1);
}
