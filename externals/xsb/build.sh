#!/bin/bash

if [ -z "$BASH_VERSION" ]; then
	echo "Invalid shell, re-running using bash..."
	exec bash "$0" "$@"
	exit $?
fi
SRCLOC="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source "$SRCLOC/../../../build/utils/functions.sh"

# Cleanup environment
cleanupEnvironment

# Verify input
targetOS=$1
compiler=$2
targetArch=$3

if [[ "$targetOS" == "ios" ]]; then
	# Configure
	path="$SRCLOC/upstream.patched/XSB/build"
	(cd "$path" && ./configure --build=arm-apple-darwin)
	#(cd "$path" && ./configure)
	retcode=$?
	if [ $retcode -ne 0 ]; then
		echo "Failed to configure 'XSB', aborting..."
		exit $retcode
	fi

	# Build XSB module
	pathConfig="$SRCLOC/upstream.patched/XSB/config/arm-apple-darwin"
	(cd "$path" && make -f "$pathConfig/topMakefile" module)
	retcode=$?
	if [ $retcode -ne 0 ]; then
		echo "Failed to build 'XSB', aborting..."
		exit $retcode
	fi
else
	echo "Only 'ios' is supported target, while '${targetOS}' was specified"
	exit 1
fi
