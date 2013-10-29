#version 330 core

in vec4 vColor;

void main(void) {
	vec4 color = vColor;

	if (color.r > 2.0 * color.g) {
		color.g = 0.0;
	}
	//color.xyz += noise3(gl_FragCoord + vColor);

    gl_FragColor = color;
}
