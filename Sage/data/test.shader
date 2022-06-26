#shader vertex
#version 300 es 
layout(location = 0) in vec4 position;

// out vec4 v_Position;

void main()
{   
    // v_Position = position;
    gl_Position = position;
}

#shader fragment
#version 300 es 
precision mediump float; 
layout(location = 0) out mediump vec4 color;

uniform vec4 u_color;

// in vec4 v_Position;
void main()
{
    // color = v_Position * 0.5 + 0.5;
    color = u_color;
}