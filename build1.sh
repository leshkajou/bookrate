#!/bin/sh

########################################
# This is shell script that can perform build operations.
########################################

COMMAND=$1
ROOT_DIR=$(pwd)

BUILD_DIR=$ROOT_DIR/build
SOURSE_DIR=$ROOT_DIR/src
PKG_DIR=$ROOT_DIR/pkg


########################################
# Help message
########################################
print_help () {
	echo 
	echo "Usage: ./run.sh [build|build-package|install|remove|clean|full-clean|help]"
	echo "	build 		-- build application from source code"
	echo "	build-package 	-- build rpm package"
	echo "	install 	-- install application"
	echo "	remove 		-- uninstall application"
	echo "	clean 		-- clean build directory"
	echo "	full-clean 	-- remove all build files and packages"
	echo
}



########################################
# Build source code
########################################
build_source () {
	if ! [ -d $BUILD_DIR ] ; then
		mkdir $BUILD_DIR
	fi

	cd $BUILD_DIR	
	cmake $SOURSE_DIR && make
	cd $ROOT_DIR
}



########################################
# Perform make clean 
########################################
clean () {
	cd $BUILD_DIR	
	make clean
	cd $ROOT_DIR
	
}



########################################
# Wipe build files
########################################
full_clean () {
	rm -rf $BUILD_DIR/*
}



########################################
# Parse command
########################################
case "${COMMAND}" in
	"help" )
		print_help
	;;
	"build" )
		echo "Building..."
		build_source
	;;
	"build-package" )
		echo "Building package..."
	;;
	"install" )
		echo "Installing..."
	;;
	"clean" )
		echo "Cleaning build dir..."
		clean
	;;
	"full-clean" )
		echo "Wiping build dir..."
		full_clean
	;;
	* )
		print_help
	;;
	
esac