#include "types.h"

/* lane N4 family: NpcCfgCmdRouteAddRunPoint_2fd2d0 / NpcCfgCmdRouteAddWalkPoint_2fd3d0 (248 B each); the only
   substitution is the 0x26 halfword constant (3 vs 2).
   All the globals here are reached with %hi/%lo, so they are declared as
   incomplete arrays (the brief's relocation rule). */

extern void *D_004E6628[];
extern s16 D_004E6634[];
extern u8 *volatile D_004E662C[];
extern u8 D_004E6620[];
extern s16 D_004E6632[];

extern void VariantReadVec3_2fd830(f32 *, void *);
extern f32 VariantGetFloat_15f740(void *);
extern void NpcCfgLocalToWorldPos_2fd8d0(void *, void *, f32 *);

s32 NpcCfgCmdRouteAddRunPoint_2fd2d0(u8 *obj, s32 kind)
{
    f32 v[4];
    u8 *e0;
    u8 *e;

    if (kind != 4) {
        return 0;
    }
    if (D_004E6628[0] == 0) {
        return 0;
    }
    if (D_004E6634[0] != 0) {
        return 0;
    }
    VariantReadVec3_2fd830(v, obj);
    v[3] = 1.0f;
    *(f32 *)(D_004E662C[0] + 0x10) = VariantGetFloat_15f740(obj + 0x18);
    *(s16 *)(D_004E662C[0] + 0x26) = 3;
    NpcCfgLocalToWorldPos_2fd8d0(D_004E6620, D_004E662C[0], v);
    e0 = D_004E662C[0];
    *(u8 **)(e0 + 0x20) = e0 + 0x30;
    e = D_004E662C[0];
    D_004E662C[0] = e + 0x30;
    D_004E6632[0] = D_004E6632[0] + 1;
    *(s16 *)(e + 0x56) = 5;
    *(s32 *)(D_004E662C[0] + 0x20) = 0;
    return 1;
}
