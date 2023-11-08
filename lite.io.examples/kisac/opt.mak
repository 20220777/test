################################################################################
#                                                                              #
#                                                                              #
#                             OPTIONAL INFORMATION                             #
#                                                                              #
################################################################################
SRC  = .
SRC += src
SRC += kisa
SRC += kisa/drbg
xSRC += kisa/lea
xSRC += kisa/lea/src
SRC += kisa/lsh
SRC += kisa/lsh/source/c/no_arch/src

INC  = -I.
INC += -Iinc
INC += -Isrc
INC += -Ikisa
INC += -Ikisa/drbg
xINC += -Ikisa/lea
xINC += -Ikisa/lea/src
INC += -Ikisa/lsh
INC += -Ikisa/lsh/source/c/no_arch/include
INC += -I$(CODEX_PATH)/

xLIB += -Xlinker --start-group
xLIB += -L$(TOOLCHAIN_LIB) -ldl -lm -lgcc_s -lpthread
xLIB += -Xlinker --end-group
