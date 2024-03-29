# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel.elf

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
ifeq ($(origin CC), default)
CC := cc
endif

# Likewise, "ld" here is just a placeholder and your mileage may vary if using the
# host's "ld".
ifeq ($(origin LD), default)
LD := ld
endif

# User controllable CFLAGS.
CFLAGS ?= -Iinclude -Wall -Wextra -O2 -pipe

# User controllable linker flags. We set none by default.
LDFLAGS ?=

# Internal C flags that should not be changed by the user.
override INTERNALCFLAGS :=   \
	-I.                  \
	-std=gnu11           \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-pie			 \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-mgeneral-regs-only  \
	-MMD

# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

SRC_DIR   := src/
BUILD_DIR := build/

# Use find to glob all *.c files in the directory and extract the object names.
override CFILES      := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c) 
override ASMFILES    := $(wildcard $(SRC_DIR)/*.asm) $(wildcard $(SRC_DIR)/**/*.asm) 
override OBJ         := $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(ASMFILES:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.o)
override HEADER_DEPS := $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d)

# Default target.
.PHONY: all
all: $(KERNEL)

stivale2.h:
	curl https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h -o $@

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

# Compilation rules for *.c files.
-include $(HEADER_DEPS)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@ -g

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	nasm $< -f elf64 -o $@ -g

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f stivale2.h
