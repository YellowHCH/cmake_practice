ninja 构建工具的安装和使用tips

sudo apt-get install ninja-build
# 没有从源码去编译 ref https://blog.csdn.net/qiuguolu1108/article/details/103842556

#gn安装 apt下载不到，选择从源码去编译。编译依赖clang，需先install clang
git clone --depth 1 https://github.com/o-lim/generate-ninja.git
cd generate-ninja
# 配置构建
python3 build/gen.py
# 编译到out
ninja -C out
# 设置软链
ln /path/to/out/gn /usr/bin/gn

