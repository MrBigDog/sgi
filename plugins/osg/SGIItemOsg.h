#pragma once

#include <sgi/plugins/SGIItemBase.h>

namespace sgi {
namespace support {
    class SGIHostItemOsg;
}

class SGIItemOsg : public SGIItemBase
{
public:
    typedef osg::Referenced ObjectType;
    typedef osg::ref_ptr<ObjectType> ObjectStorageType;
    typedef support::SGIHostItemOsg HostItemType;

    SGIItemOsg(const HostItemType * hostItem=NULL, SGIItemType type=SGIItemTypeInvalid, osg::Referenced * object=NULL, unsigned flags=0, unsigned score=0, osg::Referenced * userData=NULL)
        : SGIItemBase(type, flags, score, userData), _object(object) {}
    SGIItemOsg(SGIItemType type, const osg::Referenced * object=NULL, unsigned flags=0, unsigned score=0, osg::Referenced * userData=NULL)
        : SGIItemBase(type, flags, score, userData), _object(const_cast<osg::Referenced*>(object)) {}
    SGIItemOsg(const SGIItemOsg & rhs, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
        : SGIItemBase(rhs, copyop), _object(rhs._object) {}
    ~SGIItemOsg()
        { }

    META_Object(sgi, SGIItemOsg);

    SGIItemOsg & operator = (const SGIItemOsg & rhs)
    {
        SGIItemBase::operator=(rhs);
        _object = rhs._object;
        return *this;
    }
    ObjectType * object() { return _object.get(); }
    ObjectType * object() const { return _object.get(); }

protected:
    virtual int compare(const SGIItemBase & rhs) const
    {
        int ret = SGIItemBase::compare(rhs);
        if(!ret)
        {
            if(_object == static_cast<const SGIItemOsg&>(rhs)._object)
                return 0;
            else if(_object < static_cast<const SGIItemOsg&>(rhs)._object)
                return -1;
            else
                return 1;
        }
        else
            return ret;
    }

private:
    ObjectStorageType _object;
};

namespace osg_plugin {
enum NodeLookAt {
    NodeLookAtInvalid = -1,
    NodeLookAtDirect,
    NodeLookAtTopView,
    NodeLookAtFromBehind,
};

struct SetViewNodeLookAt
{
    SetViewNodeLookAt(osg::Node * node_, NodeLookAt mode_)
        : node(node_), mode(mode_) {}

    osg::ref_ptr<osg::Node> node;
    NodeLookAt mode;
};

typedef ReferencedDataT<SetViewNodeLookAt> ReferencedSetViewNodeLookAt;
} // namespace osg_plugin

} // namespace sgi
