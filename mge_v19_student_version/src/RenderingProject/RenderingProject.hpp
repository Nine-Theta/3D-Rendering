#ifndef RenderingProject_HPP
#define RenderingProject_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class RenderingProject: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		RenderingProject();
		virtual ~RenderingProject();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        RenderingProject(const RenderingProject&);
        RenderingProject& operator=(const RenderingProject&);
};

#endif // RenderingProject_HPP
