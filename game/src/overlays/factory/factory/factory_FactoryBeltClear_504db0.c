/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltClear_504db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504DB0 -- reset a 6-byte-element vertex list.
 *
 * 3 instructions, no frame, no branches.  This is VERBATIM the opening of
 * 0x00504CC0 (the seed, src/wf/factory/factory_FactoryBeltStart_504cc0.c) which settled
 * the list struct:
 *      sh $0,0x6($4)   -> count = 0
 *      sh $0,0x8($4)   -> f8    = 0   (in the jr delay slot)
 */

typedef struct FacVert {
    s16 x;      /* 0x0 */
    s16 y;      /* 0x2 */
    s16 z;      /* 0x4 */
} FacVert;

typedef struct FacVertList {
    FacVert *buf;   /* 0x0 */
    s16      cap;   /* 0x4 */
    s16      count; /* 0x6 */
    s16      f8;    /* 0x8 */
} FacVertList;

void factory_FactoryBeltClear_504db0(FacVertList *l)
{
    l->count = 0;
    l->f8 = 0;
}
