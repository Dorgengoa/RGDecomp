/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltReset_504dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504DC0 -- clear the handle, then reset the list.
 *
 * 3 instructions:
 *      sw $0,0x0($4)                -> buf = NULL
 *      j  factory_FactoryBeltClear_504db0      -> TAIL CALL, last statement of a void fn
 *      sh $0,0x4($4)  (delay slot)  -> cap = 0
 *
 * Struct is the seed's (src/wf/factory/factory_FactoryBeltStart_504cc0.c) verbatim.
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

/*rgp*/

void factory_FactoryBeltReset_504dc0(FacVertList *l)
{
    l->buf = NULL;
    l->cap = 0;
    factory_FactoryBeltClear_504db0(l);
}
