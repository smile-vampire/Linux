CC=gcc -g

# add.c sub.c test.h
#  wildcard : add.c sub.c ,只将当前目录的素有.c文件过滤出来
SRCS=$(wildcard *.c)
 #add.c sub.c   =>   add.o sub.o
OBJS=$(SRCS:.c=.o)
 #add.c sub.c   =>   add.d sub.d
DEPS=$(SRCS:.c=.d)

 #生成可执行程序的位置
# addprefix 添加前缀 main -> /root/framework/main
BIN := $(addprefix $(BUILD_ROOT)/, $(BIN))
#生成.o文件的路径
LINK_OBJ_DIR=$(BUILD_ROOT)/link_obj

DEP_DIR=$(BUILD_ROOT)/dep
# 临时目录，创建.o和.d文件的目录
$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))
# main.o => /root/framework/link_obj/main.o
OBJS:=$(addprefix $(LINK_OBJ_DIR)/, $(OBJS))
DEPS:=$(addprefix $(DEP_DIR)/, $(DEPS))

LINK_OBJ=$(wildcard $(LINK_OBJ_DIR)/*.o)
LINK_OBJ += $(OBJS)

all: $(DEPS) $(OBJS) $(BIN)

$(BIN) : $(LINK_OBJ)
		$(CC) -o $@ $^

$(LINK_OBJ_DIR)/%.o : %.c
	$(CC) -c $^ -o $@ -I$(INCLUDE_PATH)

$(DEP_DIR)/%.d : %.c
	 			echo -n $(LINK_OBJ_DIR)/ > $@
				$(CC) -I$(INCLUDE_PATH) -MM $^ >> $@

