#include "types.h"
#pragma opt_common_subs off
extern "C" {

extern void RevelationBoardCellLinkNeighbors_4096c0(s16 *arg0, s32 arg1, s32 arg2);

typedef struct Cell {
    __extension__ unsigned short a : 6;
    unsigned short b : 3;
    unsigned short c : 4;
    unsigned short d : 3;
    u16 pad;
} __attribute__((aligned(2))) Cell;

typedef struct Ent {
    u8 pad0[0xC];
    s16 unkC;
    u8 padE[0x1C - 0xE];
} Ent;

typedef struct Tbl {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[2];
    Ent *unk8;
} Tbl;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Tbl * f(s16 x0) { return VCM(Tbl *, (void *, s16), 0x70, x0); }
};

s32 RevelationBoardsLinkAllCells_408510(void *arg0, void *arg1)
{
    s16 *var_20;
    s32 var_19;
    s32 temp_4_2;
    Cell *var_18;
    s32 var_17;
    s32 temp_3;
    Tbl *temp_2;
    s32 var_16;
    Ent *e;
    u16 tb;

    if (arg1 == NULL) {
        return 0;
    }
    var_20 = *(s16 **)((u8 *)arg0 + 0x8C);
    if (var_20 == NULL) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0x7C) <= 0) {
        return 0;
    }
    for (var_19 = 0; var_19 < *(s16 *)((u8 *)arg0 + 0x7C); var_19++, var_20 += 0x3aa) {
        temp_2 = (*(VC_0 **)((u8 *)(*(void **)((u8 *)arg1 + 0x8C)) + 0xC))->f(*var_20);
        if (temp_2 != NULL) {
            var_18 = (Cell *)(var_20 + 2);
            for (var_17 = 0; var_17 < 0x12; var_17++) {
                for (var_16 = 0; var_16 < 0x1A; var_16++, var_18++) {
                    if (var_18->c == 0xA) {
                        temp_4_2 = var_18->a;
                        if ((temp_4_2 >= 0) && (temp_4_2 < temp_2->unk4)) {
                            e = &temp_2->unk8[temp_4_2];
                            temp_3 = (u16)(((u64)*(u16 *)var_18 << 55) >> 61);
                            if ((temp_3 >= 0) && (temp_3 < e->unkC)) {
                                RevelationBoardCellLinkNeighbors_4096c0(var_20, var_17, var_16);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

}
