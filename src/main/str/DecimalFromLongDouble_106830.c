#include "types.h"

#pragma cplusplus on
#pragma inline_depth(8)

struct Iter {
    char *p;
    Iter() {}
    Iter(char *q) : p(q) {}
};
static inline Iter mk(char *q) { Iter r; r.p = q; return r; }
static inline Iter operator-(Iter a, int n) { Iter r; r.p = a.p - n; return r; }
static inline Iter dec1(Iter a) { a.p--; return a; }
static inline char *prev(Iter a) { return a.p - 1; }
static inline bool operator==(Iter a, char *b) { return a.p == b; }
static inline bool operator!=(Iter a, char *b) { return !(a == b); }

struct Str {
    union {
        struct { u32 cap; u32 size; char *data; } l;
        struct { u8 is_long : 1; u8 size : 7; char buf[11]; } s;
    } u;
    char *data() { return (u.l.cap & 1) ? u.l.data : u.s.buf; }
    char *end() {
        char *p;
        u32 n;
        if (!(u.l.cap & 1)) {
            p = u.s.buf;
            n = u.s.size;
        } else {
            p = u.l.data;
            n = u.l.size;
        }
        return p + n;
    }
};

struct Decimal {
    Str sig;
    s16 exp;
    s16 cls;
};

extern "C" s32 Isinf_128610(f64 x);
extern "C" s32 Isnan_128658(f64 x);
extern "C" s32 Sprintf_1343b8(char *buf, const char *fmt, ...);
extern "C" void StringAssignCStr_106ee0(Str *s, const char *src);
extern "C" Iter StringEraseRange_107960(Str *s, Iter first, Iter last);
extern "C" Iter StringEraseAt_1079e0(Str *s, Iter pos);
extern "C" const char D_00455A90[16];

static inline void parse_exp(Decimal *d, char *q)
{
    Iter i;
    for (; i.p = q, i != d->sig.end(); q = i.p + 1) {
        d->exp *= 10;
        d->exp += *i.p - '0';
    }
}

static inline char *sign_pos(Decimal *d, char *q)
{
    Iter m;
    m.p = q;
    if (*q == '-') {
        d->exp = -d->exp;
        m.p = q;
    }
    return m.p;
}

static inline void unascii(Decimal *d, char *q)
{
    Iter j;
    for (; j.p = q, j != d->sig.end(); q = j.p + 1)
        *j.p -= '0';
}

extern "C" Decimal *DecimalFromLongDouble_106830(Decimal *d, f64 x)
{
    char buf[48];

    d->sig.u.l.cap = 0;
    d->sig.u.l.size = 0;
    d->sig.u.l.data = 0;
    d->exp = 0;
    d->cls = 0;
    if (Isinf_128610(x)) {
        d->cls = 2;
        return d;
    }
    if (Isnan_128658(x)) {
        d->cls = 1;
        return d;
    }
    Sprintf_1343b8(buf, D_00455A90, 31, x);
    StringAssignCStr_106ee0(&d->sig, buf);
    Iter it;
    parse_exp(d, d->sig.data() + 0x23);
    it.p = sign_pos(d, d->sig.data() + 0x22) - 1;
    StringEraseRange_107960(&d->sig, it, Iter(d->sig.end()));
    it.p = d->sig.data() + 1;
    StringEraseAt_1079e0(&d->sig, it);
    unascii(d, d->sig.data());
    return d;
}
