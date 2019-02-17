rm -f transform genmatrix simpletfx exercises
[ -d build/ ] || {
	mkdir build && pushd build &> /dev/null
	cmake ..
	popd &> /dev/null
}
pushd build &> /dev/null
make -j8
cp genmatrix transform simpletfx exercises ..
popd &> /dev/null
#./genmatrix
#./transform
#./transform 400  80 2> /dev/null
#./transform 800 100 2> /dev/null
#./transform 200 200 2> /dev/null
#./transform 400 400 2> /dev/null
./exercises 300 190
