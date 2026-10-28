#include "types.h"
#undef NULL
#define NULL 0

extern "C" {
class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * m388() { return VCM0(void *, 0x388); }
    void * m38c() { return VCM0(void *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * m3c4() { return VCM0(void *, 0x3C4); }
};
extern void *GetGameData_1fede0(void);
extern void ScriptSetRefInt_26a1e0(s32, s16);
extern s32 ScriptGetInt_26a2a0(s32);
extern Obj *CharaMgrPoolFindById_3a8c60(s32, s32);

s32 EvCmdCharaGetEquipItemId_267810(s64 *arg0)
{
    Obj *obj;
    s32 firstResult;
    s32 kind;
    s16 var19;
    void *var18;

    firstResult = ScriptGetInt_26a2a0((s32)arg0++);
    kind = ScriptGetInt_26a2a0((s32)arg0++);
    var19 = -1;
    obj = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), firstResult);
    if (obj != NULL) {
        switch (kind) {
        case 0:
            var18 = obj->m388();
            break;
        case 1:
            var18 = obj->m38c();
            break;
        case 2:
            var18 = obj->m3c4();
            break;
        }
        if (var18 != NULL) {
            var19 = *(s16 *)(*(s32 *)((u8 *)var18 + 0x10));
        }
    }
    ScriptSetRefInt_26a1e0((s32)arg0, var19);
    return 1;
}

}
