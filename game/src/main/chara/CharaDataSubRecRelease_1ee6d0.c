/* rgp:protos */
#define RGP_SELF_CharaDataSubRecRelease_1ee6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node_FUN_001ee6d0 {
    u8 pad000[0x4];
    struct Node_FUN_001ee6d0 *f04;
} Node_FUN_001ee6d0;

typedef struct Obj_FUN_001ee6d0 {
    u8 pad000[0xA];
    u8 f0A;
    u8 pad00B[0x1];
    u8 f0C;
    u8 pad00D[0x57];
    Node_FUN_001ee6d0 *f64;
} Obj_FUN_001ee6d0;

/*rgp*/
/*rgp*/

void CharaDataSubRecRelease_1ee6d0(Obj_FUN_001ee6d0 *o)
{
    Node_FUN_001ee6d0 *n;

    n = o->f64;
    while (n != 0) {
        CharaDataNodeFree_1eeba0(n);
        n = n->f04;
    }
    o->f0A = 1;
    o->f64 = 0;
    MemStackReset_14d830(&o->f0C);
}
