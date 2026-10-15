#include "types.h"
#pragma opt_propagation off

typedef struct {
    s16 unk0;
    u8 pad2[6];
    s8 *unk8;
} Ent;

typedef struct {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    s16 unk6;
    s8 *unk8[16];
    s8 *unk48[16];
} Obj0Arg0;

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} Obj001fede0;

extern Obj001fede0 *GetGameData_1fede0(void);
extern s32 PartyLoadSlotGetId_2f5550(Obj0Arg0 *);
extern s32 CharaCollectEquipEffectRefsMaybe_2f5850(s32, Ent **, s32);
extern s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 StrNotEqual_1f5300(s8 *, s8 *);

void PartyLoadSlotQueueEquipEffectsMaybe_2f5640(Obj0Arg0 *arg0)
{
    Ent *buf[64];
    Obj001fede0 *o;
    s32 n;
    s32 i;
    s32 j;
    s32 k;

    o = GetGameData_1fede0();
    if (CharaMgrPoolFindById_3a8c60(o->unk14, PartyLoadSlotGetId_2f5550(arg0)) == 0) {
        return;
    }
    n = CharaCollectEquipEffectRefsMaybe_2f5850(arg0->unk0, buf, 0x40);
    for (i = 0; i < n; i++) {
        for (j = 0; j < arg0->unk4; j++) {
            s8 *b = buf[i]->unk8;
            s8 *a = arg0->unk8[j];
            if (*a == *b && StrNotEqual_1f5300(b + 1, a + 1) == 0) {
                break;
            }
        }
        if (j >= arg0->unk4) {
            break;
        }
    }
    if (i < n) {
        for (k = 0; k < n; k++) {
            if (buf[k]->unk0 != 0x64B) {
                arg0->unk48[arg0->unk6] = buf[k]->unk8;
                arg0->unk6++;
            }
        }
    } else {
        arg0->unk4 = 0;
        arg0->unk6 = 0;
    }
}
