/* rgp:protos */
#define RGP_SELF_RefracTexInit_140430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x3BD8];
    u8 sub[0x3C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} O140430;

/*rgp*/
/*rgp*/

extern u8 D_00458A50[0x400];

int RefracTexInit_140430(O140430 *arg0) { int rgp_v0 = 0;
    s32 flag;

    flag = 0;
    NameTableNodeReset_15ada0(&arg0->sub);
    (rgp_v0 = NameTableNodeSetImage_15a640(arg0->sub, -0xA, D_00458A50, 0, 0x100, 0x100, 0x20, 0, flag, (int)(flag)));
    arg0->b2 = flag;
return rgp_v0; }
