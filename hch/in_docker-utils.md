## docker concept
### *image*
打包的环境
### *container*
运行的镜像  
## docker cmd
### *查看本地已有的image*
`docker images` or `docker image ls`
### *拉取镜像*
`docker pull <imnage_name>`
### *查找镜像*
`docker search <image_name>`
### *删除镜像*
`docker rmi <image_name>`
### *从容器构建镜像*
`docker commit -m="<commit msg>" -a="<author_name>"  <container_id> <image_name>:version`
### *从Dockerfile构建镜像*
create Dockerfile and then `docker build xxx`
**TODO**
### *从image运行container*
`docker run -it <image_name> /bin/bash`
查看参数 `docker run --help`  
-d 运行但不进入，即后台运行  
-t 终端  
-i 交互式操作  
**TODO**  show more cmd  
ref [run/login container decent](https://github.com/YellowHCH/cmake_practice/blob/master/hch/start_docker_with_user.sh.sh)
### *查看容器*
`docker ps -a`
### *启动停止的容器*
`docker start <container_name or container_id>`
### *进入容器*
`docker attach <container_name>` 进入到运行的容器中，退出时会停止容器，**不推荐使用**
`docker exec -it <container_name> /bin/bash `
