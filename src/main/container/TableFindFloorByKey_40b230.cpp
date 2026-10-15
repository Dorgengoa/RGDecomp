#include "types.h"

typedef struct Candidate {
    s16 unk0;
    s16 unk2;
} Candidate;

typedef struct Result {
    u8 pad0[0xE];
    s16 unkE;
    Candidate *unk10;
} Result;

class VE {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25();
    virtual Result *method26();   /* slot 8 + 4*26 = 0x70 */
};

typedef struct T0040b230 {
    u8 pad0[0xC];
    VE *unkC;
} T0040b230;

extern "C" void *TableFindFloorByKey_40b230(T0040b230 *arg0, s32 unused1, s32 arg2, s32 arg3)
{
    Candidate *var_7;
    Candidate *var_6;
    Result *temp_2;
    VE *temp_4;
    s32 i;
    s16 temp_3;

    temp_4 = arg0->unkC;
    temp_2 = temp_4->method26();
    if (temp_2 == 0) {
        return 0;
    }
    var_6 = temp_2->unk10;
    var_7 = 0;
    if (var_6 == 0) {
        return 0;
    }
    for (i = 0; i < temp_2->unkE; i += 1, var_6 = (Candidate *)((u8 *)var_6 + 0x18)) {
        if (var_6->unk0 == arg3) {
            temp_3 = var_6->unk2;
            if ((temp_3 <= arg2) && ((var_7 == 0) || (var_7->unk2 < temp_3))) {
                var_7 = var_6;
            }
        }
    }
    return var_7;
}
