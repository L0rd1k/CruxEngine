#shader vertex
#version 300 es
precision mediump float;
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 view_proj;
uniform mat4 transform;

out mediump vec3 v_Position;
out mediump vec4 v_Color;

void main()
{   
    v_Position = a_Position;
    v_Color = a_Color;
    gl_Position = view_proj * transform * vec4(a_Position, 1.0);
}

#shader fragment
#version 300 es 
precision mediump float; 
layout(location = 0) out mediump vec4 color;

in vec3 v_Position;
in vec4 v_Color;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;
}