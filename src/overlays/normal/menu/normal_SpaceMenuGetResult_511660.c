#include "types.h"
/* normal 0x00511660 -- publishes the map-marker module's current cell into the
 * caller's 8-byte slot.  Pass-33 LIST rank: 44 bytes, 11 instructions, ZERO
 * branches, ZERO calls.
 *
 * The `lwc1`/`swc1` pair is NOT a float copy -- it is mwcc's 8-byte STRUCT
 * ASSIGNMENT, which it does through the FPU because that leaves the GPRs
 * alone.  The members are an `s16` and an `s32`, which is why the frame is
 * filled by `sh` and `sw` and read back by `lwc1`. */

typedef struct Cell { s16 a; u8 pad02[2]; s32 b; } Cell;

extern s16 D_004846A8;            /* gp - 0xAC8  */
extern s32 D_00480678;            /* gp - 0x4AF8 */

extern void normal_SpaceMenuGetResult_511660(Cell *p);

void normal_SpaceMenuGetResult_511660(Cell *p)
{
    Cell t;

    t.a = D_004846A8;
    t.b = D_00480678;
    *p = t;
}
