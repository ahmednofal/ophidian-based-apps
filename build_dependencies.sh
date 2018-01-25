################################################################################
#   This shell script is used to compile and install dependencies of the 
# Ophidian library
################################################################################

git submodule update --init --recursive

# Absolute path to project root
PROJECT_ROOT=$(pwd)
OPHIDIAN_PATH=$PROJECT_ROOT/ophidian

cd $OPHIDIAN_PATH
sh build_dependencies.sh

mkdir $OPHIDIAN_PATH/build && cd $OPHIDIAN_PATH/build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

mv $OPHIDIAN_PATH/dependencies $PROJECT_ROOT/dependencies

cd $OPHIDIAN_PATH/build
make DESTDIR=$PROJECT_ROOT/dependencies install
