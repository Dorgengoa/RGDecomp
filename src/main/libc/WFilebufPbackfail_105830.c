#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t>::pbackfail(int_type c) -- wide twin of FilebufPbackfail_104cb0.
 *   if (!is_open()) return eof; reading straight from the FILE (+0x66 clear, +0x65 set): eof -> eof, else
 *   ungetc(c, FILE at +0x1C) (Ungetc_1364e8); otherwise back up gptr in the buffer (eof if gptr <= eback)
 *   and store c (16-bit) unless eof; return not_eof(c).
 * Built as C++ like FilebufPbackfail_104cb0: `#pragma opt_rebuildlogicals off` + inline ne() give the value-form
 * not/sltiu/xori test; the `gptr <= eback` test through inline const accessors gives the $at compare and
 * the gptr reload. Elements are 4 bytes (wchar4) with a 16-bit store. libdeasm 105830. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

typedef struct File File;
typedef s32 wchar4;
extern "C" s32 Ungetc_1364e8(s32 c, File *f);   /* ungetc */

static inline bool eq(s32 a, s32 b) { return a == b; }
static inline bool ne(s32 a, s32 b) { return !eq(a, b); }

struct WFilebuf {
    virtual ~WFilebuf();
    wchar4 *eback, *gptr, *egptr;   /* +0x04 */
    wchar4 *pbase, *pptr, *epptr;   /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    wchar4 buf[16];                 /* +0x24 */
    u8 b64, b65, b66;               /* +0x64 */
    wchar4 *eback_() const { return eback; }
    wchar4 *gptr_() const { return gptr; }
};

extern "C" s32 WFilebufPbackfail_105830(WFilebuf *self, s32 c)
{
    if (!self->file)
        return -1;
    if (!self->b66 && self->b65) {
        if (c == -1)
            return -1;
        if (Ungetc_1364e8(c, self->file) == -1)
            return -1;
    } else {
        if (self->gptr_() <= self->eback_())
            return -1;
        self->gptr--;
        if (ne(c, -1))
            *(u16 *)self->gptr = c;
    }
    return eq(c, -1) ? 0 : c;
}
