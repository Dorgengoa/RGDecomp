/* rgp:protos */
#line 1
#include "types.h"

class B002da6c0 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v58() { VCM0(void, 0x58); }
};

class A002da6c0 {
public:
    s16 unk0;
    u8 pad2[0x10 - 2];
    s32 unk10;
    u8 pad14[0x18 - 0x14];
    s32 unk18;
    s32 unk1C;
    u8 pad20[0x190 - 0x20];
    VC_VPTR_MEMBER;
    
    
    
    B002da6c0 * v18(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(B002da6c0 *, (void *, int, int, int), 0x18, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    s32 v24() { return VCM0(s32, 0x24); }
    
    
    s32 v30() { return VCM0(s32, 0x30); }
};

typedef struct Node002da6c0 Node002da6c0;
struct Node002da6c0 {
    Node002da6c0 *next;
    Node002da6c0 **prev;
    s32 pad8;
    s32 key;
};

typedef struct Obj002da6c0 {
    Node002da6c0 *head;
    u8 pad4[0xA8 - 4];
    s32 unkA8;
} Obj002da6c0;

typedef struct Sub002da6c0 {
    u8 pad0[0xB6];
    s16 unkB6;
} Sub002da6c0;

extern "C" void MemStackHeapFree_14dcb0(s32, s32);
extern "C" void ModelObjExEffectsStopAll_1b0870(B002da6c0 *);
extern "C" s32 GetObjRefTable_313de0();
extern "C" Sub002da6c0 *HandleRegistryLookup_314aa0(s32, s32);

extern "C" void EffectEntryReleaseNode_2da6c0(Obj002da6c0 *o, A002da6c0 *a, int rgp_a2, int rgp_a3)
{
    B002da6c0 *b;
    Node002da6c0 *n;
    Node002da6c0 *nx;
    Node002da6c0 **pv;
    Sub002da6c0 *s;
    s32 k;

    if (a == 0) {
        return;
    }
    b = a->v18((int)(long)(a), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (b != 0) {
        ModelObjExEffectsStopAll_1b0870(b);
        b->v58();
    }
    if (a->unk0 == 2 && a->v30() != 0) {
        MemStackHeapFree_14dcb0(o->unkA8, a->v30());
    }
    if (a->v24() != 0) {
        MemStackHeapFree_14dcb0(o->unkA8, a->v24());
    }
    k = a->unk10;
    for (n = o->head; n != 0; n = nx) {
        nx = n->next;
        if (k == n->key) {
            pv = n->prev;
            if (pv == 0) {
                o->head = nx;
                if (nx != 0) {
                    nx->prev = 0;
                }
            } else {
                *pv = nx;
                if (nx != 0) {
                    nx->prev = pv;
                }
            }
            n->next = 0;
            n->prev = 0;
        }
    }
    if (a->unk1C != 0) {
        MemStackHeapFree_14dcb0(o->unkA8, a->unk1C);
    }
    s = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), a->unk18);
    if (s != 0) {
        s->unkB6 = 1;
    }
}
