/* rgp:protos */
#define RGP_SELF_TextReaderOpen_15f1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Point the reader at a blob and check its three-byte magic. A match sets the
   flag at +0x24 and steps the cursor past the header; anything else goes to
   the error path with the reader as its argument.

   D_00458CE0 is declared as an incomplete array so it is reached with
   `lui %hi` / `addiu %lo` -- a sized object small enough for $gp would be one
   instruction and the function would come out a word short. */

typedef struct Reader0015f1b0 {
    u8 *blob;          /* +0x00 */
    s32 size;          /* +0x04 */
    s32 cursor;        /* +0x08 */
    s32 unkC;          /* +0x0C */
    u8 pad10[0x24 - 0x10];
    s32 magicOk;       /* +0x24 */
} Reader0015f1b0;

extern char D_00458CE0[];

extern s32 strncmp(const char *a, const char *b, s32 n);
/*rgp*/

void TextReaderOpen_15f1b0(Reader0015f1b0 *r, u8 *blob, s32 size)
{
    r->blob = blob;
    r->size = size;
    r->cursor = 0;
    r->unkC = 0;
    r->magicOk = 0;
    if (strncmp((const char *)blob, D_00458CE0, 3) == 0) {
        r->magicOk = 1;
        r->cursor = r->cursor + 4;
    } else {
        TextReaderStripComments_15e7f0(r);
    }
}
