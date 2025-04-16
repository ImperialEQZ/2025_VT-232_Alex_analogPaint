# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PaintAnalog_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PaintAnalog_autogen.dir\\ParseCache.txt"
  "PaintAnalog_autogen"
  )
endif()
