# g++ -std=c++11 ./main.cpp -o ./main && ./main < ./inputs/randValues.txt
# g++ -std=c++11 ./main.cpp -o ./main && ./main < ./inputs/size8.txt
cd build
cmake ..
make
./BLOCKARRAY
cd ..