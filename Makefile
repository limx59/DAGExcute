# 编译器和编译选项
CC = g++
CFLAGS = -std=c++11 -Wall

# 可执行文件的名称
TARGET = DAGTest

# 源代码文件
SRCS = src/main.cpp src/DAGexcute.cpp

# 头文件
INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR)

# 链接库文件（如果有）
LIBS = -L/home/limx59/DAGTest/libs -lYourLibrary

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)


# 测试目标
test:
	./$(TARGET)

# 清理生成的文件
clean:
	rm -f $(TARGET)
