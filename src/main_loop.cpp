#include "main_loop.h"

MainLoop::MainLoop()
{

    screen_x= 640;
    screen_y= 480;
#ifdef MRPG_OS_WIN32
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
                        300, 300, 0, vi->depth, InputOutput, vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask, &swa);
    XSetStandardProperties(dpy, win, "main", "main", None,
                           NULL, 0, NULL);


    glXMakeCurrent(dpy, win, cx);
    XMapWindow(dpy, win);

#endif

    //gl state initialisation
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    glViewport(0, 0, 300, 300);


    return;

display_error:
    exit(1024);
}

int EventFunc (
    Display*	dpy,
    XEvent*	e,
    XPointer	p
)
{
    return 0;
}


void MainLoop::Loop()
{
#ifdef MRPG_OS_WIN32
#else
    XEvent               event;
    if(XPending(dpy)) /* loop to compress events */
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



//redraw
    static float ang= 0.0f;

    ang+=5.0f;


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef( ang, 0.0, 1.0, 0.0 );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* front face */
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.1);  /* green */
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    /* back face */
    glColor3f(0.9, 1.0, 0.0);  /* yellow */
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    /* top side face */
    glColor3f(0.2, 0.2, 1.0);  /* blue */
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    /* bottom side face */
    glColor3f(0.7, 0.0, 0.1);  /* red */
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();

    glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );

    glXSwapBuffers(dpy, win);/* buffer swap does implicit glFlush */

#endif
}
