/*-
 * This file is part of Libight <https://libight.github.io/>.
 *
 * Libight is free software. See AUTHORS and LICENSE for more
 * information on the copying conditions.
 */

//
// Tests for src/common/async.cpp's
//

#define CATCH_CONFIG_MAIN
#include "src/ext/Catch/single_include/catch.hpp"

#include <ight/common/async.hpp>
#include <ight/common/log.hpp>
#include <ight/common/pointer.hpp>
#include <ight/common/settings.hpp>

#include <ight/ooni/dns_injection.hpp>
#include <ight/ooni/http_invalid_request_line.hpp>
#include <ight/ooni/tcp_connect.hpp>

#include <unistd.h>

using namespace ight::common::async;
using namespace ight::common::pointer;
using namespace ight::common;

using namespace ight::ooni::dns_injection;
using namespace ight::ooni::http_invalid_request_line;
using namespace ight::ooni::tcp_connect;

static void run_http_invalid_request_line(Async &async) {
    auto test = SharedPointer<HTTPInvalidRequestLine>(
        new HTTPInvalidRequestLine(Settings{
            {"backend", "http://nexa.polito.it/"},
        })
    );
    test->set_log_verbose(1);
    test->set_log_function([](const char *s) {
        (void) fprintf(stderr, "test #1: %s\n", s);
    });
    ight_debug("test created: %llu", test->identifier());
    async.run_test(test);
}

static void run_dns_injection(Async& async) {
    auto test = SharedPointer<DNSInjection>(
        new DNSInjection("test/fixtures/hosts.txt", Settings{
            {"nameserver", "8.8.8.8:53"},
        })
    );
    test->set_log_verbose(1);
    test->set_log_function([](const char *s) {
        (void) fprintf(stderr, "test #3: %s\n", s);
    });
    ight_debug("test created: %llu", test->identifier());
    async.run_test(test);
}

static void run_tcp_connect(Async& async) {
    auto test = SharedPointer<TCPConnect>(
        new TCPConnect("test/fixtures/hosts.txt", Settings{
            {"port", "80"},
        })
    );
    test->set_log_verbose(1);
    test->set_log_function([](const char *s) {
        (void) fprintf(stderr, "test #4: %s\n", s);
    });
    ight_debug("test created: %llu", test->identifier());
    async.run_test(test);
}

TEST_CASE("The async engine works as expected") {

    ight_set_verbose(1);
    Async async;

    // Note: the two following callbacks execute in a background thread
    volatile bool complete = false;
    async.on_complete([](SharedPointer<NetTest> test) {
        ight_debug("test complete: %llu", test->identifier());
    });
    async.on_empty([&complete]() {
        ight_debug("all tests completed");
        complete = true;
    });

    for (int i = 0; i < 4; ++i) {
        ight_debug("do another iteration of tests");
        complete = false;

        // Create tests in temporary void functions to also check that we can
        // create them in functions that later return in real apps
        run_dns_injection(async);
        run_http_invalid_request_line(async);
        run_http_invalid_request_line(async);
        run_tcp_connect(async);

        // TODO Maybe implement a better sync mechanism but for now polling will do
        while (!complete) {
            sleep(1);
        }
    }
}