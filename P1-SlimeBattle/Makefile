# 编译器
CXX = g++
# 编译选项
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
# 目标文件
OBJS = main.o battle.o slime.o
# 目标可执行文件名
TARGET = main

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 编译每个 .cpp 文件为 .o 文件
main.o: main.cpp battle.h slime.h
	$(CXX) $(CXXFLAGS) -c main.cpp

battle.o: battle.cpp slime.h
	$(CXX) $(CXXFLAGS) -c battle.cpp

slime.o: slime.cpp slime.h
	$(CXX) $(CXXFLAGS) -c slime.cpp

# 清除所有编译生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
