#Virtual Machine Sandbox

This project is meant to serve as a virtual machine, compiler and optimisation testbed for prototyping ideas in the future.
It will also be useful as reference for anybody looking into simple parsers, virtual machine construction or assembly generation.

CoreASM depends on CoreVM and Regex-Parser (https://github.com/mmjack/Regex-Parser).

To install the project -
First ensure you have Regex-Parser (https://github.com/mmjack/Regex-Parser) installed.
Then execute install.sh from the root directory to build all other dependancies.

Any build after (To verify changes) can be done either using install.sh or with the make command from the root directory (Note: The make command will not install libraries so any changes to a dependancy will not reflect in an application until make install is executed).
