#include "types.h"

/* title.bin overlay, 0x004EF390 -- lui/addiu %hi/%lo: the ADDRESS of an
 * overlay object, materialised absolutely rather than gp-relative.
 *
 *     lui    $2, %hi(D_004F1980)
 *     jr     $31
 *      addiu $2, $2, %lo(D_004F1980)
 *
 * ★ `const` is the %gp_rel -> %hi/%lo switch (measured recipe, not a size
 * threshold): a plain `extern u8` compiles this to two words, addiu off $28.
 * The cast is a relocation lever, not a claim about the original type.
 */

extern const u8 D_004F1980;

void *title_TitleGetLoadSysMsgBuf_4ef390(void)
{
    return (void *)&D_004F1980;
}
