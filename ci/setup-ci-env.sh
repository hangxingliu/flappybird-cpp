#!/usr/bin/env bash

function setup_linux () {
	sudo apt-get update -y || exit 1;
	sudo apt-get install -y libegl1-mesa-dev libgles2-mesa-dev; # for libsdl2 (travis-ci bug)
	sudo apt-get install -y cmake make pkg-config \
		libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev || exit 1;
}

function brew_install () {
	(brew outdated "$1" || brew install $1) || (echo "Error installing $1"; exit 1);
}

function setup_osx () {
	brew update || exit 1;
	brew_install "pkg-config" || exit 1;
	brew_install "sdl2" || exit 1;
	brew_install "sdl2_image" || exit 1;
	brew_install "sdl2_ttf" || exit 1;
	brew ln "sdl2" --force || exit 1;
	brew ln "sdl2_image" --force || exit 1;
	brew ln "sdl2_ttf" --force || exit 1;
}

if [[ "$TRAVIS_OS_NAME" == "" ]]; then
	echo "WARNING: set TRAVIS_OS_NAME as \"linux\", because it is empty!";
	TRAVIS_OS_NAME=linux;
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
	setup_linux
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
	setup_osx
else
	echo "fatal: unknown TRAVIS_OS_NAME: \"$TRAVIS_OS_NAME\"";
	exit 1;
fi
