#include "types.h"

class Node {
public:
    Node *next;
    Node *prev;
    s32 m8;
    s32 mC;
    s32 m10[4];
    virtual void init();
};

extern "C" {
extern Node *MemStackNew_14e230(s32, s32);
extern u8 D_00471020[];
extern u8 *D_0049D4E0[];
extern s32 D_0049D45C[];
extern s32 D_0049D4E4[];
extern s32 D_0049D4F0[];
extern s32 D_0049D4F4[];
extern s32 D_0049D4F8[];
extern s32 D_0049D4FC[];
extern s32 D_0049D500[];
}

extern "C" s32 ParamScriptSeEndCmd_1af300(void)
{
    u8 *ctx;
    s32 heap;
    s32 v;
    Node *p;
    Node *n;
    s32 *q;

    ctx = D_0049D4E0[0];
    heap = D_0049D45C[0];
    if (ctx == 0 || heap == 0) {
        return 0;
    }
    if (D_0049D500[0] <= 0) {
        return 0;
    }
    v = D_0049D4E4[0];
    n = MemStackNew_14e230(0x24, heap);
    if (n != 0) {
        *(u8 **)((u8 *)n + 0x20) = D_00471020;
        *(s32 *)((u8 *)n + 0x18) = 0;
        *(s32 *)((u8 *)n + 0x1C) = 0;
        n->init();
    }
    if (n == 0) {
        q = 0;
    } else {
        n->init();
        n->m8 = heap;
        n->mC = v;
        if (*(Node **)(ctx + 0x51C) == 0) {
            *(Node **)(ctx + 0x51C) = n;
        } else {
            p = *(Node **)(ctx + 0x51C);
            while (p != 0) {
                if (p->next == 0) {
                    break;
                }
                p = p->next;
            }
            p->next = n;
            if (n != 0) {
                n->prev = p;
            }
        }
        q = (s32 *)((u8 *)n + 0x10);
    }
    if (q == 0) {
        return 0;
    }
    q[0] = D_0049D4F0[0];
    q[1] = D_0049D4F4[0];
    q[2] = D_0049D4F8[0];
    q[3] = D_0049D4FC[0];
    return 1;
}
