#include "types.h"

/* retail's indirect call is `lw $25,0x0($3) / lw $25,0xC($25) / jalr $25` --
   a jalr on $25 is C++ virtual dispatch, unreachable from any C spelling.
   The vtable pointer is the FIRST (and only) member of the node, i.e. the
   node itself is a polymorphic base class with no other data. slot 0xC is
   virtual index (0xC - 8) / 4 = 1. */

class VNodeFUN_0036ff80 {
public:
    virtual s32 v0(s16);
    virtual s32 v1(s16);
};

class ObjFUN_0036ff80 {
public:
    VNodeFUN_0036ff80 *unk0;
    s16 unk4;
    s16 unk6;
};

extern "C" s32 IterGetCurrent_36ff80(ObjFUN_0036ff80 *arg0)
{
    VNodeFUN_0036ff80 *node;
    s16 idx;

    node = arg0->unk0;
    if (node == NULL) {
        return 0;
    }
    idx = arg0->unk6;
    if (idx >= 0 && idx < arg0->unk4) {
        return node->v1(idx);
    }
    return 0;
}
