/* rgp:protos */
#define RGP_SELF_ScreenMarkerMgrDtor_31bd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MW C++ destructor with the delete flag:
       if (this) { <body>; if (flag > 0) operator delete(this); }
       return this;
   The (s16) narrowing of the flag is retail's dsll32/dsra32 pair. */

/*rgp*/
/*rgp*/

void *ScreenMarkerMgrDtor_31bd70(void *o, s16 flag)
{
    if (o != 0) {
        ScreenMarkerMgrBaseDtor_31c0a0(o, -1);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
