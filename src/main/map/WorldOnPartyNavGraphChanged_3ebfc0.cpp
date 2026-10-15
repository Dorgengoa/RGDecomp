#include "types.h"

/* retail's two calls go through `jalr $25`, which only a real C++ virtual
   dispatch reaches (see jalr-is-cpp-virtual lever). vptr at node+0, slot
   0x70 => 26 dummy virtuals ahead of the real one (slot = 8 + 4*N). */
class VE003ebfc0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 v26(s32 a);
};

typedef struct MidFUN_003ebfc0 {
    u8 pad0[0x18];
    VE003ebfc0 *unk18;
} MidFUN_003ebfc0;

typedef struct InnerFUN_003ebfc0 {
    u8 pad0[0x34];
    MidFUN_003ebfc0 *unk34;
} InnerFUN_003ebfc0;

typedef struct ObjFUN_003ebfc0 {
    u8 pad0[0x8];
    InnerFUN_003ebfc0 *unk8;
    u8 pad0C[0x2C - 0xC];
    u8 unk2C;
} ObjFUN_003ebfc0;

extern "C" s32 WorldOnPartyNavGraphChanged_3ebfc0(ObjFUN_003ebfc0 *arg0, s32 arg1, s32 arg2)
{
    InnerFUN_003ebfc0 *inner;
    VE003ebfc0 *node;

    if (arg0->unk2C & 1) {
        return 0;
    }
    inner = arg0->unk8;
    if (inner == NULL) {
        return 0;
    }
    node = inner->unk34->unk18;
    node->v26(arg2);
    node = arg0->unk8->unk34->unk18;
    node->v26(arg1);
    return 1;
}
