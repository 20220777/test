################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
#OUTPUT_NAME = $(notdir $(shell pwd))

PROJ_PATH = ./
LITE_IO_PATH = ../../lite.io
USR_PATH = ../../usr

COPT += -D__NODE__=$(NODE)

################################################################################
#                                                                              #
#                                definitions                                   #
#                                                                              #
################################################################################
COPT += -D__NHTTP__=$(NHTTP)
COPT += -D__NHTTPD__=$(NHTTPD)
COPT += -D__NHTTPSD__=$(NHTTPSD)
COPT += -D__NSERIAL__=$(NSERIAL)
COPT += -D__NWSC__=$(NWSC)
COPT += -D__NWSD__=$(NWSD)
COPT += -D__NSHM__=$(NSHM)
COPT += -D__NTCP__=$(NTCP)
COPT += -D__NTCPD__=$(NTCPD)
COPT += -D__NTCPSD__=$(NTCPSD)

################################################################################
#                                                                              #
#                              io definitions                                  #
#                                                                              #
################################################################################
COPT += -D__TRIGONOMETRIC__=1
COPT += -D__WEBSOCKET__=1
COPT += -D__HTTP__=1
COPT += -D__MIME__=1
COPT += -D__SHM__=1
COPT += -D__SERIAL__=1
COPT += -D__SOCKET__=1
COPT += -D__PACKET__=1
COPT += -D__SHA1__=1
COPT += -D__JSON__=1
COPT += -D__NIC__=0
COPT += -D__CGI__=0
COPT += -D__XML__=0
COPT += -D__DBC__=0
COPT += -D__LIST__=0
COPT += -D__QUEUE__=0
COPT += -D__STACK__=0
COPT += -D__SYSQUEUE__=0

################################################################################
#                                                                              #
#                            mtif definitions                                  #
#                                                                              #
################################################################################
COPT += -D__TRIGONOMETRIC__=1
COPT += -D__SSL_TLS__=1
COPT += -D__CUSTOM_X_SOCKET__=1
COPT += -D__CUSTOM_X_HTTP__=1
COPT += -D__CUSTOM_X_HTTPD__=1
COPT += -D__CUSTOM_X_HTTPSD__=1
COPT += -D__CUSTOM_X_WS__=1
COPT += -D__CUSTOM_X_SERIAL__=1
COPT += -D__CUSTOM_X_SIFR__=1

SRC  = .
SRC += $(PROJ_PATH)
SRC += $(PROJ_PATH)/dccf
SRC += $(PROJ_PATH)/dpcf
SRC += $(PROJ_PATH)/dzcf
SRC += $(PROJ_PATH)/i
SRC += $(PROJ_PATH)/n
SRC += $(PROJ_PATH)/z

INC  = -I.
INC += -I$(PROJ_PATH)
INC += -I$(PROJ_PATH)/dccf
INC += -I$(PROJ_PATH)/dpcf
INC += -I$(PROJ_PATH)/dzcf
INC += -I$(PROJ_PATH)/i
INC += -I$(PROJ_PATH)/n
INC += -I$(PROJ_PATH)/z
INC += -I$(PROJ_PATH)/$(LITE_IO_PATH)/$(ARCH_TYPE)

xINC += -I$(PROJ_PATH)/$(USR_PATH)/mysql/$(ARCH_TYPE)/include
INC += -I$(PROJ_PATH)/$(USR_PATH)/openssl/v1.1.1t/$(ARCH_TYPE)/include
INC += -I$(PROJ_PATH)/$(USR_PATH)/openssl/v1.1.1t/$(ARCH_TYPE)/include/openssl

ifeq ($(OUTPUT_TYPE), .a)
else
xLIB += -Xlinker --start-group
endif

#xLIB += $(USR_PATH)/mysql/$(ARCH_TYPE)/lib/libmysqlclient.a
xLIB += $(PROJ_PATH)/$(USR_PATH)/openssl/v1.1.1t/$(ARCH_TYPE)/lib/libcrypto.a
xLIB += $(PROJ_PATH)/$(USR_PATH)/openssl/v1.1.1t/$(ARCH_TYPE)/lib/libssl.a

xLIB += $(PROJ_PATH)/$(LITE_IO_PATH)/$(ARCH_TYPE)/liblite.io.a
xLIB += $(PROJ_PATH)/$(LITE_IO_PATH)/$(ARCH_TYPE)/libio.a

ifeq ($(OUTPUT_TYPE), .a)
else
xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group
endif


_TARGET_NAME = $(OUTPUT_NAME)
