/* rgp:protos */
#define RGP_SELF_title_TitleGetLoadSysMsgBuf_4ef390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF390 -- lui/addiu %hi/%lo: the ADDRESS of an
 * overlay object, materialised absolutely rather than gp-relative.
 *
 *     lui    $2, %hi(title_D_004F1980)
 *     jr     $31
 *      addiu $2, $2, %lo(title_D_004F1980)
 *
 * ★ `const` is the %gp_rel -> %hi/%lo switch (measured recipe, not a size
 * threshold): a plain `extern u8` compiles this to two words, addiu off $28.
 * The cast is a relocation lever, not a claim about the original type.
 */

extern u8 title_D_004F1980;

void *title_TitleGetLoadSysMsgBuf_4ef390(void)
{
    return (void *)&title_D_004F1980;
}
