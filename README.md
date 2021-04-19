# Halide-xGEMV
This project is an implementation of xGEMV BLAS routine using C and Halide.
This routine compute the general matrix-vector multiplication of the form ```alpha*A*B + beta*C```.

##Installation of Halide in Linux
To install Halide from source, we can follow this steps:
  - ```cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra" \
  -DLLVM_TARGETS_TO_BUILD="X86;ARM;NVPTX;AArch64;Mips;Hexagon" \ 
  -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=ON \
  -DLLVM_ENABLE_EH=ON -DLLVM_ENABLE_RTTI=ON -DLLVM_BUILD_32_BITS=OFF \
  -S llvm-project/llvm -B llvm-build```
  - ``` cmake --install llvm-build --prefix llvm-install ```
  - ``` export LLVM_ROOT=$PWD/llvm-install ```
  - ``` export LLVM_CONFIG=$LLVM_ROOT/bin/llvm-config ```
  - ``` git clone https://github.com/halide/Halide.git ```
  - ``` cd Halide ```
  - ``` make -j8 ```
The file log.txt contains the log of all the text printed on terminal during the installation.

##Script execution
You have to clone this repository, then give the script file the execute permission, as below:
- ``` git clone https://github.com/sami15as42/Halide-xGEMV.git ```
- ``` cd Halide-xGEMV ```
- ``` chmod +x script.sh ```
To run the ```script.sh```, you just need to execute: ``` ./script.sh ```

If everything turns well, you should get this output:
```
Please enter the absolute path or a relative path of your Halide folder: ../Halide
Deleting ./result.txt if it exists
[sudo] Mot de passe de assenine-sami : 
###############################
Compiling halide_program.cpp...
###############################
Compiling c_program.c...
###############################
Executing halide_program...
Vector calculation with Halid program completed successfully !
Saving our result vector to ./result/result.txt...
Saving process completed successfully !
###############################
Executing c_program...
Start of the checking process...
xGEVM function implemented in Halid works correctly.
###############################
```
