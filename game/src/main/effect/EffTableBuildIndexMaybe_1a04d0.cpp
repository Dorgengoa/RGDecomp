#pragma opt_propagation off
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Elem100990;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;
} SFlag24;

typedef struct SNode16 SNode16;
struct SNode16 {
    u8 pad0[0xC8];
    s32 unkC8;
    u8 padCC[0xDC - 0xCC];
    SNode16 *unkDC;
    u8 pad_e0[0xEC - 0xE0];
    SFlag24 *unkEC;
};

class SNode17Base {
public:
    u8 pad0[0x40];
    VC_VPTR_MEMBER; void f(Elem100990 * a0, SNode16 * a1) { VCM(void, (void *, Elem100990 *, SNode16 *), 0x8, a0, a1); }
};

class SNode17 : public SNode17Base {
public:
    u8 pad44[0x52 - 0x44];
    u8 unk52;
    u8 pad53[0x58 - 0x53];
    SNode17 *unk58;
    SNode16 *unk5C;
};

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x108 - 8];
    SNode17 *unk108;
    Elem100990 *unk10C;
    s32 unk110;
    s32 unk114;
} Obj;

typedef struct {
    s32 unk0;
    s32 unk4;
} Out;

extern "C" {
Elem100990 *OperatorNew_100990(s32);
void IdTableInitMaybe_1a9fd0(Elem100990 *, s32, s32);
}

static inline void Init(Elem100990 *p) {
    p->unk0 = 0;
    p->unk8 = 0;
    p->unk10 = 0;
    p->unkC = 0;
    p->unk4 = 0;
}

extern "C" void EffTableBuildIndexMaybe_1a04d0(Obj *arg0, Out *arg1) {
    s32 n;
    Elem100990 *mem;
    Elem100990 *q;
    Elem100990 *e;
    SFlag24 *flag;
    SNode17 *var_17;
    SNode16 *var_16;

    mem = OperatorNew_100990(0x14);
    e = mem;
    if (e != NULL) {
        Init(e);
    }
    q = e;
    if (e != NULL) {
        q = e;
    }
    arg0->unk10C = mem;
    if (q == 0) return;

    IdTableInitMaybe_1a9fd0(q, arg0->unk110, arg0->unk114);
    n = arg0->unk4 + 1;
    arg0->unk4 = n;
    if (n > 0x3fffffff) {
        arg0->unk4 = 0;
    }
    if (arg0->unk10C != NULL) {
        var_17 = arg0->unk108;
        while (var_17 != NULL) {
            if (var_17->unk52 == 0) {
                var_16 = var_17->unk5C;
                while (var_16 != NULL) {
                    if (!(var_16->unkC8 & 1)) {
                        flag = var_16->unkEC;
                        if (flag != NULL) {
                            if (flag->unk24 & 1) {
                                var_17->f(arg0->unk10C, var_16);
                            }
                        } else {
                            var_17->f(arg0->unk10C, var_16);
                        }
                    }
                    var_16 = var_16->unkDC;
                }
            }
            var_17 = var_17->unk58;
        }
        arg1->unk0 = arg0->unk10C->unkC;
        arg1->unk4 = arg0->unk10C->unk10;
    }
}
