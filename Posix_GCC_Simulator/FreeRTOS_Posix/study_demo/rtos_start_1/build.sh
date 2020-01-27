#!/bin/sh

set -e

# if [ ! -n "$1" ] ;then
#     APP_VER="1.0.0"
#     echo "you have not input version default 1.0.0!"
# else
#     APP_VER=$1
#     echo "the version you input is $1"
# fi

project_path=$(cd `dirname $0`; pwd)
echo $project_path

APP_NAME="${project_path##*/}"
echo $APP_NAME

export APP_NAME

echo "start freertos demo:[$APP_NAME""_app]"

if [ ! -d "./output" ] ;then
    mkdir ./output
fi

if [ -f "./output/$APP_NAME""_app" ] ;then
    rm ./output/$APP_NAME"_app"
fi

if [ -f "./$APP_NAME""_app" ] ;then
    rm ./$APP_NAME"_app"
fi

cd ../../Debug
make clean

if [ $1 = "clean" ] ;then
    echo "clean compile"
    exit 0
fi

make -j4

# rm ../study_demo/rtos_start_1/$APP_NAME_app_v$APP_VER
cp FreeRTOS_Posix ../study_demo/$APP_NAME/$APP_NAME"_app"
cp FreeRTOS_Posix ../study_demo/$APP_NAME/output/$APP_NAME"_app"

echo ""
echo "*******************************************************************"
echo " $APP_NAME""_app"
echo "*******************************************************************"
echo "********************** Compile complete ***************************"
echo ""
echo "                       _/                          _/    _/      "
echo "    _/_/    _/_/_/          _/_/    _/    _/          _/_/_/_/   "
echo " _/_/_/_/  _/    _/  _/  _/    _/  _/    _/      _/    _/        "
echo "_/        _/    _/  _/  _/    _/  _/    _/      _/    _/         "
echo " _/_/_/  _/    _/  _/    _/_/      _/_/_/      _/      _/_/      "
echo "                  _/                  _/                         "
echo "               _/                _/_/                            "
echo ""
echo "*******************************************************************"
echo ""
