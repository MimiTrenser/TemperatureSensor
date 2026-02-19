CC       = gcc
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
CFLAGS   = -DUNIT_TEST --coverage -Iinclude -I.
LDFLAGS  = -fprofile-arcs -ftest-coverage

TESTOBJ  = temperatureSensor.o evaluateData.o logError.o
OUTDIR   = gtest

# Executables for HLTC and LLTC
TARGETS  = $(OUTDIR)/hltc_temperatureSensor_test $(OUTDIR)/lltc_temperatureSensor_test

.PHONY: all clean

# Compile C sources into OUTDIR
$(OUTDIR)/%.o: ../../source/TemperatureSensor/%.c
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ test sources into OUTDIR
$(OUTDIR)/%.o: %.cpp
	mkdir -p $(OUTDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Build HLTC test executable
$(OUTDIR)/hltc_temperatureSensor_test: $(OUTDIR)/hltc_temperatureSensor.o $(addprefix $(OUTDIR)/,$(TESTOBJ))
	$(CXX) $^ $(CXXFLAGS) -o $@

# Build LLTC test executable
$(OUTDIR)/lltc_temperatureSensor_test: $(OUTDIR)/lltc_temperatureSensor.o $(addprefix $(OUTDIR)/,$(TESTOBJ))
	$(CXX) $^ $(CXXFLAGS) -o $@

# Build, run both, and generate unified coverage report
all: $(TARGETS)

test: all
	@echo "Running HLTC and LLTC tests..."
	for t in $(TARGETS); do ./$$t; done
	@echo "Capturing coverage..."
	# Capture from  both executables
	lcov --capture --directory $(OUTDIR) --directory ../../source/TemperatureSensor --output-file $(OUTDIR)/coverage.info
	# Filter out unwanted files
	lcov --remove $(OUTDIR)/coverage.info '/usr/*' '*/gtest/*' '*/c++/*' --output-file $(OUTDIR)/coverage.info
	# Generate HTML report
	genhtml $(OUTDIR)/coverage.info --output-directory $(OUTDIR)/coverage_html
	@echo "Combined coverage report ready at $(OUTDIR)/coverage_html/index.html"

clean:
	rm -rf $(OUTDIR)
