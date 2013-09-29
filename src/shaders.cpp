//text shader
const char* text_shader_v=
"attribute vec2 v;"
"attribute vec2 tc;"
"attribute vec4 c;"
"varying vec4 vc;"
"varying vec2 vtc;"
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
"gl_FragColor=vec4(vc.xyz*texture2D(tex,vtc).x,vc.a);"
"}";

//microbe shader
const char* microbe_shader_v=
"attribute vec3 v;"
"attribute vec4 c;"
"varying vec4 vc;"
"void main(void)"
"{"
"vc=c;"
"gl_Position=vec4(v,1.0);"
"}";

const char* microbe_shader_f=
"varying vec4 vc;"
"void main(void)"
"{"
"gl_FragColor=vc;"
"}";