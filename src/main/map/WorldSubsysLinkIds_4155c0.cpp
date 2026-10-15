#include "types.h"

class VCvt {
public:
    /* +0x008 */ virtual void slot008();
    /* +0x00C */ virtual void slot00C();
    /* +0x010 */ virtual void slot010();
    /* +0x014 */ virtual void slot014();
    /* +0x018 */ virtual void slot018();
    /* +0x01C */ virtual void slot01C();
    /* +0x020 */ virtual void slot020();
    /* +0x024 */ virtual void slot024();
    /* +0x028 */ virtual void slot028();
    /* +0x02C */ virtual void slot02C();
    /* +0x030 */ virtual void slot030();
    /* +0x034 */ virtual void slot034();
    /* +0x038 */ virtual void slot038();
    /* +0x03C */ virtual void slot03C();
    /* +0x040 */ virtual void slot040();
    /* +0x044 */ virtual void slot044();
    /* +0x048 */ virtual void slot048();
    /* +0x04C */ virtual void slot04C();
    /* +0x050 */ virtual void slot050();
    /* +0x054 */ virtual void slot054();
    /* +0x058 */ virtual void slot058();
    /* +0x05C */ virtual void slot05C();
    /* +0x060 */ virtual void slot060();
    /* +0x064 */ virtual void slot064();
    /* +0x068 */ virtual void slot068();
    /* +0x06C */ virtual void slot06C();
    /* +0x070 */ virtual s32 fn70(s16);
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
void IterInit_370170(void *it, s32 arg1);
}

extern "C" s32 WorldSubsysLinkIds_4155c0(s32 arg0, Arg1Obj *arg1)
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
    IterInit_370170(sp38, var_5);
    while ((temp_2 = (Elem *)IterNext_370040(sp38)) != 0) {
        temp_2->unk4 = arg1->unk34->unk8->fn70(*(s16 *)&temp_2->unk4);
        temp_2->unk8 = arg1->unk34->unkC->fn70(*(s16 *)&temp_2->unk8);
    }
    return 1;
}
