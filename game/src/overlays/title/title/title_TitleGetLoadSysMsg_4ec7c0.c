/* rgp:protos */
#define RGP_SELF_title_TitleGetLoadSysMsg_4ec7c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC7C0 -- a tail call and nothing else:
 *
 *     j     title_TitleGetLoadSysMsgBuf_4ef390
 *      nop
 *
 * Two words; the other two inside the recorded size are padding.
 */

/*rgp*/

void * title_TitleGetLoadSysMsg_4ec7c0(void)
{
    return title_TitleGetLoadSysMsgBuf_4ef390();
}
