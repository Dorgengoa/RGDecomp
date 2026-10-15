#include "types.h"

class Node {
public:
    Node *next;
    Node *prev;
    s32 m8;
    s32 mC;
    u8 *obj;
    virtual void init();
};

extern "C" {
extern u8 *MemStackNew_14e230(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(u8 *, s32);
extern s32 ModelGetFrameMesh_152000(u8 *, u8 *, s32);
extern s32 SlotGetInt_15f720(void);
extern void ClothBuildFromMeshMaybe_185500(u8 *, s32 *, s32);
extern void ClothInit_185c50(u8 *);
extern void MapModelCfgMdsEnd_195750(s32, s32);
extern u8 D_00470528[];
extern u8 *D_00481328;
extern s32 D_0048132C;
extern u8 *D_00481354;
}

extern "C" s32 MapModelCfgCloth_195b40(void)
{
    s32 key;
    s32 r;
    s32 heap;
    u8 *owner;
    u8 *o;
    Node *n;
    Node *p;
    s32 sp5C;

    key = SlotGetInt_15f720();
    MapModelCfgMdsEnd_195750(0, 0);
    if (D_00481328 == 0) {
        return 0;
    }
    {
        u8 *q = *(u8 **)(D_00481328 + 0x8);
        r = ModelGetFrameMesh_152000(q, q + 0x120, ModelFindFrameIndexByName_151220(q, key));
    }
    if (r == 0) {
        return 0;
    }
    heap = D_0048132C;
    owner = D_00481328;
    o = MemStackNew_14e230(0x90, heap);
    if (o != 0) {
        ClothInit_185c50(o);
    }
    if (o == 0) {
        o = 0;
    } else {
        n = (Node *)MemStackNew_14e230(0x18, heap);
        if (n != 0) {
            *(u8 **)((u8 *)n + 0x14) = D_00470528;
            n->init();
        }
        if (n == 0) {
            o = 0;
        } else {
            n->obj = o;
            if (*(Node **)(owner + 0x10) == 0) {
                *(Node **)(owner + 0x10) = n;
            } else {
                p = *(Node **)(owner + 0x10);
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
        }
    }
    if (o == 0) {
        return 0;
    }
    sp5C = r;
    ClothInit_185c50(o);
    ClothBuildFromMeshMaybe_185500(o, &sp5C, D_0048132C);
    D_00481354 = o;
    return 1;
}
