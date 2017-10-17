#import <QCocoaNativeContext>

#import "CCocoaGLContext.h"

void * GetCocoaGLContext(void * x)
{
    QCocoaNativeContext * p = (QCocoaNativeContext *)(x);
    if (p)
    {
        NSOpenGLContext * x = p->context();
        return [x CGLContextObj];
    }
    return 0;
}