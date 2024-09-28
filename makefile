# 컴파일러 설정
CXX = g++
CXXFLAGS = -Wall -g -c

LIBS = -lurcu
# 타겟 파일
TARGET = droneFileDeleter

# 소스 파일
SRCS = main.cpp 


# 오브젝트 파일
OBJS = $(SRCS:.cpp=.o)


# 기본 타겟
all: $(TARGET)

# 타겟 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

# 오브젝트 파일 빌드 규칙
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린업 규칙
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean