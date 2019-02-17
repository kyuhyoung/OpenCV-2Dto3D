rm -f transform genmatrix
#vi -p genmatrix.cpp transform.cpp intrinsics.yml pointssets.yml README.md .x
#vi -p intrinsics.yml pointssets.yml .x
[ -d build/ ] || {
	mkdir build && pushd build &> /dev/null
	cmake ..
	popd &> /dev/null
}
pushd build &> /dev/null
make -j8
cp genmatrix transform simpletfx ..
popd &> /dev/null
#./genmatrix
#./transform
#./transform 400  80 2> /dev/null
#./transform 800 100 2> /dev/null
#./transform 200 200 2> /dev/null
#./transform 400 400 2> /dev/null
./simpletfx
