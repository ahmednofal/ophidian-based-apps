# Ophidian Project Template
This is a template for starting projects using ophidian.

## Build status:
Master: [![pipeline status](https://gitlab.com/eclufsc/ophidian_project_template/badges/master/pipeline.svg)](https://gitlab.com/eclufsc/ophidian_project_template/commits/master)

# Compiling:
This will teach you how to compile an ophidian project

## Prerequisites:
* Cmake (>= 3.5.2)
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

> **If you do not have permissions** to install ophidian to your system or **if you want to compile ophidian** and its dependencies at source root.
> Make shure you have all [software dependencies](https://gitlab.com/eclufsc/ophidian/tree/build_system#prerequisites), then run:
> ```
> $ bash build_dependencies.sh
> ```
> Now ophidian is installed to `"ophidian_project_templatesource_root"/dependencies`

# Starting your repository
Either fork this repository or pull ophidian_project_template files to a new project using remote repositories as follows:

```
git init
git remote add ophidian_template git@gitlab.com:eclufsc/ophidian_project_template
git pull ophidian_template master
git remote add origin "your.repository.url"
git push origin master
```
