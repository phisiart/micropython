/******************************************************************************
 *
 * Copyright 2014 Altera Corporation. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 ******************************************************************************/

/*
 * This file contains minimal IO support to make printf work over UART
 * The code relies on the Preloader to set the UART module including baud rate
 */

#include <stdio.h>
#include <inttypes.h>

// #include "socal/alt_uart.h"
// #include "socal/hps.h"
// #include "socal/socal.h"
#include "mpconfigport.h"

#define STDOUT_FILENO 1
#define STDIN_FILENO 0

int _close(int file)
{
    /* Succeeds only for STDOUT */
    return (file == STDOUT_FILENO) ? 0 : -1;
}

int _fstat(int file, void *st)
{
    /* Succeeds only for STDOUT */
    return (file == STDOUT_FILENO) ? 0 : -1;
}

int _isatty(int file)
{
    /* Succeeds only for STDOUT */
    return (file == STDOUT_FILENO) ? 1 : -1;
}

off_t _lseek(int file, off_t ptr, int dir)
{
    /* Succeeds only for STDOUT */
    return (file == STDOUT_FILENO) ? 0 : -1;
}

int _read(int file, void *ptr, size_t len)
{
    /* Succeeds only for STDIN */
    if (file != STDIN_FILENO) {
        return -1;
    }
    
    for (int i = 0; i < len; i++) {
        ((char *)ptr)[i] = mp_hal_stdin_rx_chr();
    }
    
    return len;
}

int _write(int file, char * ptr, unsigned len, int flag)
{
    /* Succeeds only for STDOUT */
    if (file != STDOUT_FILENO) {
        return -1;
    }

    mp_hal_stdout_tx_strn(ptr, len);
    return len;
}