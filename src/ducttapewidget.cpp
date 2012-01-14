#include "ducttapewidget.hpp"
#include "State.hpp"

DucttapeWidget::DucttapeWidget(dt::Game* game, QWidget* parent) :
    QWidget(parent),
    mGame(game),
    mDisplay(nullptr) {

    connect(mGame, SIGNAL(BeginFrame(double)), SLOT(updateQt(double)));
    connect(qApp, SIGNAL(aboutToQuit()), mGame, SLOT(RequestShutdown()));

    mDisplay = dt::Root::GetInstance().GetDisplayManager();

    bool stealparent (parentWidget() != NULL);
    QWidget *nativewin ((stealparent)? parentWidget () : this);

    Ogre::NameValuePairList params;
    Ogre::String winhandle;

    #ifdef Q_WS_WIN
    // According to Ogre Docs
    // positive integer for W32 (HWND handle)
    winhandle = Ogre::StringConverter::toString((unsigned int)(nativewin-> winId()));

    //Add the external window handle parameters to the existing params set.
    params["externalWindowHandle"] = winhandle;
    #endif

    #ifdef Q_WS_X11
    // GLX - According to Ogre Docs:
    // poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*)
    QX11Info info = x11Info();

    winhandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winhandle += ":";
    winhandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winhandle += ":";
    winhandle += Ogre::StringConverter::toString((unsigned long)nativewin->winId());

    //Add the external window handle parameters to the existing params set.
    params["parentWindowHandle"] = winhandle;
    #endif

    mDisplay->SetRenderWindowParam(params);
    mDisplay->CreateOgreRoot();
    Ogre::RenderWindow* win_ = mDisplay->GetRenderWindow();

    // take over ogre window
    // needed with parent windows
     if (stealparent)
    {
        WId ogre_winid = 0x0;
    #ifndef Q_WS_WIN
        win_-> getCustomAttribute ("WINDOW", &ogre_winid);
    #else
        win_-> getCustomAttribute ("HWND", &ogre_winid);
    #endif
        assert (ogre_winid);
        create (ogre_winid);
    }
}

DucttapeWidget::~DucttapeWidget() {
    delete mGame;
}

void DucttapeWidget::Run(dt::State *state, int argc, char **argv) {
    mGame->Run(state, argc, argv);
}

void DucttapeWidget::updateQt(double d) {
    update();
}

DucttapeThread::DucttapeThread(DucttapeWidget *dt, int argc, char** argv) :
    mDt(dt),
    mArg(argc),
    mArgv(argv) {}

void DucttapeThread::run() {
    mDt->Run(new EditorState(), mArg, mArgv);
}

void DucttapeThread2::run() {
    qApp->exec();
}
