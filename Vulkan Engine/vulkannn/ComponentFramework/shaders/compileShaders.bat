@echo off
rem "rem" means remark Microsoft's comment in a .bat file - gross.
rem .bat files are the worst form of scripting ever created by our human species.
rem I hate pretty much everthing Microsoft has ever done but bat files are the worst ever.
rem Unix, developed at the University California Berkley and later perfected at AT&T Bell labs, 
rem created real shell scripting language(s). Meanwhile, Microsoft floundered in it own stupidity in 
rem it's early days only to claim world dominance as the best amature crap on our earth. 
rem "Let's give it a go," as Umer would say - he's too nice. 

rem drag and drop a file will set %1 to the name of the file
set filename=%1

rem the next line will remove the quotation marks from the file name
set filename=%filename:"=%

rem append the '.spv' suffix on the compiled glsl output file
set output=%filename%.spv
echo Compiling: %filename%

rem if the old output file exists delete it. 
if exist %output% ( del %output% )
rem get the path to your install version of Vulkan
glslc.exe -c "%filename%" -o "%output%"
echo Created spv file: %output%
pause
