#include "types.h"

typedef struct {
    s8 *name;
    s32 val;
} Ent001CAB50;

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
inline bool StrEqI(s8 *a, s8 *b) {
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

extern "C" s32 LookupNameValueNoCase_1cab50(s8 *key, Ent001CAB50 *tbl, bool *found)
{
    if (key == NULL || tbl == NULL || tbl->name == NULL) {
        return 0;
    }
    while (tbl->name != NULL) {
        if (StrEqI(key, tbl->name)) {
            if (found != NULL) {
                *found = 1;
            }
            return tbl->val;
        }
        tbl++;
    }
    if (found != NULL) {
        *found = 0;
    }
    return 0;
}
