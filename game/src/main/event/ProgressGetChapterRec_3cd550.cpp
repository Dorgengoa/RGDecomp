/* rgp:protos */
#line 1
#include "types.h"

class SubB003cd550 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 a) { return VCM(s32, (void *, s16), 0x70, a); }
};

typedef struct SubA003cd550 {
    u8 pad0[0x8];
    SubB003cd550 *unk8;
} SubA003cd550;

typedef struct Obj003cd550 {
    u8 pad0[0x4];
    SubA003cd550 *unk4;
} Obj003cd550;

extern "C" s32 StateGetChapter_3cd5b0(Obj003cd550 *arg0);

extern "C" s32 ProgressGetChapterRec_3cd550(Obj003cd550 *arg0)
{
    SubA003cd550 *a;
    SubB003cd550 *b;
    s16 val;

    a = arg0->unk4;
    if (a == 0) {
        return 0;
    }
    val = (s16) ((short)StateGetChapter_3cd5b0(arg0));
    a = arg0->unk4;
    b = a->unk8;
    return b->v26(val);
}
