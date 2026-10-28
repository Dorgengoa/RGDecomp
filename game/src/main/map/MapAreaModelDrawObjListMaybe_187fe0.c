/* rgp:protos */
#define RGP_SELF_MapAreaModelDrawObjListMaybe_187fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x32];
    s16 unk32;
} Elem00187FE0;

/*rgp*/
/*rgp*/

void MapAreaModelDrawObjListMaybe_187fe0(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    Elem00187FE0 *p;

    for (i = 0; i < arg2; i++) {
        p = *(Elem00187FE0 **)(arg1 + i * 4);
        if (p != NULL && p->unk32 != 0) {
            NodeObjIsInView_194200(p);
            NodeObjDrawChildren_194700(p);
        }
    }
}
