////////////////////////////////////////////////////
// anim.cpp version 4.1
// Template code for drawing an articulated figure.
// CS 174A 
////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifdef WIN32
#include "GL/freeglut.h"
#else
#include <GLUT/glut.h>
#endif

#include "Ball.h"
#include "FrameSaver.h"
#include "Timer.h"
#include "Shapes.h"
#include "tga.h"

#include "Angel.h"

#ifdef __APPLE__
#define glutInitContextVersion(a,b)
#define glutInitContextProfile(a)
#define glewExperimental int glewExperimentalAPPLE
#define glewInit()
#endif

FrameSaver FrSaver ;
Timer TM ;

BallData *Arcball = NULL ;
int Width = 480 ;
int Height = 480 ;
int Button = -1 ;
float Zoom = 1 ;
int PrevY = 0 ;

int Animate = 0 ;
int Recording = 0 ;

void resetArcball() ;
void save_image();
void instructions();
void set_colour(float r, float g, float b) ;

const int STRLEN = 100;
typedef char STR[STRLEN];

#define PI 3.1415926535897
#define X 0
#define Y 1
#define Z 2

// Structs that hold the Vertex Array Object index and number of vertices of each shape.
ShapeData cubeData;
ShapeData sphereData;
ShapeData coneData;
ShapeData cylData;
ShapeData thingData;

// Matrix stack that can be used to push and pop the modelview matrix.
class MatrixStack {
    int    _index;
    int    _size;
    mat4*  _matrices;

   public:
    MatrixStack( int numMatrices = 32 ):_index(0), _size(numMatrices)
        { _matrices = new mat4[numMatrices]; }

    ~MatrixStack()
	{ delete[]_matrices; }

    void push( const mat4& m ) {
        assert( _index + 1 < _size );
        _matrices[_index++] = m;
    }

    mat4& pop( void ) {
        assert( _index - 1 >= 0 );
        _index--;
        return _matrices[_index];
    }
};

MatrixStack  mvstack;
mat4         model_view;
GLint        uModelView, uProjection, uView;
GLint        uAmbient, uDiffuse, uSpecular, uLightPos, uShininess;
GLint        uTex, uEnableTex;

// The eye point and look-at point.
// Currently unused. Use to control a camera with LookAt().
vec4 eye(0.0, 0.0, -50.0, 1.0);
vec4 ref(0.0, 0.0, 0.0, 1.0);
vec4 up(0.0, 1.0, 0.0, 0.0);

double TIME = 0.0 ;

/////////////////////////////////////////////////////
//    PROC: drawCylinder()
//    DOES: this function 
//          render a solid cylinder  oriented along the Z axis. Both bases are of radius 1. 
//          The bases of the cylinder are placed at Z = 0, and at Z = 1.
//
//          
// Don't change.
//////////////////////////////////////////////////////
void drawCylinder(void)
{
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );
    glBindVertexArray( cylData.vao );
    glDrawArrays( GL_TRIANGLES, 0, cylData.numVertices );
}

//////////////////////////////////////////////////////
//    PROC: drawCone()
//    DOES: this function 
//          render a solid cone oriented along the Z axis with base radius 1. 
//          The base of the cone is placed at Z = 0, and the top at Z = 1. 
//         
// Don't change.
//////////////////////////////////////////////////////
void drawCone(void)
{
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );
    glBindVertexArray( coneData.vao );
    glDrawArrays( GL_TRIANGLES, 0, coneData.numVertices );
}


//////////////////////////////////////////////////////
//    PROC: drawCube()
//    DOES: this function draws a cube with dimensions 1,1,1
//          centered around the origin.
// 
// Don't change.
//////////////////////////////////////////////////////

void drawCube(void)
{
    //glUniform1i( uEnableTex, 1 );
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );
    glBindVertexArray( cubeData.vao );
    glDrawArrays( GL_TRIANGLES, 0, cubeData.numVertices );
    //glUniform1i( uEnableTex, 0 );
}


//////////////////////////////////////////////////////
//    PROC: drawSphere()
//    DOES: this function draws a sphere with radius 1
//          centered around the origin.
// 
// Don't change.
//////////////////////////////////////////////////////

void drawSphere(void)
{ 
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );
    glBindVertexArray( sphereData.vao );
    glDrawArrays( GL_TRIANGLES, 0, sphereData.numVertices );
}


//ADDED
//draws pyramidal "thing" in the sky
void drawThing(void)
{
    glUniformMatrix4fv( uModelView, 1, GL_TRUE, model_view );
    glBindVertexArray( thingData.vao );
    glDrawArrays( GL_TRIANGLES, 0, thingData.numVertices );
}

void resetArcball()
{
    Ball_Init(Arcball);
    Ball_Place(Arcball,qOne,0.75);
}


//////////////////////////////////////////////////////
//    PROC: myKey()
//    DOES: this function gets caled for any keypresses
// 
//////////////////////////////////////////////////////

void myKey(unsigned char key, int x, int y)
{
    float time ;
    switch (key) {
        case 'q':
        case 27:
            exit(0); 
        case 's':
            FrSaver.DumpPPM(Width,Height) ;
            break;
        case 'r':
            resetArcball() ;
            glutPostRedisplay() ;
            break ;
        case 'a': // togle animation
            Animate = 1 - Animate ;
            // reset the timer to point to the current time		
            time = TM.GetElapsedTime() ;
            TM.Reset() ;
            // printf("Elapsed time %f\n", time) ;
            break ;
        case '0':
            //reset your object
            break ;
        case 'm':
            if( Recording == 1 )
            {
                printf("Frame recording disabled.\n") ;
                Recording = 0 ;
            }
            else
            {
                printf("Frame recording enabled.\n") ;
                Recording = 1  ;
            }
            FrSaver.Toggle(Width);
            break ;
        case 'h':
        case '?':
            instructions();
            break;
    }
    glutPostRedisplay() ;

}

/*********************************************************
    PROC: myinit()
    DOES: performs most of the OpenGL intialization
     -- change these with care, if you must.

**********************************************************/

void myinit(void)
{
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram(program);

    // Generate vertex arrays for geometric shapes
    generateCube(program, &cubeData);
    generateSphere(program, &sphereData);
    generateCone(program, &coneData);
    generateCylinder(program, &cylData);
	generateThing(program, &thingData);

    uModelView  = glGetUniformLocation( program, "ModelView"  );
    uProjection = glGetUniformLocation( program, "Projection" );
    uView       = glGetUniformLocation( program, "View"       );

    glClearColor( 51.0/255.0, 51.0/255.0, 1.0, 1.0); //light blue

    uAmbient   = glGetUniformLocation( program, "AmbientProduct"  );
    uDiffuse   = glGetUniformLocation( program, "DiffuseProduct"  );
    uSpecular  = glGetUniformLocation( program, "SpecularProduct" );
    uLightPos  = glGetUniformLocation( program, "LightPosition"   );
    uShininess = glGetUniformLocation( program, "Shininess"       );
    uTex       = glGetUniformLocation( program, "Tex"             );
    uEnableTex = glGetUniformLocation( program, "EnableTex"       );

    glUniform4f(uAmbient,    0.2f,  0.2f,  0.2f, 1.0f);
    glUniform4f(uDiffuse,    0.6f,  0.6f,  0.6f, 1.0f);
    glUniform4f(uSpecular,   0.2f,  0.2f,  0.2f, 1.0f);
    glUniform4f(uLightPos,  15.0f, 15.0f, 30.0f, 0.0f);
    glUniform1f(uShininess, 100.0f);

    glEnable(GL_DEPTH_TEST);
	/*
    TgaImage coolImage;
    if (!coolImage.loadTGA("challenge.tga"))
    {
        printf("Error loading image file\n");
        exit(1);
    }
	*/

	//loading my image
	TgaImage suitImage;
	if (!suitImage.loadTGA("min_suit_square.tga"))
	{
		printf("error loading image file\n");
		exit(1);
	}


    GLuint texture;
    glGenTextures( 1, &texture );

    glBindTexture( GL_TEXTURE_2D, texture );
    
    glTexImage2D(GL_TEXTURE_2D, 0, 4, suitImage.width, suitImage.height, 0,
                 (suitImage.byteCount == 3) ? GL_RGB : GL_RGBA,
                 GL_UNSIGNED_BYTE, suitImage.data );


    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );



    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );
    
    // Set texture sampler variable to texture unit 0
    // (set in glActiveTexture(GL_TEXTURE0))
    glUniform1i( uTex, 0 );
    
    Arcball = new BallData ;
    Ball_Init(Arcball);
    Ball_Place(Arcball,qOne,0.75);
}

/*********************************************************
    PROC: set_colour();
    DOES: sets all material properties to the given colour
    -- don't change
**********************************************************/

void set_colour(float r, float g, float b)
{
    float ambient  = 0.2f;
    float diffuse  = 0.6f;
    float specular = 0.2f;
    glUniform4f(uAmbient,  ambient*r,  ambient*g,  ambient*b,  1.0f);
    glUniform4f(uDiffuse,  diffuse*r,  diffuse*g,  diffuse*b,  1.0f);
    glUniform4f(uSpecular, specular*r, specular*g, specular*b, 1.0f);
}

/*********************************************************
**********************************************************
**********************************************************

    PROC: display()
    DOES: this gets called by the event handler to draw
          the scene, so this is where you need to build
          your ROBOT --  
      
        MAKE YOUR CHANGES AND ADDITIONS HERE

    Add other procedures if you like.

**********************************************************
**********************************************************
**********************************************************/

void resetModelView()
{
	model_view = mat4(1.0f);
	/*model_view *= Translate(0.0f, 0.0f, -10.0f);
	HMatrix r;
    Ball_Value(Arcball,r);

    mat4 mat_arcball_rot(
        r[0][0], r[0][1], r[0][2], r[0][3],
        r[1][0], r[1][1], r[1][2], r[1][3],
        r[2][0], r[2][1], r[2][2], r[2][3],
        r[3][0], r[3][1], r[3][2], r[3][3]);
    model_view *= mat_arcball_rot;

    mat4 view = model_view;
    glUniformMatrix4fv( uView, 1, GL_TRUE, view ); */

    // Previously glScalef(Zoom, Zoom, Zoom);
	model_view = LookAt(eye, ref, up);
    model_view *= Scale(Zoom);
}



class Robot
{
public:
	//basic, just build a robot
	Robot(bool isWalking);
	//makes the robot walk
	void setWalk(bool isWalking);
	void extendHead(); //jokes
	void extendEyes(); //joaks

	
	//draw the whole robot
	void drawRobot();
private:
	
	//indiv helper functions
	void drawBody();
	void drawHead();
	void drawButtons();
	void drawBowtie();
	void drawEye(char side);
	void drawLegs(char side);
	void drawArm(char side);
	void setRobotColor();
	void resetRobotModelView();
	double robotMoveAngle(); //internal function to get the movement angle
	float getHeadScalar();
	float getEyeScalar();

	bool m_isWalking;
	double m_timeElapsed; //used to calculate angles for walking
	double m_headTimer;   //used to do the head extend
	double m_eyeTimer;   //used to do the eye extend
	double m_angle;       //used for walking etc

};

Robot::Robot(bool isWalking)
{
	m_isWalking = isWalking;
	m_timeElapsed = 0;
	m_angle = 0;
	m_headTimer = 0;
	m_eyeTimer = 0;
}
void Robot::setWalk(bool isWalking)
{
	m_isWalking = isWalking;
}

void Robot::extendHead() //only call once to get the result
{
	if (m_headTimer == 0)
		m_headTimer += .033;
	// can't call it while already running

}

void Robot::extendEyes() //only call once
{
	if (m_eyeTimer == 0)
		m_eyeTimer += .033;
	// can't call while already running 
}

void Robot::drawRobot()
{
	if (m_isWalking) //used to calculate angles for walking
		m_timeElapsed += .033;

	drawBody();
	drawHead();
	drawButtons();
	drawBowtie();
	drawEye('l');
	drawEye('r');
	drawLegs('l');
	drawLegs('r');
	drawArm('l');
	drawArm('r');
}

void Robot::setRobotColor() //helper to get the color of the robot
{
	set_colour(0.5f, 0.5f, 0.5f);
}

void Robot::resetRobotModelView()
{
	model_view = mat4(1.0f);
	
	model_view *= LookAt(eye, ref, up);
	if (m_isWalking)
	{
		model_view *= Translate(0.0f, -abs(.01*robotMoveAngle()), 0.0f);
	}

	if (TIME >= 2.0 && TIME <= 6.65)
		model_view *= Translate(0.0f, 0.0f, 2*(TIME-2.0));
	else if (TIME >= 6.65)
		model_view *= Translate(0.0f, 0.0f, 2*(4.65));

	if (TIME >= 52.3) //"blows up"
	{
		model_view *= Translate(0.0f, 0.0f, -((TIME-52.3)*(TIME-52.3)*(TIME-52.3)*(TIME-52.3)*(TIME-52.3)));
	}
	/*HMatrix r;
    Ball_Value(Arcball,r);

    mat4 mat_arcball_rot(
        r[0][0], r[0][1], r[0][2], r[0][3],
        r[1][0], r[1][1], r[1][2], r[1][3],
        r[2][0], r[2][1], r[2][2], r[2][3],
        r[3][0], r[3][1], r[3][2], r[3][3]);
    model_view *= mat_arcball_rot;

    mat4 view = model_view;
    glUniformMatrix4fv( uView, 1, GL_TRUE, view );  

    // Previously glScalef(Zoom, Zoom, Zoom); */
    //model_view *= Scale(Zoom); 
}

double Robot::robotMoveAngle()
{
	double checkAngle = 10*sin(2*m_timeElapsed);
	if (checkAngle >= 8.5) //want to flatten the top
		return 8.5;
	else if (checkAngle <= -8.5) //flatten the bottom,
		return -8.5;
	else
		return checkAngle;
}

void Robot::drawArm(char side)
{
	//resetting before starting
	//arm
	
	if (m_isWalking) 
		//"realistic" robot arm movement -- sin wave with "flattened" top
		m_angle = robotMoveAngle();


	int SIDE_FACTOR; //negative/positive to indicate side
	if (side == 'l') SIDE_FACTOR = 1;
	else			 SIDE_FACTOR = -1;


	resetRobotModelView();
		
	model_view *= RotateX(m_angle * SIDE_FACTOR);
	model_view *= Translate(SIDE_FACTOR*0.7f, 0.3f, 0.0f);
	model_view *= RotateY(90.0f);
	model_view *= Scale(0.12f, 0.12f, 0.42f);
	setRobotColor();
	drawCylinder();

	//hand
	resetRobotModelView();
	model_view *= RotateX(m_angle * SIDE_FACTOR);
	model_view *= Translate(SIDE_FACTOR*1.07f, 0.17f, 0.0f);
	
	model_view *= RotateX(80.0f);
	model_view *= Scale(0.1f, 0.1f, 0.2f);
	setRobotColor();
	drawCylinder();
}

void Robot::drawLegs(char side)
{
	resetRobotModelView();

	if (m_isWalking) 
		//"realistic" robot leg movement -- sin wave with "flattened" top
		m_angle = robotMoveAngle();
	
	//to get alternate movement on each side
	int SIDE_FACTOR;
	if (side == 'l') SIDE_FACTOR = 1;
	else			 SIDE_FACTOR = -1;
	
	model_view *= RotateX(90.0f + (SIDE_FACTOR*m_angle));
	model_view *= Translate(0.0f, 0.0f, 1.9f);
	
	model_view *= Scale(0.1f, 0.1f, 0.9f);
	model_view *= Translate(SIDE_FACTOR*2.0f, 0.0f, 0.0f);
	setRobotColor();
	drawCylinder();

}

float Robot::getEyeScalar()
{
	if (m_eyeTimer == 0)
		return 1.0;
	if (m_eyeTimer > 0.0 && m_eyeTimer < 8.0)
		return 1.0f + m_eyeTimer/(4.0);
	else if (m_eyeTimer >= 8.0 && m_eyeTimer < 14.0) //pause
		return 3.0f;
	else if (m_eyeTimer >= 14.0 && m_eyeTimer < 22.0)
		return (6.5f - (m_eyeTimer/4.0));
	else if (m_eyeTimer >= 22.0)
		return 1.0;


}

void Robot::drawEye(char side)
{
	int SIDE_FACTOR; //negative/positive to indicate side
	if (side == 'l') SIDE_FACTOR = 1;
	else			 SIDE_FACTOR = -1;

	resetRobotModelView();

	model_view *= Translate(0.0f, 1.3f, 0.2f);
	model_view *= Translate(0.0f, (getHeadScalar()-1)/2, 0.2f);
	model_view *= Scale(0.07f, 0.07f, 0.24f);

	model_view *= Scale(1.0f, 1.0f, getEyeScalar());
	model_view *= Translate(0.0f, 0.0f, getEyeScalar()/4);

	model_view *= Translate(SIDE_FACTOR*1.5f, 0.0f, 0.0f);
	set_colour(1.0f, 1.0f, 1.0f);
	drawCone();
	 
	//eyeball
	model_view *= Scale(0.2f, 0.2f, 1.1f);
	set_colour(0.0f, 0.0f, 0.0f);
	drawCone();


	if (m_eyeTimer > 24.0) //reset
		m_eyeTimer = 0;
	else if (m_eyeTimer != 0)
		m_eyeTimer += .033;

};

void Robot::drawButtons()
{
	resetRobotModelView();
	model_view *= Translate(0.0f, -0.25f, 0.5f);
	model_view *= Scale(0.05f, 0.05f, 0.07f);

	set_colour((204.0f/255.0f), (204.0f/255.0f), (102.0f/255.0f)); //button color
	for (int i = 0; i < 3; i++)
	{
		model_view *= Translate(0.0f, -4.0f, 0.0f);
		drawCone();
	}
}

void Robot::drawBowtie() //heehee
{
	resetRobotModelView();
	model_view *= Translate(0.0f, 0.83f, 0.5f);
	model_view *= Scale(0.1f, 0.1f, 0.1f);
	set_colour(0.0f, 0.0f, 0.0f);

	model_view *= Translate(0.0f,0.0f,0.15f);
	model_view *= RotateY(90);
	drawCone();
	model_view *= Translate(0.0f,0.0f,-0.3f);
	model_view *= RotateY(180);
	drawCone();
}

float Robot::getHeadScalar()
{
	if (m_headTimer == 0)
		return 1.0;
	if (m_headTimer > 0.0 && m_headTimer < 14.0)
		return 1.0f + (m_headTimer/2.0f);
	
	else
		return 8.0f;
	/*
	
	else if (m_headTimer >= 4.0 && m_headTimer < 8.0) //pause
		return 5.0f;
	else if (m_headTimer >= 8.0 && m_headTimer <= 12.0) //pause
		return 13.0f - m_headTimer;
		*/
}

void Robot::drawHead()
{
	resetRobotModelView();
	model_view *= Translate(0.0f, 1.2f, 0.0f);
	model_view *= Scale(0.5f, 0.5f, 0.5f);

	
	model_view *= Translate(0.0, (getHeadScalar()-1) / 2, 0.0f);
	model_view *= Scale (1.0f, getHeadScalar(), 1.0f);

	/*if (m_headTimer >= 12.0) //reset
		m_headTimer = 0;
	else if (m_headTimer != 0)
		m_headTimer += .033; */
	if (m_headTimer != 0)
		m_headTimer += .033;
	setRobotColor();
	drawCube();
}

void Robot::drawBody()
{
	resetRobotModelView();
	set_colour(0.8f, 0.8f, 0.8f);
	model_view *= Scale(1.0f, 2.0f, 1.0f);

	set_colour((71.0f/255.0f), (71.0f/255.0f), (71.0f/255.0f));
	drawCube();


	//hacky way of texturing 1 face: draw a suit "shell" over front face.

	model_view *= Translate(0.0f, 0.0f, 0.5f);
	model_view *= Scale(1.0f, 1.0f, 0.001f);
	
	glUniform1i( uEnableTex, 1 );
	drawCube();
	glUniform1i( uEnableTex, 0 );
}

void drawDiamond()
{
	resetModelView();
	float color1 = abs(sin(TIME));
	set_colour(color1, 0.5, 0.5);

	
	model_view *= Translate(0.0, 5.0, 16.0);

	if (TIME < 46.5 || TIME > 52.0)
	{
		model_view *= RotateX(120*TIME);
		model_view *= RotateY(120*TIME);
	}
	else
	{
		model_view *= RotateX(120*46.5);
		model_view *= RotateY(120*46.5);
	}

	float scalar = 1.0;

	if (TIME >= 52.0)
		scalar = (TIME-51.0)*(TIME-51.0)*(TIME-51.0);

	model_view *= Scale(scalar, scalar, scalar);
	drawThing();
}

void drawGround()
{
	resetModelView();

	if (TIME >= 52.3)
		model_view *= Translate(0.0f, -((TIME-52.3)*(TIME-52.3)*(TIME-52.3)*(TIME-52.3)), 0.0f);
	model_view *= Translate(0.0f, -2.9f, 0.0f);
	model_view *= Scale(100.0f, 0.01f, 100.0f);

	set_colour(51.0/255.0, 153.0/255.0, 0.0);
	drawCube();

	model_view *= Scale(0.04f, 1.0f, 1.0f);
	model_view *= Translate(0.0f, 0.05f, 0.0f);
	set_colour(32.0/255.0, 32.0/255.0, 32.0/255.0);
	drawCube();
}

Robot* ROBOT;
int frameCount = 0;
double previousTime = 0;
int fps = 0;

void getFPS()
{
	frameCount++;
	double currentTime = TM.GetElapsedTime();
	double timeInterval = currentTime - previousTime;

	if (timeInterval > 1.0)
	{
		fps = frameCount / timeInterval;
		previousTime = currentTime;
		frameCount = 0;
		printf("FPS = %i\n", fps); 
	}
}

void cameraHelper()
{
	double t;
	//SHOT 1: front shot
	if (TIME <= 3.0)
	{
		t = TIME - 1;
		eye.x = 0;
		eye.y = 1-(t/4);
		eye.z = 4;
		ref.x = 0;
		ref.y = 1-(t/4);
		ref.z = 0;
	}


	//SHOT 2: side shot of robot walking, stops
	else if (TIME <= 9.0)
	{
		eye.x = 10;
		eye.y = 0.5;
		eye.z = 8.0;
		ref.x = -15.0;
		ref.y = 0.5;
		ref.z = 8;
	}


	//SHOT 3: shot looking up at the spinning thingie
	else if (TIME <= 14.0)
	{
		eye.x = 2.0;
		eye.y = 0.0;
		eye.z = 4.0;
		ref.x = 1.0;
		ref.y = 2.5;
		ref.z = 12.0;
	}

	//SHOT 4: quick face "reaction shot", then head extends
	else if (TIME <= 20.0)
	{
		eye.x = 0.0;
		eye.y = 1.5;
		eye.z = 11.0;
		ref.x = 0.0;
		ref.y = 1.5;
		ref.z = 0.0;
	}

	//SHOT 5: 360 panorama
	
	else if (TIME <= 30.9)
	{
		eye.x = 10*cos(TIME);
		eye.y = 5.0;
		eye.z = 10*sin(TIME)+12.0;
		ref.x = 0.0;
		ref.y = 1.5;
		ref.z = 12.0;
	}

	//SHOT 6: side shot of eyes extending
	else if (TIME <= 39.0)
	{
		eye.x = 10;
		eye.y = 5.0;
		eye.z = 8.0;
		ref.x = 0.0;
		ref.y = 1.5;
		ref.z = 12.0;
	}
	
	//SHOT 7: close shot of diamond
	else if (TIME <= 43.0)
	{
		eye.x = 0.0;
		eye.y = 5.0;
		eye.z = 14.0;
		ref.x = 0.0;
		ref.y = 5.0;
		ref.z = 16.0;
	} 

	//SHOT 8: close shot of robot face
	else if (TIME <= 45.0)
	{
		eye.x = 0.0;
		eye.y = 5.0;
		eye.z = 13.0;
		ref.x = 0.0;
		ref.y = 5.0;
		ref.z = 12.0;
	}

	//SHOT 9: diamond begins to expand
	else if (TIME <= 50.0)
	{
		eye.x = 0.0;
		eye.y = 5.3;
		eye.z = 8.0;
		ref.x = 0.0;
		ref.y = 5.0;
		ref.z = 16.0;
	} 

	//SHOT 10: eye shot
	else if (TIME <= 52.0)
	{
		eye.x = 0.0;
		eye.y = 4.7;
		eye.z = 10.7;
		ref.x = 0.15;
		ref.y = 4.5;
		ref.z = 0.0;
	}

	//SHOT 12: long shot, robot goes flying
	else if (TIME <= 58.0)
	{
		eye.x = 40.0;
		eye.y = 0.5;
		eye.z = 15.0;
		ref.x = -25.0;
		ref.y = 0.5;
		ref.z = 15;
	}
	//SHOT 13 : text
	else
	{
		eye.x = 0.0;
		eye.y = 0.0;
		eye.z = 3.0;
		ref.x = 0.0;
		ref.y = 0.0;
		ref.z = 0.0;
	}

	
}

void display(void)
{
    // Clear the screen with the background colour (set in myinit)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	resetModelView();
    
	/*
    // Draw Something
    set_colour(0.8f, 0.8f, 0.8f);
    drawSphere();

    // Previously glTranslatef(3,0,0);
    model_view *= Translate(3.0f, 0.0f, 0.0f);

    // Previously glScalef(3,3,3);
    model_view *= Scale(3.0f, 3.0f, 3.0f);
	glUniform1i( uEnableTex, 1 );
    drawCube();
	glUniform1i( uEnableTex, 0 );

    // And extra shapes!
    model_view *= Scale(1.0f/3.0f, 1.0f/3.0f, 1.0f/3.0f);
    model_view *= Translate(3.0f, 0.0f, 0.0f);
    set_colour(1.0f, 1.0f, 0.0f);
    drawCone();

    model_view *= Translate(-9.0f, 0.0f, 0.0f);
    set_colour(1.0f, 1.0f, 1.0f);
    drawCylinder();
	*/

	//stored our objects as globals so as to not new / delete every tick
	if (TIME <= 58.0)
	{
		drawGround();
		drawDiamond();

		if (TIME == 0) //need to draw our scene for the first time
		{
			ROBOT = new Robot(false);
		}

		if (TIME >= 2.0)
			ROBOT->setWalk(true);

		if (TIME >= 6.65)
			ROBOT->setWalk(false);

		if (TIME >= 17.0 && TIME <= 18.0)
			ROBOT->extendHead();

		if (TIME >= 32.5 && TIME <= 32.9)
			ROBOT->extendEyes();
	
		ROBOT->drawRobot();
	}
	
	getFPS();
	cameraHelper();

	model_view = LookAt(eye, ref, up);

    glutSwapBuffers();
    if(Recording == 1)
        FrSaver.DumpPPM(Width, Height) ;
}

/**********************************************
    PROC: myReshape()
    DOES: handles the window being resized 
    
      -- don't change
**********************************************************/

void myReshape(int w, int h)
{
    Width = w;
    Height = h;

    glViewport(0, 0, w, h);

    mat4 projection = Perspective(50.0f, (float)w/(float)h, 1.0f, 1000.0f);
    glUniformMatrix4fv( uProjection, 1, GL_TRUE, projection );
}

void instructions() 
{
    printf("Press:\n");
    printf("  s to save the image\n");
    printf("  r to restore the original view.\n") ;
    printf("  0 to set it to the zero state.\n") ;
    printf("  a to toggle the animation.\n") ;
    printf("  m to toggle frame dumping.\n") ;
    printf("  q to quit.\n");
}

// start or end interaction
void myMouseCB(int button, int state, int x, int y)
{
    Button = button ;
    if( Button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        HVect arcball_coords;
        arcball_coords.x = 2.0*(float)x/(float)Width-1.0;
        arcball_coords.y = -2.0*(float)y/(float)Height+1.0;
        Ball_Mouse(Arcball, arcball_coords) ;
        Ball_Update(Arcball);
        Ball_BeginDrag(Arcball);

    }
    if( Button == GLUT_LEFT_BUTTON && state == GLUT_UP )
    {
        Ball_EndDrag(Arcball);
        Button = -1 ;
    }
    if( Button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        PrevY = y ;
    }


    // Tell the system to redraw the window
    glutPostRedisplay() ;
}

// interaction (mouse motion)
void myMotionCB(int x, int y)
{
    if( Button == GLUT_LEFT_BUTTON )
    {
        HVect arcball_coords;
        arcball_coords.x = 2.0*(float)x/(float)Width - 1.0 ;
        arcball_coords.y = -2.0*(float)y/(float)Height + 1.0 ;
        Ball_Mouse(Arcball,arcball_coords);
        Ball_Update(Arcball);
        glutPostRedisplay() ;
    }
    else if( Button == GLUT_RIGHT_BUTTON )
    {
        if( y - PrevY > 0 )
            Zoom  = Zoom * 1.03 ;
        else 
            Zoom  = Zoom * 0.97 ;
        PrevY = y ;
        glutPostRedisplay() ;
    }
}

void idleCB(void)
{
    if( Animate == 1 )
    {
        // TM.Reset() ; // commenting out this will make the time run from 0
        // leaving 'Time' counts the time interval between successive calls to idleCB
        if( Recording == 0 )
            TIME = TM.GetElapsedTime() ;
        else
            TIME += 0.033 ; // save at 30 frames per second.
        //printf("TIME %f\n", TIME) ;

        glutPostRedisplay() ; 
    }
}
/*********************************************************
     PROC: main()
     DOES: calls initialization, then hands over control
           to the event handler, which calls 
           display() whenever the screen needs to be redrawn
**********************************************************/

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    // If your code fails to run, uncommenting these lines may help.
    //glutInitContextVersion(3, 2);
    //glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(Width,Height);
    glutCreateWindow(argv[0]);
    printf("GL version %s\n", glGetString(GL_VERSION));
    glewExperimental = GL_TRUE;
    glewInit();
    
    myinit();

    glutIdleFunc(idleCB) ;
    glutReshapeFunc (myReshape);
    glutKeyboardFunc( myKey );
    glutMouseFunc(myMouseCB) ;
    glutMotionFunc(myMotionCB) ;
    instructions();

    glutDisplayFunc(display);
    glutMainLoop();

    TM.Reset() ;
    return 0;         // never reached
}




