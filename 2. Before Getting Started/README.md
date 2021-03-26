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

## 3. Using Visual Studio Code
1. Visual Studio Code (VSC) couple with **west** is a powerful tool for code editing
2. **west** is a command line tool and can be used using VSCs terminal
3. Inside VSC open a terminal (press ` ctrl+shift+\` `)
4. In terminal "select default shell" as command prompt
5. Do [step 5 of setting up zephyr](https://github.com/Nafih-SA/Complete-Zephyr-Tutorial/tree/master/1.%20Setting%20Up%20Zephyr#step-4-set-environment-variables) if you havn't set before
6. Now you are good to start using west

## 4. Kconfig
- In west