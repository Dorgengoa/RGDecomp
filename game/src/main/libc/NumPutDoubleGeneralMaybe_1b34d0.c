/* rgp:protos */
#define RGP_SELF_Has 1
#define RGP_SELF_NumPutDoubleGeneralMaybe_1b34d0 1
#define RGP_SELF_StringReplace_106f90 1
#define RGP_SELF_is_long 1
#define RGP_SELF_is_short 1
#define RGP_SELF_is_short2 1
#define RGP_SELF_str_end 1
#include "port/game_protos.h"
#line 1
#pragma opt_scalarize off
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

typedef struct Ios {
    u8 pad0[0x28];
    s64 prec;
    s64 width;
    s16 flags;
} Ios;

typedef struct Saver {
    Ios *io;
    s16 flags;
    s64 width;
    s64 prec;
} Saver;

typedef struct Alloc {
    s8 c;
} Alloc;

typedef struct Iter {
    s8 *p;
} Iter;

/*rgp*/
extern void StringReplace_106f90(Str *, s32, s32, u8 *, u8 *, Alloc);
extern void StringEraseAt_1079e0(Iter *, Str *, s8 *);
/*rgp*/
/*rgp*/
extern void StringEraseRange_107960(Iter *, Str *, s8 *, s8 *);
/*rgp*/

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

static inline u8 *str_end(Str *s)
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

static inline u16 Has(u16 f, u16 m)
{
    return f & m;
}

void NumPutDoubleGeneralMaybe_1b34d0(Ios *io, s32 x, Str *s)
{
    Saver sv __attribute__((aligned(16)));
    s8 * volatile q1;
    s8 * volatile e1;
    s8 *q2;
    s8 *e2;
    Iter r1 __attribute__((aligned(16)));
    s8 * volatile vc1;
    s8 * volatile vb1;
    Iter r2 __attribute__((aligned(16)));
    s8 * volatile vc2;
    s8 * volatile vb2;
    Iter r3 __attribute__((aligned(16)));
    s8 * volatile b3;
    Iter r4 __attribute__((aligned(16)));
    s8 * volatile vp1;
    s8 * volatile vp2;
    s8 * volatile v90;
    s8 *t;
    s32 ne;
    s32 sz;
    s64 prec;
    s32 n;
    s64 n64;
    s8 *p;
    u8 sh;
    s32 k;
    s8 ec;
    s16 fl;

    sv.io = io;
    sv.flags = io->flags;
    sv.width = io->width;
    sv.prec = prec = io->prec;
    if (prec == 0) {
        prec = 1;
    }
    io->prec = prec - 1;
    n = NumPutDoubleScientificMaybe_1b3090(io, (long long)(x), s);
    if (n >= -4 && (n64 = n) < prec) {
        p = (s8 *)((s->u.w.w0 & 1) ? s->data : (u8 *)s + 1);
        if (p[1] == '.') {
            Alloc al1 __attribute__((aligned(16)));
            StringReplace_106f90(s, prec + 1, -1, 0, 0, al1);
        } else {
            Alloc al2 __attribute__((aligned(16)));
            StringReplace_106f90(s, 1, -1, 0, 0, al2);
        }
        if (n < 0) {
            sh = is_short2(s);
            p = (s8 *)(sh ? (u8 *)s + 1 : s->data);
            if (p[1] == '.') {
                t = (s8 *)(sh ? (u8 *)s + 1 : s->data);
                vb1 = t;
                vc1 = vp1 = t + 1;
                StringEraseAt_1079e0(&r1, s, t + 1);
            }
            StringReplaceFill_1075d0(s, 0, 0, -n, '0');
            StringReplaceFill_1075d0(s, 1, 0, 1, '.');
        } else if (n > 0) {
            t = (s8 *)((s->u.w.w0 & 1) ? s->data : (u8 *)s + 1);
            vb2 = t;
            vc2 = vp2 = t + 1;
            StringEraseAt_1079e0(&r2, s, t + 1);
            if (n64 < prec - 1 || (u16)((u16)io->flags & 0x400)) {
                StringReplaceFill_1075d0(s, n + 1, 0, 1, '.');
            }
        }
        if (!(u16)((u16)io->flags & 0x400)) {
            if (StringFindChar_1b3c20(s, '.', 0) != -1) {
                t = (s8 *)str_end(s);
                e1 = t;
                q1 = t - 1;
                while (*(t = q1) == '0') {
                    q1--;
                }
                t++;
                ne = !(t == e1);
                q1 = t;
                if (ne) {
                    StringEraseRange_107960(&r3, s, t, e1);
                }
                sh = is_short2(s);
                sz = (sh ? s->u.b.len : s->u.w.size) - 1;
                if (sh) {
                    t = (s8 *)s + 1;
                } else {
                    t = (s8 *)s->data;
                }
                if (t[sz] == '.') {
                    StringPopBack_1b3bb0(s);
                }
            }
        }
        sv.io->flags = sv.flags;
        sv.io->width = sv.width;
        sv.io->prec = sv.prec;
        return;
    }
    fl = io->flags;
    if (!Has((s16)(u32)fl, 0x400)) {
        p = (s8 *)((s->u.w.w0 & 1) ? s->data : (u8 *)s + 1);
        if (p[1] == '.') {
            ec = Has(fl, 0x4000) ? 'E' : 'e';
            k = StringFindChar_1b3c20(s, ec, 0);
            t = (s8 *)((s->u.w.w0 & 1) ? s->data : (u8 *)s + 1);
            b3 = t;
            t += k;
            v90 = t;
            e2 = t;
            q2 = t - 1;
            while (*(t = *(s8 *volatile *)&q2) == '0') {
                *(s8 *volatile *)&q2 = *(s8 *volatile *)&q2 - 1;
            }
            t++;
            ne = !(t == *(s8 *volatile *)&e2);
            q2 = t;
            if (ne) {
                StringEraseRange_107960(&r4, s, t, *(s8 *volatile *)&e2);
            }
            if (ec == ((s8 *)((s->u.w.w0 & 1) ? s->data : (u8 *)s + 1))[2]) {
                Alloc al3 __attribute__((aligned(16)));
                StringReplace_106f90(s, 1, 1, 0, 0, al3);
            }
        }
    }
    sv.io->flags = sv.flags;
    sv.io->width = sv.width;
    sv.io->prec = sv.prec;
}
