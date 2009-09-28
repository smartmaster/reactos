<?xml version="1.0"?>
<!DOCTYPE module SYSTEM "../../../tools/rbuild/project.dtd">
<group>
<module name="shell32_winetest" type="win32cui" installbase="bin" installname="shell32_winetest.exe" allowwarnings="true">
	<include base="shell32_winetest">.</include>
	<define name="__ROS_LONG64__" />
	<redefine name="_WIN32_WINNT">0x0501</redefine>
	<library>wine</library>
	<library>shell32</library>
	<library>ole32</library>
	<library>oleaut32</library>
	<library>shlwapi</library>
	<library>user32</library>
	<library>gdi32</library>
	<library>advapi32</library>
	<library>kernel32</library>
	<library>uuid</library>
	<library>ntdll</library>
	<file>appbar.c</file>
	<file>autocomplete.c</file>
	<file>generated.c</file>
	<file>shelllink.c</file>
	<file>shellpath.c</file>
	<file>shlexec.c</file>
	<file>shlfileop.c</file>
	<file>shlfolder.c</file>
	<file>string.c</file>
	<file>systray.c</file>
	<file>testlist.c</file>
	<file>shfldr_netplaces.c</file>
	<file>shfldr_special.c</file>
	<file>rsrc.rc</file>
</module>
</group>
