#shader vertex
#version 300 es
precision mediump float;
layout(location = 0) in vec3 a_Position;

uniform mat4 view_proj;
uniform mat4 transform;

out mediump vec3 v_Position;

void main()
{   
    v_Position = a_Position;
    gl_Position = view_proj * transform * vec4(a_Position, 1.0);
}

#shader fragment
#version 300 es 
precision mediump float; 
layout(location = 0) out mediump vec4 color;

in vec3 v_Position;
uniform vec3 n_color;

void main()
{
	// color = vec4(0.2, 0.3, 0.8, 1.0);
    color = vec4(n_color, 1.0);
}