#VM
This project is meant to serve as a virtual machine, compiler and optimisation testbed for prototyping ideas in the future.
It will also be useful as reference for anybody looking into simple parsers, virtual machine construction or assembly generation.

CoreASM depends on CoreVM and Regex-Parser (https://github.com/mmjack/Regex-Parser).

To build the project from the root directory execute

cd CoreVM
make && sudo make install
cd ../CoreASM
make && sudo make install

To compile a asm file into a Virtual machine binary execute

coreasm Path/To/AsmFile Path/To/Outfile

To execute it then type
corevm Path/To/Outfile