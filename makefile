include makefile.inc

all: bin/test_chainedHash_06 bin/test_linearHash_06 bin/test_cuckooHash_06 bin/test_doubleHash_06 bin/test_chainedHash_07 bin/test_linearHash_07 bin/test_cuckooHash_07 bin/test_doubleHash_07

run:
	./bin/test_chainedHash_06
	./bin/test_linearHash_06
	./bin/test_cuckooHash_06
	./bin/test_doubleHash_06
run_collide:
	./bin/test_chainedHash_07
	./bin/test_linearHash_07
	./bin/test_cuckooHash_07
	./bin/test_doubleHash_07
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
