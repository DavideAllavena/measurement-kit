// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#ifdef ENABLE_INTEGRATION_TESTS
#define CATCH_CONFIG_MAIN
#include "src/libmeasurement_kit/ext/catch.hpp"

#include "utils.hpp"

using namespace mk::nettests;
using namespace mk;

TEST_CASE("Synchronous meek-fronted-requests test") {
    test::nettests::with_test<MeekFrontedRequestsTest>(
          "meek_fronted_requests.txt", test::nettests::run_test);
}

#else
int main() {}
#endif
