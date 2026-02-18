#include "property.h"

bool Property::isOwned() const {
    return owner != -1;
}
