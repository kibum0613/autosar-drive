# Host build + test for the AEB SWC generated from Simulink (Embedded Coder).
CC      := gcc
CFLAGS  ?= -std=c99 -O2 -Wall -Wextra -pedantic -Werror
LDLIBS  := -lm

BUILD   := build
REPORTS := reports

ERT_DIR   := model_gen/ert
SWC_DIR   := model_gen/autosar/src
RTE_DIR   := model_gen/autosar/rte_stub
PLAT_DIR  := platform
TEST_DIR  := test

INC_SWC := -I$(PLAT_DIR) -I$(SWC_DIR) -I$(RTE_DIR) -I$(TEST_DIR)
INC_ALL := $(INC_SWC) -I$(ERT_DIR)

SWC_SRC := $(SWC_DIR)/AEB_Core_SWC.c $(TEST_DIR)/rte_test_double.c
ERT_SRC := $(ERT_DIR)/AEB.c $(ERT_DIR)/rt_nonfinite.c $(ERT_DIR)/rtGetNaN.c

.PHONY: all binaries test test-unit test-b2b static clean

all: binaries

binaries: $(BUILD)/libaeb_swc.a $(BUILD)/test_swc_unit $(BUILD)/test_b2b

$(BUILD):
	mkdir -p $@

$(REPORTS):
	mkdir -p $@

# The SWC alone, as it would be handed to an ECU integrator.
$(BUILD)/AEB_Core_SWC.o: $(SWC_DIR)/AEB_Core_SWC.c | $(BUILD)
	$(CC) $(CFLAGS) -I$(PLAT_DIR) -I$(SWC_DIR) -I$(RTE_DIR) -c $< -o $@

$(BUILD)/libaeb_swc.a: $(BUILD)/AEB_Core_SWC.o
	ar rcs $@ $^
	size $^

$(BUILD)/test_swc_unit: $(TEST_DIR)/test_swc_unit.c $(SWC_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(INC_SWC) $^ -o $@ $(LDLIBS)

$(BUILD)/test_b2b: $(TEST_DIR)/test_b2b.c $(SWC_SRC) $(ERT_SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(INC_ALL) $^ -o $@ $(LDLIBS)

test: test-unit test-b2b

test-unit: $(BUILD)/test_swc_unit | $(REPORTS)
	$< $(REPORTS)/junit-unit.xml

test-b2b: $(BUILD)/test_b2b | $(REPORTS)
	$< $(REPORTS)/junit-b2b.xml

# Static analysis of the generated SWC (report only, does not fail the build).
static: | $(REPORTS)
	cppcheck --enable=warning,style,performance,portability --std=c99 \
	  --inline-suppr --xml --xml-version=2 \
	  -I$(PLAT_DIR) -I$(SWC_DIR) -I$(RTE_DIR) \
	  $(SWC_DIR)/AEB_Core_SWC.c 2> $(REPORTS)/cppcheck.xml
	@echo "cppcheck findings:" $$(grep -c '<error ' $(REPORTS)/cppcheck.xml || true)

clean:
	rm -rf $(BUILD) $(REPORTS)
