#pragma once

/**
 * Handle layer activation:
 * - If a layer key is held:
 *     -> Activate the layer until the key is released.
 * - If a layer key is tapped:
 *     -> Register the layer as a one-shot layer, active for the next key press.
 * - If a layer key is double-tapped:
 *     -> Activate the layer and keep it active until the key is tapped again.
 * - If both layer keys (e.g., RAISE and LOWER) are held simultaneously:
 *     -> Activate the ADJUST layer until both keys are released.
 */
void handle_layer_activation(uint16_t layer, keyrecord_t *record);

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
