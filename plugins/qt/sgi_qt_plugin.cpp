#include "stdafx.h"
#include <stdio.h>
#include <iostream>

#include <sgi/plugins/SGIPluginImpl.h>
#include <sgi/plugins/SGIPluginInterface.h>
#include <sgi/plugins/SGIHostItemQt.h>
#include <sgi/plugins/GenerateItemImpl>
#include <sgi/plugins/SGIPluginMacros.h>
#include <sgi/SGIItemInternal>
#include <sgi/plugins/SceneGraphDialog>
#include <sgi/plugins/SettingsDialog>
#include "SGIItemQt"

#include <QtCore/QThread>
#include <QCoreApplication>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QColorDialog>
#include <QPicture>
#include <QWindow>
#include <QtWidgets/private/qwidgetwindow_p.h>
#include <QPaintDeviceWindow>
#include <QSurface>
#include <QOffscreenSurface>
#include <QPagedPaintDevice>
#include <QRasterWindow>

#include <QOpenGLWidget>
#include <QOpenGLWindow>
#include <QOpenGLPaintDevice>

#ifdef WITH_QTOPENGL
#include <QGLWidget>
#include <QGLFramebufferObject>
#include <QGLPixelBuffer>
#endif

#include "writeHTMLQt.h"
#include "getObjectInfoQt.h"
#include "ObjectTreeQt.h"
#include "ContextMenuQt.h"
#include "MenuActionQt.h"
#include "SettingsDialogQt.h"

using namespace sgi::qt_plugin;

SGI_CALL_FUNCTION_FOR_OBJECT_TEMPLATE()

SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QObject, LOKI_TYPELIST(QWindow, QWidget, QThread,
                                                         QCoreApplication,
                                                         QOpenGLContext
                                                        ));
//SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QWindow, LOKI_TYPELIST(QPaintDeviceWindow, QQuickWindow));
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QWindow, LOKI_TYPELIST(QPaintDeviceWindow, QWidgetWindow));
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QPaintDeviceWindow, LOKI_TYPELIST(QOpenGLWindow, QRasterWindow));

SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QSurface, LOKI_TYPELIST(QWindow, QOffscreenSurface));
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QCoreApplication, LOKI_TYPELIST(QApplication));

#ifdef WITH_QTOPENGL
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QWidget, LOKI_TYPELIST(QDialog,
                                                         QOpenGLWidget,
                                                         QGLWidget));
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QPaintDevice, LOKI_TYPELIST(QGLFramebufferObject, QGLPixelBuffer, QImage, QPicture, QPixmap,
                                                              QOpenGLPaintDevice, QPagedPaintDevice, QPaintDeviceWindow,
                                                              QWidget))
#else
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QWidget, LOKI_TYPELIST(QDialog,
                                                         QOpenGLWidget
                                                            ));
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QPaintDevice, LOKI_TYPELIST(QImage, QPicture, QPixmap,
                                                              QOpenGLPaintDevice, QPagedPaintDevice, QPaintDeviceWindow,
                                                              QWidget))
#endif
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QDialog, LOKI_TYPELIST(QFileDialog, QMessageBox, QInputDialog, QProgressDialog, QColorDialog));

SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QMetaObject, sgi::details::type_list<>);
SGI_CALL_FUNCTION_FOR_OBJECT_BASE(QIcon, sgi::details::type_list<>);

SGI_CALL_FUNCTION_FOR_OBJECT_BASE(osg::Referenced, LOKI_TYPELIST(ISceneGraphDialog))

namespace sgi {

namespace qt_plugin {

GENERATE_IMPL_TEMPLATE()
GENERATE_IMPL_NO_ACCEPT(osg::Referenced)


typedef generateItemImplT<generateItemAcceptImpl, SGIItemQt, SGIItemQtMeta, SGIItemQtPaintDevice, SGIItemQtSurface, SGIItemQtIcon > generateItemImpl;

typedef SGIPluginImplementationT<       generateItemImpl,
                                        writePrettyHTMLImpl,
                                        getObjectNameImpl,
                                        getObjectNameImpl,
                                        getObjectTypeImpl,
                                        getObjectPathImpl,
                                        defaultPluginGetObjectInfoStringImpl,
                                        defaultPluginGetObjectInfoStringImpl,
                                        defaultPluginGetObjectFilenameFiltersImpl,
                                        defaultPluginGetObjectHasCallbackImpl,
                                        defaultPluginWriteObjectFileImpl,
                                        objectTreeBuildImpl,
                                        objectTreeBuildRootImpl,
                                        contextMenuPopulateImpl,
                                        actionHandlerImpl,
                                        settingsDialogCreateImpl
                                        >
    SGIPluginImpl;

} // namespace qt_plugin

class SGIPlugin_qt_Implementation : public qt_plugin::SGIPluginImpl
{
public:
    SGIPlugin_qt_Implementation(SGIPluginHostInterface * hostInterface=NULL)
        : qt_plugin::SGIPluginImpl(hostInterface)
    {
        SGIITEMTYPE_NAME(SGIItemTypeWidgets);
        SGIITEMTYPE_NAME(SGIItemTypeMethods);
    }
    SGIPlugin_qt_Implementation(const SGIPlugin_qt_Implementation & rhs, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
        : qt_plugin::SGIPluginImpl(rhs, copyop)
    {
    }

    META_Object(sgi_qt, SGIPlugin_qt_Implementation);
};

} // namespace sgi

SGI_PLUGIN_IMPLEMENT(qt)
