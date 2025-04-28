
BUILD_DIR=build
FILE_NAME=xcapka06_xjanou24_xlepes00_xstranj00

#Define by OS
ifeq ($(OS),Windows_NT)
    RM=del /q /s
    RMDIR=rmdir /s /q
    MKDIR=mkdir
    COPY=copy
    REMOVE_DIR=@if exist $(BUILD_DIR) ($(RMDIR) $(BUILD_DIR)) \
               if exist ../$(FILE_NAME).zip ( del /q ../$(FILE_NAME).zip )
else
    RM=rm -f
    RMDIR=rm -rf
    MKDIR=mkdir -p
    COPY=cp
    REMOVE_DIR=@if [ -d $(BUILD_DIR) ]; then $(RMDIR) $(BUILD_DIR); fi; \
               if [ -f ../$(FILE_NAME).zip ]; then rm -f ../$(FILE_NAME).zip; fi
endif

.PHONY: all clean run pack test doc stddev

#Compile all files
all:
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
	#TODO

	@cp -r ../.git ../pack/repo/.git
	@cp -r ../* ../pack/repo/

	cd ../pack && zip -r ../$(FILE_NAME).zip *

	@$(RMDIR) ../pack_temp

#Run tests
test: all
	cd $(BUILD_DIR) && ctest

#Create documentation
doc:
	doxygen Doxyfile

#Compile stddev
stddev:
	@$(MKDIR) $(BUILD_DIR)
	@g++ -pg -O2 -o $(BUILD_DIR)/stddev stddev.cpp

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
