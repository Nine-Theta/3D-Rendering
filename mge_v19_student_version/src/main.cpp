#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "RenderingProject/RenderingProject.hpp"
#include "RenderingProject/AssignmentThree.hpp"
#include "mge/MGEDemo.hpp"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */
int main()
{
    std::cout << "Starting Game" << std::endl;

    /**/ MGE::AbstractGame* game = new RP::AssignmentThree();
    /** MGE::AbstractGame* game = new RP::RenderingProject();
    /** MGE::AbstractGame* game = new MGE::MGEDemo(); /**/
    game->initialize();
    game->run();

	delete game;

    return 0;
}