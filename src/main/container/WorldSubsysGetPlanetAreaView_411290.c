#include "types.h"

typedef struct Obj00411290 {
    u8 pad0[0x1C];
    s32 unk1C;
    s32 unk20;
} Obj00411290;

extern s32 PlanetAreaQuerySetSource_415430(s32, s32, s64);

s32 WorldSubsysGetPlanetAreaView_411290(Obj00411290 *self, s16 idx)
{
    s32 v;
    s32 temp;

    if (idx < 0) {
        v = self->unk1C;
        if (v != 0) {
            v += 0x88;
        }
        return v;
    }
    temp = self->unk20;
    if (temp != 0) {
        PlanetAreaQuerySetSource_415430(temp, self->unk1C, idx);
    }
    return self->unk20;
}
