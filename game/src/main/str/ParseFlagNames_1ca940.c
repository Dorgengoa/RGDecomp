/* rgp:protos */
#define RGP_SELF_Lookup 1
#define RGP_SELF_ParseFlagNames_1ca940 1
#define RGP_SELF_StrEq 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry {
    s8 *name;
    s32 val;
} Entry;

extern s32 strcmp(const s8 *, const s8 *);

#define IsIdent(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9') || (c) == '_')

static inline s32 StrEq(const s8 *a, const s8 *b)
{
    if (a == 0 || b == 0) return 0;
    return strcmp(a, b) == 0;
}

static inline s32 Lookup(Entry *tbl, s8 *name, volatile u8 *found)
{
    Entry *e = tbl;
    if (name == 0 || tbl == 0 || tbl->name == 0) return 0;
    for (; e->name != 0; e++) {
        if (StrEq(name, e->name)) {
            *found = 1;
            return e->val;
        }
    }
    *found = 0;
    return 0;
}

s32 ParseFlagNames_1ca940(s8 *str, Entry *tbl, u8 *outflag)
{
    s32 result = 0;
    s8 *p;
    s8 *q;
    s8 c;
    volatile u8 found;

    if (str == 0 || tbl == 0) return 0;
    p = str;
    if (outflag != 0) {
        *outflag = 0;
    }
    while (*p != 0) {
        while (!IsIdent(*p)) {
            if (*p == 0) return result;
            p++;
        }
        for (q = p; IsIdent(*q); q++) {
        }
        c = *q;
        *q = 0;
        result |= Lookup(tbl, p, &found);
        *q = c;
        if (outflag != 0) {
            *outflag = *outflag | found;
        }
        if (*q == 0) break;
        p = q + 1;
    }
    return result;
}
