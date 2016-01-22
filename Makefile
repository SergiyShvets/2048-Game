# Target definition
TARGET := Game2048

# Directories and files
TARGET_DIR := ./bin
OBJ_DIR := ./obj/$(TARGET)
LIB_DIRS := ./lib
SRC_DIRS ?= ./src
SOURCES ?= $(foreach D,$(SRC_DIRS),$(wildcard $D/*.cpp))
INC_DIRS ?= ./include ../common/include 
INCLUDES ?= $(foreach D,$(INC_DIRS),$(wildcard $D/*.h))
COPY_FILES = ./readme.txt

# Compilation flags
LDFLAGS += -lm -L$(LIB_DIRS)
CXXFLAGS = $(foreach D,$(INC_DIRS),-I$D) -D_LINUX_
ENDFLAGS += -lrt
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)gcc

ifeq ($(DEBUG),1)
    CXXFLAGS += -g -DDEBUG
endif

# Verbosity
ifeq ($(VERBOSE),1)
    ECHO :=
else
    ECHO := @
endif

# Make it all!
all: app

# Prepare the folders needed for build
init:
	@[ -d $(TARGET_DIR) ] || mkdir -p $(TARGET_DIR)
	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)

ifdef $(COPY_FILES)
	cp $(COPY_FILES) $(TARGET_DIR) || true
endif
	
# Host executable target
app: init
	$(ECHO) $(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET_DIR)/$(TARGET) $(ENDFLAGS)

# Standard clean procedure
clean :
	$(ECHO)rm -rf $(TARGET_DIR)
	$(ECHO)rm -rf $(OBJ_DIR)

.PHONY : all clean init app
