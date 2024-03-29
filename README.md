<!-- markdownlint-disable-next-line -->
<p align="center">
  <a href="#" rel="noopener" target="_blank"><img width="150" src="/Resources/Icon128.png" alt="IniParser logo"></a>
</p>

<h1 align="center">IniParser [Unreal Engine]</h1>

<div align="center">

*Read/Write an .Ini file the unreal way!*
  
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/mrrobinofficial/unreal-iniparser/blob/HEAD/LICENSE.txt)
![plugin-status](https://img.shields.io/badge/plugin_status-ready_to_use-green)
![maintenance-status](https://img.shields.io/badge/maintenance-passively--maintained-yellowgreen.svg)

</div>

#

## ⚙️ Supported Platforms
This plug-in was last built against Unreal Engine 5.1. It should work on all platforms, since it made with raw c++ code and basic Unreal Engine features.

## ⚒️ Installation

You can install from the <a href="https://github.com/MrRobinOfficial/Unreal-IniParser/releases/latest">release section</a>.

Alternatively, you can install this plugin via terminal with [*git*](https://git-scm.com/). **Here is the command for installing it**.

```console
git clone git@github.com:MrRobinOfficial/Unreal-IniParser.git IniParser
```

#

<details open> 
    <summary><h2>🖼️ Screenshots</h2></summary>
    <img src="Resources/Screenshot_01.png" alt="Overview of Blueprint nodes from .Ini Library">
    <img src="Resources/Screenshot_02.png" alt="Creating .ini data via Blueprint Editor">
    <img src="Resources/Screenshot_03.png" alt="Write .ini data into a file">
    <img src="Resources/Screenshot_04.png" alt="Output text from .ini data that was written">
    <img src="Resources/Screenshot_05.png" alt="Parse .ini data structure from a file path">
</details>

#

## 📝 Quick guide

This plugin is parsing system for file type `.ini`. You can  <a href="https://en.wikipedia.org/wiki/INI">read more</a> about `.ini` file system.

From the `IniLibrary` (Blueprint Function Library class), you have a couple functions to use:

* Mainly: `ParseIniFromString(FString String)`, `ParseIniFromFile(FString FilePath)` and `ParseIniToString(const FIniData& Data)` for C++ users.
* And for Blueprint users, it's: "*Parse .Ini From String*", "*Parse .Ini From File*" and "*Parse .Ini To String*".
* Use `ReadIniFromFile` and `WriteIniToFile` for reading and writing to a specific file.

This `.ini` parsing system support:

* Sections and properties, names are case-insensitive.
* Data container (`FIniData`) support for global comments and properties. Meaning, comments/properties is defined under a section.
* Property support values with double quote and apostrophe.

## 🆘 Support
If you have any questions or issue, just write either to my [YouTube channel](https://www.youtube.com/@mrrobinofficial), [Email](mailto:mrrobin123mail@gmail.com) or [Twitter DM](https://twitter.com/MrRobinOfficial).

## 🔗 References
- [Introduction to Unreal Engine Plugins](https://docs.unrealengine.com/5.0/en-US/plugins-in-unreal-engine/)
- [Introduction to .ini file format](https://en.wikipedia.org/wiki/INI_file)
