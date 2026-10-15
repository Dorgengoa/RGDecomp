#include "types.h"

extern s32 ResGroupGetStack_42c720(s32, s32);
extern void MemStackReset_14d830(s32);
extern void MemStackClear_14dff0(s32);

struct Node {
    struct Node *next;
    u8 pad4[6];
    u8 m0A;
};

struct Obj0 {
    u8 pad000[0x174];
    u16 m174;
    u16 m176;
    u16 m178;
    u16 m17A;
    u16 m17C;
    u8 pad17E[2];
    struct Node *m180;
    struct Node *m184;
    struct Node *m188;
    struct Node *m18C;
    struct Node *m190;
    struct Node *m194;
    struct Node *m198;
    struct Node *m19C;
    struct Node *m1A0;
    struct Node *m1A4;
};

s32 ResGroupUnloadGroup_42b650(struct Obj0 *p0, s32 p1)
{
    struct Node *prev;
    struct Node *cur;
    struct Node *next;
    struct Node *prev2;
    struct Node *cur2;
    struct Node *next2;
    struct Node *prev3;
    struct Node *cur3;
    struct Node *next3;
    struct Node *prev4;
    struct Node *cur4;
    struct Node *next4;
    struct Node *prev5;
    struct Node *cur5;
    struct Node *next5;
    s32 r2;

    cur = p0->m180;
    prev = 0;
    while (cur != 0) {
        next = cur->next;
        if (p1 == (cur->m0A & 3)) {
            if (prev == 0) {
                p0->m180 = next;
            } else {
                prev->next = next;
            }
            if (next == 0) {
                p0->m184 = prev;
            }
            p0->m174--;
        } else {
            prev = cur;
        }
        cur = next;
    }

    cur2 = p0->m188;
    prev2 = 0;
    while (cur2 != 0) {
        next2 = cur2->next;
        if (p1 == (cur2->m0A & 3)) {
            if (prev2 == 0) {
                p0->m188 = next2;
            } else {
                prev2->next = next2;
            }
            if (next2 == 0) {
                p0->m18C = prev2;
            }
            p0->m176--;
        } else {
            prev2 = cur2;
        }
        cur2 = next2;
    }

    cur3 = p0->m190;
    prev3 = 0;
    while (cur3 != 0) {
        next3 = cur3->next;
        if (p1 == (cur3->m0A & 3)) {
            if (prev3 == 0) {
                p0->m190 = next3;
            } else {
                prev3->next = next3;
            }
            if (next3 == 0) {
                p0->m194 = prev3;
            }
            p0->m178--;
        } else {
            prev3 = cur3;
        }
        cur3 = next3;
    }

    cur4 = p0->m198;
    prev4 = 0;
    while (cur4 != 0) {
        next4 = cur4->next;
        if (p1 == (cur4->m0A & 3)) {
            if (prev4 == 0) {
                p0->m198 = next4;
            } else {
                prev4->next = next4;
            }
            if (next4 == 0) {
                p0->m19C = prev4;
            }
            p0->m17A--;
        } else {
            prev4 = cur4;
        }
        cur4 = next4;
    }

    cur5 = p0->m1A0;
    prev5 = 0;
    while (cur5 != 0) {
        next5 = cur5->next;
        if (p1 == (cur5->m0A & 3)) {
            if (prev5 == 0) {
                p0->m1A0 = next5;
            } else {
                prev5->next = next5;
            }
            if (next5 == 0) {
                p0->m1A4 = prev5;
            }
            p0->m17C--;
        } else {
            prev5 = cur5;
        }
        cur5 = next5;
    }

    r2 = ResGroupGetStack_42c720((s32)p0, p1);
    MemStackReset_14d830(r2);
    if ((p1 == 1) || (p1 == 2) || (p1 == 3)) {
        MemStackClear_14dff0(r2);
    }
    return 1;
}
