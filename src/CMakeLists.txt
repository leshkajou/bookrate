cmake_minimum_required(VERSION 2.8)
project ("ratebook")

find_package(Boost COMPONENTS system thread signals)
find_library(wt wt)
find_library(wthttp wthttp)
find_library(wtdbo wtdbo)
find_library(wtdbosqlite3 wtdbosqlite3)

aux_source_directory(. 	SRCLIST)
add_executable(${PROJECT_NAME} ${SRCLIST})

target_link_libraries(${PROJECT_NAME}
		      ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
		      wt wthttp wtdbo wtdbosqlite3) 