#include "types.h"

/* MSL C++ library: basic_filebuf<char>::overflow(int_type c) (vtable slot 0x34).
 *   if (!is_open()) return eof; in read mode with no put area: seekoff(0, cur, out) (vtable +0x10, pos_type
 *   through sret) then setp(buf +0x24, +0x34); flag +0x34 = 1. Flush pbase..pptr either through the newlib
 *   putc macro on the FILE at +0x1C (__swbuf = Swbuf_138e90) when +0x35 is set, or char-by-char through
 *   FilebufWriteChar_106100(this, 1, ch); on failure shift the unwritten tail down (memcpy) and return eof; then write c
 *   unless eof; return not_eof(c).
 * Built as C++. `#pragma opt_rebuildlogicals off` keeps the bool flags as values (not/sltiu/xori);
 * after-loop pbump through inline accessors (pbase_/pptr_) blocks CSE of the loop-condition pptr load;
 * branch-2 test through inline ne() = !eq() gives the value-form compare. Same object at -O4 and -O4,p.
 * libdeasm 1048d0. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

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
extern "C" s32 FilebufWriteChar_106100(Filebuf *self, s32 n, char c);

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
    char *eback, *gptr, *egptr;     /* +0x04 */
    char *pbase, *pptr, *epptr;     /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    char buf[16];                   /* +0x24 */
    u8 b34, b35, b36;               /* +0x34 */
    void pbump(s32 n) { pptr += n; }
    char *pbase_() const { return pbase; }
    char *pptr_() const { return pptr; }
};

extern "C" s32 FilebufOverflow_1048d0(Filebuf *self, s32 c)
{
    char *p;
    char ch;
    bool failed;

    if (!self->file)
        return -1;
    if (self->b36) {
        if (!self->pptr) {
            if (self->gptr < self->egptr) {
                if (self->seekoff(0, 2, 8).off == -1)
                    return -1;
            }
            self->pbase = self->pptr = self->buf;
            self->epptr = self->buf + 16;
        }
    }
    self->b34 = 1;
    if (self->b35) {
        for (p = self->pbase; p < self->pptr; p++) {
            ch = *p;
            if (((my_putc(ch, self->file) == -1) ? -1 : (s32)(u8)ch) == -1) {
                if (self->pbase < p) {
                    memcpy(self->pbase, p, self->pptr - p);
                    self->pbump(self->pbase - p);
                }
                return -1;
            }
        }
        self->pbump(self->pbase_() - self->pptr_());
        failed = !(c == -1);
        if (failed) {
            ch = (char)c;
            failed = ((my_putc(ch, self->file) == -1) ? -1 : (s32)(u8)ch) == -1;
        }
        if (failed)
            return -1;
    } else {
        for (p = self->pbase; p < self->pptr; p++) {
            if (FilebufWriteChar_106100(self, 1, *p) == -1) {
                if (self->pbase < p) {
                    memcpy(self->pbase, p, self->pptr - p);
                    self->pbump(self->pbase - p);
                }
                return -1;
            }
        }
        self->pbump(self->pbase_() - self->pptr_());
        failed = false;
        if (ne(c, -1)) {
            if (FilebufWriteChar_106100(self, 1, (char)c) == -1)
                failed = true;
        }
        if (failed)
            return -1;
    }
    return eq(c, -1) ? 0 : c;
}
