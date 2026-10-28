/* rgp:protos */
#define RGP_SELF_CdDirTablesDtor_183700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern u8 D_00495FB0[];
/*rgp*/

void CdDirTablesDtor_183700(void)
{
    DestroyArray_1005b0(D_00495FB0, CdDirTableDtor_183720, 0xC, 2);
}
