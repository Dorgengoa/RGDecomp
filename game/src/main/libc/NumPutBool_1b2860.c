/* rgp:protos */
#define RGP_SELF_NumPutBool_1b2860 1
#define RGP_SELF_is_long 1
#define RGP_SELF_is_short 1
#define RGP_SELF_is_short2 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft references `sp70[0]`,
 * `sp74`, `sp78` as if they were declared locals but none of the three
 * appear in the local declaration list (only sp71/sp60/sp50/sp4C/var_10 are
 * declared) -- these are almost certainly the same flag+7bit-length SSO
 * struct idiom as StringPrependStrMaybe_1b3dd0/NumPutNanInfStr_1b3990 laid out across an undeclared
 * stack region m2c never named. Needs a raw-asm trace of the frame before
 * compiling. Deferred. See asm/matchings/main/NumPutBool_1b2860.s. */
/* s49m: MATCH */
#include "types.h"

typedef struct Str {
    union {
        struct {
            unsigned char flag : 1;
            unsigned char len : 7;
        } __attribute__((aligned(8))) b;
        struct {
            u32 w0;
            s32 size;
        } w;
    } u;
    u8 *data;
} Str;

typedef struct A2 { u8 pad[0x38]; u16 x38; } A2;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045AA90[];
extern u8 D_0045AA88[];

static inline u8 is_short(Str *s)
{
    return !(s->u.w.w0 & 1);
}

static inline u8 is_long(Str *s)
{
    return !is_short(s);
}

static inline u8 is_short2(Str *s)
{
    return !is_long(s);
}

s32 NumPutBool_1b2860(s32 arg0, s32 arg1, A2 *arg2, s32 arg3, s32 arg4)
{
    Str s __attribute__((aligned(16)));
    Str t1 __attribute__((aligned(16)));
    Str t0 __attribute__((aligned(16)));
    u32 i;
    u32 *p;
    u8 sh;

    if (arg2->x38 & 1) {
        p = (u32 *)&s;
        for (i = 0; i < 3; i++) {
            p[i] = 0;
        }
        if (arg4 != 0) {
            StringCtorFromCStrThunk_1a2110(&t1, D_0045AA90);
            StringAssign_1a77a0(&s, &t1);
            StringDtor_107b00(&t1, -1);
        } else {
            StringCtorFromCStrThunk_1a2110(&t0, D_0045AA88);
            StringAssign_1a77a0(&s, &t0);
            StringDtor_107b00(&t0, -1);
        }
        sh = is_short2(&s);
        NumPutPadOutput_1a4610(arg0, *(volatile s32 *)&arg1, arg2, arg3, 0, 0,
                     sh ? (u8 *)&s + 1 : s.data,
                     sh ? s.u.b.len : s.u.w.size);
        StringDtor_107b00(&s, -1);
        return 0;
    }
    return (NumPutSigned_1a4300(arg0, arg1, arg2, arg3, (u8)arg4), (s32)0);
}
