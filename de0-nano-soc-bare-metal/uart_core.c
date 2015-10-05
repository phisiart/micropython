#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>

#include "socal/alt_uart.h"
#include "socal/hps.h"
#include "socal/socal.h"

#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    // Wait until data ready
    while (1 != ALT_UART_LSR_DR_GET(alt_read_word(ALT_UART0_LSR_ADDR))) { }
    
    // Read character from THR
    return alt_read_word(ALT_UART0_RBR_THR_DLL_ADDR);
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    for (int i = 0; i < len; i++) {
        // Wait until THR is empty
        while (1 != ALT_UART_LSR_THRE_GET(alt_read_word(ALT_UART0_LSR_ADDR))) { }

        // Write character to THR
        alt_write_word(ALT_UART0_RBR_THR_DLL_ADDR, str[i]);
    }
}
