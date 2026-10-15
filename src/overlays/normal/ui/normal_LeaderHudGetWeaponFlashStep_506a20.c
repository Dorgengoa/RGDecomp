#include "types.h"
/* normal 0x00506A20 -- `jr $31 / lwc1 $f0, 0x9C($4)` */
typedef struct Obj { u8 pad00[0x9C]; f32 f9C; } Obj;
extern f32 normal_LeaderHudGetWeaponFlashStep_506a20(Obj *p);
f32 normal_LeaderHudGetWeaponFlashStep_506a20(Obj *p) { return p->f9C; }
