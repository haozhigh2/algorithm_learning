

GXX:=g++ -std=c++14
BuildDir:=./build
Hiho:=${BuildDir}/hiho

default:	init ${Hiho}
			
HihoFiles:=./src/hiho_coder/*.cc
${Hiho}:	${HihoFiles} ./include/*.h
			${GXX} ${HihoFiles} -o $@

init:		
			mkdir ${BuildDir} -p

clean:		clear

clear:		
			rm ${BuildDir}/*
