# External Libraries

These are external libraries that are included into the project. Since git makes it hard to have repositories inside other repositories, a workaround had to be used here. Therefore the `.git` folder got renamed to `.pseudogit`. To make commits inside the subrepo the argument `--git-dir .pseudogit` has to be added.

[[Source]](https://stackoverflow.com/questions/33406739/git-treat-nested-git-repos-as-regular-file-folders)

## Used Libraries

### SSD1306

A library that controls SSD1306 based OLED displays: https://github.com/TimGoll/stm32-ssd1306
