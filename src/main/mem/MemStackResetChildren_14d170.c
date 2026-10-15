#pragma opt_propagation off
#include "types.h"

typedef struct Node0014d170 {
    u8 pad0[0x20];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u8 pad38[4];
    s32 unk3C;
    u8 pad40[8];
    struct Node0014d170 *unk48;
    struct Node0014d170 *unk4C;
    u8 pad50[4];
    s32 unk54;
} Node0014d170;

extern s32 MemStackRefCountGet_14d350(Node0014d170 *arg0);
extern void MemStackClearCursor_14d360(Node0014d170 *arg0);
extern s32 MemStackHasBase_14d380(Node0014d170 *arg0);
extern void MemStackClearFrozen_14d390(Node0014d170 *arg0);
extern void MemStackResetMark_14d3a0(Node0014d170 *arg0);
extern void MemStackResetCursor_14d7f0(Node0014d170 *arg0);
extern void MemStackReset_14d830(Node0014d170 *arg0);
extern void MemStackWaitUnlocked_14d8b0(Node0014d170 *arg0);

void MemStackResetChildren_14d170(Node0014d170 *arg0)
{
    Node0014d170 *var_19;
    Node0014d170 *var_18;
    Node0014d170 *var_18_2;
    Node0014d170 *var_16;
    s32 on;

    var_16 = arg0->unk4C;
    while (var_16 != NULL) {
        var_19 = var_16->unk4C;
        while (var_19 != NULL) {
            var_18 = var_19->unk4C;
            while (var_18 != NULL) {
                MemStackResetChildren_14d170(var_18);
                MemStackReset_14d830(var_18);
                MemStackResetCursor_14d7f0(var_18);
                var_18 = var_18->unk48;
            }
            MemStackResetMark_14d3a0(var_19);
            MemStackClearFrozen_14d390(var_19);
            if (!(MemStackHasBase_14d380(var_19) != 0)) {
                MemStackClearCursor_14d360(var_19);
            } else {
                if (MemStackRefCountGet_14d350(var_19) > 0) {
                    MemStackWaitUnlocked_14d8b0(var_19);
                }
                MemStackClearCursor_14d360(var_19);
                MemStackResetChildren_14d170(var_19);
            }
            var_19->unk28 = 0;
            var_19->unk2C = 0;
            var_19->unk34 = 0;
            MemStackResetMark_14d3a0(var_19);
            var_19 = var_19->unk48;
        }
        var_16->unk30 = -1;
        var_16->unk3C = 0;
        var_16->unk20 = 0;
        on = var_16->unk28 != 0;
        if (on == 0) {
            var_16->unk2C = 0;
            MemStackResetMark_14d3a0(var_16);
            MemStackClearFrozen_14d390(var_16);
        } else {
            if (var_16->unk24 > 0) {
                while (var_16->unk54 != 0) {
                    /* spin */
                }
            }
            var_16->unk2C = 0;
            MemStackResetMark_14d3a0(var_16);
            MemStackClearFrozen_14d390(var_16);
            var_18_2 = var_16->unk4C;
            while (var_18_2 != NULL) {
                MemStackResetChildren_14d170(var_18_2);
                MemStackReset_14d830(var_18_2);
                MemStackResetCursor_14d7f0(var_18_2);
                var_18_2 = var_18_2->unk48;
            }
            MemStackResetMark_14d3a0(var_16);
            MemStackClearFrozen_14d390(var_16);
        }
        var_16->unk28 = 0;
        var_16->unk2C = 0;
        var_16->unk34 = 0;
        var_16->unk30 = -1;
        var_16->unk3C = 0;
        var_16 = var_16->unk48;
    }
    arg0->unk30 = -1;
    arg0->unk3C = 0;
    arg0->unk20 = 0;
}
