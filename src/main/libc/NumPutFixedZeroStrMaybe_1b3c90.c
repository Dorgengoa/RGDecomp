#include "types.h"

typedef union {
    struct {
        u64 flag : 1;
        u64 size : 7;
    } s;
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
void StringReplaceFill_1075d0(Str001B3C90 *, u64, s32, s64, s8);          /* extern */
void StringReplaceRange_1b3da0(Str001B3C90 *, u64, s32, s8 *, s8 *, Tag001B3C90); /* extern */

void NumPutFixedZeroStrMaybe_1b3c90(Obj001B3C90 *arg0, s8 arg1, s8 arg2, Str001B3C90 *arg3) {
    s8 sp4F;
    Tag001B3C90 tag;
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
        StringReplaceRange_1b3da0(arg3, (arg3->l.flag & 1) ? (u64)arg3->l.size : (u64)arg3->s.size, 0, &sp4F, &sp4F + 1, tag);
    }
    StringReplaceFill_1075d0(arg3, (arg3->l.flag & 1) ? (u64)arg3->l.size : (u64)arg3->s.size, 0, (s32)temp_16, arg1);
}
