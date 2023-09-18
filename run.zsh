# g++ -std=c++11 ./main.cpp -o ./main && ./main < ./inputs/randValues.txt
# g++ -std=c++11 ./main.cpp -o ./main && ./main < ./inputs/size8.txt
cd build
cmake ..
make

while getopts ij opt; do
    case $opt in
    i)
      ./BLOCKARRAY < ../inputs/size8.txt
      ;;
    j)
    ./BLOCKARRAY < ../inputs/randValues.txt
      ;;
    esac
done

cd ..