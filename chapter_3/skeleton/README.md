Skeleton application as described in the book.
This sample create a winapi window and display skeletons randomly.
Compared to chapter 2 : a game engine has been created.

Using vscode/cmakelist & mscvc to manage project.


## Resources : 
Icons were created with paint as png then converted with imagemagick tool using "convert_png_to_ico.bat".
imagemagick tool can be installed with chocolatey
Gimp can also be used for the conversion.

## Pre-requesites : 
- Install SDK for windows with visual studio installer 
- your code editor (vscode) with C/C++ extension and cmake build tool

## Build instruction : 
- Launch "developper command prompt" from window menu & call code from there.
- Open the skeleton folder.
- call shift+ctrl+p and then type : cmake:configure & cmake:build.
- you can also use the vscode bottom bar or build.bat

## Running from cli : 
- Launch "developper command prompt" from window menu & call code from there.


## TODO : 
- use nmake/make instead those bat files
- support mingw as MSVC.

## NOTE : 

There are some improvments to be made to this code structure, but the aim so far was to stay consistent with the code.  
Some fix were added to support WIN64 arch, and loading icon since there was an issue in the book listing.
