#pragma once

/**
 * Handle the one-shot and swapping behavior of modifiers:
 * - If CMD or ALT is held:
 *     -> Act as the respective modifier (CMD or ALT).
 * - If CMD or ALT is tapped:
 *     -> Register the key as a one-shot modifier, active for the next key press.
 * - If CMD or ALT is double-tapped:
 *     -> Register a one-shot modifier of the opposite modifier:
 *         - CMD double-tap registers a one-shot ALT.
 *         - ALT double-tap registers a one-shot CMD.
 */
void handle_mod_swap_oneshot(uint16_t mod_primary, uint16_t mod_secondary, keyrecord_t *record);
