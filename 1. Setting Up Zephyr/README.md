# Getting Started Guide
- Follow this guide to:
	Set up a command-line Zephyr development environment on Ubuntu

## Step 1: Install Dependencies
Use **apt** to install dependencies

1. Open a terminal and enter the following:
```
sudo apt install --no-install-recommends git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev
```

2. Verify cmake version is above **3.13.1** by entering the following command
```
cmake --version
```
If found a lower version update it.

## Step 2: Get Zephyr and install Python dependencies
1. Install **west**. west is Zephyrs meta-tool. 
`pip3 install --user -U west`
3. Make sure environment variables are set correctly
```
echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
source ~/.bashrc
```
4. Get zephyr source code:
```
west init ~/zephyrproject
cd ~/zephyrproject
west update
```

5. Export a Zephyr CMake package. This allows CMake to automatically load boilerplate code required for building Zephyr applications.
```
west zephyr-export
```

6. Zephyr’s scripts/requirements.txt file declares additional Python dependencies. Install them with pip3.

```
pip3 install --user -r ~/zephyrproject/zephyr/scripts/requirements.txt
```

## Step 3 install Toolchain
1. Goto nordic semi official website and download **nRF Command Line Tools**.
2. Extract the .tar.gz file to a folder.
3. Install NRFTools with deb package:
```
sudo dpkg -i --force-overwrite nRF-Command-Line-Tools_10_12_1_Linux-amd64.deb
```
