#include "types.h"

class Node {
public:
    Node *next;
    Node *prev;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    u8 pad28[0x50 - 0x28];
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }
};

extern "C" {
extern Node *MemStackNew_14e230(s32, s32);
extern s32 FuncDataTableIterNext_1908b0(u8 *);
extern void FuncDataTableIterBegin_1908e0(u8 *, s32);
extern void FuncAnimeBind_190fc0(s32 *, s32, u8 *);
extern u8 D_00470610[];
}

extern "C" s32 NodeObjCreateFuncAnimes_193900(u8 *self, s32 heap)
{
    s32 id;
    Node *p;
    Node *n;

    FuncDataTableIterBegin_1908e0(self + 0x114, 5);
    while ((id = FuncDataTableIterNext_1908b0(self + 0x114)) != 0) {
        n = MemStackNew_14e230(0x60, heap);
        if (n != 0) {
            *(u8 **)((u8 *)n + 0x50) = D_00470610;
            n->m14 = 0;
            n->m18 = 0;
            n->m1C = 0;
            n->m10 = 0;
            n->m24 = 0;
            n->m20 = 0;
            n->init();
        }
        if (n == 0) {
            return 0;
        }
        n->init();
        if (*(Node **)(self + 0x13C) == 0) {
            *(Node **)(self + 0x13C) = n;
        } else {
            p = *(Node **)(self + 0x13C);
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
        FuncAnimeBind_190fc0(&n->m10, id, self);
    }
    return 1;
}
