#include "types.h"

/* MSL C++ library: basic_filebuf<char> per-char write helper FilebufWriteChar_106100(this, n, c). memcpy the char's
 *   byte into a buffer, then write n bytes with the newlib putc macro on the FILE at +0x1C
 *   (__swbuf = Swbuf_138e90); -1 on failure, else returns (u8)c.
 * Char twin of WFilebufWriteWChar_105e00 (wchar_t write helper); put-side twin of FilebufReadChar_105fe0. Built -O4,p
 *   (config/toolchain.txt row). libdeasm 106100. */

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

struct Filebuf {
    void *vt;
    void *eback, *gptr, *egptr;
    void *pbase, *pptr, *epptr;
    File *file;                     /* +0x1C */
};

extern "C" s32 FilebufWriteChar_106100(Filebuf *self, s32 n, char c)
{
    s8 buf[12];
    s32 i;

    memcpy(buf, &c, n);
    for (i = 0; i < n; i++) {
        if (my_putc(buf[i], self->file) == -1)
            return -1;
    }
    return (u8)c;
}
