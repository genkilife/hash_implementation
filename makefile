include makefile.inc

all: basicHash.o

#$(BINDIR)/$(TARGET): $(OBJECTS)
#    @$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
#    @echo "Linking complete!"

# c file dependencies
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

$(OBJDIR)/test_basicHash_01.o: $(TESTDIR)/test_basicHash_01.cpp $(INCLUDEROOT)/BasicHash.h
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# binary dependencies
$(BINDIR)/test_basicHash_01: $(OBJDIR)/test_basicHash_01.o $(OBJECTS)
	@$(CXX) $(OBJECTS) $(OBJDIR)/test_basicHash_01.o $(LFLAGS) -o $@
	@echo "Link "$<"!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*
	@echo "Cleanup complete!"
