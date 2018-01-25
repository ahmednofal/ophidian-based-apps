# Ophidian Project Template
This is a template for starting projects using ophidian.

## Build status:
Master: [![pipeline status](https://gitlab.com/eclufsc/ophidian_project_template/badges/master/pipeline.svg)](https://gitlab.com/eclufsc/ophidian_project_template/commits/master)

# Compiling:
This will teach you how to compile an ophidian project

## Prerequisites:
* Ophidian

Make shure you have installed a version of the [ophidian library](https://gitlab.com/eclufsc/ophidian), then run:

```
git clone https://gitlab.com/eclufsc/ophidian_project_template hello_world
cd hello_world
mkdir build
cd build
cmake ..
make
./hello_world ../input_files/simple/simple.v ../input_files/simple/simple.def ../input_files/simple/simple.lef
```

> If you do not have permissions to install the library or you simply want to compile everything inside the repository, run:
>```
>$ sh build_dependencies.sh
>```
> Now ophidian is installed to `"ophidian_project_templatesource_root"/dependencies`

# Start a new project
Just start a new repositiory, pull the files from this repository, then push it to yours!
```
git init
git remote add ophidian_project git@gitlab.com:eclufsc/ophidian_project_template
git pull ophidian_project master
git remote add "your repo" "your.repo.url"
git push "your repo" master
```
