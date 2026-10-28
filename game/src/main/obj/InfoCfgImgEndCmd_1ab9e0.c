/* rgp:protos */
#define RGP_SELF_InfoCfgImgEndCmd_1ab9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* BOTH globals are `lui %hi` / `lw %lo`, so both sit outside small data. */
typedef struct D1AB9E0 { s32 m00; s32 pad[3]; } D1AB9E0;
typedef struct T1AB9E0 { u8 pad000[0x4DC]; s32 m4DC; } T1AB9E0;
typedef struct H1AB9E0 { T1AB9E0 *p; s32 pad[3]; } H1AB9E0;
extern D1AB9E0 D_0049D3A4;
extern H1AB9E0 D_0049D418;
s32 InfoCfgImgEndCmd_1ab9e0(void)
{
    D_0049D418.p->m4DC = D_0049D3A4.m00;
    return 1;
}
