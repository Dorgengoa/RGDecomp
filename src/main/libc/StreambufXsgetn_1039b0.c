#include "types.h"

/* MSL C++ iostreams: basic_streambuf<char>::xsgetn(char *s, streamsize n), C-linkage form.
 * memcpy the part already in the get area (min() returns a reference -> frame-resident
 * diff/n slots), then sbumpc() the rest one char at a time until uflow() (virtual,
 * vtable +0x28 -> $t9) returns eof.  Built as C++ at -O4,p.  Narrow twin of the
 * xsputn at StreambufXsputn_103890. */

#pragma cplusplus on

extern "C" void *memcpy(void *d, const void *s, unsigned int n);

typedef s64 streamsize;

template <class T> inline const T &min_(const T &a, const T &b) { return b < a ? b : a; }

struct StreamBuf {
    virtual void v0(void);
    virtual void v1(void);
    virtual void v2(void);
    virtual void v3(void);
    virtual void v4(void);
    virtual void v5(void);
    virtual void v6(void);
    virtual void v7(void);
    virtual s32 uflow(void); /* vtable +0x28 */
    char *pad[1];
    char *gnext; /* +0x08 */
    char *gend;  /* +0x0c */

    s32 sbumpc(void)
    {
        if (gnext < gend) {
            char *p = gnext++;
            return (u8)*p;
        }
        return uflow();
    }
};

extern "C" streamsize StreambufXsgetn_1039b0(StreamBuf *self, char *s, streamsize n)
{
    streamsize nc = min_(n, (streamsize)(self->gend - self->gnext));
    if (nc > 0) {
        memcpy(s, self->gnext, (s32)nc);
        s += (s32)nc;
        self->gnext += (s32)nc;
        n -= nc;
    }
    while (n > 0) {
        s32 c = self->sbumpc();
        if (c == -1)
            break;
        *s++ = (char)c;
        ++nc;
        --n;
    }
    return nc;
}
