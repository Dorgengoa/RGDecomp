/* rgp:protos */
#define RGP_SELF_NumPutNanInfStr_1b3990 1
#define RGP_SELF_str_end 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str001b3990 {
    union {
        struct {
            unsigned char flag : 1;
            unsigned char len : 7;
        } __attribute__((aligned(8))) b;
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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

void NumPutNanInfStr_1b3990(S001b3990 *arg0, double arg1, Str001b3990 *arg2)
{
    Str001b3990 a __attribute__((aligned(16)));
    Str001b3990 b __attribute__((aligned(16)));
    u8 * volatile p;
    s8 c;

    if (Isnan_128658(arg1) != 0) {
        StringCtorFromCStrThunk_1a2110(&a, D_0045AA80);
        StringAssign_1b3ab0(arg2, &a);
        StringDtor_107b00(&a, -1);
    } else {
        StringCtorFromCStrThunk_1a2110(&b, D_0045AA78);
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
