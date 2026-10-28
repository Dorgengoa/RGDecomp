/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 3/3: length-wrong (42w vs retail 45w). Tried if-wrapped-body and
   early-return polarities for the `temp_2 != NULL` guard; retail wants a
   `bnel` at that test and this consistently emits a plain form, then the
   var_2/sp3C boolean-normalize sequence (xori+sltu+sb, same class of
   residue as EvCmdEventPlayerIsIdle_261050/EvDoorObjPlayOpen_303c90 in this same lane) never appears. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VTable2E {
    u8 pad[0x30];
    void (*unk30)(void *, f32 *);
    void (*unk34)(void *, f32 *);
} VTable2E;

typedef struct Obj2E {
    u8 pad[0xDC];
    VTable2E *unkDC;
} Obj2E;

f32 GameSceneGetTimeStep_1ceba0(s32);
s32 GetGameMode_1f59c0(void);
s32 GetCurrentScene_1f5be0(void);
Obj2E *EventObjMgrFindObjByName_2e9920(s32, s32 xa1, s32 xa2);
typedef struct Arg2E { f32 f; bool b; } Arg2E;
typedef struct Arg2Ec { f32 f; s8 b; } Arg2Ec;
void EvDoorObjSetOpened_303c60(Obj2E *, s32);

class VC_0 {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0x30, x0); }
};
class VC_1 {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    void f(void * x0) { VCM(void, (void *, void *), 0x34, x0); }
};
s32 EvDoorObjSetOpenedByName_2e8e70(s32 arg0, s32 arg1, s32 arg2) {
    Arg2E s __attribute__((aligned(16)));
    Obj2E *temp_2;

    temp_2 = EventObjMgrFindObjByName_2e9920(arg0, arg1, 9);
    if (temp_2 == NULL) {
        return 0;
    }
    EvDoorObjSetOpened_303c60(temp_2, arg2);
    s.f = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    s.b = GetGameMode_1f59c0() != 6 && GetGameMode_1f59c0() != 7;
    ((VC_0 *)(temp_2))->f(&s);
    ((VC_1 *)(temp_2))->f(&s);
    return 1;
}

}
