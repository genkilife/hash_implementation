include makefile.inc

all: basicHash.o

#$(BINDIR)/$(TARGET): $(OBJECTS)
#    @$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
#    @echo "Linking complete!"

# c file dependencies
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# test object files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp $(INCLUDEROOT)/$(wildcard *.h)
	@$(CXX) $(CPPFLAGS) -c $< -o $@
	@echo "Compiled "$<"!"

# binary dependencies
$(BINDIR)/%: $(OBJDIR)/%.o $(OBJECTS)
	@$(CXX) $(OBJECTS) $< $(LFLAGS) -o $@
	@echo "Link "$<"!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*
	@$(rm) $(BINDIR)/*
	@echo "Cleanup complete!"
