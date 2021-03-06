#include "main_loop.h"
#include "gl_functions.h"

MainLoop* MainLoop::current_main_loop= NULL;


#ifdef MRPG_OS_WINDOWS


#define KEY(x) (65 + x - 'A' )
LRESULT CALLBACK MainLoop::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if( uMsg == WM_CLOSE )
        PostQuitMessage(0);
    switch( uMsg )
    {
    case WM_CLOSE:
        exit(0);

    case WM_KEYUP:
        if( wParam < 256 )
            current_main_loop->keys[ wParam ]= false;
        break;

    case WM_KEYDOWN:
    {
        if( wParam < 256 )
            current_main_loop->keys[ wParam ]= true;

		switch( wParam )
		{
			case KEY('Q'):
			exit(0);
			default:
			break;
		}
    }//key down
    break;

    case WM_MOUSEWHEEL:
     {

        if( GET_WHEEL_DELTA_WPARAM(wParam) > 1 )
            current_main_loop->renderer->ZoomIn();
        else
            current_main_loop->renderer->ZoomOut();
     }
     break;

#ifdef MRPG_DEBUG
        printf( "key: %d\n", wParam );
#endif
        break;


    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif//win


inline void MainLoop::InitOGL()
{
#ifdef MRPG_OS_WINDOWS

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

    hrc= wglCreateContext( hdc );
    wglMakeCurrent( hdc, hrc );

#else
    int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    XVisualInfo         *vi;
    Colormap             cmap;
    XSetWindowAttributes swa;
    GLXContext           cx;
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
    XSetStandardProperties(dpy, win, "MicroRPG", "MicroRPG", None,
                           NULL, 0, NULL);



    glXMakeCurrent(dpy, win, cx);
    XMapWindow(dpy, win);

#endif

    int ver[2];
    glGetIntegerv( GL_MAJOR_VERSION, ver );
    glGetIntegerv( GL_MINOR_VERSION, ver + 1 );
    if( ver[0] * 10 + ver[1] < MRPG_GL_VERSION )
        exit(1025);


    return;
display_error:
    exit(1024);
}

inline void MainLoop::SetupOGLState()
{
    //gl state initialisation
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL );
    glClearDepth(1.0f);
    glClearColor(0.7f, 0.8f, 0.9f, 0.0f);
    glViewport(0, 0, screen_x, screen_y );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}


MainLoop::MainLoop( Level* l, Player* p ):
    level(l), player(p)
{

    screen_x= 1024;
    screen_y= 768;
    current_main_loop= this;

    for( int i= 0; i< 256; i++ )
        keys[i]= false;

    InitOGL();
    GetGLFunctions();
    SetupOGLState();

    renderer= new Renderer( level, player );
}

void MainLoop::Loop()
{

#ifdef MRPG_OS_WINDOWS

    MSG msg;
    while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
#else
    XEvent               event;
    while(XPending(dpy))
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


            if( XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) != 1 )
                break;


            switch (keysym)
            {
            case XK_Up:

                break;

            case XK_Down:
                break;

			case XK_Escape:
			case XK_Q:
			case XK_q:
				exit(0);

            default:
                break;
            }
            break;
        }//key press

        case ButtonPress:
        {
            switch (event.xbutton.button)
            {
            case Button4:
                renderer->ZoomIn();
                break;

            case Button5:
                renderer->ZoomOut();
                break;

            default:
                break;
            }
        }//mouse button press
        break;

        case ConfigureNotify:
            // XResizeWindow( dpy, win, screen_x, screen_y );

        case Expose:
            break;

        }

    }

#endif

    renderer->Draw();

#ifdef MRPG_OS_WINDOWS
    SwapBuffers(hdc);
#else
    glXSwapBuffers(dpy, win);
#endif


    usleep(1000);//1 ms

}
