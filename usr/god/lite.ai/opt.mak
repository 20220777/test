################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
#OUTPUT_NAME = $(notdir $(shell pwd))
PROJ_PATH = .

COPT += -DLINUX
COPT += -D__NSERIAL__=1
COPT += -D__NSOCKET__=1
COPT += -D__IO__=1
COPT += -D__STATIC__=1
COPT += -D__SSL_TLS__=1
COPT += -D__SOCKET__=1
COPT += -D__SERIAL__=1

SRC += $(PROJ_PATH)/.
SRC += $(PROJ_PATH)/m
SRC += $(PROJ_PATH)/n

INC  = -I.
INC += -I$(PROJ_PATH)/.
INC += -I$(PROJ_PATH)/m
INC += -I$(PROJ_PATH)/n
INC += -I$(PROJ_PATH)/../../../../lite/core/x/coms/$(XTARGET)
INC += -I$(PROJ_PATH)/../../openssl/v1.1.1t/$(XTARGET)/include

xLIB += -Xlinker --start-group
xLIB += $(PROJ_PATH)/../../../../lite/core/x/coms/$(XTARGET)/liblite.io.$(XTARGET).a
xLIB += $(PROJ_PATH)/../../openssl/v1.1.1t/$(XTARGET)/lib/libcrypto.a
xLIB += $(PROJ_PATH)/../../openssl/v1.1.1t/$(XTARGET)/lib/libssl.a

xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group

_TARGET_NAME = $(OUTPUT_NAME)
