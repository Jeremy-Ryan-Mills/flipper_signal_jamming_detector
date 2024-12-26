#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "furi_hal_gpio.h"
#include "core/thread.h"
#include "furi_hal.h"

void scan_for_jamming() {
    SubGhzStatus status;
    SubGhzConfig config = {
        .frequency = 433920000, // Frequency in Hz
        .power = SubGhzPower18dBm,
    };

    status = subghz_init();
    if(status != SubGhzStatusOk) return;

    subghz_set_config(&config);
    while(true) {
        int rssi = subghz_get_rssi();
        if(rssi > JAMMING_THRESHOLD) {
            printf("Potential jamming detected! RSSI: %d\n", rssi);
        }
        furi_delay_ms(500);
    }
    subghz_deinit();
}