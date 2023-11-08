################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
#OUTPUT_NAME = $(notdir $(shell pwd))
PROJ_PATH = .
LWIP=$(PROJ_PATH)/../../../../lwip/src

COPT += -DNO_SYS=1

SRC  = $(PROJ_PATH)/.
SRC += $(PROJ_PATH)/i
SRC += $(LWIP)/core
SRC += $(LWIP)/core/ipv4
xSRC += $(LWIP)/core/ipv6
SRC += $(LWIP)/netif
xSRC += $(LWIP)/netif/ppp
xSRC += $(LWIP)/netif/ppp/polarssl

INC  = -I.
INC += -I$(PROJ_PATH)/.
INC += -I$(PROJ_PATH)/x
INC += -I$(LWIP)/api
INC += -I$(LWIP)/core
INC += -I$(LWIP)/core/ipv4
xINC += -I$(LWIP)/core/ipv6
INC += -I$(LWIP)/netif
xINC += -I$(LWIP)/netif/ppp
xINC += -I$(LWIP)/netif/ppp/polarssl
INC += -I$(LWIP)/include
INC += -I$(LWIP)/include/compat
INC += -I$(LWIP)/include/compat/posix/arpa
INC += -I$(LWIP)/include/compat/posix/net
INC += -I$(LWIP)/include/compat/posix/sys
INC += -I$(LWIP)/include/compat/stdc
INC += -I$(LWIP)/include/lwip/
INC += -I$(LWIP)/include/lwip/apps
INC += -I$(LWIP)/include/lwip/priv
INC += -I$(LWIP)/include/lwip/prot
INC += -I$(LWIP)/include/netif/
xINC += -I$(LWIP)/include/netif/ppp
xINC += -I$(LWIP)/include/netif/ppp/polarssl

xxLIB += -L$(TOOLCHAIN_LIB) -lgcc_ -lpthread
xxLIB += -Xlinker --start-group
xxLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xxLIB += -Xlinker --end-group

_TARGET_NAME = $(OUTPUT_NAME)
