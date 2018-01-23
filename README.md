# ophidian_project_template
This is a template for starting projects using ophidian.

## Build status
Master [![pipeline status](https://gitlab.com/eclufsc/ophidian_project_template/badges/master/pipeline.svg)](https://gitlab.com/eclufsc/ophidian_project_template/commits/master)

## Compiling
First make shure you have installed a version of the [ophidian library](https://gitlab.com/eclufsc/ophidian).
Then run:
```
git clone https://gitlab.com/eclufsc/ophidian_project_template hello_world
cd hello_world
mkdir build
cd build
cmake ..
make
./hello_world ../input_files/simple/simple.v ../input_files/simple/simple.def ../input_files/simple/simple.lef
```

## Start a new project
Just start a new repositiory, pull the files from this repository, then push it to yours!
```
git init
git remote add ophidian_project git@gitlab.com:eclufsc/ophidian_project_template
git pull ophidian_project master
git remote add "your repo" "your.repo.url"
git push "your repo" master
```
