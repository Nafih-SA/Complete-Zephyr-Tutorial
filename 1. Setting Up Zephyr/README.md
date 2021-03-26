# Getting Started Guide
- Follow this guide to:
	Set up a command-line Zephyr development environment on Windows

## Step 1: Install Dependencies
1. Install Chocolatey
2. Open an Administrator cmd.exe window\
Press the Windows key, type “cmd.exe”, right-click the result, and choose “Run as Administrator”.

3. Disable global confirmation to avoid having to confirm installation of individual programs:
```
choco feature enable -n allowGlobalConfirmation
```
4. Use choco to install dependencies:
```
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python git
```
Open a new **cmd.exe** window as a regular user to continue.

## Step 2: Get Zephyr and install Python dependencies
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


## Step 3 install Toolchain
1. Goto nordic semi official website and download [**nRF Command Line Tools**](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools/Download).
2. Install the nRF Command Line Tools
3. Setup 3rd Party Toolchain, GNU ARM Embedded
[Click Here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm) to goto the download page.
4. Install the toolchain in the path `C:\gnu_arm_embedded`

## Step 4 Ste Environment variables
**IMPORTANT:** This step is to be repeated every time you restart command prompt(cmd.exe window).
1. In the command prompt window enter the following command
```
set ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb && set GNUARMEMB_TOOLCHAIN_PATH=C:\gnu_arm_embedded
```