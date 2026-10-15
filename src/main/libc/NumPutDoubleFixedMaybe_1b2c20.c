#include "types.h"

typedef struct Str {
    union {
        struct {
            u64 flag : 1;
            u64 len : 7;
        } b;
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

s32 DoubleEqual_1002f0(s32, s64);
void OperatorDelete_100840(char *);
void DecimalFromLongDouble_106830(Str *, s64);
s32 DecimalCompareToHalf_106ab0(Str *, s32);
void DecimalRoundToDigits_106b50(Str *, Str *, s32, s32 *);
void StringAppendFill_106e90(Str *, s32, s32);
void StringReplaceFill_1075d0(Str *, s32, s32, s32, s8);
void StringReplaceWithStr_1a7820(Str *, s32, u32, Str *);
void StringAssignChar_1b3b30(Str *, s32);
void StringAppendStr_1b3b80(Str *, Str *);
void NumPutFixedZeroStrMaybe_1b3c90(Fmt *, s8, s8, Str *);
void StringPrependStrMaybe_1b3dd0(Str *, char *, char *, s32);
void StringPushBack_1b3e40(Str *, s64);

typedef struct Body {
    f32 v[3];
} Body;

void NumPutDoubleFixedMaybe_1b2c20(Fmt *io, s64 x, Str *s)
{
    s32 e;
    char *volatile vb;
    char *volatile ve;
    Str r;
    Str t;
    Dec d;
    s64 prec;
    s32 m;
    char *p;
    u32 n;
    u32 i;
    u8 lg;

    prec = io->prec;
    if (DoubleEqual_1002f0(0, x) != 0) {
        NumPutFixedZeroStrMaybe_1b3c90(io, '0', '.', s);
        return;
    }
    DecimalFromLongDouble_106830(&d.s, x);
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
            if (DecimalCompareToHalf_106ab0(&d.s, 0) == 1) {
                StringAssignChar_1b3b30(s, '1');
            } else {
                StringAssignChar_1b3b30(s, '0');
            }
            if ((u16)(io->flags & 0x400)) {
                StringPushBack_1b3e40(s, '.');
            }
        } else {
            StringAssignChar_1b3b30(s, '0');
            StringPushBack_1b3e40(s, '.');
            if (e < -2) {
                StringAppendFill_106e90(s, -2 - e, '0');
            }
            if (DecimalCompareToHalf_106ab0(&d.s, 0) == 1) {
                StringPushBack_1b3e40(s, '1');
            } else {
                StringPushBack_1b3e40(s, '0');
            }
        }
        if (d.s.u.w.w0 & 1) {
            OperatorDelete_100840(d.s.data);
        }
        return;
    }
    DecimalRoundToDigits_106b50(&r, &d.s, m, &e);
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
        StringPrependStrMaybe_1b3dd0(s, b, p, 0);
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
        StringPushBack_1b3e40(&t, '.');
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
            StringPushBack_1b3e40(s, '0');
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
