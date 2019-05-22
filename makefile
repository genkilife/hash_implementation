include makefile.inc

all: basicHash.o

#$(BINDIR)/$(TARGET): $(OBJECTS)
#    @$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
#    @echo "Linking complete!"

# c file dependencies
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# binary dependencies
test_basic_00:  $(OBJECTS) $(TESTDIR)/test_basic_00.cpp


.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"
