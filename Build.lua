-- premake5.lua
workspace "Snake_Game_Project"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

SFML_DIR = "External/SFML"
SFML_INC = SFML_DIR .. "/include"
SFML_LIB = SFML_DIR .. "/build/lib"
SFML_BIN = SFML_DIR .. "/build/bin"

group "Core"
	include "Snake_Game_Core/Build-Core.lua"
group ""

include "Snake_Game_App/Build-App.lua"