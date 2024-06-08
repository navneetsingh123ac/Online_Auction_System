# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Executable name
EXEC = auction_system

# Source files
SRCS = main.cpp User.cpp Auction.cpp Database.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Libraries
LIBS = -lmysqlcppconn

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

# Dependencies
main.o: main.cpp User.h Auction.h Database.h
	$(CXX) $(CXXFLAGS) -c main.cpp

User.o: User.cpp User.h Database.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Auction.o: Auction.cpp Auction.h Database.h
	$(CXX) $(CXXFLAGS) -c Auction.cpp

Database.o: Database.cpp Database.h
	$(CXX) $(CXXFLAGS) -c Database.cpp

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)
