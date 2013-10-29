#version 330 core

layout(location = 0) in vec3 aVertex;
layout(location = 1) in vec4 aColor;

out vec4 vColor;

void main(void) {
    vec4 pos = vec4(aVertex, 1.0);
    gl_Position = 
    		gl_ModelViewMatrix *
    		gl_ProjectionMatrix * pos;
    vColor = aColor ;
}
