################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
#OUTPUT_NAME = $(notdir $(shell pwd))
PROJ_PATH = .

COPT += -DLINUX
COPT += -D__IO__=1
COPT += -D__STATIC__=1
COPT += -D__SSL_TLS__=1
COPT += -D__NSOCKET__=1
COPT += -D__NSERIAL__=1
COPT += -D__NWEBSOCKET__=1
COPT += -D__NHTTPD__=1
COPT += -D__NSHM__=0


SRC += $(PROJ_PATH)/.
SRC += $(PROJ_PATH)/m

INC  = -I.
INC += -I$(PROJ_PATH)/.
INC += -I$(PROJ_PATH)/m
INC += -I$(PROJ_PATH)/ua
INC += -I$(PROJ_PATH)/../../lite.io/__nio
INC += -I$(PROJ_PATH)/../../lite.io/$(XTARGET)
INC += -I$(PROJ_PATH)/../openssl/v1.1.1t/$(XTARGET)/include

xLIB += -Xlinker --start-group
xLIB += $(PROJ_PATH)/out/liblite.console.ua.$(XTARGET).a
xLIB += $(PROJ_PATH)/../../lite.io/$(XTARGET)/libio.$(XTARGET).a
xLIB += $(PROJ_PATH)/../../lite.io/$(XTARGET)/liblite.io.$(XTARGET).a
xxLIB += $(PROJ_PATH)/../openssl/v1.1.1t/$(XTARGET)/lib/libcrypto.a
xxLIB += $(PROJ_PATH)/../openssl/v1.1.1t/$(XTARGET)/lib/libssl.a

xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group

_OUTPUT_NAME = $(OUTPUT_NAME).$(XTARGET)
_TARGET_NAME = $(OUTPUT_NAME).$(XTARGET)$(OUTPUT_TYPE)
