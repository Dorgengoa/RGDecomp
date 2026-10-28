/* rgp:protos */
#define RGP_SELF_NumPutDoubleFixedMaybe_1b2c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str {
    union {
        struct {
            unsigned char flag : 1;
            unsigned char len : 7;
        } __attribute__((aligned(8))) b;
        struct {
            u32 w0;
            u32 size;
        } w;
    } u;
    char *data;
} Str;

typedef struct Dec {
    Str s;
    s16 exp;
} Dec;

typedef struct Fmt {
    u8 pad[0x28];
    s64 prec;
    u8 pad30[8];
    u16 flags;
} Fmt;

/*rgp*/
/*rgp*/
void DecimalFromLongDoubleMaybe_106830(Str *, s64);
s32 DecimalRoundDirectionMaybe_106ab0(Str *, s32);
void DecimalRoundDigitsMaybe_106b50(Str *, Str *, s32, s32 *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Body {
    f32 v[3];
} Body;

void NumPutDoubleFixedMaybe_1b2c20(Fmt *io, s64 x, Str *s)
{
    s32 e;
    char *volatile vb;
    char *volatile ve;
    Str r __attribute__((aligned(16)));
    Str t __attribute__((aligned(16)));
    Dec d __attribute__((aligned(16)));
    s64 prec;
    s32 m;
    char *p;
    u32 n;
    u32 i;
    u8 lg;

    prec = io->prec;
    if (((unsigned char)DoubleEqual_1002f0(__builtin_bit_cast(double, (long long)(int)(0)), __builtin_bit_cast(double, (long long)(x)))) != 0) {
        NumPutFixedZeroStrMaybe_1b3c90(io, '0', '.', s);
        return;
    }
    DecimalFromLongDoubleMaybe_106830(&d.s, x);
    m = (s32)(prec + d.exp + 1);
    e = d.exp;
    if (m < 0) {
        NumPutFixedZeroStrMaybe_1b3c90(io, '0', '.', s);
        if (d.s.u.w.w0 & 1) {
            OperatorDelete_100840(d.s.data);
        }
        return;
    }
    if (m == 0) {
        if (d.exp == -1) {
            if (DecimalRoundDirectionMaybe_106ab0(&d.s, 0) == 1) {
                StringAssignChar_1b3b30(s, '1');
            } else {
                StringAssignChar_1b3b30(s, '0');
            }
            if ((u16)(io->flags & 0x400)) {
                StringPushBack_1b3e40(s, (char)('.'));
            }
        } else {
            StringAssignChar_1b3b30(s, '0');
            StringPushBack_1b3e40(s, (char)('.'));
            if (e < -2) {
                StringAppendFill_106e90(s, -2 - e, '0');
            }
            if (DecimalRoundDirectionMaybe_106ab0(&d.s, 0) == 1) {
                StringPushBack_1b3e40(s, (char)('1'));
            } else {
                StringPushBack_1b3e40(s, (char)('0'));
            }
        }
        if (d.s.u.w.w0 & 1) {
            OperatorDelete_100840(d.s.data);
        }
        return;
    }
    DecimalRoundDigitsMaybe_106b50(&r, &d.s, m, &e);
    vb = (r.u.w.w0 & 1) ? r.data : (char *)&r + 1;
    if (!(r.u.w.w0 & 1)) {
        p = (char *)&r + 1;
        n = r.u.b.len;
    } else {
        p = r.data;
        n = r.u.w.size;
    }
    {
        char *b = ((char **)&e)[-1];
        p = p + n;
        ve = p;
        StringPrependStrMaybe_1b3dd0(s, b, p);
    }
    m = (s32)(prec + e + 1);
    if (e < 0) {
        {
            s32 *z = (s32 *)&t;
            for (i = 0; i < 3; i++) {
                z[i] = 0;
            }
        }
        StringAssignChar_1b3b30(&t, '0');
        StringPushBack_1b3e40(&t, (char)('.'));
        if (e < -1) {
            StringAppendFill_106e90(&t, -1 - e, '0');
        }
        StringAppendStr_1b3b80(&t, s);
        lg = (s->u.w.w0 & 1) != 0;
        if (!lg && !(t.u.w.w0 & 1)) {
            *(Body *)s = *(Body *)&t;
        } else {
            StringReplaceWithStr_1a7820(s, 0, lg ? s->u.w.size : s->u.b.len, &t);
        }
        if (prec + 2 - (u64)((t.u.w.w0 & 1) ? t.u.w.size : t.u.b.len) == 1) {
            StringPushBack_1b3e40(s, (char)('0'));
        }
        if (t.u.w.w0 & 1) {
            OperatorDelete_100840(t.data);
        }
        if (r.u.w.w0 & 1) {
            OperatorDelete_100840(r.data);
        }
        if (d.s.u.w.w0 & 1) {
            OperatorDelete_100840(d.s.data);
        }
        return;
    }
    StringAppendFill_106e90(s, m - ((s->u.w.w0 & 1) ? s->u.w.size : s->u.b.len), '0');
    if ((u16)(io->flags & 0x400) || prec > 0) {
        StringReplaceFill_1075d0(s, e + 1, 0, 1, '.');
    }
    if (r.u.w.w0 & 1) {
        OperatorDelete_100840(r.data);
    }
    if (d.s.u.w.w0 & 1) {
        OperatorDelete_100840(d.s.data);
    }
}
