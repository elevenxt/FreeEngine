########################################################################################
 INCLUDE_DIR  = ../otherlib/include
# SOURCE_DIR   = 
#
# EXCLUDE      = A*.cpp
#
 COMPILEFLAGS = -Wall 
#
#
 TARGET       = libut.a
#
# include liba.mk
#
# # clean:
# # rebuild:
########################################################################################

GCC     = gcc
G++     = g++
AR      = ar -ruv
RANLIB  = ranlib
MKDIR   = mkdir -p
REMOVE  = rm -f
SLEEP   = sleep 1

_SRCS   = $(wildcard *.c) $(wildcard *.cpp)
ifneq ($(SOURCE_DIR),)
	_SRCS  += $(wildcard $(addsuffix /*.c,$(SOURCE_DIR))) $(wildcard $(addsuffix /*.cpp,$(SOURCE_DIR)))
endif
SRCS    = $(filter-out $(wildcard $(EXCLUDE)), $(_SRCS) )
OBJS    = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
DEPS    = $(patsubst %.o,%.d,$(OBJS))

ifneq ("","$(release)")
COMPILEFLAGS   += -O3 -g
else
COMPILEFLAGS   += -D_DEBUG -g 
endif

ifneq ("","$(gprof)")
COMPILEFLAGS   += -pg 
endif

CPPFLAGS  = -I. $(addprefix -I,$(INCLUDE_DIR)) $(COMPILEFLAGS) -MMD
LFLAGS    = -L. $(addprefix -L,$(LIBS_DIR)) $(addprefix -l,$(LIBS))

.PHONY : deps objs all clean rebuild
all  : $(TARGET)
deps : $(DEPS)
objs : $(OBJS)

*.cpp.o:
	$(G++) $(CPPFLAGS) -o Debug/$@ -c $<
*.c.o:
	$(GCC) $(CPPFLAGS) -o Debug/$@ -c $<
	
$(TARGET):$(OBJS)
	mkdir -p `dirname $(TARGET)`
	$(AR) $@ $(OBJS)
	$(RANLIB) $@
	@$(SLEEP)

clean: 
	$(REMOVE) $(OBJS)
	$(REMOVE) $(DEPS)
	$(REMOVE) $(TARGET)
	
rebuild: clean $(TARGET)

-include $(DEPS)

