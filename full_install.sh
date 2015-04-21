#Install CoreConstraint
cd CoreConstraint
make clean && make && sudo make install
cd ../

#CoreVM depends on CoreConstraint
cd CoreVM
make clean && make && sudo make install
cd ../

#CoreASM depends on CoreVM
cd CoreASM
make clean && make && sudo make install
cd ../