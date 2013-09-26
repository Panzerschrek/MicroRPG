#include "main_loop.h"


MainLoop* MainLoop::current_main_loop= NULL;


#ifdef MRPG_OS_WIN32
LRESULT CALLBACK MainLoop::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if( uMsg == WM_CLOSE )
        PostQuitMessage(0);
    switch( uMsg )
    {
    case WM_CLOSE:
        exit(0);

        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif//win32


inline void MainLoop::InitOGL()
{
#ifdef MRPG_OS_WIN32

    int border_size, top_border_size, bottom_border_size;
    static const char* WINDOW_NAME= "MicroRPG";

    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.style = CS_OWNDC;
    window_class.lpfnWndProc = WindowProc;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance =  0;
    window_class.hIcon = LoadIcon( 0 , IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = WINDOW_NAME;
    window_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


    if ( ! RegisterClassEx( &window_class ) )
        goto display_error;


    border_size=  GetSystemMetrics(SM_CXFIXEDFRAME);
    bottom_border_size= GetSystemMetrics(SM_CYFIXEDFRAME);
    top_border_size= bottom_border_size + GetSystemMetrics(SM_CYCAPTION);

    hwnd  = CreateWindowEx(0,
                           WINDOW_NAME,
                           WINDOW_NAME,
                           WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
                           0,
                           0,
                           screen_x + border_size * 2,
                           screen_y + top_border_size + bottom_border_size,
                           NULL,
                           NULL,
                           /*h_instance*/0,
                           NULL);

    if ( ! hwnd )
        goto display_error;

    ShowWindow( hwnd, SW_SHOWNORMAL );
    hdc= GetDC( hwnd );


    wglMakeCurrent( 0, 0 );
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    ZeroMemory( &pfd, sizeof(pfd) );
    pfd.nVersion= 1;
    pfd.dwFlags= PFD_DRAW_TO_WINDOW|
                 PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType= PFD_TYPE_RGBA;
    pfd.cColorBits= 32;
    pfd.cDepthBits= 32;
    pfd.cStencilBits= 8;
    pfd.iLayerType= PFD_MAIN_PLANE;

    format= ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, format, &pfd);


    /*  HGLRC temp_rc= wglCreateContext( hdc );
      wglMakeCurrent( hdc, temp_rc );


      PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB= NULL;
      wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

      wglMakeCurrent( NULL, NULL );
      wglDeleteContext( temp_rc );

      int attribs[] =
      {
          WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
          WGL_CONTEXT_MINOR_VERSION_ARB, 3,
          WGL_CONTEXT_FLAGS_ARB,        0x0002,
         0x9126, 0x00000001,
          0
      };

      hrc= wglCreateContextAttribsARB( hdc, 0, attribs );*/
    hrc= wglCreateContext( hdc );
    wglMakeCurrent( hdc, hrc );

#else
    int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    XVisualInfo         *vi;
    Colormap             cmap;
    XSetWindowAttributes swa;
    GLXContext           cx;
    // GLboolean				recalcModelView = GL_TRUE;
    int                  dummy;


    dpy = XOpenDisplay(NULL);
    if (dpy == NULL )
        goto display_error;


    if(!glXQueryExtension(dpy, &dummy, &dummy))
        goto display_error;

    if ( ( vi= glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf) ) == NULL)
        goto display_error;

    cx = glXCreateContext(dpy, vi, /* no shared dlists */ None,
                          /* direct rendering if possible */ GL_TRUE );
    if (cx == NULL)
        goto display_error;


    cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = KeyPressMask    | ExposureMask
                     | ButtonPressMask | StructureNotifyMask;
    win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0,
                        screen_x, screen_y, 0, vi->depth, InputOutput, vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask, &swa);
    XSetStandardProperties(dpy, win, "main", "main", None,
                           NULL, 0, NULL);


    glXMakeCurrent(dpy, win, cx);
    XMapWindow(dpy, win);

#endif

    return;
display_error:
    exit(1024);
}

inline void MainLoop::SetupOGLState()
{
    //gl state initialisation
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
    glViewport(0, 0, screen_x, screen_y );

}


MainLoop::MainLoop()
{

    screen_x= 640;
    screen_y= 480;
    current_main_loop= this;

    InitOGL();
    SetupOGLState();
}

inline void MainLoop::Draw()
{
    static float ang= 0.0f;

    ang+=5.0f;


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef( ang, 0.0f, 1.0f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* front face */
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.7f, 0.1f);  /* green */
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    /* back face */
    glColor3f(0.9, 1.0f, 0.0f);  /* yellow */
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    /* top side face */
    glColor3f(0.2, 0.2, 1.0f);  /* blue */
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    /* bottom side face */
    glColor3f(0.7, 0.0f, 0.1);  /* red */
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );
}

void MainLoop::Loop()
{

#ifdef MRPG_OS_WIN32

    MSG msg;
    while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
#else
    XEvent               event;
    while(XPending(dpy)) /* loop to compress events */
    {


        XNextEvent(dpy, &event);

        switch (event.type)
        {
        case KeyPress:
        {
            KeySym     keysym;
            XKeyEvent *kevent;
            char       buffer[1];

            kevent = (XKeyEvent *) &event;
            if (   (XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) == 1)
                    && (keysym == (KeySym)XK_Escape) )
                exit(0);
            break;
        }
        case ButtonPress:
            switch (event.xbutton.button)
            {
            default:
                break;
            }
            break;
        case ConfigureNotify:
            glViewport(0, 0, event.xconfigure.width,
                       event.xconfigure.height);

        case Expose:
            break;

        }

    }

#endif

    Draw();

#ifdef MRPG_OS_WIN32
    SwapBuffers(hdc);
#else
    glXSwapBuffers(dpy, win);
#endif

}
