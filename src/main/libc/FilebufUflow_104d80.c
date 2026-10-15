#include "types.h"

/* MSL C++ library: basic_filebuf<char>::uflow().
 *   In read mode (+0x36) with no get area: flush the put area through overflow(eof) (vtable +0x34) when
 *   pptr > pbase (eof -> eof), clear the put area, setg(buf +0x24 x3). With a get area: underflow()
 *   (vtable +0x24), eof -> eof, else return *gptr and gbump(1). Otherwise flag +0x34 = 0; eof if not open;
 *   read one char straight from the FILE via FilebufGetcPeek_105f30(this, 0) (+0x35 set) or FilebufReadChar_105fe0(this, 1, 0).
 * Built as C++ (layout shared with FilebufOverflow_1048d0 / FilebufPbackfail_104cb0). Inline const accessors give the pptr-first
 * compare and the gptr reload; setg() gives the eback/gptr/egptr store order. Same object at -O4 and -O4,p.
 * libdeasm 104d80. */

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

extern "C" s32 FilebufUflow_104d80(Filebuf *self)
{
    s32 r;
    bool failed;

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
    if (self->gptr) {
        if (self->underflow() == -1)
            return -1;
        r = (u8)*self->gptr_();
        self->gbump(1);
        return r;
    }
    self->b34 = 0;
    if (!self->file)
        return -1;
    if (self->b35)
        r = FilebufGetcPeek_105f30(self, 0);
    else
        r = FilebufReadChar_105fe0(self, 1, 0);
    if (r == -1)
        return -1;
    return r;
}
