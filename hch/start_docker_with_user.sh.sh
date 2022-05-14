#!/bin/bash -xe

VER="v2"
IMAGE="iamge_name:${VER}"
CONTAINER_NAME=${USER}.for_dev.${VER}

MOUNT_DIR=/data/${USER}
if [ ! -z "$1" ]; then
  MOUNT_DIR=$1
fi

GROUP=`id -g -n | sed 's/ /%20/g'`
GROUPID=`id -g`
OLD_ID=`docker ps -aq -f name=$CONTAINER_NAME -f status=running`

if [ -z "$OLD_ID" ]; then
  # Attention: add "--gpus all' to load GPU Driver
  ID=`docker run --privileged --gpus all --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -t -d --name $CONTAINER_NAME -v $MOUNT_DIR:/host --tmpfs /tmp:exec --rm $IMAGE `
  docker exec --user root $ID groupadd -f -g $GROUPID ${GROUP}
  docker exec --user root $ID adduser --shell /bin/bash --uid $UID --gecos '' --ingroup ${GROUP} --disabled-password --force-badname --home /home/${USER} ${USER}
  docker exec --user root $ID bash -c "echo ${USER} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USER} && chmod 0440 /etc/sudoers.d/${USER}"

  if [ -f ~/.ssh/authorized_keys ]; then
    docker cp ~/.ssh/authorized_keys $ID:/home/${USER}/.ssh
  fi
  if [ -f ~/.ssh/config ]; then
    docker cp ~/.ssh/config $ID:/home/${USER}/.ssh
  fi
  if [ -f ~/.ssh/id_rsa.pub ]; then
    docker cp ~/.ssh/id_rsa.pub $ID:/home/${USER}/.ssh
  fi
  if [ -f ~/.ssh/id_rsa ]; then
    docker cp ~/.ssh/id_rsa $ID:/home/${USER}/.ssh
  fi

  GIT_USER=`git config --get user.name`
  GIT_EMAIL=`git config --get user.email`
  docker exec --user ${USER} $ID bash -c "git config --global user.name \"$GIT_USER\""
  docker exec --user ${USER} $ID bash -c "git config --global user.email \"$GIT_EMAIL\""
fi

docker exec -it --user ${USER} $CONTAINER_NAME bash

# login as root
# docker exec -it --user root $CONTAINER_NAME bash