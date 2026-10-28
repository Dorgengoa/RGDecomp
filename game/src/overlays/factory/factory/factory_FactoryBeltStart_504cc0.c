/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltStart_504cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504CC0 -- reset a 6-byte-element vertex list and
 * push its first element.
 *
 * 27 instructions, ZERO branches, ZERO calls, a leaf with no stack frame.
 *
 * The handle is the same one 0x00504D30 allocates:
 *      sw $2, 0x0($18)   -> the buffer pointer at 0x0
 *      sh $17, 0x4($18)  -> the capacity at 0x4
 *      sll/addu/sll n    -> n * 6, so the element is SIX bytes
 * and this function reads the count at 0x6 and clears a second short at 0x8.
 *
 * The four `lh 0x6($4)` / `lw 0x0($4)` reloads are NOT a loop and NOT a helper:
 * each of the three element stores re-reads both the count and the buffer
 * pointer because the preceding `sh` through that same buffer may alias them.
 * So they are three explicit source statements, and the tail is a fourth.
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

void factory_FactoryBeltStart_504cc0(FacVertList *l, s16 x, s16 y, s16 z)
{
    l->count = 0;
    l->f8 = 0;

    l->buf[l->count].x = x;
    l->buf[l->count].y = y;
    l->buf[l->count].z = z;

    l->count = l->count + 1;
}
