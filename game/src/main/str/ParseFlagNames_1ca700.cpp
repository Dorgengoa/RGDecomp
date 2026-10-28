#include "types.h"
#pragma inline_depth(8)

typedef struct Entry {
    char *name;
    s32 val;
} Entry;

static inline s32 lower(char c) {
    bool up;
    up = 0;
    if (c >= 0x41 && c <= 0x5A) {
        up = 1;
    }
    if (up) {
        return c + 0x20;
    }
    return c;
}

static inline u8 streq(char *a, char *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    while (*a) {
        s32 cb = lower(*b);
        s32 ca = lower(*a);
        if (ca != cb) {
            return 0;
        }
        a++;
        b++;
    }
    return !*b;
}

static inline s32 lookup(char *name, Entry *tab, volatile u8 *found) {
    Entry *p = tab;
    if (name == NULL || tab == NULL || tab->name == NULL) {
        return 0;
    }
    for (; p->name != NULL; p++) {
        if (streq(name, p->name)) {
            *found = 1;
            return p->val;
        }
    }
    *found = 0;
    return 0;
}

#define ISIDENT(c) (((c) >= 0x61 && (c) <= 0x7A) || ((c) >= 0x41 && (c) <= 0x5A) || ((c) >= 0x30 && (c) <= 0x39) || (c) == 0x5F)

extern "C" s32 ParseFlagNames_1ca700(char *s, Entry *tab, u8 *flag) {
    s32 result;
    char *e;
    char saved;
    volatile u8 found;

    result = 0;
    if (s == NULL || tab == NULL) {
        return 0;
    }
    if (flag != NULL) {
        *flag = 0;
    }
    while (*s) {
        while (!ISIDENT(*s)) {
            if (*s == 0) {
                return result;
            }
            s++;
        }
        e = s;
        while (ISIDENT(*e)) {
            e++;
        }
        saved = *e;
        *e = 0;
        result |= lookup(s, tab, &found);
        *e = saved;
        if (flag != NULL) {
            *flag = *flag | found;
        }
        if (*e == 0) {
            return result;
        }
        s = e + 1;
    }
    return result;
}
