// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/ooni.hpp>
#include <measurement_kit/report.hpp>

namespace mk {
namespace report {

OoniReporter::OoniReporter(Settings s, Var<Reactor> r, Var<Logger> l) {
    settings = s;
    reactor = r;
    logger = l;
    if (settings.find("collector_base_url") == settings.end()) {
        // Note: by default we use the testing collector URL because otherwise
        // testing runs would be collected creating noise and using resources
        settings["collector_base_url"] =
            ooni::collector::testing_collector_url();
    }
    logger->info("Using collector: %s", settings["collector_base_url"].c_str());
}

/* static */ Var<BaseReporter> OoniReporter::make(Settings settings,
        Var<Reactor> reactor, Var<Logger> logger) {
    Var<OoniReporter> reporter(new OoniReporter(settings, reactor, logger));
    return reporter;
}

Continuation<Error> OoniReporter::open(Report &report) {
    return do_open_([=](Callback<Error> cb) {
        logger->info("Opening report...");
        ooni::collector::connect_and_create_report(
                report.get_dummy_entry(),
                [=](Error error, std::string rid) {
                    logger->info("Opening report... %d", error.code);
                    if (not error) {
                        logger->info("Report ID: %s", rid.c_str());
                        report_id = rid;
                    }
                    cb(error);
                },
                settings,
                reactor,
                logger);
    });
}

Continuation<Error> OoniReporter::write_entry(Entry entry) {

    // Register action for when we will be asked to write the entry
    return do_write_entry_(entry, [=](Callback<Error> cb) {
        if (report_id == "") {
            logger->warn("ooni_reporter: missing report ID");
            cb(MissingReportIdError());
            return;
        }
        logger->info("Submitting entry...");
        ooni::collector::connect_and_update_report(report_id, entry,
                                             [=](Error e) {
                                                 logger->info(
                                                     "Submitting entry... %d",
                                                     e.code);
                                                 cb(e);
                                             },
                                             settings,
                                             reactor,
                                             logger);
    });
}

Continuation<Error> OoniReporter::close() {
    return do_close_([=](Callback<Error> cb) {
        if (report_id == "") {
            logger->warn("ooni_reporter: missing report ID");
            cb(MissingReportIdError());
            return;
        }
        logger->info("Closing report...");
        ooni::collector::connect_and_close_report(report_id,
                                            [=](Error e) {
                                                logger->info(
                                                    "Closing report... %d",
                                                    e.code);
                                                cb(e);
                                            },
                                            settings,
                                            reactor,
                                            logger);
    });
}

std::string OoniReporter::get_report_id() {
    return report_id;
}

} // namespace report
} // namespace mk