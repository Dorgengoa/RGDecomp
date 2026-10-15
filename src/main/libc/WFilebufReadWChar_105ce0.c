#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t> per-char read helper, called as WFilebufReadWChar_105ce0(this, 4, !gptr) by
 *   the wide filebuf members (105a30 underflow, 105900). Reads n (<= 12) bytes from the FILE at +0x1C with
 *   the newlib getc macro (Srget_133f30 = __srget), eof -> eof; memcpy them into a 4-byte slot; if putback,
 *   ungetc them back in reverse (Ungetc_1364e8); returns the low 16 bits of the slot.
 * Char twin FilebufReadChar_105fe0 (n=1). Built -O4,p (config/toolchain.txt row). libdeasm 105ce0. */

#pragma cplusplus on

typedef struct File { u8 *p; s32 r; } File;
extern "C" s32 Srget_133f30(File *f);          /* __srget */
extern "C" s32 Ungetc_1364e8(s32 c, File *f);   /* ungetc */
extern "C" void *memcpy(void *d, const void *s, u32 n);

struct WFilebuf {
    void *vt;
    void *eback, *gptr, *egptr;
    void *pbase, *pptr, *epptr;
    File *file;                     /* +0x1C */
};

extern "C" s32 WFilebufReadWChar_105ce0(WFilebuf *self, s32 n, s32 putback)
{
    s8 buf[12];
    s32 wc;
    s32 i;
    s32 c;

    if ((u32)n > 12)
        return -1;
    for (i = 0; i < n; i++) {
        c = --self->file->r < 0 ? Srget_133f30(self->file) : *self->file->p++;
        if (c == -1)
            return -1;
        buf[i] = c;
    }
    memcpy(&wc, buf, n);
    if (putback) {
        while (n > 0) {
            if (Ungetc_1364e8(buf[--n], self->file) == -1)
                return -1;
        }
    }
    return *(u16 *)&wc;
}
