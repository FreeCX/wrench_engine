#!/usr/bin/env python2
from ctypes import *
from OpenGL.GL import *

RENDERFUNC = CFUNCTYPE( c_voidp )

def render():
	glClear( GL_COLOR_BUFFER_BIT )
	glPointSize( 5.0 )
	glBegin( GL_POINTS )
	glColor3f( 1.0, 0.0, 0.0 )
	glVertex2f( 0.0, 0.0 )
	glEnd()
	wrench.weSwapBuffers()


if __name__ == '__main__':
	wrench = CDLL("../lib/libwrench.so")
	wrench.weInit( )
	wrench.weInitWindow( 500, 500, 0 )
	wrench.weInitOpenGL( 0 )
	wrench.weCreateWindow( "Wrench Engine Python Test")
	wrench.weRenderFunc( RENDERFUNC( render ) )
	wrench.weLoop()