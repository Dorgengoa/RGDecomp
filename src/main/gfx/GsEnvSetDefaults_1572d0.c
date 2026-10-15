#include "types.h"

typedef struct S001572d0 {
    u8 pad0[0x10];
    u64 unk10;
    u8 pad18[8];
    u32 a : 1;
    u32 b : 3;
    u32 c : 8;
    u32 d : 2;
    u32 e : 1;
    u32 f : 1;
    u32 g : 1;
    u32 h : 2;
    u32 rest : 13;
    u8 pad24[0x34 - 0x24];
    u32 i : 1;
    u32 r34 : 31;
    u8 pad38[0x40 - 0x38];
    u32 j : 1;
    u32 r40 : 31;
    u8 pad44[0x5C - 0x44];
    s32 unk5C;
} S001572d0;

extern u64 D_00449EF8[];

void GsEnvSetDefaults_1572d0(S001572d0 *p) {
    p->unk10 = D_00449EF8[0];
    p->a = 0;
    p->b = 1;
    p->c = 0;
    p->e = 0;
    p->f = 0;
    p->g = 1;
    p->h = 1;
    p->i = 0;
    p->j = 0;
    p->unk5C = -1;
    p->unk5C = -1;
}
