#ifndef _OSMAND_CORE_MAP_SYMBOL_H_
#define _OSMAND_CORE_MAP_SYMBOL_H_

#include <OsmAndCore/stdlib_common.h>
#include <functional>

#include <OsmAndCore/QtExtensions.h>
#include <QSet>

class SkBitmap;

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/Callable.h>
#include <OsmAndCore/Map/MapCommonTypes.h>

namespace OsmAnd
{
    class MapSymbolsGroup;

    class OSMAND_CORE_API MapSymbol
    {
        Q_DISABLE_COPY_AND_MOVE(MapSymbol);

    public:
        enum class ContentClass
        {
            Unknown = -1,
            Icon,
            Caption,
        };

    private:
    protected:
        MapSymbol(
            const std::shared_ptr<MapSymbolsGroup>& group,
            const bool isShareable);
    public:
        virtual ~MapSymbol();

        const std::weak_ptr<MapSymbolsGroup> group;
        MapSymbolsGroup* const groupPtr;

        const bool isShareable;

        int order;
        ContentClass contentClass;
        QSet<MapSymbolIntersectionClassId> intersectsWithClasses;
        QSet<MapSymbolIntersectionClassId> intersectedByClasses;

        bool isHidden;
        FColorARGB modulationColor;
    };
}

#endif // !defined(_OSMAND_CORE_MAP_SYMBOL_H_)
