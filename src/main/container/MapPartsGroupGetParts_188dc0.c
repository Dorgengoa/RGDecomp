#include "types.h"

extern s32 strcmp(s32 arg0, s32 arg1);

typedef struct Node { struct Node *next; s32 pad[3]; s32 val; } Node;
typedef struct { s32 name; s32 p4; s32 p8; Node *head; } Entry;
typedef struct { u8 pad[0x2A8]; s32 count; Entry e[1]; } Tbl;

static inline u8 empty(s32 p) { return !(p != 0); }

static inline s32 find(Tbl *t, s32 name)
{
    s32 i;
    for (i = 0; i < t->count; i++) {
        if (empty(t->e[i].name)) {
            continue;
        }
        if (strcmp(t->e[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline Entry *get(Tbl *t, s32 i)
{
    if (i < 0 || i >= t->count) {
        return NULL;
    }
    return &t->e[i];
}

s32 MapPartsGroupGetParts_188dc0(Tbl *t, s32 name, s32 *out, s32 max)
{
    Entry *e;
    Node *n;
    s32 c;

    e = get(t, find(t, name));
    if (e == NULL) {
        return 0;
    }
    c = 0;
    for (n = e->head; n != NULL; n = n->next) {
        if (c >= max) {
            break;
        }
        out[c++] = n->val;
    }
    return c;
}
