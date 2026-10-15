#include "types.h"

/* MSL C++ library: basic_filebuf<char>::pbackfail(int_type c).
 *   if (!is_open()) return eof; reading straight from the FILE (+0x36 clear, +0x35 set): eof -> eof, else
 *   ungetc(c, FILE at +0x1C) (Ungetc_1364e8); otherwise back up gptr in the buffer (eof if gptr <= eback)
 *   and store c unless eof; return not_eof(c).
 * Built as C++ (layout shared with FilebufOverflow_1048d0 overflow / FilebufSeekoff_104750 seekoff). `#pragma
 * opt_rebuildlogicals off` + inline ne() give the value-form not/sltiu/xori test; the `gptr <= eback` test
 * through inline const accessors gives the $at compare and the gptr reload. Same object at -O4 and -O4,p.
 * libdeasm 104cb0. */

#pragma cplusplus on
#pragma opt_rebuildlogicals off

typedef struct File File;
extern "C" s32 Ungetc_1364e8(s32 c, File *f);   /* ungetc */

static inline bool eq(s32 a, s32 b) { return a == b; }
static inline bool ne(s32 a, s32 b) { return !eq(a, b); }

struct Filebuf {
    virtual ~Filebuf();
    char *eback, *gptr, *egptr;     /* +0x04 */
    char *pbase, *pptr, *epptr;     /* +0x10 */
    File *file;                     /* +0x1C */
    s32 pad20;
    char buf[16];                   /* +0x24 */
    u8 b34, b35, b36;               /* +0x34 */
    char *eback_() const { return eback; }
    char *gptr_() const { return gptr; }
};

extern "C" s32 FilebufPbackfail_104cb0(Filebuf *self, s32 c)
{
    if (!self->file)
        return -1;
    if (!self->b36 && self->b35) {
        if (c == -1)
            return -1;
        if (Ungetc_1364e8(c, self->file) == -1)
            return -1;
    } else {
        if (self->gptr_() <= self->eback_())
            return -1;
        self->gptr--;
        if (ne(c, -1))
            *self->gptr = c;
    }
    return eq(c, -1) ? 0 : c;
}
