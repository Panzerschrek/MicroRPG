//text shader
const char* text_shader_v=
"attribute vec2 v;"//in position
"attribute vec2 tc;"//in texture coord
"attribute vec4 c;"//in color
"varying vec4 vc;"//out color
"varying vec2 vtc;"//out texture coord
"void main(void)"
"{"
"vc=c;"
"vtc=tc*vec2(1.0/96.0,1.0);"
"gl_Position=vec4(v,0.0,1.0);"
"}";

const char* text_shader_f=
"varying vec4 vc;"
"varying vec2 vtc;"
"uniform sampler2D tex;"
"void main(void)"
"{"
"float c=texture2D(tex,vtc).x;"
"gl_FragColor=vec4(vc.xyz*c,max(vc.a,c));"
"}";

//microbe shader
const char* microbe_shader_v=
"attribute vec3 v;"//in position
"attribute vec4 c;"//in clolor
"varying vec4 vc;"//out color
"uniform mat4 m;"//transformation matrix( scale, translate, rotate )
"void main(void)"
"{"
"vc=c;"
"gl_Position=m*vec4(v,1.0);"
"}";

const char* microbe_shader_f=
"varying vec4 vc;"
"void main(void)"
"{"
"gl_FragColor=vc;"
"}";
