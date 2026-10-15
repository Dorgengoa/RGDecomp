#include "types.h"
inline bool IsUp(s8 c) {
    bool r = false;
    if (c >= 0x41 && c <= 0x5A) {
        r = true;
    }
    return r;
}
inline s32 Low(s8 c) {
    if (IsUp(c)) {
        return c + 0x20;
    }
    return c;
}
extern "C" bool StrEqualNoCase_1ca610(s8 *a, s8 *b) {
    s32 cb;
    s32 ca;

    if (a == NULL || b == NULL) {
        return 0;
    }
    while ((ca = *a) != 0) {
        cb = Low(*b);
        ca = Low(ca);
        if (ca != cb) {
            return 0;
        }
        a++;
        b++;
    }
    return !*b;
}
