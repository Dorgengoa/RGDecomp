#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t>::seekoff(off_type off, seekdir way, openmode which) -> pos_type
 *   (wide twin of FilebufSeekoff_104750; pos_type returned through the hidden a0 pointer: {s64 off; s32 state}).
 *   if (!is_open()) return -1; flush pending output (pptr > pbase -> overflow(eof), vtable slot 0x34);
 *   way beg/cur/end (1/2/4) -> whence 0/1/2, cur with `in` (8) subtracts egptr - gptr (in 4-byte chars);
 *   fseek (Fseek_12fe60) at off * 4 bytes fails -> -1; else clear get/put areas + byte +0x64,
 *   return ftell (Ftell_130370).
 * The buffer element is 4 bytes wide (wchar4); plain wchar_t did not match (v1 a.c).
 * Same pragmas/join-copy as 104750 (opt_rebuildlogicals off keeps `failed` in s0; `fb = self` with
 * opt_propagation off gives retail's `beqz ret; b main`). Same object at -O4 and -O4,p.
 * libdeasm 105250. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off
#pragma opt_propagation off

typedef s32 wchar4;

struct Pos {
    s64 off;
    s32 st;
    Pos(s64 o) : off(o), st(0) {}
};

struct Filebuf {
    virtual ~Filebuf();
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual s32 overflow(s32 c);    /* vtable +0x34 */
    wchar4 *eback, *gptr, *egptr;     /* +0x04 */
    wchar4 *pbase, *pptr, *epptr;     /* +0x10 */
    void *file;                     /* +0x1C */
    s32 pad20[17];
    u8 b64;                         /* +0x64 */
};

extern "C" s32 Fseek_12fe60(void *f, s64 off, s32 whence);
extern "C" s64 Ftell_130370(void *f);

extern "C" Pos WFilebufSeekoff_105250(Filebuf *self, s64 off, u8 way, u8 which)
{
    Filebuf *fb;
    s32 whence;
    bool failed;

    if (self->file) fb = self; else return Pos(-1);
    failed = false;
    if (fb->pptr > fb->pbase) {
        if (fb->overflow(-1) == -1) failed = true;
    }
    if (failed)
        return Pos(-1);
    switch (way) {
    case 1: whence = 0; break;
    case 2:
        whence = 1;
        if ((u8)(which & 8))
            off -= self->egptr - self->gptr;
        break;
    case 4: whence = 2; break;
    default:
        return Pos(-1);
    }
    if (Fseek_12fe60(self->file, off * (s64)sizeof(wchar4), whence))
        return Pos(-1);
    self->eback = 0; self->gptr = 0; self->egptr = 0;
    self->pptr = 0; self->pbase = 0; self->epptr = 0;
    self->b64 = 0;
    return Pos(Ftell_130370(self->file));
}
