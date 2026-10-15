#include "types.h"

extern s32 strlen(char *);

void DebugMenuWidgetSetLabel_209bb0(char *dst, char *src)
{
    s32 len;
    s32 i;
    dst[0] = 0;
    if (src == 0) return;
    len = strlen(src);
    if (len >= 0x18) {
        len = 0x17;
    }
    for (i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    dst[i] = 0;
}
