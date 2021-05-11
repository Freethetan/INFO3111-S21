#pragma once
// globalStuff.h

// This is here because glad has to be included 
// BEFORE glfw or it won't build.
// Since we can't control the order of the build
// (which cpp file is compiled 1st, etc.), they
// all include this, ensuring it's A-OK
// 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
