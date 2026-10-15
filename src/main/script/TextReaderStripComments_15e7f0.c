#include "types.h"


typedef struct {
    u8 *data;
    s32 len;
} Buf;

void TextReaderStripComments_15e7f0(Buf *arg0)
{
    u8 *s;
    s32 i;
    u8 *p;
    u8 *q;
    u8 *r;

    s = arg0->data;
    i = 0;
    while (i < arg0->len) {
        p = s + i;
        if (p[0] == 0x2F && p[1] == 0x2F) {
            while (i < arg0->len) {
                p = s + i;
                if (*p == 0xA || *p == 0xD) {
                    break;
                }
                *p = 0x20;
                i++;
            }
        }
        p = s + i;
        if (p[0] == 0x2F && p[1] == 0x2A) {
            while (i < arg0->len) {
                q = s + i;
                if (*q == 0x2A && *(r = q + 1) == 0x2F) {
                    *q = 0x20;
                    *r = 0x20;
                    break;
                }
                *q = 0x20;
                i++;
            }
        } else {
            i++;
        }
    }
}
