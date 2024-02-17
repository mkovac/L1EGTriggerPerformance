#makefile

CC = g++ -std=c++17
UCFLAGS = -g -O3 -Wall -Wextra
RUCFLAGS := $(root-config --cflags) -I${ROOFITSYS}/include/ -I./include/

LIBS :=  $(root-config --libs) -lTreePlayer -lGpad -lHist -lRIO -lCore -L${ROOFITSYS}/lib/ -lRooFit  -lRooFitCore ./obj/FuncCB_cpp.so
GLIBS := $(root-config --glibs)


VPATH = ./src/

SRC = main.cpp\
      TurnonFit.cpp\
      TurnonManager.cpp\
      Utilities.cpp\


INCLUDES = TurnonFit.h\
           TurnonManager.h\
           Utilities.h\
    
    
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))


all: run_fitter


obj/%.o: %.cpp
	@echo "==> Compiling $*"
	@mkdir -p obj/
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@
   

run_fitter: $(OBJ)
	@echo "==> Linking..."
	@$(CC) $^ $(LIBS) $(GLIBS) -o $@


clean:
	@echo "==> Cleaning objects and executable"
	@rm -f obj/*.o
	@rm -f run_fitter


uninstall:
	@echo "==> Uninstalling fitter"
	@rm -f obj/*.o obj/*.so obj/*.d obj/*.pcm
	@rm -f ext/*.so ext/*.d ext/*.pcm
	@rm -f run_fitter


# $@ references the target file name
# $^ references all of the prerequisite files as a space-separated list
# patsubst function in a makefile is used to perform pattern substitution on a list of strings
# VPATH variable can be used to specify a list of directories where make should look for prerequisite files that are not found in the current directory