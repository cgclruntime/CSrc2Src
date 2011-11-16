ifndef MSG_MK
MSG_MK:=yes

CURRENT_PATH := $(PROJ_PATH)msg/
SUBDIRS+=$(CURRENT_PATH)detail/ \
$(CURRENT_PATH)msgType/


TEMP_OBJS:=$(CURRENT_PATH)TMMsgBase.o

OBJS+=$(TEMP_OBJS)

DEPS+= $(TEMP_OBJS:%.o=%.d)

$(CURRENT_PATH)%.o:$(CURRENT_PATH)%.cpp
	@echo 'Building $@'
	g++ $(INCLUDES) $(DEFINES) $(COMPILE_FLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finish building $@'
	@echo ' '
endif
