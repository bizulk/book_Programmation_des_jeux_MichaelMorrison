rem script to convert png to ico files :
rem need imagemagick installed (use chocolatey)

rem can define multiple icon in the same file : icon:auto-resize=32,16,8
magick.exe skeleton.png -define icon:auto-resize=32 skeleton.ico
magick.exe skeleton.png -define icon:auto-resize=16 skeleton_sm.ico