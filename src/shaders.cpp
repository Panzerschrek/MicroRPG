
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
"gl_Position= vec4( v,-1.0,1.0);"
"}";

const char* text_shader_f=
"varying vec4 vc;"
"varying vec2 vtc;"
"uniform sampler2D tex;"
"void main(void)"
"{"
"float a=texture2D(tex,vtc).x;"
"gl_FragColor=vec4(vc.xyz,a*0.5+0.5);"
"}"
;
