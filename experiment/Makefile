OUTPUT_DIR=exec
CPP=g++
SRC_DIR=src
CPP_FLAGS=-I src

.PHONY: experiment

all:
	make exp_simitrans
	make exp_transpose

exp_simitrans:
	$(CPP) `pkg-config --cflags --libs opencv` $(CPP_FLAGS) $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp SimTransExp.cpp;
	mv a.out $(OUTPUT_DIR)/exp_simitrans;

exp_transpose:
	$(CPP) `pkg-config --cflags --libs opencv` $(CPP_FLAGS) $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp CVtransposeExp.cpp;
	make clean
	mv a.out $(OUTPUT_DIR)/exp_transpose

clean:
	rm -f $(SRC_DIR)/*.gch;

