/*
 * Adapted from: https://gist.github.com/drashna/4f12ea060e37e752e725f009fc1e7297
*/
#include QMK_KEYBOARD_H
#include "transactions.h"
#include "sync.h"

user_runtime_config_t user_state; 

/**
 * Synchronizes the slave device's state with data received from the master.
 *
 * This function is designed to be used as an RPC (Remote Procedure Call) handler
 * that updates the slave's state to match that of the master. It is triggered
 * when the master sends synchronization data.
 */
void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    if (in_buflen == sizeof(user_state)) {
        memcpy(&user_state, in_data, in_buflen);
    }
}

/**
 * Registers the synchronization handler after keyboard initialization.
 *
 * Sets up the necessary RPC handler to synchronize state between
 * the keyboard's master and slave halves. It should be called during the keyboard's
 * post-initialization phase to ensure all necessary services are active.
 */
void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

/**
 * Updates the user state to reflect the current status of modifiers.
 *
 * Checks both the persistent and one-shot modifier states to determine
 * if either form modifiers is active. 
 */
void add_current_mods_state_to_user_state(void) {
    uint8_t mod_state;
    uint8_t oneshot_mod_state;

    mod_state = get_mods(); // Get the current active modifiers
    oneshot_mod_state = get_oneshot_mods(); // Get the current active one-shot modifiers

    // Check if either a regular mod or a one-shot mod is active
    user_state.shift_mod_enabled = (mod_state & MOD_MASK_SHIFT) || (oneshot_mod_state & MOD_MASK_SHIFT);
    user_state.alt_mod_enabled = (mod_state & MOD_MASK_ALT) || (oneshot_mod_state & MOD_MASK_ALT);
    user_state.gui_mod_enabled = (mod_state & MOD_MASK_GUI) || (oneshot_mod_state & MOD_MASK_GUI);
    user_state.ctrl_mod_enabled = (mod_state & MOD_MASK_CTRL) || (oneshot_mod_state & MOD_MASK_CTRL);

    // Check if CAPS_WORD is active
    user_state.caps_word_enabled = is_caps_word_on();
}

/**
 * Regularly checks and syncs the state between the keyboard halves.
 *
 * This function is part of the keyboard's main loop and runs continuously in the
 * background. It checks for state changes and initiates synchronization if the state
 * has changed or on a set interval (every 250ms). This ensures that both halves of
 * the keyboard maintain consistent states.
 *
 * The function handles state comparisons, updates the last known state, and triggers
 * the RPC call to synchronize the state if needed. On the slave half, this function
 * does not perform active handling, as the state synchronization is driven by the master.
 */
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Update user state variables to be synced
        add_current_mods_state_to_user_state();

        // Sync values
        static uint32_t last_sync = 0;
        static user_runtime_config_t last_user_state = {0};
        static bool needs_sync = false;

        // Check if state has changed or sync every 250ms
        if (memcmp(&user_state, &last_user_state, sizeof(user_state)) || timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_state));
        }

        if (needs_sync) {
            if (transaction_rpc_send(USER_SYNC_A, sizeof(user_state), &user_state)) {
                last_sync = timer_read32();
                needs_sync = false;
            }
        }
    } else {
        // The slave half does not need active handling in this context
    }
}

