#include "types.h"
/* insect 0x00512AB0 -- 92 bytes.  $4 is overwritten with the frame buffer
 * before it is ever read, so the first parameter is unused. */

typedef struct Buf {
    u8 b[0x48];
} Buf;

extern void func_26C610(Buf *b);
extern void func_2931C0(Buf *b, s8 v);
extern void func_26DAF0(Buf *b, s32 n, s32 *x, s32 *y);

s32 insect_InsectMsgTextWidth_512ab0(s32 unused, s32 n, s32 v)
{
    s32 x;
    s32 y;
    Buf t;

    func_26C610(&t);
    func_2931C0(&t, (s8)v);
    func_26DAF0(&t, n, &x, &y);
    return x;
}
