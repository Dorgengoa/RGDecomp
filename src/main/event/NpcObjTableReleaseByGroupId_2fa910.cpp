#include "types.h"
extern "C" {
#define M2C_FIELD(expr,type,off) (*(type)((u8 *)(expr)+(off)))
extern u8 *GetGameData_1fede0(void);
extern u8 *GetTargetMng_313dd0(void);
extern s32 IsInBattle_288420(void);
extern void TargetMngClearRef_320810(s8 *);
extern void NpcObjReleaseRes_2fba00(s8 *,s32);
extern s8 *GroupGetRecordById_41c2a0(s32,s32,s32,s32);
typedef struct {s32 a;s8 *array;s16 n;u8 pad[0x20E];s16 flag;u8 pad2[2];s8 *active;} Obj;
void NpcObjTableReleaseByGroupId_2fa910(Obj *arg0, s32 arg1) {
    s16 **temp_3;
    s16 *temp_3_2;
    s8 *var_18;
    s32 var_17;
    bool var_4;
    s8 *temp_2;
    s8 *temp_2_2;
    s8 *temp_2_3;

    temp_2 = (s8 *)(GetGameData_1fede0());
    if (temp_2 != NULL) {
        temp_2_2 = (s8 *)(GetTargetMng_313dd0());
        if (temp_2_2 != NULL) {
            if (IsInBattle_288420() == 0) {
                TargetMngClearRef_320810(temp_2_2);
            }
            var_18 = (s8 *)(arg0->array);
            var_17 = 0;
            while (var_17 < arg0->n) {
                temp_2_3 = (s8 *)(GroupGetRecordById_41c2a0(M2C_FIELD(M2C_FIELD(temp_2, s8 **, 8), s32 *, 0x6C), M2C_FIELD(var_18, s16 *, 0xC6), -1, 1));
                var_4 = true;
                if (temp_2_3 != NULL) {
                    temp_3 = (s16 **)(M2C_FIELD(temp_2_3, s16 ***, 0x28));
                    if (temp_3 != NULL) {
                        temp_3_2 = (s16 *)(*temp_3);
                        if ((temp_3_2 != NULL) && (arg1 >= 0) && (arg1 != *temp_3_2)) {
                            var_4 = false;
                        }
                    }
                }
                if (var_4) {
                    NpcObjReleaseRes_2fba00(var_18, 1);
                    if ( (s32)(var_18) == (s32)(arg0->active)) {
                        arg0->flag = 0;
                        arg0->active = 0;
                    }
                }
                var_17 += 1;
                var_18 += 0xE0;

            }
        }
    }
}

}
