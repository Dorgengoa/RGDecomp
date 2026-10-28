/* rgp:protos */
#define RGP_SELF_TextLayoutPushStr_313090 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct E313090 { u8 pad000[8]; s32 m08; };
struct S313090 { struct E313090 arr[0x80]; s32 m600; };

void TextLayoutPushStr_313090(struct S313090 *p, s32 v)
{
    s32 n;

    n = p->m600;
    if (n < 0x80) {
        p->arr[n].m08 = v;
        p->m600 = p->m600 + 1;
    }
}
