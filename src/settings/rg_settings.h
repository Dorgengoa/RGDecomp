/* SPDX-License-Identifier: CC0-1.0 */
/* Typed settings registry (PLAN.md P4 "Settings foundation", P6 ground rules;
 * docs/SETTINGS.md).
 *
 * One registry drives the config file, the command line (--set id=value,
 * --preset name) and the in-game settings menu, so they cannot disagree.
 *
 *   definitions  id ("display.vsync"), type, default, range / enum names /
 *                validator, category, label, help, flags (needs restart,
 *                display change with timed revert, gameplay option,
 *                placeholder for a feature that is not built yet), and the
 *                value of the "original" preset (the PS2 look and behaviour)
 *   values       two layers per setting: the persistent value (default,
 *                preset, config file, menu) and the effective value (the
 *                persistent one, or a command-line override).  Saving writes
 *                the persistent layer, so --set never leaks into the file.
 *   text         a tiny INI dialect: "[section]" + "key = value", '#'
 *                comments; ids are "section.key".  Unknown keys are kept
 *                and written back (forward compatibility).  Invalid values
 *                fall back to the default with a warning.
 *   presets      "original" (every setting's original value, default where
 *                none is given) and "default" built in; more can be added as
 *                id=value lists.
 *   menu API     iteration by index, rg_settings_step (left/right on a menu
 *                row), display trials that revert after a timeout unless
 *                confirmed, the restart-pending list, change callbacks.
 *
 * Pure C, no SDL, no globals: every function takes the registry.  One thread.
 */
#ifndef RG_SETTINGS_H
#define RG_SETTINGS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum rg_setting_type {
    RG_SET_BOOL,
    RG_SET_INT,
    RG_SET_FLOAT,
    RG_SET_ENUM,      /* one of enum_names (stored as the index) */
    RG_SET_STRING,
    RG_SET_BINDING    /* an input binding list; a string checked by `validate` */
} rg_setting_type;

enum {
    RG_SETF_RESTART     = 1u << 0, /* takes effect after a restart */
    RG_SETF_DISPLAY     = 1u << 1, /* display change: the menu applies it as a
                                      trial that reverts unless confirmed */
    RG_SETF_GAMEPLAY    = 1u << 2, /* changes game logic: labelled, off in "original" */
    RG_SETF_PLACEHOLDER = 1u << 3, /* planned (P6); stored and validated, no effect yet */
    RG_SETF_HIDDEN      = 1u << 4, /* not listed in the menu (still in the file) */
    RG_SETF_HAS_ORIGINAL = 1u << 5 /* orig_* holds the "original" preset value */
};

/* A validator for STRING/BINDING settings: 0 = ok (it may write a normalised
 * form into norm, NUL-terminated, at most normcap bytes; norm[0] = 0 keeps the
 * text as given), -1 = invalid (reason in err). */
typedef int (*rg_setting_validate_fn)(const char *text, char *norm, size_t normcap,
                                      char *err, size_t errcap, void *user);

typedef struct rg_setting_def {
    const char *id;            /* "category.name[.more]": lower case, [a-z0-9_.] */
    rg_setting_type type;
    const char *category;      /* menu page; NULL = the id's first component */
    const char *label;         /* menu text (NULL = id) */
    const char *help;          /* one line (may be NULL) */
    unsigned flags;            /* RG_SETF_* */
    /* default */
    int def_i;                 /* BOOL (0/1), INT, ENUM (index) */
    double def_f;              /* FLOAT */
    const char *def_s;         /* STRING, BINDING */
    /* the "original" preset (RG_SETF_HAS_ORIGINAL; else the default is used) */
    int orig_i;
    double orig_f;
    const char *orig_s;
    /* range: INT [min_i, max_i], FLOAT [min_f, max_f]; step for the menu */
    int min_i, max_i, step_i;
    double min_f, max_f, step_f;
    /* ENUM */
    const char *const *enum_names;
    const char *const *enum_labels;  /* menu text per value (NULL = names) */
    int enum_count;
    /* STRING / BINDING */
    rg_setting_validate_fn validate;
    void *validate_user;
    size_t max_len;            /* 0 = 1023 */
} rg_setting_def;

/* Where a setting's effective value came from. */
typedef enum rg_setting_source {
    RG_SRC_DEFAULT, RG_SRC_PRESET, RG_SRC_FILE, RG_SRC_MENU, RG_SRC_API, RG_SRC_CMDLINE
} rg_setting_source;

/* Result of a set. */
enum {
    RG_SET_OK = 0,
    RG_SET_UNCHANGED = 1,   /* valid, same value as before */
    RG_SET_INVALID = -1,    /* bad text / out of range (value left as it was) */
    RG_SET_UNKNOWN = -2,    /* no such setting */
    RG_SET_TYPE = -3        /* wrong accessor for the setting's type */
};

typedef struct rg_settings rg_settings;

typedef void (*rg_settings_warn_fn)(void *user, const char *msg);
/* Called after a setting's EFFECTIVE value changed (index, the registry). */
typedef void (*rg_settings_change_fn)(rg_settings *s, int index, void *user);

rg_settings *rg_settings_create(void);
void rg_settings_destroy(rg_settings *s);

/* Warnings (invalid values, unknown keys, ...).  Default: stderr with an
 * "rg-settings: " prefix.  fn NULL = silent.  rg_settings_warnings counts
 * them since creation. */
void rg_settings_set_warn(rg_settings *s, rg_settings_warn_fn fn, void *user);
unsigned rg_settings_warnings(const rg_settings *s);
const char *rg_settings_last_warning(const rg_settings *s);

/* Register definitions (copied; strings must stay valid: use literals or
 * storage that outlives the registry).  Each starts at its default.  A bad
 * definition (duplicate id, default outside its range, ...) is refused with a
 * warning and -1; the others are still registered. */
int rg_settings_register(rg_settings *s, const rg_setting_def *defs, int n);
/* The P4 core set: display, audio, system, graphics placeholders
 * (rg_settings_core.c).  Input settings are registered by the input layer
 * (src/host, rg_actions_register_settings). */
int rg_settings_register_core(rg_settings *s);

/* ---- lookup / iteration (the menu walks these) ---- */
int rg_settings_count(const rg_settings *s);
int rg_settings_find(const rg_settings *s, const char *id);     /* -1 if unknown; resolves aliases */
/* An old id that keeps meaning a registered setting (a renamed id): the file
 * parser, presets, --set and rg_settings_find accept it; the file is always
 * written with the current id.  0, or -1 (unknown target, old id taken). */
int rg_settings_add_alias(rg_settings *s, const char *old_id, const char *id);
const rg_setting_def *rg_settings_def(const rg_settings *s, int index);
const char *rg_settings_category(const rg_settings *s, int index);
/* Categories in registration order; returns the count. */
int rg_settings_categories(const rg_settings *s, const char **out, int cap);
rg_setting_source rg_settings_source(const rg_settings *s, int index);
bool rg_settings_is_default(const rg_settings *s, int index);
bool rg_settings_overridden(const rg_settings *s, int index);   /* by the command line */

/* ---- typed access (effective value).  get_* on the wrong type returns the
 * zero value; set_* returns RG_SET_* ---- */
bool rg_settings_get_bool(const rg_settings *s, const char *id);
int rg_settings_get_int(const rg_settings *s, const char *id);     /* INT, BOOL, ENUM index */
double rg_settings_get_float(const rg_settings *s, const char *id);
const char *rg_settings_get_string(const rg_settings *s, const char *id); /* STRING, BINDING, ENUM name */
int rg_settings_get_enum(const rg_settings *s, const char *id);    /* index, -1 if not an enum */
int rg_settings_set_bool(rg_settings *s, const char *id, bool v, rg_setting_source src);
int rg_settings_set_int(rg_settings *s, const char *id, int v, rg_setting_source src);
int rg_settings_set_float(rg_settings *s, const char *id, double v, rg_setting_source src);
int rg_settings_set_string(rg_settings *s, const char *id, const char *v, rg_setting_source src);

/* Parse `text` for setting `index` and set it.  RG_SRC_CMDLINE writes the
 * effective layer only (an override); every other source writes both
 * layers.  On RG_SET_INVALID the reason is in err and nothing changes. */
int rg_settings_set_text(rg_settings *s, int index, const char *text,
                         rg_setting_source src, char *err, size_t errcap);
/* The effective (or persistent) value as text, in the file syntax. */
size_t rg_settings_value_text(const rg_settings *s, int index, char *out, size_t cap);
size_t rg_settings_persistent_text(const rg_settings *s, int index, char *out, size_t cap);
size_t rg_settings_default_text(const rg_settings *s, int index, char *out, size_t cap);
/* Menu text of the effective value (enum label, "On"/"Off", ...). */
size_t rg_settings_display_text(const rg_settings *s, int index, char *out, size_t cap);

/* Back to the default (both layers, drops an override). */
void rg_settings_reset(rg_settings *s, int index);
void rg_settings_reset_all(rg_settings *s);

/* ---- presets ---- */
/* "original" and "default" are built in.  Applying a preset resets every
 * setting it covers (both layers; the source becomes RG_SRC_PRESET);
 * command-line overrides are re-applied on top. */
int rg_settings_apply_preset(rg_settings *s, const char *name);   /* 0 / -1 unknown */
/* A user preset: lines "id = value" (the file syntax, sections allowed).
 * Settings it does not name are set to their defaults when it is applied.
 * Returns 0, or -1 (bad text: message in err). */
int rg_settings_add_preset(rg_settings *s, const char *name, const char *label,
                           const char *text, char *err, size_t errcap);
int rg_settings_preset_count(const rg_settings *s);
const char *rg_settings_preset_name(const rg_settings *s, int i);
const char *rg_settings_preset_label(const rg_settings *s, int i);
/* Does every setting currently equal the preset's value?  (The verification
 * runs use "original"; this is their guard.) */
bool rg_settings_matches_preset(const rg_settings *s, const char *name);

/* ---- the config file ---- */
/* Parse INI text into the persistent layer (source RG_SRC_FILE).  Lines:
 *   [section]           ids below are "section.key" ([] = top level)
 *   key = value         surrounding spaces trimmed; value may be "quoted"
 *   preset = name       (top level only) applies the preset at that point
 *   # comment           '#' at line start, or after whitespace
 * Invalid values fall back to the DEFAULT with a warning naming the line;
 * unknown keys warn and are kept for rg_settings_format.  Returns the number
 * of warnings (0 = clean); never fails. */
int rg_settings_parse(rg_settings *s, const char *text, const char *name);
/* Load a file.  A missing file is not an error (returns 0, nothing set);
 * returns -1 only when it exists but cannot be read. */
int rg_settings_load(rg_settings *s, const char *path);

enum {
    RG_FMT_CHANGED_ONLY = 1u << 0,  /* only settings that differ from the default */
    RG_FMT_NO_COMMENTS  = 1u << 1   /* no label/range/default comment lines */
};
/* The persistent layer as INI text (round-trips through rg_settings_parse).
 * Returns the full length (NUL-terminated if cap > 0, truncated to fit). */
size_t rg_settings_format(const rg_settings *s, char *out, size_t cap, unsigned flags);
/* Writes rg_settings_format to `path` via "<path>.tmp" + rename (a crash never
 * leaves a half-written file).  0 / -1. */
int rg_settings_save(const rg_settings *s, const char *path, unsigned flags);

/* ---- command line ---- */
/* Consumes, in order:  --set id=value | --set=id=value,  --preset name |
 * --preset=name,  --settings path | --settings=path  (loads a file).
 * Overrides from --set go to the effective layer (RG_SRC_CMDLINE) and are
 * re-applied after later presets/loads.  Other arguments are kept: argv is
 * compacted in place and the new argc returned.  Unknown ids / invalid values
 * warn and are skipped; *errors (may be NULL) counts them.  If
 * `settings_path` is non-NULL it receives the last --settings path (a
 * pointer into argv; NULL if none) so the caller can save back to it. */
int rg_settings_apply_args(rg_settings *s, int argc, char **argv, int *errors,
                           const char **settings_path);
/* One "id=value" override, as --set does.  0 / RG_SET_*. */
int rg_settings_override(rg_settings *s, const char *assignment);
void rg_settings_clear_overrides(rg_settings *s);

/* ---- change tracking ---- */
/* Up to 16 callbacks; called once per effective-value change. */
int rg_settings_on_change(rg_settings *s, rg_settings_change_fn fn, void *user);
/* Snapshot of the values the running process applied at start.  Settings
 * flagged RG_SETF_RESTART whose value differs from the snapshot are
 * "restart pending". */
void rg_settings_mark_applied(rg_settings *s);
int rg_settings_restart_pending(const rg_settings *s, int *out, int cap);
/* Bumped on every effective change (cheap "anything changed?" test). */
uint64_t rg_settings_generation(const rg_settings *s);

/* ---- menu helpers ---- */
/* Left/right on a menu row: BOOL toggles, ENUM cycles (wraps), INT/FLOAT move
 * by the step and clamp.  STRING/BINDING: no-op (RG_SET_TYPE).  The source is
 * RG_SRC_MENU (both layers). */
int rg_settings_step(rg_settings *s, int index, int dir);

/* Display trials: the menu applies a RG_SETF_DISPLAY change at once and asks
 * the player to confirm.  rg_settings_trial_begin remembers the current
 * (pre-change) values of the trial set; rg_settings_tick reverts them all
 * when `now_ms` passes the deadline.  Only one trial at a time (a second
 * begin extends the open one, keeping the oldest values). */
int rg_settings_trial_begin(rg_settings *s, int index, uint64_t now_ms, uint32_t timeout_ms);
void rg_settings_trial_confirm(rg_settings *s);
void rg_settings_trial_revert(rg_settings *s);
bool rg_settings_trial_active(const rg_settings *s);
/* Milliseconds left (0 when no trial). */
uint32_t rg_settings_trial_remaining(const rg_settings *s, uint64_t now_ms);
/* Reverts an expired trial.  Returns 1 if it reverted now, else 0. */
int rg_settings_tick(rg_settings *s, uint64_t now_ms);

/* ---- parsing helpers shared with other modules ---- */
int rg_settings_parse_bool(const char *text, bool *out);       /* 0 / -1 */

#ifdef __cplusplus
}
#endif
#endif
