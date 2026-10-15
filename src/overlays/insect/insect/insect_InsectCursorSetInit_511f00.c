#include "types.h"
/* insect 0x00511F00 -- 152 B / 38 words.
 * Two no-arg factory calls whose results land in +0x00 and +0x04 (the first
 * store rides the second jal's delay slot), then a clear of +0x08, an
 * i = 0..7 clear of the 0xC array, and a byte clear at 0x2C (0xC + 8*4), so
 * 0x2C is the member AFTER the array, not its ninth element -- it is a `sb`.
 * `ori $5, $0, 0xF00F` is mwcc's logical form for a constant too wide for a
 * signed 16-bit immediate; nothing about signedness is inferable from it.
 * `daddu $3, $0, $0` (i = 0) between the 0x4 and 0x8 stores is loop-preheader
 * scheduling.  The two handles are RE-LOADED before each call -- pointer
 * derefs across a call, not CSE'd locals. */

typedef struct Obj {
    void *m00;                  /* +0x00 */
    void *m04;                  /* +0x04 */
    s32   m08;                  /* +0x08 */
    s32   m0C[8];               /* +0x0C */
    u8    m2C;                  /* +0x2C */
} Obj;

extern void *func_1C6C60(void);
extern void *func_1C6C50(void);
extern void  func_183D50(void *h, u32 a, s32 b, s32 c);
extern void  func_183950(void *h, s32 a);

void insect_InsectCursorSetInit_511f00(Obj *o)
{
    s32 i;

    o->m00 = func_1C6C60();
    o->m04 = func_1C6C50();
    o->m08 = 0;
    for (i = 0; i < 8; i++) {
        o->m0C[i] = 0;
    }
    o->m2C = 0;
    func_183D50(o->m00, 0xF00F, 0xF, 4);
    func_183950(o->m00, 0x78);
    func_183D50(o->m04, 0xF00F, 0xF, 4);
    func_183950(o->m04, 0x78);
}
