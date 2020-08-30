# shell是函数, /root/framework
export BUILD_ROOT=$(shell pwd)
export INCLUDE_PATH=$(BUILD_ROOT)/include

#每个需要编译的子目录
export BUILD_PATH = $(BUILD_ROOT)/src

#make -C 指定要编译哪个目录中的makefile
#all 目标, 需要遍历执行每个build_path中的makefile
all:
		@for dir in $(BUILD_PATH); \
			do \
					make -C $$dir; \
			done

clean:
		rm -rf $(BUILD_ROOT)/link_obj
		rm -rf $(BUILD_ROOT)/dep
		rm -rf main

