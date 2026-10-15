#include "types.h"

/* MSL C++ library: basic_filebuf<char>::underflow().
 *   eof if no FILE (+0x1C). In read mode (+0x36) with no get area: flush the put area through overflow(eof)
 *   (vtable +0x34) when pptr > pbase (eof -> eof), clear the put area, setg(buf +0x24 x3). Flag +0x34 = 0.
 *   gptr < egptr -> *gptr. Else read one char from the FILE via FilebufGetcPeek_105f30(this, !gptr) (+0x35 set) or
 *   FilebufReadChar_105fe0(this, 1, !gptr); eof -> eof; with a get area keep a 4-byte putback window when the buffer
 *   is full, then setg(buf, buf+n, buf+n+1) and store the char.
 * Built as C++ (layout shared with FilebufUflow_104d80 / FilebufPbackfail_104cb0). `n++` then buf+n-1 / buf+n gives the
 * n+1 / +0x23 / +0x24 address shape; plain field gptr (no accessor) keeps the one gptr load. Same object at
 * -O4 and -O4,p. libdeasm 104eb0. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

typedef struct File File;
extern "C" s32 FilebufGetcPeek_105f30(struct Filebuf *self, s32 a);
extern "C" s32 FilebufReadChar_105fe0(struct Filebuf *self, s32 a, s32 b);

struct Filebuf {
    virtual ~Filebuf();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual s32 underflow();        /* vtable +0x24 */
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual s32 overflow(s32 c);    /* vtable +0x34 */
    char *eback, *gptr, *egptr;     /* +0x04 */
    char *pbase, *pptr, *epptr;     /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    char buf[16];                   /* +0x24 */
    u8 b34, b35, b36;               /* +0x34 */
    char *pbase_() const { return pbase; }
    char *pptr_() const { return pptr; }
    char *gptr_() const { return gptr; }
    void gbump(s32 n) { gptr += n; }
    void setg(char *a, char *b, char *c) { eback = a; gptr = b; egptr = c; }
};

extern "C" s32 FilebufUnderflow_104eb0(Filebuf *self)
{
    s32 r;
    bool failed;
    char c;

    if (!self->file)
        return -1;
    if (self->b36) {
        if (!self->gptr) {
            failed = false;
            if (self->pptr_() > self->pbase_()) {
                if (self->overflow(-1) == -1)
                    failed = true;
            }
            if (failed)
                return -1;
            self->pptr = 0;
            self->pbase = 0;
            self->epptr = 0;
            self->setg(self->buf, self->buf, self->buf);
        }
    }
    self->b34 = 0;
    if (self->gptr < self->egptr)
        return (u8)*self->gptr;
    if (self->b35)
        r = FilebufGetcPeek_105f30(self, self->gptr == 0);
    else
        r = FilebufReadChar_105fe0(self, 1, self->gptr == 0);
    if (r == -1)
        return -1;
    c = r;
    if (self->gptr) {
        s32 n = self->egptr - self->eback;
        if (n == 16) {
            *(s32 *)self->buf = *(s32 *)(self->buf + 12);
            n = 4;
        }
        n++;
        self->setg(self->buf, self->buf + n - 1, self->buf + n);
        *self->gptr_() = c;
    }
    return r;
}
