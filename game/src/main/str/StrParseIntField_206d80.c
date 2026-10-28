/* rgp:protos */
#define RGP_SELF_StrParseIntField_206d80 1
#define RGP_SELF_skipws 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

static inline char *skipws(char *s) { for (;;) { s32 c = *s; if (c != 32) { if (c != 9) break; } s++; } return s; }
s32 StrParseIntField_206d80(char *s, char **end)
{
    char buf[16] __attribute__((aligned(16)));
    char *d;
    char *e;
    s32 c;

    if (s == NULL) {
        return -1;
    }
    s = skipws(s);
    d = buf;
    for (;;) {
        c = *s;
        if (c == 0) {
            break;
        }
        switch ((char)c) {
        case '.':
        case '-':
            goto store;
        case 0x0A:
        case 0x0D:
        case ',':
            goto out;
        }
        if ((char)c < '0') {
            goto skip;
        }
        if ((char)c <= '9') {
store:
            *d++ = c;
        }
skip:
        s++;
    }
out:
    *d = 0;
    e = NULL;
    if (*s != 0) {
        s++;
        for (;;) {
            c = *s;
            if (c != '\r') {
                if (c != '\n') {
                    break;
                }
            }
            s++;
        }
        e = s;
    }
    if (end != NULL) {
        *end = e;
    }
    return atoi(buf);
}
