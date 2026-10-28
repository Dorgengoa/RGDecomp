/* rgp:protos */
#define RGP_SELF_CageRecGetYaw_3d0b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct I3D0B30 { u8 pad000[0x1C]; f32 m1C; } I3D0B30;
typedef struct O3D0B30 { u8 pad000[0x18]; I3D0B30 *m18; } O3D0B30;
f32 CageRecGetYaw_3d0b30(O3D0B30 *p) { return p->m18->m1C; }
