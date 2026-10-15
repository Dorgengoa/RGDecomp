#include "types.h"

extern void MenuHelpResRelease_203230(void);
extern void MenuTransdataRelease_206260(void);
extern void MenuTranstempRelease_206230(void);

void HelpMenuClose_203200(void)
{
    MenuHelpResRelease_203230();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
