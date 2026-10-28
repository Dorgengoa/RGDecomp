/* rgp:protos */
#define RGP_SELF_InsectCagePreviewModelDraw_389340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004832F8;
extern f32 D_004832F0;
extern f32 D_004832F4;
/*rgp*/

void InsectCagePreviewModelDraw_389340(void)
{
    void *p;

    p = D_004832F8;
    if (p != 0) {
        DrawModelPreview_28be80(p, D_004832F0, D_004832F4);
    }
}
