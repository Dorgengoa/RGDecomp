#include "types.h"

/* title.bin overlay, 0x004EC7C0 -- a tail call and nothing else:
 *
 *     j     title_TitleGetLoadSysMsgBuf_4ef390
 *      nop
 *
 * Two words; the other two inside the recorded size are padding.
 */

extern void title_TitleGetLoadSysMsgBuf_4ef390(void);

void title_TitleGetLoadSysMsg_4ec7c0(void)
{
    title_TitleGetLoadSysMsgBuf_4ef390();
}
