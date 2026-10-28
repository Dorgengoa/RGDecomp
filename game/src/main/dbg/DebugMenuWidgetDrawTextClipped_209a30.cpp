#include "types.h"
#undef NULL
#define NULL 0

extern "C" void TextGridPrintAt_208880(s32, s32, s32, s32, s8 *, f32);
extern "C" s32 strlen(s8 *);

extern "C" void DebugMenuWidgetDrawTextClipped_209a30(void *arg0, s8 *arg1, s32 pd2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 fparg0)
{
    s8 *s;
    s8 *e;
    s32 m;
    s32 n;
    s8 saved;
    bool more;

    s = arg1;
    if (s == NULL) {
        return;
    }
    e = s + strlen(s);
    n = *(s16 *)((u8 *)arg0 + 0x20);
    saved = *e;
    if (n > 0 && n < arg3) {
        m = *(s16 *)((u8 *)arg0 + 0x24);
        while (!!*s && m > 0) {
            if (*s == 0xA) {
                s++;
                m--;
            } else {
                s++;
            }
        }
        e = s;
        while (!!*e && n > 0) {
            if (*e == 0xA && --n == 0) {
                break;
            }
            e++;
        }
        saved = *e;
        *e = 0;
    }
    TextGridPrintAt_208880(arg4, arg5, arg6, arg7, s, fparg0 * fparg0);
    *e = saved;
}
