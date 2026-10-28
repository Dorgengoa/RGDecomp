/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Obj0242d70 Obj0242d70;
typedef struct VT0242d70 {
    u8 pad0[0x19C];
    s32 (*unk19C)(Obj0242d70 *, s32);
} VT0242d70;
struct Obj0242d70 {
    VT0242d70 *vtable;
};

extern s32 GetGameData_1fede0(void);
extern void ScriptSetRefInt_249030(s32, s32);
extern s32 ScriptGetInt_2490f0(s32);
extern Obj0242d70 *ActorFindById_3eb870(s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x19C, x0); }
};
s32 EvCmdStatusTest_242d70(s64 *arg0) {
    s32 result;
    Obj0242d70 *temp_2;
    s32 temp_16_2;
    s32 temp_17;
    s32 temp_16;

    temp_17 = GetGameData_1fede0();
    temp_16 = ScriptGetInt_2490f0((s32)arg0++);
    temp_16_2 = ScriptGetInt_2490f0((s32)arg0++);
    temp_2 = ActorFindById_3eb870(temp_17, temp_16);
    if (temp_2 == NULL) {
        return 0;
    }
    ScriptSetRefInt_249030((s32)arg0, ((VC_0 *)(temp_2))->f(temp_16_2) & 0xFF);
    return 1;
}

}
