/* rgp:protos */
#line 1
#include "types.h"

class VCvt {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ 
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ s32 fn70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

typedef struct ObjUnk34 {
    u8 pad0[8];
    VCvt *unk8;
    VCvt *unkC;
} ObjUnk34;

typedef struct Arg1Obj {
    u8 pad0[0x34];
    ObjUnk34 *unk34;
} Arg1Obj;

typedef struct Elem {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
} Elem;

extern "C" {
void *IterNext_370040(void *it);
void IterInit_370170(void *, s32, int, int);
}

extern "C" s32 WorldSubsysLinkIds_4155c0(s32 arg0, Arg1Obj *arg1, int rgp_a2, int rgp_a3)
{
    u8 sp38[8];
    s32 var_5;
    Elem *temp_2;

    if (arg1 == 0) {
        return 0;
    }
    var_5 = arg0;
    if (arg0 != 0) {
        var_5 += 0x88;
    }
    IterInit_370170(sp38, var_5, (int)rgp_a2, (int)rgp_a3);
    while ((temp_2 = (Elem *)IterNext_370040(sp38)) != 0) {
        temp_2->unk4 = arg1->unk34->unk8->fn70(*(s16 *)&temp_2->unk4);
        temp_2->unk8 = arg1->unk34->unkC->fn70(*(s16 *)&temp_2->unk8);
    }
    return 1;
}
