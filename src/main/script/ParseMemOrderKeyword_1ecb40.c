#include "types.h"

extern u8 D_0044B390[];
extern void *LookupNameValueNoCase_1cab50(void *a, u8 *b, s32 c);

void *ParseMemOrderKeyword_1ecb40(void *p)
{
    if (p != 0) {
        return LookupNameValueNoCase_1cab50(p, D_0044B390, 0);
    }
    return 0;
}
