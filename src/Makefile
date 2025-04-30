
BUILD_DIR=build
FILE_NAME=xcapka06_xjanou24_xlepes00_xstranj00

#Define by OS
ifeq ($(OS),Windows_NT)
    RM=del /q /s
    RMDIR=rmdir /s /q
    MKDIR=mkdir
    REMOVE_DIR=@if exist $(BUILD_DIR) ($(RMDIR) $(BUILD_DIR)) \
			   if exist ../doc ($(RMDIR) ../doc) \
			   if exist gmon.out ($(RM) gmon.out) \
               if exist ../$(FILE_NAME).zip ( del /q ../$(FILE_NAME).zip )
else
    RM=rm -f
    RMDIR=rm -rf
    MKDIR=mkdir -p
    REMOVE_DIR=@if [ -d $(BUILD_DIR) ]; then $(RMDIR) $(BUILD_DIR); fi; \
			   if [ -d ../doc ]; then $(RMDIR) ../doc; fi; \
			   if [ -f gmon.out ]; then $(RM) gmon.out; fi; \
               if [ -f ../$(FILE_NAME).zip ]; then $(RM) ../$(FILE_NAME).zip; fi
endif

.PHONY: all clean run pack test doc stddev

#Compile all files
all: mathlib.cpp calculator.cpp helpdialog.cpp main.cpp
	@$(MKDIR) $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DBUILD_TESTS=ON .. && $(MAKE)

#Clean build and .zip files
clean:
	$(REMOVE_DIR)

#Run calculator
run:
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR)\SkibidiCalculator.exe ( \
		$(MAKE) all \
	)
	@$(BUILD_DIR)\SkibidiCalculator.exe
else
	@if [ ! -f $(BUILD_DIR)/SkibidiCalculator ]; then \
		$(MAKE) all; \
	fi
	@./$(BUILD_DIR)/SkibidiCalculator
endif
 
#Pack all files to .zip
pack: clean doc
	@$(RMDIR) ../pack || true

	@$(MKDIR) ../pack/doc
	@$(MKDIR) ../pack/install
	@$(MKDIR) ../pack/repo

	@cp -r ../doc/* ../pack/doc/

	@cp -r ../install/* ../pack/install/

	@cp -r ../.git ../pack/repo/.git
	@rsync -a --exclude=pack ../ ../pack/repo/


	cd ../pack && zip -r ../$(FILE_NAME).zip *

	@$(RMDIR) ../pack

#Run tests
test: all
	cd $(BUILD_DIR) && ctest

#Create documentation
doc:
	@$(RMDIR) ../doc
	@$(MKDIR) ../doc
	doxygen Doxyfile

#Compile stddev
stddev: stddev.cpp mathlib.cpp
	@$(MKDIR) $(BUILD_DIR)
	g++ -pg -g -o $(BUILD_DIR)/stddev stddev.cpp mathlib.cpp

#Print help
help:
	@echo "Dostupné cíle:"
	@echo "  make all      - Přeloží projekt"
	@echo "  make run      - Spustí kalkulačku"
	@echo "  make test     - Spustí testy"
	@echo "  make clean    - Smaže překladové soubory"
	@echo "  make pack     - Zabalí projekt do .zip"
	@echo "  make doc      - Vygeneruje dokumentaci"
	@echo "  make stddev   - Profiling"
	@echo "  make help     - Vypíše nápovědu"
