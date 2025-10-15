#pragma once

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINDOWS

// #define TAPPING_TERM 175

/* Send up to 4 key press events per scan */
#define QMK_KEYS_PER_SCAN 12

// /* Set debounce time to 2ms */
#define DEBOUNCE 2
#define USB_POLLING_INTERVAL_MS 1 /* 1000hz polling rate - 2 = 500hz, etc. */