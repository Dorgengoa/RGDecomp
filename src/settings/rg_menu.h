/* SPDX-License-Identifier: CC0-1.0 */
/* The settings menu model (docs/SETTINGS.md "Menu API").  Pure: it walks the
 * registry, takes abstract commands (from keyboard OR gamepad through the
 * input layer's UI actions) and produces text lines; the host overlay draws
 * them.  Display changes are applied as a trial that reverts after
 * `trial_ms` unless the player accepts. */
#ifndef RG_MENU_H
#define RG_MENU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "rg_settings.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum rg_menu_cmd {
    RG_MENU_UP, RG_MENU_DOWN, RG_MENU_LEFT, RG_MENU_RIGHT,
    RG_MENU_ACCEPT, RG_MENU_BACK, RG_MENU_PAGE_PREV, RG_MENU_PAGE_NEXT,
    RG_MENU_TOGGLE
} rg_menu_cmd;

#define RG_MENU_MAX_PAGES 24
#define RG_MENU_MAX_ROWS 128

/* Row kinds on a page (rg_menu_rows encodes them as -1 - (kind + 8 * i)). */
enum { RG_ROW_SETTING, RG_ROW_PRESET, RG_ROW_SAVE, RG_ROW_RESET_PAGE, RG_ROW_RESET_BINDINGS };
#define RG_ROW_STRIDE 8

/* What the menu shows. */
enum {
    RG_MENU_VIEW_PAGE = 0,    /* a settings page (or presets) */
    RG_MENU_VIEW_BINDINGS,    /* one action's binding editor */
    RG_MENU_VIEW_TEXT         /* text entry for a STRING setting */
};

/* Editing keys for text entry (keyboard; the gamepad uses the on-screen
 * selector through ordinary commands). */
typedef enum rg_text_key {
    RG_TEXT_BACKSPACE, RG_TEXT_DELETE, RG_TEXT_LEFT, RG_TEXT_RIGHT, RG_TEXT_HOME, RG_TEXT_END,
    RG_TEXT_COMMIT, RG_TEXT_CANCEL
} rg_text_key;

#define RG_MENU_TEXT_MAX 256
/* Mouse-motion capture distance shown in the prompt (= RG_CAPTURE_MOUSE_DIST
 * in src/host/rg_input.h; host_sdl.c checks they agree). */
#define RG_MENU_MOTION_DIST 300

/* Prompt tags in the menu's own hint lines (docs/INPUT.md "Prompts in the
 * settings overlay"): "[accept]" etc. expand to the label the host set for
 * the device in use (rg_menu_set_prompt; host side rg_menu_prompts_from_input),
 * or to a generic word when none was set.  [cancel] is capture_hint. */
typedef enum rg_menu_prompt {
    RG_MP_UP, RG_MP_DOWN, RG_MP_LEFT, RG_MP_RIGHT, RG_MP_ACCEPT, RG_MP_BACK,
    RG_MP_PREV, RG_MP_NEXT,
    RG_MP_TOGGLE,     /* what opens / closes the overlay */
    RG_MP_START, RG_MP_SELECT, RG_MP_DPAD, RG_MP_LS, RG_MP_RS,   /* the game's buttons */
    RG_MP_COUNT
} rg_menu_prompt;
#define RG_MENU_PROMPT_LEN 64

/* Choices for a STRING setting (e.g. the audio devices for audio.device): fills out[]
 * with up to cap strings (they must stay valid until the next call) and returns the
 * count; 0 = free text only.  LEFT / RIGHT on the row then steps through them; ACCEPT
 * still opens the text editor. */
typedef int (*rg_menu_choices_fn)(const char *id, const char **out, int cap, void *user);
#define RG_MENU_MAX_CHOICES 32

typedef struct rg_menu {
    rg_settings *s;
    bool open;
    int page, cursor;
    int npages;
    const char *pages[RG_MENU_MAX_PAGES];   /* categories + "presets" */
    uint32_t trial_ms;                      /* default 15000 */
    const char *save_path;                  /* NULL: the Save row is hidden */
    char status[320];                       /* last action's message */
    bool dirty;                             /* changed since the last save */
    /* sub-views */
    int view;                               /* RG_MENU_VIEW_* */
    int edit;                               /* the setting being edited */
    int sub;                                /* cursor inside the editor */
    int sub_col;                            /* binding row: 0 = replace, 1 = remove */
    /* "press a key" capture (binding editor) */
    bool capturing;
    bool capture_motion;                    /* "Capture mouse motion": only motion binds */
    int capture_slot;                       /* binding to replace, -1 = add */
    uint64_t capture_deadline;
    uint32_t capture_ms;                    /* default 5000 */
    char capture_hint[64];                  /* names the cancel inputs */
    char confirm[96];                       /* captured motion awaiting accept / back */
    char offer[96];                         /* refused replace: "Add <offer> instead" */
    /* text entry */
    char text[RG_MENU_TEXT_MAX];
    int text_cur;                           /* byte offset of the cursor */
    int osk_row, osk_col;                   /* on-screen selector cursor */
    /* prompts for the device in use ("" = the generic word) */
    char prompt[RG_MP_COUNT][RG_MENU_PROMPT_LEN];
    char prompt_style[16];                  /* informational: "xbox", ... */
    /* choice lists for STRING settings (rg_menu_set_choices; NULL = none) */
    rg_menu_choices_fn choices;
    void *choices_user;
} rg_menu;

typedef struct rg_menu_line {
    char text[320];
    bool selected;
    bool header;
    int indent;     /* columns to indent wrapped continuation lines */
} rg_menu_line;

void rg_menu_init(rg_menu *m, rg_settings *s);
/* Choice lists for STRING settings (after rg_menu_init, which clears them). */
void rg_menu_set_choices(rg_menu *m, rg_menu_choices_fn fn, void *user);
/* Re-reads the categories (after more settings were registered). */
void rg_menu_refresh(rg_menu *m);
/* Applies one command at time now_ms.  Returns true if the menu used it (a
 * closed menu only uses TOGGLE).  While a display trial runs, ACCEPT keeps
 * the change, BACK reverts it, LEFT/RIGHT on a display row change it again
 * (extending the trial); other commands are ignored. */
bool rg_menu_command(rg_menu *m, rg_menu_cmd cmd, uint64_t now_ms);
/* Reverts an expired display trial (call every frame).  1 if it reverted. */
int rg_menu_tick(rg_menu *m, uint64_t now_ms);
/* Rows of the current page: setting indices, or -1 - RG_ROW_* for the action
 * rows of the "presets" page.  Returns the count. */
int rg_menu_rows(const rg_menu *m, int *rows, int cap);
/* Text lines to draw: a title, the page bar, rows (value and markers:
 * [restart], [gameplay], (planned), (restart pending), (--set)), the help of
 * the selected row with what its flags mean, the trial prompt, the capture
 * prompt and the status.  Returns the count. */
int rg_menu_render(const rg_menu *m, uint64_t now_ms, rg_menu_line *lines, int cap);
/* Wraps lines to at most `cols` characters (cols >= 8): breaks at the last
 * space that fits, else hard; continuation lines start with the source
 * line's `indent` spaces (at most cols / 2) and keep its selected/header
 * flags.  Returns the number of lines written to out (at most cap). */
int rg_menu_wrap(const rg_menu_line *in, int n, int cols, rg_menu_line *out, int cap);

/* ---- rebinding (docs/INPUT.md "Rebinding from the menu") ----
 * ACCEPT on a binding row opens its editor: one row per binding (LEFT/RIGHT
 * picks Replace or Remove, ACCEPT does it), "Add a binding", "Reset to
 * default", "Back".  Replace and Add start a capture: the host feeds the
 * next press through its detector (rg_bind_capture in rg_input.h) and calls
 * rg_menu_capture_input.  No input within capture_ms cancels (rg_menu_tick).
 * A binding another action of the same context (category) already has is
 * kept on both, with a warning.
 * "Capture mouse motion" starts a motion capture (rg_capture_begin_motion in
 * rg_input.h): the result is shown for confirmation, ACCEPT adds it, BACK
 * discards it.
 * Menu controls (category controls_ui) are guarded: a replace or remove that
 * would take away an action's last keyboard binding (key:) or its last
 * gamepad binding (pad:/axis:) is refused with a message, and the cursor
 * moves to "Add a binding" (for a refused replace, "Add <input> instead"). */
bool rg_menu_capturing(const rg_menu *m);
/* Capturing, and the capture is a mouse-motion capture. */
bool rg_menu_capturing_motion(const rg_menu *m);
/* The captured binding's canonical text, or NULL when the capture was
 * cancelled.  Ignored unless capturing. */
void rg_menu_capture_input(rg_menu *m, const char *binding, uint64_t now_ms);
/* Settings in the same category as `index` (not `index` itself) whose
 * binding list contains `token` (case-insensitive).  Returns the count. */
int rg_menu_binding_conflicts(const rg_menu *m, int index, const char *token, int *out, int cap);

/* ---- text entry (STRING settings) ----
 * ACCEPT on a string row opens the editor with the current value.  The
 * keyboard types through rg_menu_text_input / rg_menu_text_key; commands
 * drive the on-screen selector: directions move, ACCEPT types the selected
 * key (or Space / Delete / Clear / OK / Cancel), BACK deletes before the
 * cursor, PAGE_PREV / PAGE_NEXT move the cursor.  OK validates and stores;
 * an invalid value keeps the editor open with the reason. */
/* ---- prompts ---- */
void rg_menu_set_prompt(rg_menu *m, rg_menu_prompt p, const char *label);   /* NULL / "" = generic */
/* The label shown for a prompt (the generic word when unset). */
const char *rg_menu_prompt_text(const rg_menu *m, rg_menu_prompt p);
/* Expands the tags [up] [down] [left] [right] [accept] [back] [prev] [next]
 * [toggle] [start] [select] [dpad] [ls] [rs] [cancel] in `in`; anything else
 * (including other bracketed text) is copied.  Returns the full length. */
size_t rg_menu_expand(const rg_menu *m, const char *in, char *out, size_t cap);

bool rg_menu_text_editing(const rg_menu *m);
void rg_menu_text_input(rg_menu *m, const char *utf8);
void rg_menu_text_key(rg_menu *m, rg_text_key k);

#ifdef __cplusplus
}
#endif
#endif
