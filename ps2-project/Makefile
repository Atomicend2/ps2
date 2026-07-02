# =================================================================
# MASTER BUILD CONFIGURATION: THE SEVENTH VOW (PS2/TYRA ENGINE)
# =================================================================

# Target binary name
EE_BIN = BISCUS_970.00.ELF

# All compiled object dependencies from our workspace sessions
EE_OBJS = src/main.o \
          src/script_parser.o \
          src/world_state.o \
          src/extended_combat.o \
          src/meta_narrative.o \
          src/level_builder.o

# Compiler & Linker Directories
EE_INCS += -Iinclude -I$(TYRA_SRC)/include
EE_LDFLAGS += -L$(TYRA_SRC)/lib -ltyra -lpadx -lmc -lhdd -lfileXio

# Standard PS2SDK Global Build Rules
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal

# Optimized compilation flags for Emotion Engine performance
EE_CXXFLAGS += -O2 -Wall -fno-exceptions -frtti

