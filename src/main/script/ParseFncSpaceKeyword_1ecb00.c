#include "types.h"

extern u8 D_0044B3B0[];
extern void *LookupNameValueNoCase_1cab50(void *a, u8 *b, s32 c);

void *ParseFncSpaceKeyword_1ecb00(void *p)
{
    if (p != 0) {
        return LookupNameValueNoCase_1cab50(p, D_0044B3B0, 0);
    }
    return 0;
}
