  "#version 330 core\n"
  "\n"
  "layout(location = 0) in vec3 aVertex;\n"
  "layout(location = 1) in vec4 aColor;\n"
  "\n"
  "out vec4 vColor;\n"
  "\n"
  "void main(void) {\n"
  "    vec4 pos = vec4(aVertex, 1.0);\n"
  "    gl_Position = \n"
  "    \t\tgl_ModelViewMatrix *\n"
  "    \t\tgl_ProjectionMatrix * pos;\n"
  "    vColor = aColor ;\n"
  "}\n"
