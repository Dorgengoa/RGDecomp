/* SPDX-License-Identifier: CC0-1.0 */
/* MSL basic_string<char> internals the game's C code calls directly
 * (StrMapInsertNode_1a6e00/1a6fa0/1a7140 copy string keys with
 * reserve + replace; the num_put formatters use replace-with-fill).
 *
 * The 12-byte MSL string, as the retail code reads it:
 *   long  (word0 bit 0 = 1): word0 = cap << 1 | 1, word1 = size, word2 = data
 *   short (word0 bit 0 = 0): byte0 = size << 1, chars in bytes 1..11, cap 11
 * Capacities follow retail: reserve(n) rounds max(n, size) to 11 (short) or
 * (n + 16) & ~15; replace grows from (cap + 15) & ~15, doubling (rounded to
 * 16) until size + 1 fits.  Buffers come from the game's operator new.
 * Retail throws length_error/out_of_range (EH is off in this game: the
 * throw ends in terminate); the port aborts the same way. */
#include "crt.h"

#include <stdlib.h>
#include <string.h>

typedef struct msl_string {
    uint32_t w0, size;
    char *CRT_P32 data; /* the string object lives in game memory: 4-byte word on x64 */
} msl_string;

static int is_long(const msl_string *s) { return s->w0 & 1; }
static uint32_t str_size(const msl_string *s) { return is_long(s) ? s->size : (uint8_t)s->w0 >> 1; }
static uint32_t str_cap(const msl_string *s) { return is_long(s) ? s->w0 >> 1 : 11; }
static char *str_data(msl_string *s) { return is_long(s) ? s->data : (char *)s + 1; }

static void set_short_size(msl_string *s, uint32_t n)
{
    uint8_t *b = (uint8_t *)s;
    b[0] = (uint8_t)((b[0] & 1) | ((n & 0x7F) << 1));
}

static void set_long(msl_string *s, char *data, uint32_t size, uint32_t cap)
{
    s->data = data;
    s->size = size;
    s->w0 = (s->w0 & 1) | (cap << 1);
}

static void msl_throw(const char *what)
{
    (void)what;
    Abort_12de80(); /* EH off: throw -> terminate -> abort */
}

/* basic_string::reserve(n) */
void StringReserve_107e80(void *str, uint32_t n)
{
    msl_string *s = (msl_string *)str;
    int was_long = is_long(s), now_long;
    uint32_t size, cap;
    char *src, *dst;
    if (n >= 0x7FFFFFFFu) {
        msl_throw("length_error");
        return;
    }
    size = str_size(s);
    cap = str_cap(s);
    if (n < size)
        n = size;
    n = n + 1 < 12 ? 11 : (n + 16) & ~15u;
    if (n == cap)
        return;
    if (n == 11) {
        src = s->data; /* only reachable from long: short has cap 11 */
        dst = (char *)s + 1;
        now_long = 0;
    } else {
        dst = (char *)OperatorNew_100990(n);
        if (!dst)
            return;
        now_long = 1;
        src = was_long ? s->data : (char *)s + 1;
    }
    memcpy(dst, src, size);
    dst[size] = 0;
    if (was_long)
        OperatorDelete_100840(src);
    s->w0 = (s->w0 & ~1u) | (uint32_t)now_long;
    if (!now_long)
        set_short_size(s, size);
    else
        set_long(s, dst, size, n);
}

/* shared body of replace(pos, n1, [first, last)) and replace(pos, n1, n2, c) */
static void *replace_core(msl_string *s, uint32_t pos, uint32_t n1, const char *first,
                          uint32_t n2, int fill, char c)
{
    uint32_t size = str_size(s), cap = str_cap(s), xlen, tail, newsize;
    char *data = str_data(s);
    int was_long = is_long(s);
    if (pos > size) {
        msl_throw("out_of_range");
        return s;
    }
    xlen = size - pos < n1 ? size - pos : n1;
    if (n2 >= 0x7FFFFFFFu || 0x7FFFFFFEu - n2 < size - xlen) {
        msl_throw("length_error");
        return s;
    }
    tail = size - (pos + xlen);
    newsize = n2 + size - xlen;
    if (newsize >= cap) {
        uint32_t ncap = (cap + 15) & ~15u;
        char *buf;
        while (ncap < newsize + 1)
            ncap = (ncap * 2 + 15) & ~15u;
        buf = (char *)OperatorNew_100990(ncap);
        if (pos)
            memcpy(buf, data, pos);
        if (fill)
            memset(buf + pos, c, n2);
        else
            memcpy(buf + pos, first, n2);
        if (tail)
            memcpy(buf + pos + n2, data + pos + xlen, tail);
        buf[newsize] = 0;
        if (was_long)
            OperatorDelete_100840(data);
        else
            s->w0 |= 1;
        set_long(s, buf, newsize, ncap);
        return s;
    }
    {
        char *tmp = NULL;
        if (!fill && tail && data + pos + n2 < first + n2 && first + n2 <= data + size) {
            /* the source range lies in the part about to move: copy it first
             * (retail builds a temporary string) */
            tmp = (char *)malloc(n2 ? n2 : 1);
            memcpy(tmp, first, n2);
            first = tmp;
        }
        if (tail)
            memmove(data + pos + n2, data + pos + xlen, tail);
        if (fill)
            memset(data + pos, c, n2);
        else
            memmove(data + pos, first, n2);
        data[newsize] = 0;
        if (was_long)
            s->size = newsize;
        else
            set_short_size(s, newsize);
        free(tmp);
    }
    return s;
}

/* basic_string::replace(pos, n1, first, last, alloc) -- the allocator is an
 * empty by-value struct (one stack word on i686, ignored) */
void *StringReplace_106f90(void *s, uint32_t pos, uint32_t n1, const char *first, const char *last,
                           int alloc_unused)
{
    (void)alloc_unused;
    return replace_core((msl_string *)s, pos, n1, first, (uint32_t)(last - first), 0, 0);
}

/* basic_string::replace(pos, n1, n2, c) */
void *StringReplaceFill_1075d0(void *s, uint32_t pos, uint32_t n1, uint32_t n2, int c)
{
    return replace_core((msl_string *)s, pos, n1, NULL, n2, 1, (char)c);
}
