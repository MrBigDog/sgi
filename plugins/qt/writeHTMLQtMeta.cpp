#include "stdafx.h"
#include <ostream>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaClassInfo>
#include <QtCore/QMetaProperty>
#include "writeHTMLQt.h"
#include "SGIItemQt"

#include <sgi/helpers/rtti>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace sgi {
namespace qt_plugin {
WRITE_PRETTY_HTML_IMPL_DECLARE_AND_REGISTER(QMetaObject)

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaMethod::Access & access)
{
    switch(access)
    {
    case QMetaMethod::Private: os << "private"; break;
    case QMetaMethod::Protected: os << "protected"; break;
    case QMetaMethod::Public: os << "public"; break;
    default: os << (int)access; break;
    }
    return os;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaMethod::MethodType & methodType)
{
    switch(methodType)
    {
    case QMetaMethod::Method: os << "method"; break;
    case QMetaMethod::Signal: os << "signal"; break;
    case QMetaMethod::Slot: os << "slot"; break;
    case QMetaMethod::Constructor: os << "constructor"; break;
    default: os << (int)methodType; break;
    }
    return os;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaMethod & method)
{
    const char *tag = method.tag();
    const char *typeName = method.typeName();
    QByteArray signature = method.methodSignature();

    os << method.access();
    switch (method.methodType())
    {
    case QMetaMethod::Constructor:
    case QMetaMethod::Method: 
        break;
    case QMetaMethod::Signal: os << " signal"; break;
    case QMetaMethod::Slot: os << " slot"; break;
    }
    os << ":" << typeName << " " << signature.toStdString();
    if(strlen(tag))
        os << " (" << tag << ")";
    return os;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaProperty & property)
{
    const char *name = property.name();
    const char *typeName = property.typeName();
    os << name << "(" << typeName << ")";
    if(property.isReadable() && property.isWritable())
        os << " r/w";
    else if(property.isReadable())
        os << " ro";
    else if(property.isWritable())
        os << " wo";
    if(property.isEnumType())
        os << " enum";
    return os;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaEnum & metaenum)
{
    const char *name = metaenum.name();
    const char *scope = metaenum.scope();
    os << scope << "::" << name;
    if(metaenum.isFlag())
        os << " flag";
    return os;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const QMetaClassInfo & metaclassInfo)
{
    const char *name = metaclassInfo.name();
    const char *value = metaclassInfo.value();
    os << name << "=" << value;
    return os;
}


void writePrettyHTMLImpl_QMetaMethod(std::basic_ostream<char>& os, const QMetaMethod & method)
{
    os << "<table border=\'1\' align=\'left\'><tr><th>Field</th><th>Value</th></tr>" << std::endl;
    os << "<tr><td>name</td><td>" << method.name().toStdString() << "</td></tr>" << std::endl;
    os << "<tr><td>tag</td><td>" << method.tag() << "</td></tr>" << std::endl;
    os << "<tr><td>access</td><td>" << method.access() << "</td></tr>" << std::endl;
    os << "<tr><td>methodType</td><td>" << method.methodType() << "</td></tr>" << std::endl;
    os << "<tr><td>attributes</td><td>" << method.attributes() << "</td></tr>" << std::endl;
    os << "<tr><td>methodIndex</td><td>" << method.methodIndex() << "</td></tr>" << std::endl;
    os << "<tr><td>revision</td><td>" << method.revision() << "</td></tr>" << std::endl;
    os << "<tr><td>typeName</td><td>" << method.typeName() << "</td></tr>" << std::endl;
    os << "<tr><td>methodSignature</td><td>" << method.methodSignature().toStdString() << "</td></tr>" << std::endl;
    os << "<tr><td>parameterTypes</td><td><ol>";
    for (const QByteArray & pt : method.parameterTypes())
    {
        os << "<li>" << pt.toStdString() << "</li>";
    }
    os << "</td></tr>" << std::endl;
    os << "<tr><td>parameterNames</td><td><ol>";
    for (const QByteArray & pt : method.parameterNames())
    {
        os << "<li>" << pt.toStdString() << "</li>";
    }
    os << "</td></tr>" << std::endl;
    os << "</table>" << std::endl;
}

bool writePrettyHTMLImpl<QMetaObject>::process(std::basic_ostream<char>& os)
{
    QMetaObject * object = getObject<QMetaObject, SGIItemQtMeta>();
    switch(itemType())
    {
    case SGIItemTypeObject:
        {
            if(_table)
                os << "<table border=\'1\' align=\'left\'><tr><th>Field</th><th>Value</th></tr>" << std::endl;

            os << "<tr><td>this</td><td>" << std::hex << (void*)object << std::dec << "</td></tr>" << std::endl;
            os << "<tr><td>typename</td><td>" << helpers::getRTTITypename_html(object) << "</td></tr>" << std::endl;
            os << "<tr><td>classname</td><td>" << object->className() << "</td></tr>" << std::endl;

            os << "<tr><td>class info</td><td><ol>";
            int classInfoOffset = object->classInfoOffset();
            int classInfoCount = object->classInfoCount();
            for (int i=classInfoOffset; i<classInfoCount; ++i)
            {
                QMetaClassInfo metaclassInfo = object->classInfo(i);
                os << "<li>" << metaclassInfo << "</li>" << std::endl;
            }
            os << "</ol></td></tr>" << std::endl;

            os << "<tr><td>properties</td><td><ol>";
            int propertyOffset = object->propertyOffset();
            int propertyCount = object->propertyCount();
            for (int i=propertyOffset; i<propertyCount; ++i)
            {
                QMetaProperty property = object->property(i);
                os << "<li>" << property << "</li>" << std::endl;
            }
            os << "</ol></td></tr>" << std::endl;

            os << "<tr><td>enumerator</td><td><ol>";
            int enumeratorOffset = object->enumeratorOffset();
            int enumeratorCount = object->enumeratorCount();
            for (int i=enumeratorOffset; i<enumeratorCount; ++i)
            {
                QMetaEnum metaenum = object->enumerator(i);
                os << "<li>" << metaenum << "</li>" << std::endl;
            }
            os << "</ol></td></tr>" << std::endl;

            os << "<tr><td>constructors</td><td><ol>";
            int constructorOffset = 0;
            int constructorCount = object->constructorCount();
            for (int i=constructorOffset; i<constructorCount; ++i)
            {
                QMetaMethod method = object->constructor(i);
                os << "<li>" << method << "</li>" << std::endl;
            }
            os << "</ol></td></tr>" << std::endl;

            os << "<tr><td>methods</td><td><ol>";
            int methodOffset = object->methodOffset();
            int methodCount = object->methodCount();
            for (int i=methodOffset; i<methodCount; ++i)
            {
                QMetaMethod method = object->method(i);
                os << "<li>" << method << "</li>" << std::endl;
            }
            os << "</ol></td></tr>" << std::endl;

            if(_table)
                os << "</table>" << std::endl;
        }
        break;
    default:
        break;
    }
    return true;
}

} // namespace qt_plugin
} // namespace sgi
