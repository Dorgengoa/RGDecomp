/* rgp:protos */
#define RGP_SELF_CharaTableEntryCopy_226250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* CharaTableDataAssign_2262f0 takes NO arguments - nothing is written into $4..$7 between
   entry and the jal (the incoming $4 merely happens to still be live). */

typedef struct { f32 a, b; } F2;

/*rgp*/
/*rgp*/

s32 CharaTableEntryCopy_226250(void *a, void *b, s32 c, s32 d)
{
    if (b == 0) {
        return 0;
    }
    CharaTableDataAssign_2262f0((void *)a, (void *)b);
    *(s32 *)((u8 *)a + 0x34) = *(s32 *)((u8 *)b + 0x34);
    *(s16 *)((u8 *)a + 0x38) = *(s16 *)((u8 *)b + 0x38);
    *(s16 *)((u8 *)a + 0x3A) = *(s16 *)((u8 *)b + 0x3A);
    /* batched lwc1/lwc1/swc1/swc1 = ONE two-float sub-struct assignment */
    *(F2 *)((u8 *)a + 0x3C) = *(F2 *)((u8 *)b + 0x3C);
    return CharaTableDataCopy_2269f0(a, b, c, d);
}
