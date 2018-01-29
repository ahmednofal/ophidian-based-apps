################################################################################
#   This shell script is used to compile and install dependencies of the 
# Ophidian library
################################################################################

# Make shell stop at any command that not return 0
set -e

# Fetch git submodules
git submodule update --init --recursive

# Get script directory
CURRENT_DIR=$(pwd)
SCRIPT=$(readlink -f "$0")
SOURCE_ROOT=$(dirname "$SCRIPT")

# Set default Dependencies Root
DEPENDENCIES_ROOT=$SOURCE_ROOT/dependencies

# Check if user wants to install elsewhere
AUX=$2
if [ $1 = "--install_to" && ${AUX:0:1} != "/" ]; then
    DEPENDENCIES_ROOT=$CURRENT_DIR/$2
fi
if [ $1 = "--install_to" && ${AUX:0:1} = "/" ]; then
    DEPENDENCIES_ROOT=$2
fi

# Useful variables
DEPENDENCIES_BIN_PATH=$DEPENDENCIES_ROOT/bin
DEPENDENCIES_LIB_PATH=$DEPENDENCIES_ROOT/lib
DEPENDENCIES_INCLUDE_PATH=$DEPENDENCIES_ROOT/include
DEPENDENCIES_SHARE_PATH=$DEPENDENCIES_ROOT/share

# isntall dependencies directory
echo "Install dependencies to: ${DEPENDENCIES_ROOT}"
while true; do
    read -p "Do you wish to continue? (y/n):  " yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "Please answer y (yes) or n (no).";;
    esac
done

# This calls the build_dependencies of ophidian
install_hook(){
    PARENT_SCRIPT=$SOURCE_ROOT/3rdparty/ophidian/build_dependencies.sh
    echo "y" | sh ${PARENT_SCRIPT} --install_to ${DEPENDENCIES_ROOT}
}

install_ophidian(){
    cd $SOURCE_ROOT/3rdparty/ophidian
    mkdir build && cd build
    cmake -DCMAKE_PREFIX_PATH=${DEPENDENCIES_ROOT} -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="" ..
    make DESTDIR=${DEPENDENCIES_ROOT} install
    cd .. && rm -rf build
}

run_install(){
    install -d $DEPENDENCIES_ROOT
    install -d $DEPENDENCIES_BIN_PATH
    install -d $DEPENDENCIES_LIB_PATH
    install -d $DEPENDENCIES_INCLUDE_PATH

    install_hook
    install_ophidian
}

run_install
