#include "types.h"
/* insmenu 0x004F2E50 -- two calls in sequence. */
extern void insmenu_InsectVsTitleBannerReset_4f2f30(void);
extern void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void);
void insmenu_InsectVsTitleBannerOpen_4f2e50(void)
{
    insmenu_InsectVsTitleBannerReset_4f2f30();
    insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
}
