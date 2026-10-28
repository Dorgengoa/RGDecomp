/* rgp:protos */
#line 1
#include "types.h"

/* retail's indirect call is `lw $25,0x0($2) / lw $25,0x2B4($25) / jalr $25`
   -- a jalr on $25/$t9 is C++ virtual dispatch (see jalr-is-cpp-virtual
   lever). vptr offset K=0, slot 0x2B4 = 8 + 4*171 -> the 172nd declared
   virtual (0-based N=171), taking one s32 argument (the delay-slot a1=0). */

class VE_002c6b70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v171(s32 a0) { VCM(void, (void *, s32), 0x2B4, a0); }
};

typedef struct Ctx001fede0 {
    u8 pad0[0x1C];
    s32 unk1C;
} Ctx001fede0;

extern "C" Ctx001fede0 *GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_2cc9c0(void *);
extern "C" VE_002c6b70 *ObjFindById_3bb3a0(s32 a, s32 b);

extern "C" s32 AiCmdObjKill_2c6b70(void *arg0, s32 count)
{
    s32 id;
    VE_002c6b70 *obj;

    if (count <= 0) {
        return 0;
    }
    id = ScriptSlotGetInt_2cc9c0((void *)arg0);
    obj = ObjFindById_3bb3a0(GetGameData_1fede0()->unk1C, id);
    if (obj == NULL) {
        return 1;
    }
    obj->v171(0);
    return 1;
}
