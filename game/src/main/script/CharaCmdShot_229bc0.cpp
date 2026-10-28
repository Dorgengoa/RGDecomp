/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v58(s32 a0) { return VCM(s32, (void *, s32), 0xF0, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v223(s32 a0) { return VCM(s32, (void *, s32), 0x384, a0); }
};


extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" s32 ActionMgrFindById_233b50(s32, s32);
extern "C" s32 CharaGetActionTable_214cd0(s32);
extern "C" s32 CharaGetActAbortCodeMaybe_2149b0(s32);
extern "C" void * GetGameData_1fede0(void);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" s32 CharaGetBaseActionMode_213830(s32);
extern "C" void CharaSetActAbortCodeMaybe_2149a0(s32, s32);
extern "C" void CharaClearActionGaugeUsed_214000(s32);
extern "C" s32 CharaCmdRunIfElseEvnt_22e480(s32, u8, s32, s32);

struct Obj0 { s32 m00; };
struct Obj1 { u8 pad000[0x14]; s32 m14; };

extern "C" s32 CharaCmdShot_229bc0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    struct Obj1 *r4;
    s32 r6;
    s32 r7;
    s32 r8;
    u8 flag;
    s32 r5;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrFindById_233b50(r0, p0->m00);
    if (r1 == 0) {
        return 1;
    }
    if (CharaGetActionTable_214cd0(r1) == 0) {
        return 1;
    }
    flag = 0;
    if (CharaGetActAbortCodeMaybe_2149b0(r1) == 0) {
        flag = 1;
        r4 = (struct Obj1 *)GetGameData_1fede0();
        r5 = CharaMgrPoolFindById_3a8c60(r4->m14, p0->m00);
        if (r5 != 0) {
            r6 = ((short)CharaGetBaseActionMode_213830(r1));
            r7 = ((struct C0 *)r5)->v223((r6 ^ 2) != 0);
            r8 = ((struct C0 *)r7)->v58(0);
            if (r8 <= 0) {
                CharaSetActAbortCodeMaybe_2149a0(r1, 2);
                CharaClearActionGaugeUsed_214000(r1);
                flag = 0;
            }
        }
    }
    return CharaCmdRunIfElseEvnt_22e480(p0->m00, flag, p1, p2);
}
