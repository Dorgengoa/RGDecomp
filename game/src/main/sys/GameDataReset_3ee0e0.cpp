/* rgp:protos */
#line 1
/* main s22: 1 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  11 -> improved; still parked. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
typedef s32 (*FN)();


void PoolClear_36ade0(s32);                                /* extern */
void CharaSysResetAll_3a5ca0(s32);                                /* extern */
void DataTableOwnerClearTable_3b8c10(s32, int, int, int);                                /* extern */
void StateBlockReset_3cd670(s32, int, int, int);                                /* extern */
void OptionsResetDefaults_3d62c0(s32);                                /* extern */
void InteractRecResetMaybe_3ee600(void *);                         /* extern */
void InsectTeamTableReset_431d10(s32);                                /* extern */

typedef struct { u8 b0 : 1; u8 rest : 7; } BF2C;
extern "C++" { class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0x1C)((void *)this, vc_va...); }
}; }
void GameDataReset_3ee0e0(void *arg0) {
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_4;
    s32 temp_4_5;
    s32 temp_4_6;
    s32 temp_4_7;
    u8 temp_5;
    void **temp_4_3;
    void *temp_2;
    void *temp_2_2;

    temp_4 = (*(s32 *)((u8 *)(arg0) + 0xC));
    if (temp_4 != 0) {
        OptionsResetDefaults_3d62c0(temp_4);
    }
    temp_4_2 = (*(s32 *)((u8 *)(arg0) + 0x10));
    if (temp_4_2 != 0) {
        StateBlockReset_3cd670(temp_4_2, 0, 0, 0);
    }
    temp_2 = (void *)((*(s32 *)((u8 *)(arg0) + 0x14)));
    if (temp_2 != NULL) {
        PoolClear_36ade0((*(s32 *)((u8 *)(temp_2) + 0x8)));
    }
    temp_4_3 = (void **)((*(s32 *)((u8 *)(arg0) + 0x18)));
    if (temp_4_3 != NULL) {
        ((VC_0 *)(temp_4_3))->f();
    }
    temp_2_2 = (void *)((*(s32 *)((u8 *)(arg0) + 0x1C)));
    if (temp_2_2 != NULL) {
        temp_4_4 = (*(s32 *)((u8 *)(temp_2_2) + 0x10));
        if (temp_4_4 != 0) {
            PoolClear_36ade0(temp_4_4);
        }
    }
    temp_4_5 = (*(s32 *)((u8 *)(arg0) + 0x20));
    if (temp_4_5 != 0) {
        CharaSysResetAll_3a5ca0(temp_4_5);
    }
    temp_4_6 = (*(s32 *)((u8 *)(arg0) + 0x24));
    if (temp_4_6 != 0) {
        InsectTeamTableReset_431d10(temp_4_6);
    }
    temp_4_7 = (*(s32 *)((u8 *)(arg0) + 0x28));
    if (temp_4_7 != 0) {
        DataTableOwnerClearTable_3b8c10(temp_4_7, 0, 0, 0);
    }
    (*(s16 *)((u8 *)(arg0) + 0x32)) = 0;
    temp_5 = (*(u8 *)((u8 *)(arg0) + 0x2C));
    ((BF2C *)((u8 *)(arg0) + 0x2C))->b0 = 0;
    InteractRecResetMaybe_3ee600((u8 *)arg0 + 0x34);
    (*(s16 *)((u8 *)(arg0) + 0x58)) = -1;
    (*(s32 *)((u8 *)(arg0) + 0x5C)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x60)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x64)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x68)) = 0;
}

}
