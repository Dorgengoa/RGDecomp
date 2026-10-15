#include "types.h"
#pragma opt_common_subs off

typedef struct Sub152 {
    s32 a;
    s32 id;
    s32 val;
} Sub152;

typedef struct Node152 {
    struct Node152 *next;
    u8 pad4[0xC];
    Sub152 sub;
} Node152;

extern s32 ArrayGetChecked_152e40(s32, s32);

s32 ModelGetFrameMesh_152000(void *unused0, void *arg1, s32 arg2) {
    Node152 *p;
    Sub152 *s;
    s32 v;
    s32 r;

    if (arg1 == NULL) {
        return 0;
    }
    for (p = *(Node152 **)((u8 *)arg1 + 0x44); p != NULL; p = p->next) {
        s = &p->sub;
        if (s->id == arg2) {
            v = s->val;
            goto found;
        }
    }
    v = -1;
found:
    if (*(s32 *)arg1 != 0) {
        r = ArrayGetChecked_152e40(*(s32 *)((u8 *)arg1 + 0xC), v);
    } else {
        r = 0;
    }
    return r;
}
