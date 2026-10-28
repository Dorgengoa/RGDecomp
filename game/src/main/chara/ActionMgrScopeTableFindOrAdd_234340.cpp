/* rgp:protos */
#line 1
#include "types.h"

class Tree {
public:
    u8 pad[0xC];
    VC_VPTR_MEMBER; s32 v08(void * a0) { return VCM(s32, (void *, void *), 0x8, a0); }
};

struct Obj {
    u8 pad0[0x10];
    Tree tree;
    u8 pad20[0x34 - 0x20];
    u8 *f34;
    s32 pad38;
    s32 heap;
};

extern "C" {
extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern u8 *MemStackNew_14e130(s32, s32);
extern s32 ActCfgTableGetScopeId_223d00(void *);
extern s32 ActCfgTableClone_2244e0(void *, s32, void *, s32);
extern void ActCfgTableReset_225160(void *);
extern void ActCfgTableCtor_225250(void *);
extern s32 IntCompare_42ca30(s32, s32);
extern void *DListGetHead_42ea60(void *);
extern s32 DListGetCountPow2_42ea70(void *);
extern u8 *DListNodeAdvance_42eb00(void *, s32);
extern void DListNodeInit_42ec10(void *);
}

static inline u8 *create(Obj *arg0, void *arg1)
{
    s32 heap;
    s32 mem;
    u8 *node;

    heap = arg0->heap;
    if (arg1 == 0 || heap == 0) {
        return 0;
    }
    mem = MemStackHeapAlloc_14db10(heap, 2, 0, 0x40);
    if (mem == 0) {
        goto fail;
    }
    if ((node = MemStackNew_14e130(0xB0, heap)) != 0) {
        DListNodeInit_42ec10(node);
        ActCfgTableCtor_225250(node + 0x10);
        DListNodeInit_42ec10(node);
        ActCfgTableReset_225160(node + 0x10);
    }
    if (node == 0) {
        goto fail;
    }
    DListNodeInit_42ec10(node);
    ActCfgTableReset_225160(node + 0x10);
    if (ActCfgTableClone_2244e0(node + 0x10, mem, arg1, heap) == 0) {
        goto fail;
    }
    MemStackReturnToOwnerMaybe_14dad0(heap);
    if (arg0->tree.v08(node) == 0) {
        goto fail;
    }
    return node;
fail:
    MemStackReturnToOwnerMaybe_14dad0(heap);
    MemStackHeapFree_14dcb0(heap, mem);
    return 0;
}

extern "C" u8 *ActionMgrScopeTableFindOrAdd_234340(Obj *arg0, void *arg1)
{
    u8 *node;
    void *root;
    s32 n;
    u8 *p;
    s32 c;
    s32 key;
    s32 heap;
    s32 mem;

    if (arg1 == 0) {
        return 0;
    }
    key = ((short)ActCfgTableGetScopeId_223d00(arg1));
    if ((root = DListGetHead_42ea60(&arg0->tree)) == 0) {
        node = 0;
    } else {
        node = 0;
        n = ((unsigned short)DListGetCountPow2_42ea70(&arg0->tree));
        while (n > 0) {
            n >>= 1;
            p = DListNodeAdvance_42eb00(root, n);
            if (p == 0) {
                continue;
            }
            c = IntCompare_42ca30(key, ((short)ActCfgTableGetScopeId_223d00(p + 0x10)));
            if (c == 0) {
                node = p;
                break;
            }
            if (c > 0) {
                root = p;
            }
        }
    }
    if (node == 0) {
        node = create(arg0, arg1);
    }
done:
    if (node == 0) {
        return 0;
    }
    if (((short)ActCfgTableGetScopeId_223d00(node + 0x10)) == 0x7FFF) {
        arg0->f34 = node + 0x10;
    }
    return node + 0x10;
}
