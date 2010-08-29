# C/C++ compiler
CC		?= gcc
CXX		?= g++

# Directories
INCDIRS		=
LIBDIRS		=

# Includes/Libraries
INCLUDE		= $(foreach dir, $(INCDIRS), -I$(dir))
LIBS		= $(foreach dir, $(LIBDIRS), -L$(dir))

# C/C++ flags
CFLAGS		= -O2 -Wall -std=c99 $(INCLUDE)
CXXFLAGS	= -O2 -Wall $(INCLUDE)

# Linker flags
LDFLAGS		= $(LIBS) -lpthread

# Objects
OBJS	= \
	client.o	\
	error_page.o	\
	file.o		\
	header.o	\
	http.o		\
	log.o		\
	server.o	\
	socket.o	\
	thread.o	\
	main.o

# Executable target
TARGET	= httpd


# Compile target
$(TARGET): $(OBJS)
	@echo -e "   LD\t$(notdir $(TARGET))"
	@$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile objects
%.o: %.c
	@echo -e "   CC\t$(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo -e "   CXX\t$(notdir $<)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean data
clean:
	@echo -e "Cleaning..."
	@rm -f *.o $(TARGET)
