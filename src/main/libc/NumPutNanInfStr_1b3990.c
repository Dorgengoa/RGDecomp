#include "types.h"

typedef struct Str001b3990 {
    union {
        struct {
            u64 flag : 1;
            u64 len : 7;
        } b;
        struct {
            s32 w0;
            s32 size;
        } w;
    } u;
    u8 *data;
} Str001b3990;

typedef struct S001b3990 {
    u8 pad0[0x38];
    u16 unk38;
} S001b3990;

extern void StringDtor_107b00(void *, s32);
extern s32 Isnan_128658(s32);
extern s8 Toupper_1363e0(s8);
extern void StringAssign_1b3ab0(Str001b3990 *, Str001b3990 *);
extern void StringCtorFromCStrThunk_1a2110(Str001b3990 *, void *, s32);
extern u8 D_0045AA78[];
extern u8 D_0045AA80[];

static inline u8 *str_end(Str001b3990 *s)
{
    u8 *d;
    s32 n;

    if (!(s->u.w.w0 & 1)) {
        d = (u8 *)s + 1;
        n = s->u.b.len;
    } else {
        d = s->data;
        n = s->u.w.size;
    }
    return d + n;
}

void NumPutNanInfStr_1b3990(S001b3990 *arg0, s32 arg1, Str001b3990 *arg2)
{
    Str001b3990 a;
    Str001b3990 b;
    u8 * volatile p;
    s8 c;

    if (Isnan_128658(arg1) != 0) {
        StringCtorFromCStrThunk_1a2110(&a, D_0045AA80, 0);
        StringAssign_1b3ab0(arg2, &a);
        StringDtor_107b00(&a, -1);
    } else {
        StringCtorFromCStrThunk_1a2110(&b, D_0045AA78, 0);
        StringAssign_1b3ab0(arg2, &b);
        StringDtor_107b00(&b, -1);
    }
    if ((u16)(arg0->unk38 & 0x4000)) {
        p = (arg2->u.w.w0 & 1) ? arg2->data : (u8 *)arg2 + 1;
        while (p < str_end(arg2)) {
            c = Toupper_1363e0(*p);
            *p++ = c;
        }
    }
}
