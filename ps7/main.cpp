// Copyright 2024 Chris Lambert
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using boost::gregorian::date;
using boost::gregorian::date_duration;
using boost::gregorian::date_period;
using boost::gregorian::from_simple_string;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::time_from_string;

using std::cerr, std::endl;
using std::ifstream, std::ofstream;
using std::regex, std::regex_search, std::smatch;
using std::to_string;

using std::string;

int main(int argc, char* argv[]) {
  string filename = argv[1];

  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return 0;
  }

  ofstream report(filename + ".rpt");
  if (!report.is_open()) {
    cerr << "Error creating report file." << endl;
    return 0;
  }
  report << "Device Boot Report" << endl;
  regex startR(R"(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}(\.\d{1,3})?:\s\(log\.c\.166\) [A-Za-z]+\s[A-Za-z]+)");
  regex DateTime(R"((\d{4}-\d{2}-\d{2}) (\d{2}:\d{2}:\d{2}))");
  regex stopR(R"(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}(\.\d{1,3})?:[A-Za-z]+:oejs\.AbstractConnector:Started\s[A-Za-z]+@0\.0\.0\.0:9080)");

  int lineNumber = 0;
  string line;

  bool startup = false;
  bool stop_found = false;

  string entry;
  ptime p1, p2;
  while (getline(file, line)) {
    ++lineNumber;
    smatch match;

    if (std::regex_search(line, match, startR)) {
      if (!startup) {
        entry = to_string(lineNumber) + " ";
        smatch dt;
        regex_search(line, dt, DateTime);
        string date = dt[0];
        p1 = time_from_string(date);
        entry += date;
        report << entry;
        startup = true;
      } else {
        entry = " failure";
        report << entry << endl;
        startup = false;
      }

    } else if (regex_search(line, match, stopR)) {
      if (startup) {
        entry += " success ";
        report << entry << endl;
        entry.clear();
        // add the stop entry
        entry = to_string(lineNumber) + " ";
        smatch dt;
        regex_search(line, dt, DateTime);
        string date = dt[0];
        entry += dt[0];
        entry += " stopped";
        report << entry << endl;
        entry.clear();

        // calculate the elapsed time
        p2 = time_from_string(date);

        time_duration td = p2 - p1;

        entry += "Time elapsed: " + to_string(td.total_milliseconds()) + "ms";

        report << entry << endl;

        startup = false;
        stop_found = true;
      }
    }

    if (stop_found) {
      startup = false;
      stop_found = false;
    }
    entry.clear();
  }

  file.close();
  report.close();

  return 0;
}
