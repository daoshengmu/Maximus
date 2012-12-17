//
//  MGraphicsiOS.m
//  Maximous
//
//  Created by User on 6/5/11.
//  Copyright 2011 Daosheng Mu. All rights reserved.
//

#import "iOS/MGraphicsiOS.h"
#import "iOS/EAGLView.h"


// Replace the implementation of this method to do your own custom drawing.
static const GLfloat squareVertices[] = {
	-0.5f, -0.33f,
	0.5f, -0.33f,
	-0.5f,  0.33f,
	0.5f,  0.33f,
};

static const GLubyte squareColors[] = {
	255, 255,   0, 255,
	0,   255, 255, 255,
	0,     0,   0,   0,
	255,   0, 255, 255,
};

// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms1[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

static float transY = 0.0f;

//@implementation GraphicsDelegate
//static EAGLView *glView = NULL;
//@synthesize glView;

cMGraphicsiOS::cMGraphicsiOS()
{		
	
}

cMGraphicsiOS::~cMGraphicsiOS()
{
	
}

bool _validateProgram(GLuint prog)
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}

GLuint program;

bool compileShader( GLuint *shader, GLenum type, NSString *file )
{
    GLint status;
    const GLchar *source;
    
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load vertex shader");
        return FALSE;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return FALSE;
    }
    
    return TRUE;
}

bool linkProgram( GLuint prog )
{
    GLint status;
    
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0)
        return FALSE;
    
    return TRUE;
}

bool cMGraphicsiOS::loadShaders()
{
	GLuint vertShader, fragShader;
    NSString *vertShaderPathname, *fragShaderPathname;
    
    // Create shader program.
    program = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"vsh"];
    if ( !( compileShader( &vertShader, GL_VERTEX_SHADER, vertShaderPathname ) ) )
    {
        NSLog(@"Failed to compile vertex shader");
        return FALSE;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"Shader" ofType:@"fsh"];
    if ( !( compileShader( &fragShader, GL_FRAGMENT_SHADER, fragShaderPathname ) ) )
    {
        NSLog(@"Failed to compile fragment shader");
        return FALSE;
    }
    
    // Attach vertex shader to program.
    glAttachShader(program, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(program, fragShader);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(program, ATTRIB_VERTEX, "position");
    glBindAttribLocation(program, ATTRIB_COLOR, "color");
    
    // Link program.
    if ( !linkProgram(program) )
    {
        NSLog(@"Failed to link program: %d", program);
        
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (program)
        {
            glDeleteProgram(program);
            program = 0;
        }
        
        return FALSE;
    }
    
    // Get uniform locations.
    uniforms1[UNIFORM_TRANSLATE] = glGetUniformLocation(program, "translate");
    
    // Release vertex and fragment shaders.
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);
    
    return TRUE;
}

void cMGraphicsiOS::initialize()
{
	/* if ( !glView )
	{
		glView = [EAGLView getView];
	} */
	
	this->loadShaders();
}

void cMGraphicsiOS::drawTriangle()
{
	
	//if ([context API] == kEAGLRenderingAPIOpenGLES2)
	{
		// Use shader program.
		glUseProgram(program);
		
		// Update uniform value.
		glUniform1f(uniforms1[UNIFORM_TRANSLATE], (GLfloat)transY);
		transY += 0.075f;	
		
		// Update attribute values.
		glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);
		glVertexAttribPointer(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, 1, 0, squareColors);
		glEnableVertexAttribArray(ATTRIB_COLOR);
		
		// Validate program before drawing. This is a good check, but only really necessary in a debug build.
		// DEBUG macro must be defined in your debug configurations if that's not already the case.
#if defined(DEBUG)
		if ( !_validateProgram(program) )
		{
			NSLog(@"Failed to validate program: %d", program);
			return;
		}
#endif
	}
	//else
	// {
	//		 glMatrixMode(GL_PROJECTION);
	//		 glLoadIdentity();
	//		 glMatrixMode(GL_MODELVIEW);
	//		 glLoadIdentity();
	//		 glTranslatef(0.0f, (GLfloat)(sinf(transY)/2.0f), 0.0f);
	//		 transY += 0.075f;
	
	//		 glVertexPointer(2, GL_FLOAT, 0, squareVertices);
	//		 glEnableClientState(GL_VERTEX_ARRAY);
	//		 glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	//		 glEnableClientState(GL_COLOR_ARRAY);
	//	 }
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void cMGraphicsiOS::createFrameBuffer()
{
//	[glView setFramebuffer];
}

void cMGraphicsiOS::beginFrame()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cMGraphicsiOS::endFrame()
{
  //  [glView presentFramebuffer];
}

//@end
