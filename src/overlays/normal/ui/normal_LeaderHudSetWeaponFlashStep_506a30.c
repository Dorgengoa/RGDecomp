#include "types.h"
typedef struct Obj { u8 pad00[0x9C]; f32 f9C; } Obj;
extern s32 normal_LeaderHudSetWeaponFlashStep_506a30(Obj *p, f32 x);
s32 normal_LeaderHudSetWeaponFlashStep_506a30(Obj *p, f32 x) { p->f9C = x; return 0; }
