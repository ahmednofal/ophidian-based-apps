################################################################################
#   This shell script is used to compile and install dependencies of the 
# Ophidian library
################################################################################

git submodule update --init --recursive

# Absolute path to project root
SCRIPT=$(readlink -f "$0")
PROJECT_ROOT=$(dirname "$SCRIPT")
OPHIDIAN_PATH=$PROJECT_ROOT/3rdparty/ophidian

# Build Ophidian's dependencies
sh $OPHIDIAN_PATH/build_dependencies.sh

# Copy dependencies to source root
cp -r $OPHIDIAN_PATH/dependencies $PROJECT_ROOT

# Build Ophidian and install it to dependencies path
mkdir $OPHIDIAN_PATH/build && cd $OPHIDIAN_PATH/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="" ..
make DESTDIR=$PROJECT_ROOT/dependencies install
cd .. && rm -rf build
