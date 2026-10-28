/* rgp:protos */
#define RGP_SELF_UskMemoryInit_42e070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* %hi/%lo on D_00468D48 => incomplete array. */

extern s32 D_00468D48[];

struct Obj;

struct Obj {
    u8 pad000[0x10];
    s32 m10;
    u8 m14[0x2C];
    s32 m40;
};

void UskMemoryInit_42e070(struct Obj *p)
{
    DListInit_42eae0(p);
    UskStackInit_42e470(p->m14);
    p->m10 = 0;
    p->m40 = 0;
    UskStackSetName_42e3b0(p->m14, D_00468D48);
}
