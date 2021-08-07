#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"


function buildit()
{
  if [ ! -d "$DIR/$1/build" ]; then
    mkdir "$DIR/$1/build"
  fi
  cd "$DIR/$1/build"

  # To get the rootfs which is required here, use:
  # rsync -rl --delete-after --safe-links pi@192.168.1.PI:/{lib,usr} $HOME/rpi/rootfs

  cmake "$DIR/$1"
  cmake --build . --config RelWithDebInfo -j$(nproc)
}

if [ $# == 1 ]; then # 如果只有輸入一個參數(編譯檔案)
  if [ -d $1 ]; then # 如果檔案存在
    OBJ=$1
    buildit $OBJ
  else
    echo "file no found"
    exit 1
  fi
elif [ $# == 0 ]; then # 如果沒有指定要編譯資料夾，則底下的資料夾都編譯
  OBJ=$(ls -p |grep -v build/ -v | grep /)
  for i in ${OBJ}
  do
    buildit $i
  done
else
  echo 'too much argument' 
fi
