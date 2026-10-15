#pragma optimization_level 3
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} __attribute__((aligned(16))) V4_001C5CE0;

typedef struct {
    u8 pad0[0x180];
    V4_001C5CE0 pos;
} Tgt001C5CE0;

typedef struct {
    u8 pad0[0x3C];
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[8];
    V4_001C5CE0 unk50;
    s16 unk60;
    u8 pad62[2];
    f32 unk64;
    u8 pad68[8];
    V4_001C5CE0 *unk70;
} Obj001C5CE0;

Tgt001C5CE0 *ObjRecGetLiveObject_1c4a90(s32, s32);
f32 VecDistanceXZ_13d390(V4_001C5CE0 *, V4_001C5CE0 *);
void FrameGetWorldPos_148f30(V4_001C5CE0 *, V4_001C5CE0 *);
void sceVu0CopyVector(void *, void *);

void HeadLookProximityUpdate_1c5ce0(Obj001C5CE0 *self, s32 a1) {
    Tgt001C5CE0 *tgt;
    V4_001C5CE0 vec;

    tgt = ObjRecGetLiveObject_1c4a90(a1, self->unk46);
    if (tgt == NULL) {
        return;
    }
    vec = tgt->pos;
    switch (self->unk60) {
    case 0:
        sceVu0CopyVector(&self->unk50, &self->unk70);
        break;
    case 1:
        if (self->unk70 != NULL) {
            FrameGetWorldPos_148f30(self->unk70, &self->unk50);
        }
        break;
    }
    self->unk64 = VecDistanceXZ_13d390(&self->unk50, &vec);
    if (self->unk3C == 0 && self->unk44 != 0) {
        self->unk44 = 3;
    }
    if (self->unk3C == 1 && self->unk3E == 0) {
        self->unk44 = 1;
        self->unk3E = 1;
        self->unk40 = 0;
    }
    if (self->unk3C != 2) {
        return;
    }
    if (self->unk3E == 0) {
        if (self->unk64 < 100.0f) {
            self->unk42 = 0x78;
            self->unk44 = 1;
            self->unk3E = 1;
        } else if (self->unk44 == 2 || self->unk44 == 1) {
            self->unk44 = 3;
        }
    }
    if (self->unk3E == 1) {
        if (!(self->unk64 <= 160.0f)) {
            self->unk44 = 3;
            self->unk3E = 0;
        } else if (--self->unk42 <= 0) {
            self->unk40 = 0x96;
            self->unk44 = 3;
            self->unk3E = 2;
        }
    }
    if (self->unk3E == 2) {
        self->unk40--;
        if (!(self->unk64 <= 160.0f)) {
            self->unk40 = 0;
        }
        if (self->unk40 <= 0) {
            self->unk44 = 3;
            self->unk3E = 0;
        }
    }
}
