#include "types.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
    u8 padA[0x68 - 0xA];
} Ent1ee3c0;

typedef struct {
    u8 pad0[8];
    u8 sub8[0x2C];
    s32 unk34;
    u8 pad38[0x4];
    s32 unk3C;
    u8 pad40[0x20];
    s16 unk60;
    s16 unk62;
    s16 unk64;
    s16 unk66;
    Ent1ee3c0 *unk68;
} T1ee3c0;

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern void MemStackReset_14d830(void *);
extern s32 MemStackNew_14e1b0(s32, void *);
extern void EPartsStackInit_1ee8f0(Ent1ee3c0 *, void *, s32);
extern void ListNodeInit_1ef9d0(Ent1ee3c0 *);
extern void ListAppendTail_1ef9e0(Ent1ee3c0 *, Ent1ee3c0 *);
extern u8 CharaPartRecCtor_1ee570[];

s32 CharaDataRecAllocSubRecs_1ee3c0(T1ee3c0 *arg0, s32 *arg1)
{
    s32 arr50[8];
    s32 arr30[8];
    s32 i;
    s32 n;
    s32 k;
    s32 *pk;

    if (arg1 == NULL) {
        return 0;
    }
    arg0->unk62 = arg1[0];
    arg0->unk64 = arg1[1];
    MemStackReset_14d830(arg0->sub8);
    arg0->unk66 = 0;
    for (i = 0; i < 7; i++) {
        k = arg1[i + 2];
        if (k >= 0) {
            arr50[arg0->unk66] = k;
            arr30[arg0->unk66] = i;
            arg0->unk66++;
        }
    }
    n = arg0->unk66;
    arg0->unk68 = (Ent1ee3c0 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x68 + 0x10, arg0->sub8), CharaPartRecCtor_1ee570, 0, 0x68, n);
    for (i = 0; i < arg0->unk66; i++) {
        pk = &arr30[i];
        arg0->unk68[i].unk8 = *pk;
        switch (*pk) {
        case 6:
            EPartsStackInit_1ee8f0(&arg0->unk68[i], arg0->sub8, arg0->unk3C - arg0->unk34);
            break;
        default:
            EPartsStackInit_1ee8f0(&arg0->unk68[i], arg0->sub8, arr50[i]);
            break;
        }
    }
    ListNodeInit_1ef9d0(arg0->unk68);
    for (i = 1; i < arg0->unk66; i++) {
        ListAppendTail_1ef9e0(arg0->unk68, &arg0->unk68[i]);
    }
    arg0->unk60 = 1;
    return 1;
}
