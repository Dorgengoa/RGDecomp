#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t>::overflow(int_type c) (vtable slot 0x34); wide twin of FilebufOverflow_1048d0.
 *   if (!is_open()) return eof; in read mode with no put area: seekoff(0, cur, out) (vtable +0x10, pos_type
 *   through sret) then setp(buf +0x24, +0x64); flag +0x64 = 1. Flush pbase..pptr either through the newlib
 *   putc macro on the FILE at +0x1C (__swbuf = Swbuf_138e90) when +0x65 is set, or element-by-element through
 *   WFilebufWriteWChar_105e00(this, 4, ch); on failure shift the unwritten tail down (memcpy, bytes) and return eof; then
 *   write c unless eof; return not_eof(c).
 * Buffer elements are 4 bytes (wchar4), read back as u16 (lhu). `ch` is an s32 holding the truncated value
 * (andi/lhu at assignment, plain moves at use); WFilebufWriteWChar_105e00 takes an int. Pragmas/inline accessors as 1048d0.
 * libdeasm 1053e0. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

typedef s32 wchar4;
typedef u16 wchar;   /* char_type as converted for output */

typedef struct File {
    u8 *_p;          /* +0x00 */
    s32 r;          /* +0x04 */
    s32 w;          /* +0x08 */
    s16 flags, file;
    u8 *base; s32 size;
    s32 lbfsize;    /* +0x18 */
} File;

extern "C" s32 Swbuf_138e90(s32 c, File *f);   /* __swbuf */
extern "C" void memcpy(void *d, const void *s, u32 n);

struct Pos {
    s64 off;
    s32 st;
    Pos(s64 o) : off(o), st(0) {}
};

struct Filebuf;
static inline bool eq(s32 a, s32 b) { return a == b; }
static inline bool ne(s32 a, s32 b) { return !eq(a, b); }
extern "C" s32 WFilebufWriteWChar_105e00(Filebuf *self, s32 n, s32 c);

#define my_putc(c, fp) \
    (--(fp)->w < 0 ? \
        (fp)->w >= (fp)->lbfsize ? \
            (*(fp)->_p = (c)), *(fp)->_p != '\n' ? \
                (s32)*(fp)->_p++ : \
                Swbuf_138e90('\n', fp): \
            Swbuf_138e90((s32)(c), fp) : \
        (*(fp)->_p = (c), (s32)*(fp)->_p++))

struct Filebuf {
    virtual ~Filebuf();
    virtual void v1();
    virtual Pos seekoff(s64 off, u8 way, u8 which);   /* vtable +0x10 */
    wchar4 *eback, *gptr, *egptr;     /* +0x04 */
    wchar4 *pbase, *pptr, *epptr;     /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    wchar4 buf[16];                 /* +0x24 */
    u8 b64, b65, b66;               /* +0x64 */
    void pbump(s32 n) { pptr += n; }
    wchar4 *pbase_() const { return pbase; }
    wchar4 *pptr_() const { return pptr; }
};

extern "C" s32 WFilebufOverflow_1053e0(Filebuf *self, s32 c)
{
    wchar4 *p;
    s32 ch;
    bool failed;

    if (!self->file)
        return -1;
    if (self->b66) {
        if (!self->pptr) {
            if (self->gptr < self->egptr) {
                if (self->seekoff(0, 2, 8).off == -1)
                    return -1;
            }
            self->pbase = self->pptr = self->buf;
            self->epptr = self->buf + 16;
        }
    }
    self->b64 = 1;
    if (self->b65) {
        for (p = self->pbase; p < self->pptr; p++) {
            ch = (wchar)*p;
            if (((my_putc(ch, self->file) == -1) ? -1 : ch) == -1) {
                if (self->pbase < p) {
                    memcpy(self->pbase, p, (self->pptr - p) * sizeof(wchar4));
                    self->pbump(self->pbase - p);
                }
                return -1;
            }
        }
        self->pbump(self->pbase_() - self->pptr_());
        failed = !(c == -1);
        if (failed) {
            ch = (wchar)c;
            failed = ((my_putc(ch, self->file) == -1) ? -1 : ch) == -1;
        }
        if (failed)
            return -1;
    } else {
        for (p = self->pbase; p < self->pptr; p++) {
            if (WFilebufWriteWChar_105e00(self, 4, (wchar)*p) == -1) {
                if (self->pbase < p) {
                    memcpy(self->pbase, p, (self->pptr - p) * sizeof(wchar4));
                    self->pbump(self->pbase - p);
                }
                return -1;
            }
        }
        self->pbump(self->pbase_() - self->pptr_());
        failed = false;
        if (ne(c, -1)) {
            if (WFilebufWriteWChar_105e00(self, 4, c) == -1)
                failed = true;
        }
        if (failed)
            return -1;
    }
    return eq(c, -1) ? 0 : c;
}
