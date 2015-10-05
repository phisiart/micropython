SOCEDS_ROOT ?= $(SOCEDS_DEST_ROOT)
HWLIBS_ROOT = $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib

# look for SoC EDS 15.0 directory structure
ifneq (,$(wildcard $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av/socal))
SOCAL_ROOT := $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
endif

# look for SoC EDS 14.0 directory structure
ifneq (,$(wildcard $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib/include/socal))
SOCAL_ROOT := $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib/include
endif

ifndef SOCAL_ROOT
$(error SOCAL_ROOT is undefined)
endif

include ../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

CROSS_COMPILE = arm-altera-eabi-

INC =  -I.
INC += -I..
INC += -I../lib/mp-readline
INC += -I../stmhal
INC += -I$(BUILD)
INC += -I$(HWLIBS_ROOT)/include
INC += -I$(SOCAL_ROOT)

MULTILIBFLAGS = -mfloat-abi=softfp -mtune=cortex-a9 -mcpu=cortex-a9 -march=armv7-a
CFLAGS = $(INC) -Wall -Werror -ansi -std=gnu99 -nostdlib $(MULTILIBFLAGS) $(COPT)

LINKER_SCRIPT := cycloneV-dk-ram-modified.ld
LDFLAGS = -T$(LINKER_SCRIPT) $(MULTILIBFLAGS)
LD = $(CROSS_COMPILE)gcc
OC := $(CROSS_COMPILE)objcopy

# Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -O0 -ggdb
else
CFLAGS += -Os -DNDEBUG
endif

LIBS =

SRC_C = \
	main.c \
	uart_core.c \
	uart_extra.c \
	stmhal/printf.c \
	stmhal/pyexec.c \
	lib/libc/string0.c \
	lib/mp-readline/readline.c \
	io.c \

SRC_S = \
#	startup_stm32f40xx.s \
	gchelper.s \

OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o) $(SRC_S:.s=.o))

all: $(BUILD)/firmware.raw

$(BUILD)/firmware.raw: $(BUILD)/firmware.elf
	$(ECHO) "CREATE RAW BINARY $@"
	$(Q)$(OC) -O binary $(BUILD)/firmware.elf $(BUILD)/firmware.raw

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
	$(Q)$(SIZE) $@

include ../py/mkrules.mk
