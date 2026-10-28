/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuIsActive_4ec3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EC3E0 -- read a byte flag out of main's small data.
 *
 * One of the 27 spimdisasm auto-named functions config/factory.symbols.txt
 * never carried (pass-27 conversion, session 7).  `lbu $2, -0x704($28)` is
 * `_gp - 0x704` = 0x00484A6C; the overlay reaches MAIN's small data through
 * main's $28, which is why the link assigns _gp = 0x00485170.
 */

extern u8 D_00484A6C;                           /* _gp - 0x704 */

u8 factory_FactoryMenuIsActive_4ec3e0(void)
{
    return D_00484A6C;
}
