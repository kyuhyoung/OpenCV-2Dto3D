rm -f transform genmatrix
vi -p genmatrix.cpp transform.cpp intrinsics.yml pointssets.yml README.md .x
[ -d build/ ] || {
	mkdir build && pushd build &> /dev/null
	cmake ..
	popd &> /dev/null
}
pushd build &> /dev/null
make
cp genmatrix transform ..
popd &> /dev/null
./genmatrix
./transform
./transform   0   0 2> /dev/null
./transform 100  50 2> /dev/null
./transform 200 100 2> /dev/null
./transform 400 200 2> /dev/null
./transform 800 400 2> /dev/null
