################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
#OUTPUT_NAME = $(notdir $(shell pwd))
PROJ_PATH = .

COPT += -DLINUX

#SRC += $(PROJ_PATH)/.

INC  = -I.
INC += -I$(PROJ_PATH)/.
INC += -I$(PROJ_PATH)/ec-kcda
INC += -I$(PROJ_PATH)/../../lite.io/$(XTARGET)

#__SSL_TLS__
INC += -I$(PROJ_PATH)/../../../c/usr/openssl/v1.1.1t/$(XTARGET)/include
INC += -I$(PROJ_PATH)/../../../c/usr/openssl/v1.1.1t/$(XTARGET)/include/openssl
xLIB += $(PROJ_PATH)/../../../c/usr/openssl/v1.1.1t/$(XTARGET)/lib/libcrypto.a
xLIB += $(PROJ_PATH)/../../../c/usr/openssl/v1.1.1t/$(XTARGET)/lib/libssl.a

xLIB += -Xlinker --start-group
xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group

_TARGET_NAME = $(OUTPUT_NAME)
