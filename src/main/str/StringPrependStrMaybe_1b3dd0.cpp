#include "types.h"
#pragma optimization_level 3
#pragma opt_propagation off

struct Str {
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
};

struct Tag {};

extern "C" {
void StringReplace_106f90(Str *, s32, u32, const char *, const char *, Tag);
void StringPrependStrMaybe_1b3dd0(Str *s, const char *first, const char *last);
}

static inline u32 Size(Str *s) { return (s->u.w.w0 & 1) ? s->u.w.size : s->u.b.len; }

template <class T> inline Tag Cat(const T &, const Tag &x) { return x; }

inline void Rep(Str *s, u32 p, u32 n, const char *f, const char *l, const Tag &t)
{
    StringReplace_106f90(s, p, n, f, l, t);
}

void StringPrependStrMaybe_1b3dd0(Str *s, const char *volatile first, const char *volatile last)
{
    Tag x;
    u32 n = Size(s);

    Rep(s, 0, n, first, last, Cat(last, x));
}
