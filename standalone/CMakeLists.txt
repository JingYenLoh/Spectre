#
#    This file is part of Spectre, an open-source physically based
#    spectral raytracing library.
#   
#    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
#   
#    Spectre is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#   
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#   
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#   

# =========================================================================== #
#                        ADD SOURCE FILES TO PROJECT                          #
# =========================================================================== #

file(GLOB_RECURSE standalone_headers src/*.h)
file(GLOB_RECURSE standalone_cpps src/*.cpp)
set(all_files ${standalone_headers} ${standalone_cpps})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${all_files})

# =========================================================================== #
#                          SET COMPILATION TARGETS                            #
# =========================================================================== #

add_executable(Standalone ${all_files})
set_target_properties(Standalone PROPERTIES RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin/standalone>)

# =========================================================================== #
#                                LINK LIBRARIES                               #
# =========================================================================== #

target_link_libraries(Standalone Spectre)

