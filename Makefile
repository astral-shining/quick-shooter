TARGET_NAME := quick

CC        := em++
SRC_DIR   := src
OBJ_DIR   := build
DIST_DIR  := dist
TARGETS   := $(DIST_DIR)/$(TARGET_NAME).js $(DIST_DIR)/$(TARGET_NAME).wasm

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
OBJ_SUBDIRS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC_SUBDIRS))


OBJ_FILES := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.d,$(SRC_FILES))


CPPFLAGS += -O3 -Wall \
		  -s STRICT=1 -std=c++20 -I include -I src -Wno-deprecated-volatile


LDFLAGS += -O3 \
		   -s FILESYSTEM=0 \
		   -s USE_SDL=0 \
		   -s ASSERTIONS=1 \
		   -s ENVIRONMENT=web \
		   -s STRICT=1 \
		   -s INCOMING_MODULE_JS_API=[] \
		   -s TOTAL_STACK=524288 \
		   -s HTML5_SUPPORT_DEFERRING_USER_SENSITIVE_REQUESTS=0 \
		   -s USE_WEBGL2=1 \
		   \
		   \
		   -s EXPORT_NAME=quick \
		   -lGL 


.PHONY: all dbg clean 
all: dbg

prod: $(TARGETS)

dbg: CPPFLAGS += -g -D DEBUG=1 -fsanitize=undefined
dbg: LDFLAGS  += -fsanitize=undefined
#-s ASSERTIONS=1
dbg: $(TARGETS)

$(TARGETS): $(OBJ_SUBDIRS) $(OBJ_FILES)
	$(CC) -o $(DIST_DIR)/$(TARGET_NAME).js $(OBJ_FILES) $(LDFLAGS)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -MMD -MP $(CPPFLAGS) -c $< -o $@

$(OBJ_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(DIST_DIR)/$(TARGET).js $(DIST_DIR)/$(TARGET).wasm $(OBJ_SUBDIRS)
	
-include $(DEP_FILES)
