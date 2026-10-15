#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t>::uflow() -- wide twin of FilebufUflow_104d80.
 *   In read mode (+0x66) with no get area: flush the put area through overflow(eof) (vtable +0x34) when
 *   pptr > pbase (eof -> eof), clear the put area, setg(buf +0x24 x3). With a get area: underflow()
 *   (vtable +0x24), eof -> eof, else return the 16-bit *gptr and gbump(1). Otherwise flag +0x64 = 0; eof if
 *   not open; read one char straight from the FILE via WFilebufGetcPeek_105c30(this, 0) (+0x65 set) or
 *   WFilebufReadWChar_105ce0(this, 4, 0).
 * Built as C++ like FilebufUflow_104d80: inline const accessors give the pptr-first compare and the gptr reload;
 * setg() gives the eback/gptr/egptr store order. Elements are 4 bytes (wchar4) with a 16-bit read.
 * libdeasm 105900. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

typedef struct File File;
typedef s32 wchar4;
extern "C" s32 WFilebufGetcPeek_105c30(struct WFilebuf *self, s32 a);
extern "C" s32 WFilebufReadWChar_105ce0(struct WFilebuf *self, s32 a, s32 b);

struct WFilebuf {
    virtual ~WFilebuf();
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
    wchar4 *eback, *gptr, *egptr;   /* +0x04 */
    wchar4 *pbase, *pptr, *epptr;   /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    wchar4 buf[16];                 /* +0x24 */
    u8 b64, b65, b66;               /* +0x64 */
    wchar4 *pbase_() const { return pbase; }
    wchar4 *pptr_() const { return pptr; }
    wchar4 *gptr_() const { return gptr; }
    void gbump(s32 n) { gptr += n; }
    void setg(wchar4 *a, wchar4 *b, wchar4 *c) { eback = a; gptr = b; egptr = c; }
};

extern "C" s32 WFilebufUflow_105900(WFilebuf *self)
{
    s32 r;
    bool failed;

    if (self->b66) {
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
        r = *(u16 *)self->gptr_();
        self->gbump(1);
        return r;
    }
    self->b64 = 0;
    if (!self->file)
        return -1;
    if (self->b65)
        r = WFilebufGetcPeek_105c30(self, 0);
    else
        r = WFilebufReadWChar_105ce0(self, 4, 0);
    if (r == -1)
        return -1;
    return r;
}
