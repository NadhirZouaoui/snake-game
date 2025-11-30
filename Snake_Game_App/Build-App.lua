project "Snake_Game_App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

    includedirs {
        "Source",
        "../Snake_Game_Core/Source",
        "../External/SFML/include"
    }
    
    libdirs {
     "../External/SFML/lib"
    }

   links
   {
      "Snake_Game_Core",
      "sfml-system",
      "sfml-window",
      "sfml-graphics"
   }



   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   
      postbuildcommands {
        -- Copy all SFML DLLs to build output
        ("{COPY} ../External/SFML/bin/*.dll %{cfg.targetdir}")
    }


   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"