// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef MEASUREMENT_KIT_OONI_ERROR_HPP
#define MEASUREMENT_KIT_OONI_ERROR_HPP

#include <measurement_kit/common.hpp>

namespace mk {
namespace ooni {

MK_DEFINE_ERR(MK_ERR_OONI(0), CannotReadAnyInputFileError, "")
MK_DEFINE_ERR(MK_ERR_OONI(1), MissingRequiredInputFileError, "")
MK_DEFINE_ERR(MK_ERR_OONI(2), MissingCollectorBaseUrlError, "")
MK_DEFINE_ERR(MK_ERR_OONI(3), CannotOpenReportError, "")
MK_DEFINE_ERR(MK_ERR_OONI(4), MissingMandatoryKeyError, "")
MK_DEFINE_ERR(MK_ERR_OONI(5), InvalidMandatoryValueError, "")
MK_DEFINE_ERR(MK_ERR_OONI(6), MissingRequiredHostError, "")
MK_DEFINE_ERR(MK_ERR_OONI(7), MissingRequiredUrlError, "")
MK_DEFINE_ERR(MK_ERR_OONI(8), GeoipDatabaseOpenError, "")
MK_DEFINE_ERR(MK_ERR_OONI(9), GeoipCountryCodeLookupError, "")
MK_DEFINE_ERR(MK_ERR_OONI(10), GeoipCountryNameLookupError, "")
MK_DEFINE_ERR(MK_ERR_OONI(11), GeoipCityLookupError, "")
MK_DEFINE_ERR(MK_ERR_OONI(12), GeoipAsnLookupError, "")
MK_DEFINE_ERR(MK_ERR_OONI(13), CannotGetResourcesVersionError, "")
MK_DEFINE_ERR(MK_ERR_OONI(14), CannotGetResourcesManifestError, "")
MK_DEFINE_ERR(MK_ERR_OONI(15), CannotGetResourceError, "")
MK_DEFINE_ERR(MK_ERR_OONI(16), ResourceIntegrityError, "")
MK_DEFINE_ERR(MK_ERR_OONI(17), HttpRequestError, "")
MK_DEFINE_ERR(MK_ERR_OONI(18), RegexSearchError, "")

} // namespace mk
} // namespace ooni
#endif
