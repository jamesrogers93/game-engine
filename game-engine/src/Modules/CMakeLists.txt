
include(src/Modules/AI/CMakeLists.txt)
include(src/Modules/Animation/CMakeLists.txt)
include(src/Modules/Audio/CMakeLists.txt)
include(src/Modules/Graphics/CMakeLists.txt)
include(src/Modules/GUI/CMakeLists.txt)
include(src/Modules/Physics/CMakeLists.txt)
# AR only supported on IOS 
if(IOS)
	include(src/Modules/AR/CMakeLists.txt)
endif()