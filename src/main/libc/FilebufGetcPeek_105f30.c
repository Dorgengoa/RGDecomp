#include "types.h"

struct B105c30 { u8 *f0; s32 f4; };
struct S105c30 { u8 pad0[0x1C]; struct B105c30 *f1C; };

extern s32 Srget_133f30(struct B105c30 *b);
extern s32 Ungetc_1364e8(s32 c, struct B105c30 *b);

s32 FilebufGetcPeek_105f30(struct S105c30 *p0, s32 push)
{
    s32 c;

    if (--p0->f1C->f4 < 0) {
        c = Srget_133f30(p0->f1C);
    } else {
        c = *p0->f1C->f0++;
    }
    if (c == -1) {
        return -1;
    }
    if (push != 0) {
        if (Ungetc_1364e8(c, p0->f1C) == -1) {
            return -1;
        }
    }
    return c;
}
