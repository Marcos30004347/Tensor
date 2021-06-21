cmake:
	if [ -d "./build" ]; then rm -rf ./build; fi
	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
gcc:
	g++ -O3 main.cpp -march=native
wasm:	
	emcc ./main.cpp -march=native -msse -msse2 -msse3 -msimd128