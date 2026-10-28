/* rgp:protos */
#line 1
#include "types.h"

extern "C" s32 InvFindByUniqueId_3c85d0(s32, s32, s32, s32);

typedef struct D818Obj {
    u8 pad0[0x18];
    s32 unk18;
} D818Obj;

extern "C" D818Obj *D_00483818;

class Obj3ACFA0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void slot38(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x38, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slot3DC(s32 a0) { return VCM(s32, (void *, s32), 0x3DC, a0); }
};

extern "C" s32 CharaSetEquip244ById_3ace70(Obj3ACFA0 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    if (arg1 < 0) {
        *(s16 *)((u8 *)arg0+0x244)=-1;
        arg0->slot38((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        return 1;
    }
    if (D_00483818 == NULL) {
        return 0;
    }
    return arg0->slot3DC(InvFindByUniqueId_3c85d0(D_00483818->unk18, arg1, -1, 0));
}
