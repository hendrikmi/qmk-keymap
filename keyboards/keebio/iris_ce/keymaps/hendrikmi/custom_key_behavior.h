#pragma once

void update_layer_states(bool is_raise_held, bool is_lower_held);
void deactivate_all_layers(void);
void handle_layer_activation(uint16_t layer, keyrecord_t *record);
void handle_mod_swap_oneshot(uint16_t mod_primary, uint16_t mod_secondary, keyrecord_t *record);
