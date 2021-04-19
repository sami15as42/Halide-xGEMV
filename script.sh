read -p "Please enter the absolute path or a relative path of your Halide folder: " path
echo "Deleting ./result.txt if it exists"
sudo rm -f ./result/result.txt
echo "###############################"
echo "Compiling halide_program.cpp..."
g++ ./halide_program.cpp -g -L ${path}/bin -I ${path}/include -I ${path}/tools  -lHalide -ldl -lpthread -std=c++11 -o ./bin/halide_program
echo "###############################"
echo "Compiling c_program.c..."
gcc ./c_program.c -o ./bin/c_program
echo "###############################"
echo "Executing halide_program..."
LD_LIBRARY_PATH=${path}/bin ./bin/halide_program
echo "###############################"
echo "Executing c_program..."
./bin/c_program
echo "###############################"
