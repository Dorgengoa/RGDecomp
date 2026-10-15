#include "types.h"

/* MSL C++ iostreams: basic_streambuf<wchar_t>::xsputn(const wchar_t *s, streamsize n), C-linkage form.
 * Wide twin of StreambufXsputn_103890: char_traits::copy (element loop, unrolled x8 at -O4,p) of the part
 * that fits in the put area (min() returns a reference -> frame-resident diff/n slots), then
 * sputc() the rest one char at a time until overflow() (virtual, vtable +0x34 -> $t9) returns eof.
 * The 4-byte char_type carries a 16-bit payload (lhu/sh).  Built as C++ at -O4,p
 * (config/toolchain.txt row).  The copy count is nc implicitly narrowed to the size_t param. */

#pragma cplusplus on

typedef s64 streamsize;

template <class T> inline const T &min_(const T &a, const T &b) { return b < a ? b : a; }

typedef struct {
    u16 c;
    u16 pad;
} WChar;

struct WStreamBuf {
    virtual void v0(void);
    virtual void v1(void);
    virtual void v2(void);
    virtual void v3(void);
    virtual void v4(void);
    virtual void v5(void);
    virtual void v6(void);
    virtual void v7(void);
    virtual void v8(void);
    virtual void v9(void);
    virtual void v10(void);
    virtual s32 overflow(s32 c); /* vtable +0x34 */
    WChar *pad[4];
    WChar *pnext; /* +0x14 */
    WChar *pend;  /* +0x18 */

    s32 sputc(s32 c)
    {
        if (pnext < pend) {
            WChar *p = pnext++;
            p->c = c;
            return p->c;
        }
        return overflow(c);
    }
};

static inline void assign_(WChar &a, const WChar &b) { a.c = b.c; }

static inline WChar *copy_(WChar *d, const WChar *s, unsigned int n)
{
    WChar *r = d;
    for (unsigned int i = 0; i < n; ++i)
        assign_(*d++, *s++);
    return r;
}

extern "C" streamsize WStreambufXsputn_103b00(WStreamBuf *self, const WChar *s, streamsize n)
{
    streamsize nc = min_(n, (streamsize)(self->pend - self->pnext));
    if (nc > 0) {
        copy_(self->pnext, s, nc);
        s += (s32)nc;
        self->pnext += (s32)nc;
        n -= nc;
    }
    while (n > 0) {
        if (self->sputc((s++)->c) == -1)
            break;
        ++nc;
        --n;
    }
    return nc;
}
