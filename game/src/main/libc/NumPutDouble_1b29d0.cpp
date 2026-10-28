/* rgp:protos */
#line 1
#include "types.h"

typedef struct Fmt { u8 pad[0x38]; u16 flags; } Fmt;
struct Str {
    union {
        u32 w0;
        struct { u8 isLong : 1; u8 size : 7; } sh;
        char b[4];
    };
    u32 w1;
    char *w2;
    bool is_short() const { bool r = !(w0 & 1); return r; }
    bool is_long() const { bool r = !is_short(); return r; }
};
typedef struct It { void *p; } It;
extern "C" {
extern s32 Finite_1283d8(double);
extern void NumPutPadOutput_1a4610(s32, It, Fmt *, s32, char *, s32, char *, u32);
extern void NumPutDoubleFixedMaybe_1b2c20(Fmt *, long long, Str *);
extern void NumPutDoubleScientificMaybe_1b3090(Fmt *, long long, Str *);
extern void NumPutDoubleGeneralMaybe_1b34d0(Fmt *, int, Str *);
extern void NumPutNanInfStr_1b3990(Fmt *, double, Str *);
extern void *StringGetAllocator_1b2c10(Str *);
extern char **StringLongDataRef_1b2be0(Str *);
extern unsigned long long StringLongCapacity_1b2bf0(Str *);
extern void AllocatorDeallocate_1b2c00(void *, char *);
}

static inline s32 SignBit(double &v) { return (((u32 *)&v)[1] & 0x80000000) != 0; }
extern "C" s32 NumPutDouble_1b29d0(s32 arg0, volatile It arg1, Fmt *f, s32 arg3, double val) {
    char sign;
    Str s __attribute__((aligned(16)));
    s32 hasSign;

    hasSign = 0;
    if (!SignBit(val) && (u16)(f->flags & 0x800)) {
        hasSign = 1;
        sign = '+';
    } else if (SignBit(val)) {
        sign = '-';
        hasSign = 1;
        val = -val;
    }
    {
        u32 *w = (u32 *)&s;
        for (u32 i = 0; i < 3; i++) w[i] = 0;
    }
    if (Finite_1283d8(val)) {
        switch ((u16)(f->flags & 0x104)) {
        case 0x4:
            NumPutDoubleFixedMaybe_1b2c20(f, (long long)__builtin_bit_cast(long long, (double)(val)), &s);
            break;
        case 0x100:
            NumPutDoubleScientificMaybe_1b3090(f, (long long)__builtin_bit_cast(long long, (double)(val)), &s);
            break;
        default:
            NumPutDoubleGeneralMaybe_1b34d0(f, (int)__builtin_bit_cast(long long, (double)(val)), &s);
            break;
        }
    } else {
        NumPutNanInfStr_1b3990(f, val, &s);
    }
    NumPutPadOutput_1a4610(arg0, *(It *)&arg1, f, arg3, &sign, hasSign, !s.is_long() ? &s.b[1] : s.w2, !s.is_long() ? s.sh.size : s.w1);
    if (s.w0 & 1) {
        AllocatorDeallocate_1b2c00(((void)(StringLongCapacity_1b2bf0(&s)), StringGetAllocator_1b2c10(&s)), *StringLongDataRef_1b2be0(&s));
    }
    return 0;
}
