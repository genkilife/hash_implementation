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
$(OBJDIR)/test_basicHash_01.o: $(TESTDIR)/test_basicHash_01.cpp $(INCLUDEROOT)/BasicHash.h
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/test_linearHash_01.o: $(TESTDIR)/test_linearHash_01.cpp $(INCLUDEROOT)/LinearHash.h
	@$(CXX) $(CPPFLAGS) -c $< -o $@

# binary dependencies
$(BINDIR)/test_basicHash_01: $(OBJDIR)/test_basicHash_01.o $(OBJECTS)
	@$(CXX) $(OBJECTS) $(OBJDIR)/test_basicHash_01.o $(LFLAGS) -o $@
	@echo "Link "$<"!"

$(BINDIR)/test_linearHash_01: $(OBJDIR)/test_linearHash_01.o $(OBJECTS)
	@$(CXX) $(OBJECTS) $(OBJDIR)/test_linearHash_01.o $(LFLAGS) -o $@
	@echo "Link "$<"!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*
	@echo "Cleanup complete!"
