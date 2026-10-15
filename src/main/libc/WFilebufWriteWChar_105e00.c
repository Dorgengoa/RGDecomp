#include "types.h"

/* MSL C++ library: basic_filebuf<wchar_t> per-char write helper, called as WFilebufWriteWChar_105e00(this, 4, c) by the
 *   wide overflow (WFilebufOverflow_1053e0). memcpy the wchar_t's bytes into a buffer, then write n of them with the
 *   newlib putc macro on the FILE at +0x1C (__swbuf = Swbuf_138e90); eof on failure, else returns c.
 * Put-side twin of WFilebufReadWChar_105ce0; char twin FilebufWriteChar_106100. `#pragma wchar_type on` makes wchar_t the built-in
 *   2-byte type, whose address-taken param home is sp+0x5c (u16/s16 land at 0x5e). Built -O4,p
 *   (config/toolchain.txt row). libdeasm 105e00. */

#pragma cplusplus on

typedef struct File {
    u8 *_p;          /* +0x00 */
    s32 r;          /* +0x04 */
    s32 w;          /* +0x08 */
    s16 flags, file;
    u8 *base; s32 size;
    s32 lbfsize;    /* +0x18 */
} File;

extern "C" s32 Swbuf_138e90(s32 c, File *f);   /* __swbuf */
extern "C" void *memcpy(void *d, const void *s, u32 n);

#pragma wchar_type on

#define my_putc(c, fp) \
    (--(fp)->w < 0 ? \
        (fp)->w >= (fp)->lbfsize ? \
            (*(fp)->_p = (c)), *(fp)->_p != '\n' ? \
                (s32)*(fp)->_p++ : \
                Swbuf_138e90('\n', fp): \
            Swbuf_138e90((s32)(c), fp) : \
        (*(fp)->_p = (c), (s32)*(fp)->_p++))

struct WFilebuf {
    void *vt;
    void *eback, *gptr, *egptr;
    void *pbase, *pptr, *epptr;
    File *file;                     /* +0x1C */
};

extern "C" s32 WFilebufWriteWChar_105e00(WFilebuf *self, s32 n, wchar_t c)
{
    s8 buf[12];
    s32 i;

    memcpy(buf, &c, n);
    for (i = 0; i < n; i++) {
        if (my_putc(buf[i], self->file) == -1)
            return -1;
    }
    return c;
}
