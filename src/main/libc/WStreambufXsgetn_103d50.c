#include "types.h"

/* MSL C++ iostreams: basic_streambuf<wchar_t>::xsgetn(wchar_t *s, streamsize n), C-linkage form.
 * Wide twin of StreambufXsgetn_1039b0 and get-side twin of WStreambufXsputn_103b00: char_traits::copy (element loop,
 * unrolled x8 at -O4,p) of the part already in the get area (min() returns a reference ->
 * frame-resident diff/n slots), then sbumpc() the rest one char at a time until uflow()
 * (virtual, vtable +0x28 -> $t9) returns eof.  The 4-byte char_type carries a 16-bit payload
 * (lhu/sh).  Built as C++ at -O4,p (config/toolchain.txt row). */

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
    virtual s32 uflow(void); /* vtable +0x28 */
    WChar *pad[1];
    WChar *gnext; /* +0x08 */
    WChar *gend;  /* +0x0c */

    s32 sbumpc(void)
    {
        if (gnext < gend) {
            WChar *p = gnext++;
            return p->c;
        }
        return uflow();
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

extern "C" streamsize WStreambufXsgetn_103d50(WStreamBuf *self, WChar *s, streamsize n)
{
    streamsize nc = min_(n, (streamsize)(self->gend - self->gnext));
    if (nc > 0) {
        copy_(s, self->gnext, nc);
        s += (s32)nc;
        self->gnext += (s32)nc;
        n -= nc;
    }
    while (n > 0) {
        s32 c = self->sbumpc();
        if (c == -1)
            break;
        s->c = c;
        ++s;
        ++nc;
        --n;
    }
    return nc;
}
