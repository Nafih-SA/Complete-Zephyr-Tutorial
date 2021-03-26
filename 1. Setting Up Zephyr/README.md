# Getting Started Guide
- Follow this guide to:
	Set up a command-line Zephyr development environment on Windows

## Step 1: Install Dependencies
 \
1. Install python:\
[Cick Here](https://www.python.org/downloads/) to goto python download page. Download and install python.

2. Install west:
```
pip3 install west
```
3. Get the Zephyr source code:
```
cd %HOMEPATH%
west init zephyrproject
cd zephyrproject
west update
```
4. Export a Zephyr CMake package. This allows CMake to automatically load boilerplate code required for building Zephyr applications.
```
west zephyr-export
```
5. Zephyr’s scripts/requirements.txt file declares additional Python dependencies. Install them with pip3.
```
pip3 install -r %HOMEPATH%\zephyrproject\zephyr\scripts\requirements.txt
```

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
