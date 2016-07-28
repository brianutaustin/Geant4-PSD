# Basic config.
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ParticleInLAr)

# Find and configure GEANT4
 option(WITH_GEANT4_UIVIS "Build ParticleInLAr with Geant4 UI and Vis drivers" ON)
 if(WITH_GEANT4_UIVIS)
 	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

# Configure project to use GEANT4 and Simulation headers
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# List the sources to build the application
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Define and link the executable
add_executable(ParticleInLAr ParticleInLAr.cc ${sources} ${headers})
target_link_libraries(ParticleInLAr ${Geant4_LIBRARIES})

# Copy any runtime scripts to the build directory
set(ParticleInLAr_SCRIPTS
	vis.mac
	init_vis.mac
	)

	foreach(_script ${ParticleInLAr_SCRIPTS})
	configure_file(
		${PROJECT_SOURCE_DIR}/${_script}
		${PROJECT_BINARY_DIR}/${_script}
		COPYONLY
		)
	endforeach()

# Install if necessary
install(TARGETS ParticleInLAr DESTINATION bin)
