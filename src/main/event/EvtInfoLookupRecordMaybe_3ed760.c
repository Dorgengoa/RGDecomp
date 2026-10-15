#include "types.h"

typedef struct R_003ed760 {
    u8 pad0[0x2C];
    s16 f2C;
    u8 pad2E[2];
    s32 f30;
} R_003ed760;

typedef struct Q_003ed760 {
    u8 pad0[4];
    s16 f4;
    u8 pad6[0x12];
    R_003ed760 *f18;
} Q_003ed760;

typedef struct T_003ed760 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[4];
    s32 fC;
} T_003ed760;

typedef struct S_003ed760 {
    u8 pad0[0x18];
    Q_003ed760 *f18;
} S_003ed760;

extern T_003ed760 *PlanetAreaMatrixLookupByProgress_3ed840(S_003ed760 *, s32);

s32 EvtInfoLookupRecordMaybe_3ed760(S_003ed760 *self)
{
    Q_003ed760 *q;
    R_003ed760 *r;
    s32 v;
    T_003ed760 *t;
    T_003ed760 *u;
    q = self->f18;
    r = q->f18;
    if (r == 0) goto cont;
    v = r->f2C;
    if (v < 0) goto zero;
    if (r->f30 == 0) goto zero;
    if (v != 1) goto cont;
zero:
    return 0;
cont:
    t = PlanetAreaMatrixLookupByProgress_3ed840(self, q->f4);
    if (t == 0) return 0;
    if (t->fC == 0) return 0;
    u = PlanetAreaMatrixLookupByProgress_3ed840(self, 1);
    if (u != 0) {
        return u->f4;
    }
    return 0;
}
