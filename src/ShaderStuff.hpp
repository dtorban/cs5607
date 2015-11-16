
#ifndef SHADERSTUFF
#define SHADERSTUFF 1

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#define DEBUG_ON 0
#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))

typedef struct {
	float x, y;
} FloatType2D;

const int nvertices = 4;


// Create a NULL-terminated string by reading the provided file
static char*
readShaderSource(const char* shaderFile)
{
    FILE *fp;
	long length;
	char *buffer;
	
	// open the file containing the text of the shader code
	fp = fopen(shaderFile, "r");
	
	// check for errors in opening the file
    if ( fp == NULL ) { 
		printf("can't open shader source file %s\n", shaderFile); 
		return NULL; 
	}
	
	// determine the file size
    fseek(fp, 0, SEEK_END); // move position indicator to the end of the file;
    length = ftell(fp);  // return the value of the current position
	
	// allocate a buffer with the indicated number of bytes, plus one
	buffer = new char[length + 1];
	
	// read the appropriate number of bytes from the file
    fseek(fp, 0, SEEK_SET);  // move position indicator to the start of the file
    fread(buffer, 1, length, fp); // read all of the bytes
	
	// append a NULL character to indicate the end of the string
    buffer[length] = '\0';
	
	// close the file
    fclose(fp);
	
	// return the string
    return buffer;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint
InitShader(const char* vShaderFileName, const char* fShaderFileName)
{	
	GLuint vertex_shader, fragment_shader;
	GLchar *vs_text, *fs_text;
	GLuint program;
	
	// check GLSL version
//	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// Create shader handlers
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Read source code from file
	vs_text = readShaderSource(vShaderFileName);
	fs_text = readShaderSource(fShaderFileName);
	
	// error check
	if ( vs_text == NULL ) {
		printf("Failed to read from vertex shader file %s\n", vShaderFileName);
		exit( 1 );
	} else if (DEBUG_ON) {
		printf("read shader code:\n%s\n", vs_text);
	}
	if ( fs_text == NULL ) {
		printf("Failed to read from fragent shader file %s\n", fShaderFileName);
		exit( 1 );
	} else if (DEBUG_ON) {
		printf("read shader code:\n%s\n", fs_text);
	}
	
	// Set shader source
	const char *vv = vs_text;
	const char *ff = fs_text;
	glShaderSource(vertex_shader, 1, &vv, NULL);
	glShaderSource(fragment_shader, 1, &ff, NULL);
	
	// Compile shaders
	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);
	
	// error check
	GLint  compiled;
	glGetShaderiv( vertex_shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
		printf("vertex_shader failed to compile\n");
		if (DEBUG_ON) {
			GLint logMaxSize, logLength;
			glGetShaderiv( vertex_shader, GL_INFO_LOG_LENGTH, &logMaxSize );
			printf("printing error message of %d bytes\n", logMaxSize);
			char* logMsg = new char[logMaxSize];
			glGetShaderInfoLog( vertex_shader, logMaxSize, &logLength, logMsg );
			printf("%d bytes retrieved\n", logLength);
			printf("error message: %s\n", logMsg);
			delete[] logMsg;
		}
		exit(1);
	}
	glGetShaderiv( fragment_shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
		printf("fragment_shader failed to compile\n");
		if (DEBUG_ON) {
			GLint logMaxSize, logLength;
			glGetShaderiv( fragment_shader, GL_INFO_LOG_LENGTH, &logMaxSize );
			printf("printing error message of %d bytes\n", logMaxSize);
			char* logMsg = new char[logMaxSize];
			glGetShaderInfoLog( fragment_shader, logMaxSize, &logLength, logMsg );
			printf("%d bytes retrieved\n", logLength);
			printf("error message: %s\n", logMsg);
			delete[] logMsg;
		}
		exit(1);
	}
	
	// Create the program
	program = glCreateProgram();
	
	// Attach shaders to program
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	
    // Link and set program to use
	glLinkProgram(program);
	glUseProgram(program);
	
    return program;
}


//----------------------------------------------------------------------------

void
init( void )
{
	FloatType2D vertices[nvertices];
	GLuint vao[1], buffer, location, program;
	
	vertices[0].x = -0.9;  vertices[0].y = -0.9;
	vertices[1].x =  0.9;  vertices[1].y = -0.6;
	vertices[2].x =  0.9;  vertices[2].y =  0.6;
	vertices[3].x = -0.9;  vertices[3].y =  0.9;
	
    // Create a vertex array object
	#ifdef USE_APPLE
    glGenVertexArraysAPPLE( 1, vao );
    glBindVertexArrayAPPLE( vao[0] );
	#else
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
	#endif
    
    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );


	std::stringstream vshader, fshader;
	vshader << SRC_DIR << "/vshader1.glsl";
	fshader << SRC_DIR << "/fshader1.glsl";
	// Load shaders and use the resulting shader program
	program = InitShader( vshader.str().c_str(), fshader.str().c_str() );
	
    // Initialize the vertex position attribute from the vertex shader
	location = glGetAttribLocation( program, "vertex_position" );
    glEnableVertexAttribArray( location );
    glVertexAttribPointer( location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPointSize(10.0);  // huge points
	//glLineWidth(5.0);  // fat lines
}



#endif
