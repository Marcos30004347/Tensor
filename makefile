all:
	g++ -O3 main.cpp -march=native
wasm:	
	emcc ./main.cpp -march=native -msse -msse2 -msse3 -msimd128