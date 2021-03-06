#include "stdafx.h"
#include "SettingsDialogOSG.h"
#include "SGIItemOsg"

#include <sgi/plugins/SettingsDialog>

#include <osg/Camera>

#include "CameraSettings.h"
#include "ExtraViewDialog.h"

namespace sgi {
namespace osg_plugin {

SETTINGS_DIALOG_CREATE_IMPL_DECLARE_AND_REGISTER(SettingsDialogCamera)
SETTINGS_DIALOG_CREATE_IMPL_DECLARE_AND_REGISTER(SettingsDialogObjectLogger)
SETTINGS_DIALOG_CREATE_IMPL_DECLARE_AND_REGISTER(SettingsDialogExtraView)

bool settingsDialogCreateImpl<SettingsDialogCamera>::execute(ISettingsDialogPtr & dialog)
{
    osg::Camera * object = getObject<osg::Camera,SGIItemOsg>();
    CameraSettings * qtdialog = new CameraSettings(parent(), object);
    dialog = qtdialog->dialogInterface();
    return true;
}

bool settingsDialogCreateImpl<SettingsDialogObjectLogger>::execute(ISettingsDialogPtr & dialog)
{
    osg::Node * object = getObject<osg::Node,SGIItemOsg>();
    /*
    ObjectLogger * inspector = ObjectLogger::getOrCreateInspector(object);

    if(inspector)
    {
        dialog = inspector->getDialog();
        if(!dialog.valid())
            dialog = new ObjectLoggerDialog(parent(), inspector);
    }
    */
    return true;
}

bool settingsDialogCreateImpl<SettingsDialogExtraView>::execute(ISettingsDialogPtr & dialog)
{
    ExtraViewDialog * qtdialog = new ExtraViewDialog(parent(), _item.get(), _hostInterface);
    dialog = qtdialog->dialogInterface();
    return true;
}

} // namespace osg_plugin
} // namespace sgi
