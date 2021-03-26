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
		<summary>--project_folder</summary>
			&ensp;&ensp;&ensp;&ensp;---boards<br>
			&ensp;&ensp;&ensp;&ensp;---src<br>
			&ensp;&ensp;&ensp;&ensp;---proj.conf<br>
			&ensp;&ensp;&ensp;&ensp;---CMakeLists.txt
		</details>
- Overlay will overwrite the DT file
- Hence we can change the board configurations locally for each project using this method