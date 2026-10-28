/* rgp:protos */
#line 1
#include "types.h"

class V427370 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x) { return VCM(s32, (void *, s32), 0x70, x); }
};

extern "C" {
extern void *IterNext_370040(void *);
extern void IterInit_370170(void *, void *, int, int);
extern f32 MapLinkedAreaGetYMaybe_3f09a0(void *, s32);
extern void TreasureBoxBaseParamRowClearRuntimeMaybe_427f00(s32);
}

typedef struct {
    u8 pad0[0x88];
    u8 unk88[0xC];
    s32 unk94;
} O427370;
typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x18 - 8];
    f32 unk18;
    u8 pad1C[0x3C - 0x1C];
    s32 unk3C;
} N427370;
extern "C" s32 WorldSubsysLinkIds_427370(O427370 *arg0, void *arg1)
{
    u8 sp68[8];
    f32 f20;
    s32 v19;
    N427370 *node;
    V427370 *p;
    void *v5;

    if (arg1 == NULL) {
        return 0;
    }
    f20 = MapLinkedAreaGetYMaybe_3f09a0(arg1, arg0->unk94);
    v5 = arg0;
    if (arg0 != NULL) {
        v5 = arg0->unk88;
    }
    IterInit_370170(sp68, v5, 0, 0);
    while ((node = (N427370 *)IterNext_370040(sp68)) != NULL) {
        
        s16 id = node->unk4;
        p = *(V427370 **)((u8 *)(*(void **)((u8 *)arg1 + 0x78)) + 0x8);
        if (p != NULL) {
            v19 = p->f(id);
        } else {
            v19 = 0;
        }
        if (v19 != 0) {
            TreasureBoxBaseParamRowClearRuntimeMaybe_427f00(v19);
            node->unk4 = v19;
            node->unk3C = arg0->unk94;
        } else {
            node->unk4 = 0;
            node->unk3C = 0;
        }
        if (f20 != 0.0f) {
            node->unk18 += f20;
        }
    }
    return 1;
}
