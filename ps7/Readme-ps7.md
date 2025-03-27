# PS7: Kronos Log Parsing

## Contact

Name: Chris Lambert
Section: 203
Time to Complete: 4 hours

## Description

- The program partially works

This program parses Kronos InTouch time clock log files to analyze device startup times. It uses regular expressions to extract relevant information from the log files, such as startup messages and timestamps. The program identifies each device startup, determines whether it was successful, and calculates the elapsed time if applicable. The output is saved to a report file.

### Features

Instead of using regex to only identify the server startup lines i came up with more regex to isolate the date and time within
that line to ease string to date conversion using the posix libraries.

### Approach

I knew that if i were to allow the regex to do as much of the conversion as possible it would help simplify the program so I spend most of my time coming up with the regexs. After that I had the program construct each entry line by line before it writes to the log file

### Regex

startR: This regex matches the start of a device startup message.
DateTime: This regex captures the date and time from a timestamp in the log file.
stopR: This regex matches the stop event of a device startup.

### Issues

- N/A

### Extra Credit

- N/A

## Acknowledgements

I used a regex checker online to make sure all cases would match
