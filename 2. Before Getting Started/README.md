# Before Getting Started
- Follow this guide to:
	Get an understanding of key concepts before diving into zephyr programming

## 1. Device Tree

- In zephyr hardware configuration **should be** done inside device tree(DT)
- This ensures code portability
- DTs are board specific files and can be found in the path `Zephyr\zephyr\boards\arm\nrf52840dk_nrf52840`
- The file with DTS extension is the file we are looking for
- Editing DT in this way will change the board configuration globally hence directly editing this file is not appreciated
- Use **overlays** instead

## 2. Overlays

- Overlay can be defined in the following way:
	1. Create a `boards` folder inside project folder
	2. Inside it create `nrf52840dk_nrf52840.overlay` file
	3. The resulting folder structure will look like:
		<details>
		<summary>project_folder</summary>
			&ensp;&ensp;&ensp;&ensp;-- boards<br>
			&ensp;&ensp;&ensp;&ensp;-- src<br>
			&ensp;&ensp;&ensp;&ensp;-- proj.conf<br>
			&ensp;&ensp;&ensp;&ensp;-- CMakeLists.txt
		</details>
- Overlay will overwrite the DT file
- Hence we can change the board configurations locally for each project using this method

## 3. Kconfig
- Used to set global build configurations\
e.g:- Select device drivers like gpio drivers,i2c,spi etc
- Kconfig is accesed using the following code:
```
west build -t guiconfig
```

## 4. Proj.conf
- Used to set build configurations locally
- Overwrites Kconfig file for specific projects
- `proj.conf' will be present in the project folder

## 5. Using Visual Studio Code
1. Visual Studio Code (VSC) couple with **west** is a powerful tool for code editing
2. **west** is a command line tool and can be used using VSCs terminal
3. Inside VSC open a terminal (press `ctrl+shift+\``)
4. In terminal "select default shell" as command prompt
5. Do [step 4 of setting up zephyr](https://github.com/Nafih-SA/Complete-Zephyr-Tutorial/tree/master/1.%20Setting%20Up%20Zephyr#step-4-set-environment-variables) if you havn't set before
6. Now you are good to start using west

## 4. west Commands
### #Build application
```
west build -p auto -b nrf52840dk_nrf52840 <path/to_project>
```
&ensp;&ensp;e.g:- `west build -p auto -b nrf52840dk_nrf52840 samples\hello_world`
- Parameter **-p** can also have values `always` and `never` to rebuild or just build the application respectively (i.e., `west build -p always ...`)
- Parameter **-b** stands for boards
- Use the following commands to show the list of supported boards
```
west boards
```
### #Flash application
```
west flash
```
In case we are having multiple build files west can be coupled with **-t** parameter to target specific build file
```
west flash -t <path\to_build_file>
```
### #Clean build files
```
west build -t clean
```
### #Open Kconfig
```
west build -t guiconfig
```
### #Open serial monitor
```
python -m serial.tools.miniterm --raw COM12 115200
```
&ensp;&ensp;Change COM12 to your port and 115200 to your baud rate

&ensp;&ensp;Type the above code in the same cmd.exe or more preferably split cmd.exe and enter it