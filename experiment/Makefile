OUTPUT_DIR=bin
CPP=g++
SRC_DIR=src
CPP_FLAGS=`pkg-config --cflags --libs opencv` -I src

.PHONY: experiment

all:
	make exp_simitrans
	make exp_transpose

exp_simitrans:
	$(CPP) $(CPP_FLAGS) $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp SimTransExp.cpp;
	make clean;
	mv a.out $(OUTPUT_DIR)/exp_simitrans;

exp_transpose:
	$(CPP) $(CPP_FLAGS) $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp CVtransposeExp.cpp;
	make clean;
	mv a.out $(OUTPUT_DIR)/exp_transpose

cons_mat:
	$(CPP) $(CPP_FLAGS) $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp try_construct_mat.cpp;
	make clean;
	mv a.out $(OUTPUT_DIR)/cons_mat

clean:
	rm -f $(SRC_DIR)/*.gch;

