#include "types.h"
#pragma divbyzerocheck on

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

typedef struct It {
    char *p;
} It;

typedef struct Fmt {
    u8 pad[0x28];
    s64 prec;
    u8 pad30[8];
    u16 flags;
} Fmt;

s32 DoubleEqual_1002f0(s32, s64);
void OperatorDelete_100840(char *);
void DecimalFromLongDouble_106830(Str *, s64);
void DecimalRoundToDigits_106b50(Str *, Str *, s64, s32 *);
void StringAppendFill_106e90(Str *, s64, s32);
void StringInsertChar_107a60(It *, Str *, char *, s32);
void StringAssignChar_1b3b30(Str *, s32);
void StringPrependStrMaybe_1b3dd0(Str *, char *, char *, s32);
void StringPushBack_1b3e40(Str *, s64);

static inline void mk(It *r, char *p)
{
    r->p = p;
}

static inline s32 it_ne(It *a, It *b)
{
    return !(a->p == b->p);
}

static inline s32 pne(char *a, char *b)
{
    return !(a == b);
}

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

s32 NumPutDoubleScientificMaybe_1b3090(Fmt *fmt, s64 val, Str *out)
{
    s32 exp;
    char *volatile vB8;
    char *volatile vB4;
    It iB0;
    char *volatile vAC;
    char *volatile vA8;
    volatile It iA4;
    char *volatile vA0;
    char *volatile v9C;
    volatile It i98;
    char *volatile v94;
    char *volatile v90;
    volatile It i8C;
    volatile It i88;
    Str dig;
    union { Str s; u8 raw[0x18]; } num;
    s64 prec;
    s64 e;
    s32 r;
    u8 dot;
    s64 need;
    s32 start;
    char *dp;
    u32 dn;
    char *p;
    char c;
    u8 sh;

    e = (u16)(fmt->flags & 0x4000) ? 'E' : 'e';
    prec = fmt->prec;
    e = (s8)e;
    if (DoubleEqual_1002f0(0, val) != 0) {
        StringAssignChar_1b3b30(out, '0');
        if ((u16)(fmt->flags & 0x400) || prec > 0) StringPushBack_1b3e40(out, '.');
        if (prec > 0) StringAppendFill_106e90(out, (s32)prec, '0');
        StringPushBack_1b3e40(out, e);
        StringPushBack_1b3e40(out, '+');
        StringAppendFill_106e90(out, 2, '0');
        return 0;
    }
    DecimalFromLongDouble_106830(&num.s, val);
    DecimalRoundToDigits_106b50(&dig, &num.s, (s32)(prec + 1), &exp);
    vB8 = (dig.u.w.w0 & 1) ? dig.data : (char *)&dig + 1;
    if (!(dig.u.w.w0 & 1)) {
        dp = (char *)&dig + 1;
        dn = dig.u.b.len;
    } else {
        dp = dig.data;
        dn = dig.u.w.size;
    }
    { char *b8 = ((char **)&exp)[-1]; p = dp + dn; vB4 = p; StringPrependStrMaybe_1b3dd0(out, b8, p, 0); }
    r = exp;
    dot = 0;
    if ((u16)(fmt->flags & 0x400) || prec > 0) {
        p = (out->u.w.w0 & 1) ? out->data : (char *)out + 1;
        vA8 = p;
        p = p + 1;
        v9C = p;
        vAC = p;
        StringInsertChar_107a60(&iB0, out, p, '.');
        dot = 1;
    }
    sh = is_short2(out);
    dn = sh ? out->u.b.len : out->u.w.size;
    need = dot;
    need = (s64)((u64)(prec + 1) + need);
    if ((s64)(u64)dn < need) {
        StringAppendFill_106e90(out, (s32)(need - (u64)(sh ? out->u.b.len : out->u.w.size)), '0');
    }
    StringPushBack_1b3e40(out, e);
    if (exp < 0) {
        StringPushBack_1b3e40(out, '-');
        exp = -exp;
    } else {
        StringPushBack_1b3e40(out, '+');
    }
    if (exp < 10) {
        StringPushBack_1b3e40(out, '0');
        StringPushBack_1b3e40(out, (s8)(exp + '0'));
    } else {
        if (((out->u.w.w0 & 1) != 0) ^ 1) {
            start = out->u.b.len;
        } else {
            start = out->u.w.size;
        }
        while (exp > 0) {
            StringPushBack_1b3e40(out, (s8)(exp % 10 + '0'));
            exp /= 10;
        }
        if (!(out->u.w.w0 & 1)) {
            dp = (char *)out + 1;
            dn = out->u.b.len;
        } else {
            dp = out->data;
            dn = out->u.w.size;
        }
        v94 = dp + dn;
        p = (out->u.w.w0 & 1) ? out->data : (char *)out + 1;
        dp = v94;
        iA4.p = p + start;
        v90 = p + start;
        vA0 = p;
        i88.p = dp;
        *(It *)&i98 = *(It *)&iA4;
        {
            char *f0 = i98.p;
            char *f1 = i98.p;
            dn = pne(f0, dp);
            i8C.p = f1;
        }
        if (dn) {
            char *l;
            char *f;
            goto cond;
            do {
                f = i8C.p;
                c = *f;
                l = i88.p;
                i8C.p = f + 1;
                *f = *l;
                *l = c;
            cond:
                l = i88.p - 1;
                f = i8C.p;
                i88.p = l;
            } while (l > f);
        }
    }
    if (dig.u.w.w0 & 1) OperatorDelete_100840(dig.data);
    if (num.s.u.w.w0 & 1) OperatorDelete_100840(num.s.data);
    return r;
}
