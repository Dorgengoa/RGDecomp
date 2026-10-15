#include "types.h"

/* MSL C++ iostreams: basic_streambuf<char>::xsputn(const char *s, streamsize n), C-linkage form.
 * memcpy the part that fits in the put area (min() returns a reference -> frame-resident
 * diff/n slots), then sputc() the rest one char at a time until overflow() (virtual,
 * vtable +0x34 -> $t9) returns eof.  Built as C++ at -O4,p (config/toolchain.txt row;
 * plain -O4 = len 0x114).  StreambufXsgetn_1039b0 is the wide-char twin. */

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
    virtual void v8(void);
    virtual void v9(void);
    virtual void v10(void);
    virtual s32 overflow(s32 c); /* vtable +0x34 */
    char *pad[4];
    char *pnext; /* +0x14 */
    char *pend;  /* +0x18 */

    s32 sputc(char c)
    {
        if (pnext < pend) {
            char *p = pnext++;
            *p = c;
            return (u8)*p;
        }
        return overflow((u8)c);
    }
};

extern "C" streamsize StreambufXsputn_103890(StreamBuf *self, const char *s, streamsize n)
{
    streamsize nc = min_(n, (streamsize)(self->pend - self->pnext));
    if (nc > 0) {
        memcpy(self->pnext, s, (s32)nc);
        s += (s32)nc;
        self->pnext += (s32)nc;
        n -= nc;
    }
    while (n > 0) {
        if (self->sputc(*s++) == -1)
            break;
        ++nc;
        --n;
    }
    return nc;
}
