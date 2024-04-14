# Based on http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

# Recursive wildcard
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# ----------------------------------------
# Project definitions
# ----------------------------------------

# Folders
BDIR = bin
DDIR = .deps
SDIR = src

# Source files
SRCS = $(call rwildcard,$(SDIR),*.cpp)
# Dependency files
DEPS = $(addprefix $(DDIR)/,$(patsubst %,%.d,$(patsubst %,%,$(basename $(notdir $(SRCS))))))
# Executable target files
BINS = $(addprefix $(BDIR)/,$(patsubst %,%,$(basename $(notdir $(SRCS)))))

# ----------------------------------------
# Compiler and linker definitions
# ----------------------------------------

# Compiler and linker
CXX = g++
AR = ar

# Libraries
INCLUDES =

# Flags for compiler
CFLAGS = -W -Wall -Wextra -pedantic -Wconversion -Wswitch-enum -flto -O2 -std=c++11

# ----------------------------------------
# Fomating macros
# ----------------------------------------

BOLD = \033[1m
NORMAL = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m

# ----------------------------------------
# Compilation and linking rules
# ----------------------------------------

all: $(BINS)

$(BDIR)/%: $(SDIR)/%.cpp
$(BDIR)/%: $(SDIR)/%.cpp $(DDIR)/%.d | $(DDIR) $(BDIR)
	@ echo "${GREEN}Building target: ${BOLD}$@${GREEN}, using dependencies: ${BOLD}$^${NORMAL}"
	$(CXX) $(CFLAGS) -MT $@ -MMD -MP -MF $(DDIR)/$*.Td $(filter %.cpp %.c %.s %.o,$^) -o $@ $(INCLUDES)
	mv -f $(DDIR)/$*.Td $(DDIR)/$*.d && touch $@

$(DDIR)/%.d: ;
.PRECIOUS: $(DDIR)/%.d

-include $(DEPS)

# ----------------------------------------
# Script rules
# ----------------------------------------

test: $(BINS)
	@ for t in $(BINS); do \
		echo "${GREEN}Running test: ${BOLD}$$t${NORMAL}" ; \
		./$$t 1>/dev/null ; \
		if [ $$? -ne 0 ] ; then \
			echo "${RED}Test ${BOLD}$$t${RED} failed${NORMAL}" ; \
			exit 1 ; \
		fi ; \
	done
	@echo "${GREEN}Success, all tests passed.${NORMAL}"

$(BDIR) $(DDIR):
	@ echo "${GREEN}Creating directory: ${BOLD}$@${NORMAL}"
	mkdir -p $@

clean:
	@ echo "${GREEN}Cleaning up${NORMAL}"
	rm -rf $(BDIR) $(DDIR) *.d *.o *.a *.so

remade: clean all

.PHONY: all test clean remade

# ----------------------------------------