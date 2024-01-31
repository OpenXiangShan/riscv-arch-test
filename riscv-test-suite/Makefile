CROSS         = riscv64-unknown-linux-gnu-
CROSS_CC      = $(CROSS)gcc
RISCV_ARCH    = rv64gc_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh
CROSS_CFLAGS  = -Wl,--entry=rvtest_entry_point,-Ttext=0x80000000 \
				-nostartfiles -static -I./env -DTEST_CASE_1      \
				-march=$(RISCV_ARCH)
CROSS_OBJCOPY = $(CROSS)objcopy
CROSS_OBJDUMP = $(CROSS)objdump

BASE_DIR = $(realpath .)

BUILD_DIR = $(BASE_DIR)/build
SRC_DIR   = $(BASE_DIR)/rv64i_m
INC_DIR   = $(BASE_DIR)/env
INCLUDES  = $(shell find $(INC_DIR) -maxdepth 1 -name '*.h')

# K is included here but may cause compiling errors with riscv-gcc 10.2.0 we used
# K requires newer version toolchains
TEST_SUITES = B C D F I K M privilege Zifencei
all: $(BUILD_DIR) $(addprefix build_,$(TEST_SUITES))

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

SECTIONS = .text .data .got
SECTIONS_FLAGS = $(addprefix --only-section=, $(SECTIONS))

define cmd_template
TESTS_SRC_$(1) := $$(shell find $(SRC_DIR)/$(1)/src -maxdepth 1 -name '*.S')
SRC_NAMES_$(1) := $$(basename $$(notdir $$(TESTS_SRC_$(1))))
TARGETS_$(1)   := $$(addprefix $$(BUILD_DIR)/$(1)-,$$(SRC_NAMES_$(1)))
BINARY_$(1)    := $$(addsuffix .bin,$$(TARGETS_$(1)))
OBJDUMP_$(1)   := $$(addsuffix .txt,$$(TARGETS_$(1)))

$(BUILD_DIR)/$(1)-%.elf: $(SRC_DIR)/$(1)/src/%.S $(INCLUDES)
	$(CROSS_CC) $(CROSS_CFLAGS) -o $$@ $$<
.PRECIOUS: $(BUILD_DIR)/$(1)-%.elf

$(BUILD_DIR)/$(1)-%.bin: $(BUILD_DIR)/$(1)-%.elf
	$(CROSS_OBJCOPY) -S -O binary $(SECTIONS_FLAGS) $$< $$@

$(BUILD_DIR)/$(1)-%.txt: $(BUILD_DIR)/$(1)-%.elf
	$(CROSS_OBJDUMP) -d $$< > $$@

build_$(1): $(BUILD_DIR) $$(BINARY_$(1)) $$(OBJDUMP_$(1))

endef

$(eval $(foreach t, $(TEST_SUITES), $(call cmd_template,$(t))))
